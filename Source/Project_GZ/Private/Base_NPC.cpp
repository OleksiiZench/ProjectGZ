#include "Base_NPC.h"

//------------------------------------------------------------------------------------------------------------
ABase_NPC::ABase_NPC()
{
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
void ABase_NPC::BeginPlay()
{
	Super::BeginPlay();

	Main_Character = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

	Can_Interact_Widget_Component->SetVisibility(false);

	OnActorBeginOverlap.AddDynamic(this, &ABase_NPC::On_Begin_Overlap);
	OnActorEndOverlap.AddDynamic(this, &ABase_NPC::On_End_Overlap);
}
//------------------------------------------------------------------------------------------------------------
void ABase_NPC::Interact()
{
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
void ABase_NPC::On_Begin_Overlap(AActor *overlapped_actor, AActor *other_actor)
{
	if(other_actor == Main_Character && Can_Interact_Widget_Component)
		Can_Interact_Widget_Component->SetVisibility(true);
}
//------------------------------------------------------------------------------------------------------------
void ABase_NPC::On_End_Overlap(AActor *overlapped_actor, AActor *other_actor)
{
	if(other_actor == Main_Character && Can_Interact_Widget_Component)
		Can_Interact_Widget_Component->SetVisibility(false);
}
//------------------------------------------------------------------------------------------------------------
