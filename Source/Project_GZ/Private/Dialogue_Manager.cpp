#include "Dialogue_Manager.h"

//------------------------------------------------------------------------------------------------------------
void UDialogue_Manager::Start_Dialogue(ABase_NPC *npc, UDataTable *dialogue_table)
{
	if (!npc || !dialogue_table)
	{
		UE_LOG(LogTemp, Warning, TEXT("Invalid npc or dialogue_table!") );
		return;
	}

	Current_NPC = npc;
	Current_Dialogue_Table = dialogue_table;
	

	if (UWorld *world = npc->GetWorld() )
	{
		Dialogue_Widget = CreateWidget<UDialogue_Widget>(world, Dialogue_Widget_Class);
		if (Dialogue_Widget)
		{
			Dialogue_Widget->AddToViewport();
			
			if (APlayerController *pc = UGameplayStatics::GetPlayerController(GetWorld(), 0) )
			{// Налаштування введення
				FInputModeGameAndUI input_mode;
				input_mode.SetWidgetToFocus(Dialogue_Widget->TakeWidget() );
				input_mode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);

				pc->SetInputMode(input_mode);
				pc->bShowMouseCursor = true;
			}
			
			Dialogue_Widget->On_Option_Selected.AddDynamic(this, &UDialogue_Manager::Advance_Dialogue);
			Dialogue_Widget->On_Dialogue_Ended.AddDynamic(this, &UDialogue_Manager::End_Dialogue);
			Show_Dialogue_Node(0);
		}
	}
}
//------------------------------------------------------------------------------------------------------------
void UDialogue_Manager::Advance_Dialogue(int32 next_node_id)
{
	Show_Dialogue_Node(next_node_id);
}
//------------------------------------------------------------------------------------------------------------
void UDialogue_Manager::End_Dialogue()
{
	if (Dialogue_Widget)
	{
		Dialogue_Widget->RemoveFromParent();
		Dialogue_Widget = nullptr;
	}

	Current_NPC->Can_Interact_Widget_Component->SetVisibility(true);

	Current_NPC = nullptr;
	Current_Dialogue_Table = nullptr;

	if (APlayerController *pc = UGameplayStatics::GetPlayerController(GetWorld(), 0) )
	{// Повернення налаштування вводу до початкового
		pc->SetInputMode(FInputModeGameOnly() );
		pc->bShowMouseCursor = false;

		if (ABase_Main_Character *main_character = Cast<ABase_Main_Character>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0) ) )
		{
			main_character->Restore_After_Dialogue();
			pc->SetViewTargetWithBlend(main_character, 1.0f, EViewTargetBlendFunction::VTBlend_Cubic);
		}
	}
}
//------------------------------------------------------------------------------------------------------------
void UDialogue_Manager::Show_Dialogue_Node(int32 node_id)
{
	if (!Current_Dialogue_Table)
	{
		End_Dialogue();
		return;
	}

	FDialogue_Node *node = Current_Dialogue_Table->FindRow<FDialogue_Node>(*FString::FromInt(node_id), TEXT("Dialogue_Node") );
	if (node)
	{
		if (node->bIs_Conditional)
		{// (Опціонально) Перевірка умов	
			// Реалізуйте перевірку умов, наприклад, через теги або інвентар
			// Якщо умова не виконана, перейдіть до іншого вузла або завершіть діалог
		}

		Dialogue_Widget->Initialize_Dialogue(*node);
	}
	else
	{
		End_Dialogue();
	}
}
//------------------------------------------------------------------------------------------------------------
