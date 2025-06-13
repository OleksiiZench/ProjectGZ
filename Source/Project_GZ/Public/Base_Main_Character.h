#pragma once

#include "Blueprint/UserWidget.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"

#include "Base_NPC.h"
#include "Base_Anim_Main_Character.h"
#include "Base_Dialogue_Camera.h"
#include "Base_Pause_Menu.h"
#include "IInteractable.h"

#include "Base_Main_Character.generated.h"

class ABase_Player_Controller;

//------------------------------------------------------------------------------------------------------------
UCLASS()
class PROJECT_GZ_API ABase_Main_Character : public ACharacter
{
	GENERATED_BODY()

public:
	ABase_Main_Character();

	virtual void BeginPlay() override;
	virtual void Tick(float Delta_Time) override;
	virtual void SetupPlayerInputComponent(UInputComponent *Player_Input_Component) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation") bool Is_Crawling;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement") float Walk_Speed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement") float Crouch_Speed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement") float Sprint_Speed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement") float Max_Stamina;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement") float Current_Stamina;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement") float Stamina_Drain_Rate;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement") float Character_Velocity;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement") FVector Move_Direction_Local;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation") UAnimMontage *Interact_Montage;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components") UCameraComponent *Camera_Component;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components") UCharacterMovementComponent *Character_Movement_Component;
	UPROPERTY(EditAnywhere, Category = "UI") TSubclassOf<UUserWidget> Pause_Menu_Class;
	UPROPERTY(EditDefaultsOnly, Category = "UI") TSubclassOf<UUserWidget> Crosshair_Widget_Class;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue") ABase_Dialogue_Camera *Default_Dialogue_Camera;

private:
	void Open_Menu();
	void Interact_With();
	void Start_Sprint();
	void Stop_Sprint();
	void Start_Crouch();
	void Stop_Crouch();
	void Move_Forward(float amount);
	void Move_Right(float value);
	void Look_X(float value);
	void Look_Y(float value);

	bool Wants_To_Uncrouch;
	ABase_Player_Controller *PC;
	UUserWidget *Pause_Menu_Instance;
	UBase_Pause_Menu *Base_Pause_Menu;
};
//------------------------------------------------------------------------------------------------------------
