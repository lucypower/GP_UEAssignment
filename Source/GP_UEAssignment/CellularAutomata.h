// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CellularAutomata.generated.h"

class AMarchingSquares;

UCLASS()
class GP_UEASSIGNMENT_API ACellularAutomata : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACellularAutomata();

	AMarchingSquares* m_MS;
	
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
	TSubclassOf<AActor> m_blackCube;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CellularAutomata Cube")
	TSubclassOf<AActor> m_whiteCube;

	static int m_gHeight;
	static int m_gWidth;
	static TArray<TArray<int>> m_gGrid;

	TArray<int> m_gridWidth;
	TArray<int> m_gridHeight;
	
	// Functions
	
	UFUNCTION(BlueprintCallable)
	void GenerateGrid();

	UFUNCTION(BlueprintCallable)
	void IterateGrid();

	UFUNCTION(BlueprintCallable)
	void InstantiateGrid();
	
	UFUNCTION(BlueprintCallable)
	int GetNeighbouringWallCount(int x, int y);

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
