#include "Base_Button_Wall.h"

//------------------------------------------------------------------------------------------------------------
ABase_Button_Wall::ABase_Button_Wall()
{
	PrimaryActorTick.bCanEverTick = true;
}
//------------------------------------------------------------------------------------------------------------
void ABase_Button_Wall::Interact()
{
	UE_LOG(LogTemp, Warning, TEXT("PASASI") );
}
//------------------------------------------------------------------------------------------------------------
