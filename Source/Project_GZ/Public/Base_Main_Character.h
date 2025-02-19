#pragma once

#include "Camera/CameraComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "Base_Main_Character.generated.h"

//------------------------------------------------------------------------------------------------------------
UCLASS()
class PROJECT_GZ_API ABase_Main_Character : public ACharacter
{
	GENERATED_BODY()

public:
	ABase_Main_Character();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components") UCameraComponent *Camera_Component;

private:
	UCapsuleComponent *Capsule_Component = nullptr;
};
//------------------------------------------------------------------------------------------------------------
