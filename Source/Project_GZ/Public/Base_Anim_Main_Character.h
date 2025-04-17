#pragma once

#include "Animation/AnimInstance.h"
#include "CoreMinimal.h"

#include "Base_Anim_Main_Character.generated.h"

class ABase_Main_Character;

//------------------------------------------------------------------------------------------------------------
UCLASS()
class PROJECT_GZ_API UBase_Anim_Main_Character : public UAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeUpdateAnimation(float Delta_Seconds) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animations") bool Is_Falling;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animations") float Velocity;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animations") FVector Move_Direction_Local;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character") ABase_Main_Character *Main_Character;
};
//------------------------------------------------------------------------------------------------------------
