#pragma once

#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
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

	virtual void SetupPlayerInputComponent(UInputComponent *PlayerInputComponent) override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components") UCameraComponent *Camera_Component;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animations") UAnimationAsset* Walk_Animation;

private:
	void Open_Menu();
	void Move_Forward(float amount);
	void Move_Right(float value);
	void Look_X(float value);
	void Look_Y(float value);
};
//------------------------------------------------------------------------------------------------------------
