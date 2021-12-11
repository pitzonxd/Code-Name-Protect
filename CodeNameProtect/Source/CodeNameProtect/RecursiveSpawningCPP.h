// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "RecursiveSpawningCPP.generated.h"


USTRUCT()
struct FPadStruct {
	GENERATED_BODY()

	UPROPERTY()
	bool uncovered;

	UPROPERTY()
	float X;

	UPROPERTY()
	float Y;

	UPROPERTY()
	float Z;

};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CODENAMEPROTECT_API URecursiveSpawningCPP : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	URecursiveSpawningCPP();

	UPROPERTY()
	int rows;
	
	UPROPERTY()
	int cols;

	UPROPERTY()
	TArray<FPadStruct> allPads;
	
	UPROPERTY()
	FVector realOrigin;

	UFUNCTION(BlueprintCallable)
	void initializeVariables(FVector pRealOrigin, int pRows, int pCols);

	UFUNCTION(BlueprintCallable)
	bool stepOn(FVector position);

	UFUNCTION(BlueprintCallable)
	TArray<FVector> uncoverTick();

	UFUNCTION(BlueprintCallable)
	FVector translateRowsAndColsToPosition(int pRow, int pCol);

	UFUNCTION(BlueprintCallable)
	FIntVector translatePositionToRowsAndCols(float X, float Y, float Z);

	UFUNCTION(BlueprintCallable)
	void reset();

	UFUNCTION(BlueprintCallable)
	bool isValidPosition(FVector pos);

	UFUNCTION(BlueprintCallable)
	FVector calculateOffset(FVector gridLocation);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};