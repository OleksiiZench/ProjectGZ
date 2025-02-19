#include "Base_Main_Character.h"

//------------------------------------------------------------------------------------------------------------
ABase_Main_Character::ABase_Main_Character()
{
	PrimaryActorTick.bCanEverTick = true;

	Camera_Component = CreateDefaultSubobject<UCameraComponent>("Camera_Component");
	Camera_Component->SetupAttachment(GetRootComponent() );
}
//------------------------------------------------------------------------------------------------------------
void ABase_Main_Character::BeginPlay()
{
	Super::BeginPlay();
	
}
//------------------------------------------------------------------------------------------------------------
void ABase_Main_Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
//------------------------------------------------------------------------------------------------------------
void ABase_Main_Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}
//------------------------------------------------------------------------------------------------------------
