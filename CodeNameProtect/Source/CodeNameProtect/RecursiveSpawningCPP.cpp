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
        }
    }
}

bool URecursiveSpawningCPP::stepOn(FVector position) {
    FIntVector pos = translatePositionToRowsAndCols(position.X, position.Y, position.Z);

    int tmp = pos.X * rows + pos.Y; 

    UE_LOG(LogTemp, Warning, TEXT("tmp, %d, %d"), pos.X, pos.Y);

    if(tmp >= 0 && tmp < 100 && position.X >= realOrigin.X && position.X <= (realOrigin.X + rows * 200) && position.Y >= realOrigin.Y && position.Y <= (realOrigin.Y + rows * 200)){
        allPads[pos.X * rows + pos.Y].uncovered = true;
        return true;
    }
    
    return false;
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

            if(!allPads[i * rows + j].uncovered) {
                if(i > 0 && allPads[(i-1) * rows + j].uncovered) {
                    FVector loc = translateRowsAndColsToPosition(i, j);
                    result.Add(loc);
                    changedPositions.Add(FIntVector(i, j, 0));
                }
                if(i < (rows-1) && allPads[(i+1) * rows + j].uncovered) {
                    FVector loc = translateRowsAndColsToPosition(i, j);
                    result.Add(loc);
                    changedPositions.Add(FIntVector(i, j, 0));
                }
                if(j > 0 && allPads[i * rows + (j-1)].uncovered) {
                    FVector loc = translateRowsAndColsToPosition(i, j);
                    result.Add(loc);
                    changedPositions.Add(FIntVector(i, j, 0));
                }
                if(j < (cols-1) && allPads[i * rows + (j+1)].uncovered) {
                    FVector loc = translateRowsAndColsToPosition(i, j);
                    result.Add(loc);
                    changedPositions.Add(FIntVector(i, j, 0));
                }
            }

        }
    }

    for(int k = 0; k < changedPositions.Num(); k++) {
        allPads[changedPositions[k].X * rows + changedPositions[k].Y].uncovered = true;
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
            allPads[i * rows + 1].uncovered = false;
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