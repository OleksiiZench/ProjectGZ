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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animations") bool Is_Crawling;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animations") float Velocity;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animations") bool Is_Falling;
};
//------------------------------------------------------------------------------------------------------------
