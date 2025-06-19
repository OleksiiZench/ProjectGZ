#include "Base_Knight_NPS.h"
#include "Dialogue_Manager.h"

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

	// 3. Init Dialogue_Camera	
	Dialogue_Camera = nullptr;
}
//------------------------------------------------------------------------------------------------------------
void ABase_Knight_NPS::BeginPlay()
{
	Super::BeginPlay();

	Main_Character = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

	OnActorBeginOverlap.AddDynamic(this, &ABase_Knight_NPS::On_Begin_Overlap);
	OnActorEndOverlap.AddDynamic(this, &ABase_Knight_NPS::On_End_Overlap);

	if (!Dialogue_Camera)
		UE_LOG(LogTemp, Warning, TEXT("Dialogue camera not set for %s"), *GetName() );
}
//------------------------------------------------------------------------------------------------------------
void ABase_Knight_NPS::Tick(float Delta_Time)
{
	Super::Tick(Delta_Time);
}
//------------------------------------------------------------------------------------------------------------
void ABase_Knight_NPS::Interact()
{
	UE_LOG(LogTemp, Warning, TEXT("Knight_NPS") );
	
	if (UWorld *world = GetWorld() )
	{
		UDialogue_Manager *dialogue_manager = NewObject<UDialogue_Manager>(world);
		if (dialogue_manager)
		{
			dialogue_manager->Dialogue_Widget_Class = LoadClass<UDialogue_Widget>(nullptr, TEXT("/Game/Dialogues/WBP_Dialogue.WBP_Dialogue_C") );
			dialogue_manager->Start_Dialogue(this, Dialogue_Table);
		}

		if (Can_Interact_Widget_Component)
			Can_Interact_Widget_Component->SetVisibility(false);
	}
}
//------------------------------------------------------------------------------------------------------------
void ABase_Knight_NPS::On_Begin_Overlap(AActor *overlapped_actor, AActor *other_actor)
{
	if(other_actor == Main_Character && Can_Interact_Widget_Component)
		Can_Interact_Widget_Component->SetVisibility(true);
}
//------------------------------------------------------------------------------------------------------------
void ABase_Knight_NPS::On_End_Overlap(AActor *overlapped_actor, AActor *other_actor)
{
	if(other_actor == Main_Character && Can_Interact_Widget_Component)
		Can_Interact_Widget_Component->SetVisibility(false);
}
//------------------------------------------------------------------------------------------------------------
