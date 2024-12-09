// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CellularAutomata.h"
#include "MarchingSquares.generated.h"

class ACellularAutomata;


UCLASS()
class GP_UEASSIGNMENT_API AMarchingSquares : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMarchingSquares();

	// variables

	ACellularAutomata* m_CA;
	
	//functions
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
