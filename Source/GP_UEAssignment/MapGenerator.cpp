// Fill out your copyright notice in the Description page of Project Settings.


#include "MapGenerator.h"

// Sets default values
AMapGenerator::AMapGenerator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AMapGenerator::BeginPlay()
{
	Super::BeginPlay();

	GenerateGrid();
	IterateGrid();
	FinaliseGrid();

	GetRegionsAndEdges();
	
	MarchSquares();
}

void AMapGenerator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// cellular automata

void AMapGenerator::GenerateGrid()
{
	grid.SetNum(width);

	for (TArray<int>& currentRow : grid)
	{
		currentRow.SetNum(height);
	}

	tempNewGrid.SetNum(width);

	for (TArray<int>& currentRow : tempNewGrid)
	{
		currentRow.SetNum(height);
	}

	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			grid[i][j] = FMath::RandRange(0, 100) > density ? 0 : 1;
		}
	}
}

void AMapGenerator::IterateGrid()
{
	for (int k = 0; k < iterations; k++)
	{
		for (int i = 0; i < width; i++)
		{
			for (int j = 0; j < height; j++)
			{
				int neighbouringWalls = GetNeighbouringWallCount(i, j);

				tempNewGrid[i][j] = neighbouringWalls > 4 ? 1 : 0;
			}
		}

		for (int i = 0; i < width; i++)
		{
			for (int j = 0; j < height; j++)
			{
				grid[i][j] = tempNewGrid[i][j];
			}
		}
	}
}

int AMapGenerator::GetNeighbouringWallCount(int x, int y)
{
	int neighbouringWalls = 0;

	for (int neighbourX = x - 1; neighbourX <= x + 1; neighbourX++)
	{
		for (int neighbourY = y - 1; neighbourY <= y + 1; neighbourY++)
		{
			if (neighbourX >= 0 && neighbourX < width && neighbourY >= 0 && neighbourY < height)
			{
				if (neighbourX != 0 || neighbourY != 0)
				{
					neighbouringWalls += grid[neighbourX][neighbourY];
				}
			}
		}
	}
	
	return neighbouringWalls;
}

void AMapGenerator::FinaliseGrid()
{
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			if (i == 0 || j == 0 || i == width - 1 || j == height - 1)
			{
				grid[i][j] = 1;
			}
		}
	}
}

// regions + edges

void AMapGenerator::GetRegionsAndEdges()
{
	TArray<TArray<FVector2D>> regions = GetMapRegions();

	TArray<TArray<FVector2D>> regionsToRemove;

	for (TArray<FVector2D> region : regions)
	{
		if (region.Num() < 35)
		{
			for (int i = 0; i < region.Num(); i++)
			{
				grid[region[i].X][region[i].Y] = 1;
			}

			region.Empty();
			regionsToRemove.Add(region);
		}
	}

	for (int i = 0; i < regionsToRemove.Num(); i++)
	{
		regions.Remove(regionsToRemove[i]);
	}

	TArray<TArray<FVector2D>> edges = GetMapEdges(regions);

	if (regions.Num() > 1)
	{
		FindConnectingRooms(edges);
		FinaliseGrid();
	}

	corridorIterations++;

	if (regions.Num() > 1)
	{
		regions.Empty();
		edges.Empty();

		if (corridorIterations <= 3)
		{
			GetRegionsAndEdges();
		}
	}
}

TArray<TArray<FVector2D>> AMapGenerator::GetMapRegions()
{
	TArray<TArray<FVector2D>> mapRegions;
	TArray<TArray<int>> tilesChecked;	

	tilesChecked.SetNum(width);
	for (TArray<int>& currentRow : tilesChecked)
	{
		currentRow.SetNum(height);
	}

	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			if (tilesChecked[i][j] == 0 && grid[i][j] == 0)
			{
				TArray<FVector2D> region = GetRegion(i, j);
				mapRegions.Add(region);

				for (FVector2D tile : region)
				{
					tilesChecked[tile.X][tile.Y] = 1;
				}
			}
			else
			{
				tilesChecked[i][j] = 1;
			}
		}
	}
	
	UE_LOG(LogTemp, Warning, TEXT("Total Region Count : %d"), mapRegions.Num());	

	return mapRegions;
}

TArray<FVector2D> AMapGenerator::GetRegion(int x, int y)
{
	TArray<FVector2D> tiles;
	TArray<TArray<int>> tilesChecked;	

	tilesChecked.SetNum(width);
	for (TArray<int>& currentRow : tilesChecked)
	{
		currentRow.SetNum(height);
	}
	
	TQueue<FVector2D> tilesToCheck;
	tilesToCheck.Enqueue(FVector2D(x, y));
	tilesChecked[x][y] = 1;

	while (!tilesToCheck.IsEmpty())
	{
		FVector2D tile;
		tilesToCheck.Dequeue(tile);
		
		tiles.Add(tile);

		for (int i = tile.X - 1; i <= tile.X + 1; i++)
		{
			for (int j = tile.Y - 1; j <= tile.Y + 1; j++)
			{
				if (i >= 0 && i < width && j >= 0 && j < height && (i == tile.X || j == tile.Y))
				{
					if (tilesChecked[i][j] == 0 && grid[i][j] == 0)
					{
						tilesChecked[i][j] = 1;
						tilesToCheck.Enqueue(FVector2D(i, j));
					}
					else
					{
						tilesChecked[i][j] = 1;
					}
				}
			}
		}
	}

	UE_LOG(LogTemp, Warning, TEXT("Region Count : %d"), tiles.Num());
	
	return tiles;
}

TArray<TArray<FVector2D>> AMapGenerator::GetMapEdges(TArray<TArray<FVector2D>> regions)
{
	TArray<TArray<FVector2D>> edgeRegions;

	for (TArray<FVector2D> region : regions)
	{
		TArray<FVector2D> edges = GetRegionEdge(region);
		edgeRegions.Add(edges);
	}

	return edgeRegions;
}

TArray<FVector2D> AMapGenerator::GetRegionEdge(TArray<FVector2D> region)
{
	TArray<FVector2D> roomTiles = region;
	TArray<FVector2D> edgeTiles;

	for (FVector2D tile : roomTiles)
	{
		for (int i = tile.X - 1; i <= tile.X + 1; i++)
		{
			for (int j = tile.Y - 1; j <= tile.Y + 1; j++)
			{
				if ((i == tile.X || j == tile.Y) && grid[i][j] == 1)
				{
					edgeTiles.Add(tile);
				}
			}
		}
	}

	return edgeTiles;
}

// find corridors + connect

void AMapGenerator::FindConnectingRooms(TArray<TArray<FVector2D>> edges)
{
	bool connectionFound = false;
	int shortestDistance = 0;

	FVector2D bestA, bestB;

	for (TArray<FVector2D> regionA : edges)
	{
		connectionFound = false;

		for (TArray<FVector2D> regionB : edges)
		{
			if (regionA == regionB)
			{
				continue;
			}

			for (int i = 0; i < regionA.Num(); i++)
			{
				for (int j = 0; j < regionB.Num(); j++)
				{
					FVector2D a = regionA[i];
					FVector2D b = regionB[j];

					if (!regionA.Contains(b) && !regionB.Contains(a))
					{
						int distanceBetweenPoints = FMath::Pow(a.X - b.X, 2) + FMath::Pow(a.Y - b.Y, 2);

						if (distanceBetweenPoints < shortestDistance || !connectionFound)
						{
							connectionFound = true;
							shortestDistance = distanceBetweenPoints;

							bestA = a;
							bestB = b;
						}
					}
				}
			}
		}

		if (connectionFound)
		{
			if (bestA.X < bestB.X)
			{
				ConnectRooms(bestA, bestB);
			}
			else if (bestA.X > bestB.X)
			{
				ConnectRooms(bestB, bestA);
			}
			else
			{
				if (bestA.Y <= bestB.Y)
				{
					ConnectRooms(bestA, bestB);
				}
				else
				{
					ConnectRooms(bestB, bestA);
				}
			}
		}
	}
}

void AMapGenerator::ConnectRooms(FVector2D startCoord, FVector2D endCoord)
{
	float dx = endCoord.X - startCoord.X;
	float dy = endCoord.Y - startCoord.Y;

	float gradientOfLine = dy / dx;
	float c = endCoord.Y - (gradientOfLine * endCoord.X);

	if (startCoord.X == endCoord.X)
	{
		for (int i = startCoord.Y; i <= endCoord.Y; i++)
		{
			grid[startCoord.X][i] = 0;
		}
	}
	else if (startCoord.Y == endCoord.Y)
	{
		for (int i = startCoord.X; i <= endCoord.X; i++)
		{
			grid[i][startCoord.Y] = 0;
		}
	}
	else
	{
		for (int i = startCoord.X; i <= endCoord.X; i++)
		{
			int x = i;
			float y = (gradientOfLine * x) + c;

			y = FMath::RoundToInt(y);

			if (!isnan(y))
			{
				grid[x][y] = 0;
				grid[x + 1][y] = 0;
				grid[x - 1][y] = 0;

				if (gradientOfLine >= 1.01)
				{
					grid[x][y + 1] = 0;
					grid[x][y - 1] = 0;
					grid[x - 1][y - 1] = 0;
					grid[x - 1][y + 1] = 0;
					grid[x + 1][y - 1] = 0;
					grid[x + 1][y + 1] = 0;
				}
			}
		}
	}
}

void AMapGenerator::MarchSquares()
{
	for (int i = 0; i < (width - 1); i++)
	{
		for (int j = 0; j < (height - 1); j++)
		{
			float a = grid[i][j];
			float b = grid[i + 1][j];
			float c = grid[i + 1][j + 1];
			float d = grid[i][j + 1];

			CreateTriangles(GetHeight(a), GetHeight(b), GetHeight(c), GetHeight(d), i, j);
		}
	}
}

int AMapGenerator::GetHeight(float value)
{
	return value < 0.5f ? 0 : 1;
}

void AMapGenerator::CreateTriangles(int a, int b, int c, int d, int offsetX, int offsetY)
{
	int total = (a * 8) + (b * 4) + (c * 2) + (d * 1);

	//UE_LOG(LogTemp, Warning, TEXT("Case: "), total);
	InstantiateGrid(total, FVector2D(offsetX, offsetY));
}