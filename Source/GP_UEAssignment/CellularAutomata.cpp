// Fill out your copyright notice in the Description page of Project Settings.


#include "CellularAutomata.h"

#include "MarchingSquares.h"

// Sets default values
ACellularAutomata::ACellularAutomata()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACellularAutomata::BeginPlay()
{
	Super::BeginPlay();

	GenerateGrid();

	for (int i = 0; i < m_iterations; i++)
	{
		IterateGrid();
	}

	for (int i = 0; i < m_width; i++)
	{
		for (int j = 0; j < m_height; j++)
		{
			if (i == 0 || j == 0 || i == m_width - 1 || j == m_height - 1)
			{
				m_grid[i][j] = 1;
			}
		}
	}

	m_MS->MarchSquares();
	
	//InstantiateGrid();
}

// Called every frame
void ACellularAutomata::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACellularAutomata::GenerateGrid()
{
	m_grid.SetNum(m_width);

	for (TArray<int>& currentRow : m_grid)
	{
		currentRow.SetNum(m_height);
	}

	m_tempNewGrid.SetNum(m_width);

	for (TArray<int>& currentRow : m_tempNewGrid)
	{
		currentRow.SetNum(m_height);
	}

	for (int i = 0; i < m_width; i++)
	{
		for (int j = 0; j < m_height; j++)
		{
			m_grid[i][j] = FMath::RandRange(0, 100) > m_density ? 0 : 1;
		}
	}
}

void ACellularAutomata::IterateGrid()
{
	for (int i = 0; i < m_width; i++)
	{
		for (int j = 0; j < m_height; j++)
		{
			int neighbouringWalls = GetNeighbouringWallCount(i, j);

			m_tempNewGrid[i][j] = neighbouringWalls > 4 ? 1 : 0;
		}
	}

	for (int i = 0; i < m_width; i++)
	{
		for (int j = 0; j < m_height; j++)
		{
			m_grid[i][j] = m_tempNewGrid[i][j];
		}
	}
}

int ACellularAutomata::GetNeighbouringWallCount(int x, int y)
{
	int neighbouringWalls = 0;

	for (int neighbourX = x - 1; neighbourX <= x + 1; neighbourX++)
	{
		for (int neighbourY = y - 1; neighbourY <= y + 1; neighbourY++)
		{
			if (neighbourX >= 0 && neighbourX < m_width && neighbourY >= 0 && neighbourY < m_height)
			{
				if (neighbourX != 0 || neighbourY != 0)
				{
					neighbouringWalls += m_grid[neighbourX][neighbourY];
				}
			}
		}
	}
	
	return neighbouringWalls;
}

void ACellularAutomata::InstantiateGrid()
{
	FActorSpawnParameters spawnParameters;

	for (int i = 0; i < m_width; i++)
	{
		for (int j = 0; j < m_height; j++)
		{
			if (m_grid[i][j] == 1)
			{
				GetWorld()->SpawnActor<AActor>(m_blackCube, FVector(i * 100, j * 100, 50), FRotator(0, 0, 0),  spawnParameters);
			}
			else
			{
				GetWorld()->SpawnActor<AActor>(m_whiteCube, FVector(i * 100, j * 100, 50), FRotator(0, 0, 0),  spawnParameters);
			}
		}
	}
}