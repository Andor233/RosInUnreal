// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.IO;
using System;

public class RosUnreal : ModuleRules
{
	public RosUnreal(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		CppStandard = CppStandardVersion.Latest;
        bUseRTTI = true;
        bEnableExceptions = true;
		PrivateDefinitions.AddRange(new string[] {"HAVE_EXECINFO_H=1", "HAVE_CXXABI_H=1","HAVE_GLIBC_BACKTRACE" });
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore" });

		PrivateDependencyModuleNames.AddRange(new string[] { "Boost" });

		var ros_folder = new DirectoryInfo(Path.Combine(ModuleDirectory, "ros"));
        if (ros_folder.Exists) {
            foreach (var component_folder in ros_folder.GetDirectories()){
                PrivateIncludePaths.Add(Path.Combine(component_folder.ToString(),"include"));
            }
        }
	}
}
