#include "Base_Main_Character.h"

//------------------------------------------------------------------------------------------------------------
ABase_Main_Character::ABase_Main_Character()
{
	PrimaryActorTick.bCanEverTick = true;
	
	Camera_Component = CreateDefaultSubobject<UCameraComponent>("Camera_Component");
	Camera_Component->SetupAttachment(GetCapsuleComponent() );
	Camera_Component->SetRelativeLocation(FVector(13.0f, 0.0f, 75.0f) );
	Camera_Component->bUsePawnControlRotation = true;

	Walk_Speed = 500.0f;
	Crouch_Speed = 300.0f;
	Sprint_Speed = 700.0f;
	GetCharacterMovement()->MaxWalkSpeed = Walk_Speed;

	Max_Stamina = 100.0f; // 100 одиниць ~ 5 секунд
	Stamina_Drain_Rate = 20.0f;
	Current_Stamina = Max_Stamina;

	Pause_Menu_Class = nullptr;
}
//------------------------------------------------------------------------------------------------------------
void ABase_Main_Character::BeginPlay()
{
	Super::BeginPlay();

	UUserWidget *Crosshair = nullptr;

	Anim_Main_Character = Cast<UBase_Anim_Main_Character>(GetMesh()->GetAnimInstance());
	if (!Anim_Main_Character)
		UE_LOG(LogTemp, Error, TEXT("Anim_Main_Character == nullptr! Переконайтеся, що BP_AnimInstance встановлений у Skeletal Mesh.") );

	if (Crosshair_Widget_Class)
	{// Додаємо точку по центру екрану
		Crosshair = CreateWidget<UUserWidget>(GetWorld(), Crosshair_Widget_Class);
		if (Crosshair)
			Crosshair->AddToViewport();
	}
}
//------------------------------------------------------------------------------------------------------------
void ABase_Main_Character::Tick(float Delta_Time)
{
	Super::Tick(Delta_Time);

	// 1. Реалізація стаміни
	if (GetCharacterMovement()->MaxWalkSpeed == Sprint_Speed)
	{
		Current_Stamina -= Stamina_Drain_Rate * Delta_Time;

		if (Current_Stamina <= 0.0f)
		{
			Current_Stamina = 0.0f;
			Stop_Sprint();
		}
	}
	else  // Якщо не біжимо, то стаміна відновлюється
		Current_Stamina = FMath::Min(Current_Stamina + (Stamina_Drain_Rate * 0.5f * Delta_Time), Max_Stamina);
}
//------------------------------------------------------------------------------------------------------------
void ABase_Main_Character::SetupPlayerInputComponent(UInputComponent *Player_Input_Component)
{
	Super::SetupPlayerInputComponent(Player_Input_Component);

	Player_Input_Component->BindAction("Escape", IE_Pressed, this, &ABase_Main_Character::Open_Menu);

	Player_Input_Component->BindAction("Press_F", IE_Pressed, this, &ABase_Main_Character::Interact_With);

	Player_Input_Component->BindAction("Sprint", IE_Pressed, this, &ABase_Main_Character::Start_Sprint);
	Player_Input_Component->BindAction("Sprint", IE_Released, this, &ABase_Main_Character::Stop_Sprint);

	Player_Input_Component->BindAction("Crouch", IE_Pressed, this, &ABase_Main_Character::Start_Crouch);
	Player_Input_Component->BindAction("Crouch", IE_Released, this, &ABase_Main_Character::Stop_Crouch);
	
	Player_Input_Component->BindAxis("Move_Forward", this, &ABase_Main_Character::Move_Forward);
	Player_Input_Component->BindAxis("Move_Right", this, &ABase_Main_Character::Move_Right);

	Player_Input_Component->BindAxis("Look_X", this, &ABase_Main_Character::Look_X);
	Player_Input_Component->BindAxis("Look_Y", this, &ABase_Main_Character::Look_Y);
}
//------------------------------------------------------------------------------------------------------------
void ABase_Main_Character::Open_Menu()
{
	if (!Pause_Menu_Class)
		return;

	Pause_Menu_Instance = CreateWidget<UUserWidget>(GetWorld(), Pause_Menu_Class);
	Base_Pause_Menu = Cast<UBase_Pause_Menu>(Pause_Menu_Instance);
	Base_Pause_Menu->Pause_Game(Pause_Menu_Instance, GetWorld());
}
//------------------------------------------------------------------------------------------------------------
void ABase_Main_Character::Interact_With()
{
	FVector start;
	FVector end;
	FHitResult hit;
	FCollisionQueryParams params;

	AActor *actor = nullptr;
	
	start = Camera_Component->GetComponentLocation();
	end = start + (Camera_Component->GetForwardVector() * 200.0f);

	params.AddIgnoredActor(this);

	if (GetWorld()->LineTraceSingleByChannel(hit, start, end, ECC_Visibility, params) )
	{
		actor = hit.GetActor();
		if (IInteractable *interactable = Cast<IInteractable>(actor ) )
			interactable->Interact();
	}
}
//------------------------------------------------------------------------------------------------------------
void ABase_Main_Character::Start_Sprint()
{
	if (!(Anim_Main_Character->Is_Crawling) )
		GetCharacterMovement()->MaxWalkSpeed = Sprint_Speed;
}
//------------------------------------------------------------------------------------------------------------
void ABase_Main_Character::Stop_Sprint()
{
	GetCharacterMovement()->MaxWalkSpeed = Walk_Speed;
}
//------------------------------------------------------------------------------------------------------------
void ABase_Main_Character::Start_Crouch()
{
	Camera_Component->SetRelativeLocation(FVector(40.0f, 0.0f, 20.0f) );
	GetCapsuleComponent()->SetCapsuleHalfHeight(50.0f);  // Висота капсули під час присяду
	GetCharacterMovement()->MaxWalkSpeed = Crouch_Speed;
}
//------------------------------------------------------------------------------------------------------------
void ABase_Main_Character::Stop_Crouch()
{
	Camera_Component->SetRelativeLocation(FVector(20.0f, 0.0f, 85.0f) );
	GetCapsuleComponent()->SetCapsuleHalfHeight(88.0f);  // Висота капсули в нормальному положенні
	GetCharacterMovement()->MaxWalkSpeed = Walk_Speed;
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
