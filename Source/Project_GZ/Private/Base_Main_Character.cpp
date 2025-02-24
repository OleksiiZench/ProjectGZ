#include "Base_Main_Character.h"

//------------------------------------------------------------------------------------------------------------
ABase_Main_Character::ABase_Main_Character()
{
	PrimaryActorTick.bCanEverTick = true;
	
	Camera_Component = CreateDefaultSubobject<UCameraComponent>("Camera_Component");
	Camera_Component->SetupAttachment(GetCapsuleComponent() );
	Camera_Component->SetRelativeLocation(FVector(8.0f, 0.0f, 90.0f) );
	Camera_Component->bUsePawnControlRotation = true;
	
	GetCharacterMovement()->JumpZVelocity = 400.0;
 }
//---------------------------------------------------------------------------------------1---------------------
void ABase_Main_Character::SetupPlayerInputComponent(UInputComponent *PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Escape", IE_Pressed, this, &ABase_Main_Character::Open_Menu);

	PlayerInputComponent->BindAxis("Move_Forward", this, &ABase_Main_Character::Move_Forward);
	PlayerInputComponent->BindAxis("Move_Right", this, &ABase_Main_Character::Move_Right);

	PlayerInputComponent->BindAxis("Look_X", this, &ABase_Main_Character::Look_X);
	PlayerInputComponent->BindAxis("Look_Y", this, &ABase_Main_Character::Look_Y);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ABase_Main_Character::Jump);
}
//------------------------------------------------------------------------------------------------------------
void ABase_Main_Character::Open_Menu()
{
	UE_LOG(LogTemp, Warning, TEXT("Open Menu.") );
}
//------------------------------------------------------------------------------------------------------------
void ABase_Main_Character::Move_Forward(float value)
{
	AddMovementInput(GetActorForwardVector(), value);
}
//------------------------------------------------------------------------------------------------------------
void ABase_Main_Character::Move_Right(float value)
{
	AddMovementInput(GetActorRightVector(), value);
}
//------------------------------------------------------------------------------------------------------------
void ABase_Main_Character::Look_X(float value)
{
	AddControllerYawInput(value);
}
//------------------------------------------------------------------------------------------------------------
void ABase_Main_Character::Look_Y(float value)
{
	AddControllerPitchInput(value);
}
//------------------------------------------------------------------------------------------------------------
//void ABase_Main_Character::Jump()
//{
//}
//------------------------------------------------------------------------------------------------------------
