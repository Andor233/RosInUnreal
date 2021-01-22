// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Async/Async.h"
#include "GameFramework/Actor.h"
#include "RosActor.generated.h"

UCLASS()
class ROSUNREAL_API ARosActor : public AActor
{
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	ARosActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

    class Impl;
    Impl* pimpl;
};
