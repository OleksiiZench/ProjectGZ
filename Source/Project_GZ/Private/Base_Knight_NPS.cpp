#include "Base_Knight_NPS.h"

//------------------------------------------------------------------------------------------------------------
ABase_Knight_NPS::ABase_Knight_NPS()
{
	PrimaryActorTick.bCanEverTick = true;

	// 1. Init Dialogue_Camera	
	Dialogue_Camera = nullptr;
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

