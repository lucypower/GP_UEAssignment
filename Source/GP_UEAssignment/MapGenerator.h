// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MapGenerator.generated.h"


UCLASS()
class GP_UEASSIGNMENT_API AMapGenerator : public AActor
{
	GENERATED_BODY()
	
public:	
	AMapGenerator();

	// variables
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CellularAutomata")
	int height = 0;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CellularAutomata")
	int width = 0;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CellularAutomata")
	int iterations = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CellularAutomata")
	float density = 0.0f;

	TArray<TArray<int>> grid, tempNewGrid;

	int corridorIterations = 0;
	
	// functions

	// cellular automata
	
	void GenerateGrid();

	void IterateGrid();

	int GetNeighbouringWallCount(int x, int y);

	// find regions + edges

	void GetRegionsAndEdges();

	TArray<TArray<FVector2D>> GetMapRegions();

	TArray<FVector2D> GetRegion(int x, int y);

	TArray<TArray<FVector2D>> GetMapEdges(TArray<TArray<FVector2D>> regions);
	
	TArray<FVector2D> GetRegionEdge(TArray<FVector2D> region);
	
	// create corridors

	void FindConnectingRooms(TArray<TArray<FVector2D>> edges);

	void ConnectRooms(FVector2D startCoord, FVector2D endCoord);
	
	// final
	
	void FinaliseGrid();

	// march squares

	void MarchSquares();

	int GetHeight(float value);

	void CreateTriangles(int a, int b, int c, int d, int offsetX, int offsetY);

	UFUNCTION(BlueprintImplementableEvent)
	void InstantiateGrid(const int total, const FVector2D location);
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
