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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animations") bool Is_Crawling;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animations") float Velocity;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animations") bool Is_Falling;

private:
	ABase_Main_Character *Main_Character;
};
//------------------------------------------------------------------------------------------------------------
