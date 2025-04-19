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
	virtual void NativeInitializeAnimation() override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character") ABase_Main_Character *Main_Character;
};
//------------------------------------------------------------------------------------------------------------
