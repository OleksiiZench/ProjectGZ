#include "Base_Temp_NPC.h"

//------------------------------------------------------------------------------------------------------------
void ABase_Temp_NPC::Interact()
{
	UE_LOG(LogTemp, Warning, TEXT("Temp_NPC") );

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
