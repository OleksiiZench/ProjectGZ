#include "Base_Main_Character.h"

//------------------------------------------------------------------------------------------------------------
ABase_Main_Character::ABase_Main_Character()
{
	PrimaryActorTick.bCanEverTick = true;

	Camera_Component = CreateDefaultSubobject<UCameraComponent>("Camera_Component");
	Camera_Component->SetupAttachment(GetRootComponent() );
}
//------------------------------------------------------------------------------------------------------------
