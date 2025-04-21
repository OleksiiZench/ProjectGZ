#include "Base_Anim_Main_Character.h"
#include "Base_Main_Character.h"

//------------------------------------------------------------------------------------------------------------
void UBase_Anim_Main_Character::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	if (!Main_Character)
		Main_Character = Cast<ABase_Main_Character>(TryGetPawnOwner());
}
//------------------------------------------------------------------------------------------------------------
