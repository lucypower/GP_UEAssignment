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
	
	UPROPERTY(BlueprintReadWrite, Category = "MarchingSquares")
	TArray<FVector> m_vertices;

	UPROPERTY(BlueprintReadWrite, Category = "MarchingSquares")
	TArray<int> m_triangles;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MS Cube")
	TArray<TSubclassOf<AActor>> m_actorToSpawn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MS Cube")
	TArray<UStaticMesh*> m_staticMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CellularAutomata Cube")
	TSubclassOf<AActor> m_blackCube;

	
	
	//functions
	
	UFUNCTION(BlueprintCallable)
	void MarchSquares();

	UFUNCTION(BlueprintCallable)
	int GetHeight(float value);

	UFUNCTION(BlueprintCallable)
	void CreateTriangles(int a, int b, int c, int d, int offsetX, int offsetY);

	UFUNCTION(BlueprintImplementableEvent)
	void CreateShape(const TArray<FVector2D>& vertices, const FVector2D& location);

	UFUNCTION(BlueprintImplementableEvent)
	void SpawnCaseActors(const int total, const FVector2D location);
	//void SpawnCaseActors(const int actorCase, const FVector2D location);


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
