#pragma once

#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "Base_Main_Character.generated.h"

//------------------------------------------------------------------------------------------------------------
UCLASS()
class PROJECT_GZ_API ABase_Main_Character : public ACharacter
{
	GENERATED_BODY()

public:
	ABase_Main_Character();

	virtual void SetupPlayerInputComponent(UInputComponent *PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement") float Walk_Speed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement") float Sprint_Speed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement") float Stamina_Time;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components") UCameraComponent *Camera_Component;

private:
	void Open_Menu();
	void Start_Sprint();
	void Stop_Sprint();
	void Move_Forward(float amount);
	void Move_Right(float value);
	void Look_X(float value);
	void Look_Y(float value);
};
//------------------------------------------------------------------------------------------------------------
