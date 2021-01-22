using UnrealBuildTool;
using System.IO;
using System;

public class Boost : ModuleRules
{
	private string ProjectRoot
    {
        get
        {
            return Path.GetFullPath(Path.Combine(ModuleDirectory, "../../"));
        }
    }

    private string ThirdPartyPath
    {
         get
         {
            return Path.GetFullPath(Path.Combine(ModuleDirectory, ProjectRoot, "ThirdParty"));
         }
    }
	
	public Boost(ReadOnlyTargetRules Target) : base(Target)
	{
		// We are just setting up paths for pre-compiled binaries.
		Type = ModuleType.External;

		// For boost::
		bEnableUndefinedIdentifierWarnings = false;
		bUseRTTI = true;

		var lib_list = new string[]
        {
            "boost"
        };
		foreach (var lib in lib_list)
        {
            PublicIncludePaths.Add(Path.Combine(ThirdPartyPath, lib, "include"));

            var lib_folder = new DirectoryInfo(Path.Combine(ThirdPartyPath, lib, "lib"));
            if (lib_folder.Exists) {
                foreach (var lib_file in lib_folder.GetFiles("*.so"))
                {
                    PublicAdditionalLibraries.Add(lib_file.FullName);
                    RuntimeDependencies.Add(lib_file.FullName);
                    Console.WriteLine("Add " + lib_file.FullName);
                }
                foreach (var lib_file in lib_folder.GetFiles("*.a"))
                {
                    PublicAdditionalLibraries.Add(lib_file.FullName);
                    Console.WriteLine("Add " + lib_file.FullName);
                }
            }
        }
	}
}
