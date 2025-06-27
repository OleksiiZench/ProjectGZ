#include "Base_Main_Character.h"
#include "Base_NPC.h"
#include "Base_Player_Controller.h"

//------------------------------------------------------------------------------------------------------------
ABase_Main_Character::ABase_Main_Character()
{
	PrimaryActorTick.bCanEverTick = true;

	Camera_Component = CreateDefaultSubobject<UCameraComponent>("Camera_Component");
	Camera_Component->SetupAttachment(GetMesh(), TEXT("Head_Socket") );
	Camera_Component->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f) );
	Camera_Component->bUsePawnControlRotation = true;
	Camera_Component->bConstrainAspectRatio = false;

	Walk_Speed = 500.0f;
	Crouch_Speed = 300.0f;
	Sprint_Speed = 700.0f;
	GetCharacterMovement()->MaxWalkSpeed = Walk_Speed;
	GetCharacterMovement()->MaxWalkSpeedCrouched = Crouch_Speed;
	GetCharacterMovement()->CrouchedHalfHeight = 30.0f;

	Max_Stamina = 100.0f; // 100 одиниць ~ 5 секунд
	Stamina_Drain_Rate = 20.0f;
	Current_Stamina = Max_Stamina;

	PC = Cast<ABase_Player_Controller>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

	Pause_Menu_Class = nullptr;
}
//------------------------------------------------------------------------------------------------------------
void ABase_Main_Character::BeginPlay()
{
	Super::BeginPlay();

	UUserWidget *crosshair = nullptr;
	TArray<AActor*> found_actors;

	// 1. Додаємо точку по центру екрану
	if (Crosshair_Widget_Class)
	{
		crosshair = CreateWidget<UUserWidget>(GetWorld(), Crosshair_Widget_Class);
		if (crosshair)
			crosshair->AddToViewport();
	}

	// 2. Отримуємо Character_Movement_Component
	Character_Movement_Component = GetCharacterMovement();

	// 3. Отримуємо перший знайдений ABase_Dialogue_Camera на сцені для встановлення дефолтної камери
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABase_Dialogue_Camera::StaticClass(), found_actors);

	if (found_actors.Num() > 0)
		Default_Dialogue_Camera = Cast<ABase_Dialogue_Camera>(found_actors[0]);
}
//------------------------------------------------------------------------------------------------------------
void ABase_Main_Character::Tick(float Delta_Time)
{
	FVector velocity_vector;
	FVector move_direction_global;

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

	// 2. Отримання Velocity та Direction для BlandSpaces
	velocity_vector = GetVelocity();
	Character_Velocity = velocity_vector.Size();

	move_direction_global = velocity_vector.GetSafeNormal();
	Move_Direction_Local = GetActorTransform().InverseTransformVector(move_direction_global);

	if (Move_Direction_Local.X < 0)
	{// Якщо персонаж рухається назад, то швидкість від'ємна (передивитися цю реалізацію, бо є певні баги з Move_Direction_Local)
		Character_Velocity *= -1;
	}

	// 3. Щоб в присяді під об'єктом коректно працювало обмеження камери
	if (Wants_To_Uncrouch && !GetCharacterMovement()->IsCrouching() )
	{
		Wants_To_Uncrouch = false;

		Is_Crawling = false;

		if (PC)
			PC->Set_View_Pitch();
	}
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
void ABase_Main_Character::Restore_After_Dialogue()
{
	Camera_Component->Activate();
	Character_Movement_Component->Activate();
	bUseControllerRotationYaw = true;

	FRotator desired_rotation = GetActorRotation();
	Controller->SetControlRotation(desired_rotation);
}
//------------------------------------------------------------------------------------------------------------
void ABase_Main_Character::Open_Menu()
{
	if (!Pause_Menu_Class)
		return;

	Pause_Menu_Instance = CreateWidget<UUserWidget>(GetWorld(), Pause_Menu_Class);
	Base_Pause_Menu = Cast<UBase_Pause_Menu>(Pause_Menu_Instance);
	Base_Pause_Menu->Pause_Game(Pause_Menu_Instance, GetWorld(), Crosshair_Widget_Class);
}
//------------------------------------------------------------------------------------------------------------
void ABase_Main_Character::Interact_With()
{
	FVector start;
	FVector end;
	FHitResult hit;
	FCollisionQueryParams params;
	AActor *actor = nullptr;
	ACharacter *character_npc;
	
	start = Camera_Component->GetComponentLocation();
	end = start + (Camera_Component->GetForwardVector() * 200.0f);

	params.AddIgnoredActor(this);

	if (GetWorld()->LineTraceSingleByChannel(hit, start, end, ECC_Visibility, params) )
	{
		actor = hit.GetActor();
		if (IInteractable *interactable = Cast<IInteractable>(actor) )
		{
			character_npc = Cast<ACharacter>(actor);
			if (character_npc)
			{// Якщо actor - це Character, то анімація не потрібна
				if (PC)
				{
					ABase_NPC *npc = Cast<ABase_NPC>(character_npc);

					ABase_Dialogue_Camera *target_camera;
					if (npc && npc->Dialogue_Camera)
					{// Якщо існує камера в npc, то ставимо камеру npc, якщо ні, то дефолтну
						target_camera = npc->Dialogue_Camera;
					}
					else
						target_camera = Default_Dialogue_Camera;

					PC->SetViewTargetWithBlend(target_camera, 1.0f, EViewTargetBlendFunction::VTBlend_Linear);
				}

				Camera_Component->Deactivate();
				Character_Movement_Component->Deactivate();
				Controller->SetControlRotation(FRotator::ZeroRotator);
				bUseControllerRotationYaw = false;

				// Механіка розміщення MC (Main Character) перед NPC
				if (character_npc)
				{
					FVector npc_location = character_npc->GetActorLocation();
					FVector npc_forward = character_npc->GetActorForwardVector();

					// Визначаємо точку перед NPC де буде розміщуватися MC
					float dictance_from_npc = 200.0f;
					FVector target_location = npc_location + (npc_forward * dictance_from_npc);

					// Для уникнення провалення
					target_location.Z = GetActorLocation().Z;

					SetActorLocation(target_location);

					// Повертаємо MC до NPC
					FVector direction_to_npc = (npc_location - target_location).GetSafeNormal();
					FRotator target_rotation = direction_to_npc.Rotation();
					target_rotation.Pitch = 0.0f;
					target_rotation.Roll = 0.0f;
					SetActorRotation(target_rotation);

					Target_Rotation = target_rotation;
				}
			}
			else
			{
				if (Interact_Montage && !GetMesh()->GetAnimInstance()->Montage_IsPlaying(Interact_Montage) )
				{// Програємо анім монтаж при взаємодії
					GetMesh()->GetAnimInstance()->Montage_Play(Interact_Montage, 1.0f);
				}
			}

			interactable->Interact();
		}
	}
}
//------------------------------------------------------------------------------------------------------------
void ABase_Main_Character::Start_Sprint()
{
	if (!(Is_Crawling) && Character_Velocity >= 0.0f)
		GetCharacterMovement()->MaxWalkSpeed = Sprint_Speed;

}
//------------------------------------------------------------------------------------------------------------
void ABase_Main_Character::Stop_Sprint()
{
	if (!(Is_Crawling) )
		GetCharacterMovement()->MaxWalkSpeed = Walk_Speed;
}
//------------------------------------------------------------------------------------------------------------
void ABase_Main_Character::Start_Crouch()
{
	Crouch();
	Is_Crawling = true;

	PC->Set_View_Pitch();  // Встановлюємо обмеження для камери
}
//------------------------------------------------------------------------------------------------------------
void ABase_Main_Character::Stop_Crouch()
{
	UnCrouch();
	Wants_To_Uncrouch = true;  // Див. в Tick() в 3 пункті
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
