// Fill out your copyright notice in the Description page of Project Settings.


#include "RecursiveSpawningCPP.h"


// Sets default values for this component's properties
URecursiveSpawningCPP::URecursiveSpawningCPP()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void URecursiveSpawningCPP::BeginPlay()
{
	Super::BeginPlay();

}


// Called every frame
void URecursiveSpawningCPP::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}


void URecursiveSpawningCPP::initializeVariables(FVector pRealOrigin, int pRows, int pCols) {
    this->rows = pRows;
    this->cols = pCols;
    this->realOrigin = pRealOrigin;

    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            FVector pos = translateRowsAndColsToPosition(i, j);

            FPadStruct addedStruct;
            addedStruct.uncovered = false;
            addedStruct.X = pos.X;
            addedStruct.Y = pos.Y;
            addedStruct.Z = pos.Z;

            allPads.Add(addedStruct);

            UE_LOG(LogTemp, Warning, TEXT("tmp, %d, %d"), i, j);
        }
    }

    UE_LOG(LogTemp, Warning, TEXT("tmp, %d"), allPads.Num());
}

bool URecursiveSpawningCPP::stepOn(FVector position) {
    FIntVector pos = translatePositionToRowsAndCols(position.X, position.Y, position.Z);

    int tmp = pos.X * cols + pos.Y; 
    
    allPads[pos.X * cols + pos.Y].uncovered = true;
    return true;

}

FVector URecursiveSpawningCPP::translateRowsAndColsToPosition(int pRow, int pCol) {
	
    float locX = realOrigin[0] + 200.0f * (float)pRow;
    float locY = realOrigin[1] + 200.0f * (float)pCol;

    FVector result(locX, locY, realOrigin[2]);

	return result;
}

FIntVector URecursiveSpawningCPP::translatePositionToRowsAndCols(float pX, float pY, float pZ) {
	
    int posX = (int)((pX - realOrigin[0])/200);
    int posY = (int)((pY - realOrigin[1])/200);

    FIntVector result(posX, posY, 0);

	return result;
}

TArray<FVector> URecursiveSpawningCPP::uncoverTick() { 
	TArray<FVector> result;
    TArray<FIntVector> changedPositions;

    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {

            if(!allPads[i * cols + j].uncovered) {
                if(i > 0 && allPads[(i-1) * cols + j].uncovered) {
                    FVector loc = translateRowsAndColsToPosition(i, j);
                    result.Add(loc);
                    changedPositions.Add(FIntVector(i, j, 0));
                }
                if(i < (rows-1) && allPads[(i+1) * cols + j].uncovered) {
                    FVector loc = translateRowsAndColsToPosition(i, j);
                    result.Add(loc);
                    changedPositions.Add(FIntVector(i, j, 0));
                }
                if(j > 0 && allPads[i * cols + (j-1)].uncovered) {
                    FVector loc = translateRowsAndColsToPosition(i, j);
                    result.Add(loc);
                    changedPositions.Add(FIntVector(i, j, 0));
                }
                if(j < (cols-1) && allPads[i * cols + (j+1)].uncovered) {
                    FVector loc = translateRowsAndColsToPosition(i, j);
                    result.Add(loc);
                    changedPositions.Add(FIntVector(i, j, 0));
                }
            }

        }
    }

    for(int k = 0; k < changedPositions.Num(); k++) {
        allPads[changedPositions[k].X * cols + changedPositions[k].Y].uncovered = true;
    }


    if(changedPositions.Num() == 0) {
        for(int i = 0; i < allPads.Num(); i++) {
            allPads[i].uncovered = false;
        }
    }

	return result;
}

void URecursiveSpawningCPP::reset() {
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            allPads[i * cols + 1].uncovered = false;
        }
    }
}

bool URecursiveSpawningCPP::isValidPosition(FVector pos) {

    FIntVector position = translatePositionToRowsAndCols(pos.X, pos.Y, pos.Z);

    if(position.X >= 0 && position.Y >= 0 && position.X < rows && position.Y < cols) {
        return true;
    }

    return false;

}

FVector URecursiveSpawningCPP::calculateOffset(FVector gridLocation) {

    float posX = (float)((int)gridLocation.X % 200) - 100.0;
    float posY = (float)((int)gridLocation.Y % 200) - 100.0;

    if(posX < 0) posX += 200.0;
    if(posY < 0) posY += 200.0; 

    if(this->rows % 2 != 0) posX += 100.0;
    if(this->cols % 2 != 0) posY += 100.0;

    return FVector(posX, posY, 0.0f);
}


TArray<FVector> URecursiveSpawningCPP::getAllSpawnFunctions(int pRows, int pCols, FVector pRealOrigin) {
    TArray<FVector> allTilePositions;;
    FVector tmpVector;

    for(int i = 0; i < pRows; i++) {
        for(int j = 0; j < pCols; j++) {
            tmpVector.X = float(i) * 200 + realOrigin.X;
            tmpVector.Y = float(j) * 200 + realOrigin.Y;
            tmpVector.Z = pRealOrigin.Z;

            allTilePositions.Add(tmpVector);
        }
    }

    return allTilePositions;
}