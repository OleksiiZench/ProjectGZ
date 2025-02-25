#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Base_Anim_Main_Character.generated.h"

//------------------------------------------------------------------------------------------------------------
UCLASS()
class PROJECT_GZ_API UBase_Anim_Main_Character : public UAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components") bool Is_Falling;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animations") float Velocity;
};
//------------------------------------------------------------------------------------------------------------
