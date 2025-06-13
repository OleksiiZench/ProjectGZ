// Fill out your copyright notice in the Description page of Project Settings.


#include "Base_Temp_NPC.h"

// Sets default values
ABase_Temp_NPC::ABase_Temp_NPC()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABase_Temp_NPC::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABase_Temp_NPC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABase_Temp_NPC::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

