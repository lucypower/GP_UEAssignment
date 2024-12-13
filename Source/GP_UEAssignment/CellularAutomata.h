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
	
	int m_height = 0;
	int m_width = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CellularAutomata Cube")
	TSubclassOf<AActor> m_blackCube;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CellularAutomata Cube")
	TSubclassOf<AActor> m_whiteCube;
	
	// Functions
	
	UFUNCTION(BlueprintCallable)
	void GenerateGrid(int width, int height, float density);

	UFUNCTION(BlueprintCallable)
	void IterateGrid(int iterations);

	UFUNCTION(BlueprintCallable)
	void InstantiateGrid();
		
	int GetNeighbouringWallCount(int x, int y);

	TArray<TArray<int>> FinaliseGrid();
	
// 
	
	UFUNCTION(BlueprintCallable)
	void MarchSquares();

	UFUNCTION(BlueprintCallable)
	int GetHeight(float value);

	UFUNCTION(BlueprintCallable)
	void CreateTriangles(int a, int b, int c, int d, int offsetX, int offsetY);

	UFUNCTION(BlueprintImplementableEvent)
	void SpawnCaseActors(const int total, const FVector2D location);
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
