#include "Base_Anim_Main_Character.h"
#include "Base_Main_Character.h"

//------------------------------------------------------------------------------------------------------------
void UBase_Anim_Main_Character::NativeUpdateAnimation(float Delta_Seconds)
{
	Super::NativeUpdateAnimation(Delta_Seconds);

	FVector velocity_vector;
	FVector move_direction_global;

	// 1. Отримання Velocity та Direction для BlandSpaces
	if (!Main_Character)
	{
		Main_Character = Cast<ABase_Main_Character>(TryGetPawnOwner());
		
		if (!Main_Character)
			return;
	}

	velocity_vector = Main_Character->GetVelocity();
	Velocity = velocity_vector.Size();

	move_direction_global = velocity_vector.GetSafeNormal();
	Move_Direction_Local = Main_Character->GetActorTransform().InverseTransformVector(move_direction_global);

	if (Move_Direction_Local.X < 0)
	{// Якщо персонаж рухається назад, то швидкість від'ємна
		Velocity *= -1;
	}

	// 2. Перевірка чи персонаж в присяді
	if ((Main_Character->GetCapsuleComponent()->GetScaledCapsuleHalfHeight() ) < 80.0f)
		Is_Crawling = true;
	else
		Is_Crawling = false;
}
//------------------------------------------------------------------------------------------------------------
