#include "Base_Anim_Main_Character.h"
#include "Base_Main_Character.h"

//------------------------------------------------------------------------------------------------------------
void UBase_Anim_Main_Character::NativeUpdateAnimation(float Delta_Seconds)
{
	Super::NativeUpdateAnimation(Delta_Seconds);

	if (!Main_Character)
	{
		Main_Character = Cast<ABase_Main_Character>(TryGetPawnOwner());
		
		if (!Main_Character)
			return;
	}

	Velocity = Main_Character->GetVelocity().Size();

	if ((Main_Character->GetCapsuleComponent()->GetScaledCapsuleHalfHeight() ) < 80.0f)
		Is_Crawling = true;
	else
		Is_Crawling = false;
}
//------------------------------------------------------------------------------------------------------------
