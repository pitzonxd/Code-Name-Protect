// Fill out your copyright notice in the Description page of Project Settings.


#include "Grid_CPP.h"

// Sets default values for this component's properties
UGrid_CPP::UGrid_CPP()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

}


// Called when the game starts
void UGrid_CPP::BeginPlay()
{
	Super::BeginPlay();

	
	
}


// Called every frame
void UGrid_CPP::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UGrid_CPP::SetColsAndRows(int cols, int rows)
{
}
