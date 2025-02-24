#include "Base_Anim_Main_Character.h"

//------------------------------------------------------------------------------------------------------------
void UBase_Anim_Main_Character::NativeInitializeAnimation()
{
	OwnerPawn = TryGetPawnOwner();
}
//------------------------------------------------------------------------------------------------------------
void UBase_Anim_Main_Character::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	
	//Velocity = OwnerPawn->GetVelocity().Size();
}
//------------------------------------------------------------------------------------------------------------
