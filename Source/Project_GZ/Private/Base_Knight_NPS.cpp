#include "Base_Knight_NPS.h"

//------------------------------------------------------------------------------------------------------------
ABase_Knight_NPS::ABase_Knight_NPS()
{
	PrimaryActorTick.bCanEverTick = true;
	//Was_Previously_Overlapping = false;

	// 1. Додаємо/Налаштовуємо компонент сфери
	Sphere_Component = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	Sphere_Component->SetupAttachment(RootComponent);
	Sphere_Component->SetWorldScale3D(FVector(8.0f));
		
	// 2. Приєднуємо компонент віджета для відрображення 'F' до сокета голови
	Can_Interact_Widget_Component = CreateDefaultSubobject<UWidgetComponent>(TEXT("Can_Interact_Widget") );

	if (GetMesh() )
		Can_Interact_Widget_Component->SetupAttachment(GetMesh(), TEXT("Head_Socket"));

	if (Can_Interact_Widget_Class)
		Can_Interact_Widget_Component->SetWidgetClass(Can_Interact_Widget_Class);

	Can_Interact_Widget_Component->SetDrawSize(FVector2D(200.0f, 50.0f));
}
//------------------------------------------------------------------------------------------------------------
void ABase_Knight_NPS::BeginPlay()
{
	Super::BeginPlay();

	Main_Character = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

	OnActorBeginOverlap.AddDynamic(this, &ABase_Knight_NPS::On_Begin_Overlap);
	OnActorEndOverlap.AddDynamic(this, &ABase_Knight_NPS::On_End_Overlap);
}
//------------------------------------------------------------------------------------------------------------
void ABase_Knight_NPS::Tick(float Delta_Time)
{
	Super::Tick(Delta_Time);

	//// 1. Реалізація надпису 'F' коли заходиш в зону актора (Knight_NPS)
	//if (Main_Character)
	//	Is_Overlaping = IsOverlappingActor(Main_Character);

	//if (Is_Overlaping != Was_Previously_Overlapping)
	//{
	//	Can_Interact_Widget_Component->SetVisibility(Is_Overlaping);
	//	Was_Previously_Overlapping = Is_Overlaping;
	//}
}
//------------------------------------------------------------------------------------------------------------
void ABase_Knight_NPS::Interact()
{
	UE_LOG(LogTemp, Warning, TEXT("Knight_NPS") );
}
//------------------------------------------------------------------------------------------------------------
void ABase_Knight_NPS::On_Begin_Overlap(AActor *overlapped_actor, AActor *other_actor)
{
	if(other_actor == Main_Character)
		Can_Interact_Widget_Component->SetVisibility(true);
}
//------------------------------------------------------------------------------------------------------------
void ABase_Knight_NPS::On_End_Overlap(AActor *overlapped_actor, AActor *other_actor)
{
	if(other_actor == Main_Character)
		Can_Interact_Widget_Component->SetVisibility(false);
}
//------------------------------------------------------------------------------------------------------------
