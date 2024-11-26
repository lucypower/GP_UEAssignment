// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CellularAutomata.generated.h"

UCLASS()
class GP_UEASSIGNMENT_API ACellularAutomata : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACellularAutomata();

	TArray<TArray<int>> m_grid, m_tempNewGrid;	

	TArray<FVector> m_openSpaces; // TODO: idk if this is right
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CellularAutomata")
	int m_height = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CellularAutomata")
	int m_width = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CellularAutomata")
	int m_iterations = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CellularAutomata")
	float m_density = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CellularAutomata Cube")
	TSubclassOf<AActor> m_whiteCube;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CellularAutomata Cube")
	TSubclassOf<AActor> m_blackCube;
	
	// Functions
	
	UFUNCTION(BlueprintCallable)
	void GenerateGrid();

	UFUNCTION(BlueprintCallable)
	void IterateGrid();

	UFUNCTION(BlueprintCallable)
	void InstantiateGrid();
	
	UFUNCTION(BlueprintCallable)
	int GetNeighbouringWallCount(int x, int y);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
