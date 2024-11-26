// Fill out your copyright notice in the Description page of Project Settings.


#include "MarchingSquares.h"

// Sets default values
AMarchingSquares::AMarchingSquares()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMarchingSquares::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMarchingSquares::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMarchingSquares::MarchSquares()
{
	for (int i = 0; i < m_CA->m_width - 1; i++)
	{
		for (int j = 0; j < m_CA->m_height; j++)
		{
			float a = m_CA->m_grid[i][j];
			float b = m_CA->m_grid[i + 1][j];
			float c = m_CA->m_grid[i + 1][j + 1];
			float d = m_CA->m_grid[i][j + 1];

			CreateTriangles(GetHeight(a), GetHeight(b), GetHeight(c), GetHeight(d), i, j);
		}
	}
}

int AMarchingSquares::GetHeight(float value)
{
	return value < 0.5f ? 0 : 1;
}

void AMarchingSquares::CreateTriangles(int a, int b, int c, int d, int offsetX, int offsetY)
{
	int total = (a * 8) + (b * 4) + (c * 2) + (d * 1);

	TArray<FVector> localVertices;
	TArray<int> localTriangles;

	int vertexCount = m_vertices.Num();

	switch (total)
	{
		case 0:
			return;

	case 1:
		
		localVertices = {FVector(0, 1, 0), FVector(0, 0.5f, 0), FVector(0.5f, 1, 0)};
		localTriangles = {2, 1, 0};

		break;

	case 2:
		
		localVertices = {FVector(1, 1, 0), FVector(1, 0.5f, 0), FVector(0.5f, 1, 0)};
		localTriangles = {0, 1, 2};

		break;

	case 3:
		
		localVertices = {FVector(0, 0.5f, 0), FVector(0, 1, 0), FVector(1, 1, 0), FVector(1, 0.5f, 0)};
		localTriangles = {0, 1, 2, 0, 2, 3};

		break;

	case 4:

		localVertices = {FVector(1, 0, 0), FVector(0.5f, 0, 0), FVector(1, 0.5f, 0)};
		localTriangles = {0, 1, 2};

		break;

	case 5:

		localVertices = {FVector(0, 0.5f, 0), FVector(0, 1, 0), FVector(0.5f, 1, 0), FVector(1, 0, 0), FVector(0.5f, 0, 0), FVector(1, 0.5f, 0)};
		localTriangles = {0, 1, 2, 3, 4, 5};

		break;

	case 6:

		localVertices = {FVector(0.5f, 0, 0), FVector(0.5f, 1, 0), FVector(1, 0, 0)};
		localTriangles = {0, 1, 2, 0, 2, 3};

		break;

	case 7:

		localVertices = {FVector(0, 1, 0), FVector(1, 1, 0), FVector(1, 0, 0), FVector(0.5f, 0, 0), FVector(0, 0.5f, 0)};
		localTriangles = {2, 3, 1, 3, 4, 1, 4, 0, 1};

		break;

	case 8:

		localVertices = {FVector(0, 0.5f, 0), FVector(0, 0, 0), FVector(0.5f, 0, 0)};
		localTriangles = {2, 1, 0};

		break;

	case 9:

		localVertices = {FVector(0, 0, 0), FVector(0.5f, 0, 0), FVector(0.5f, 1, 0), FVector(0, 1, 0)};
		localTriangles = {1, 0, 2, 0, 3, 2};

		break;

	case 10:

		localVertices = {FVector(0, 0, 0), FVector(0, 0.5f, 0), FVector(0.5, 0, 0), FVector(1, 1, 0), FVector(0.5f, 1, 0), FVector(1, 0.5f, 0)};
		localTriangles = {0, 1, 2, 5, 4, 3};

		break;

	case 11:

		localVertices = {FVector(0, 0, 0), FVector(0, 1, 0), FVector(1, 1, 0), FVector(1, 0.5f, 0), FVector(0.5f, 0, 0)};
		localTriangles = {0, 1, 2, 0, 2, 3, 4, 0, 3};

		break;

	case 12:

		localVertices = {FVector(0, 0, 0), FVector(1, 0, 0), FVector(1, 0.5f, 0), FVector(0, 0.5f, 0)};
		localTriangles = {0, 3, 2, 0, 2, 1};

		break;

	case 13:

		localVertices = {FVector(0, 0, 0), FVector(0, 1, 0), FVector(0.5f, 1, 0), FVector(1, 0.5f, 0), FVector(1, 0, 0)};
		localTriangles = {0, 1, 2, 0, 2, 3, 0, 3, 4};

		break;

	case 14:

		localVertices = {FVector(1, 1, 0), FVector(1, 0, 0), FVector(0, 0, 0), FVector(0, 0.5f, 0), FVector(0.5f, 1, 0)};
		localTriangles = {0, 1, 4, 1, 3, 4, 1, 2, 3};

		break;

	case 15:

		localVertices = {FVector(0, 0, 0), FVector(0, 1, 0), FVector(1, 1, 0), FVector(1, 0, 0)};
		localTriangles = {0, 1, 2, 0, 2, 3};

		break;
	}

	for (FVector v : localVertices)
	{
		FVector newV = FVector(v.X + (offsetX * 100), v.Y + (offsetY * 100), 50);
		m_vertices.Add(newV);
	}

	for (int t :localTriangles)
	{
		m_triangles.Add(t + vertexCount);
	}
}
