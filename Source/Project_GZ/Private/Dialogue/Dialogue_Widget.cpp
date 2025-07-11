﻿#include "Dialogue/Dialogue_Widget.h"

#include "Dialogue/Base_Dialogue_Option.h"

//------------------------------------------------------------------------------------------------------------
void UDialogue_Widget::Initialize_Dialogue(const FDialogue_Node &node)
{
	if (Speaker_Name_Text)
		Speaker_Name_Text->SetText(node.Speaker_Name);

	if (Dialogue_Text)
		Dialogue_Text->SetText(node.Dialogue_Text);
		
	if (Options_Container)
	{
		Options_Container->ClearChildren();

		for (const FDialogue_Option &option : node.Options)
		{
			if (UBase_Dialogue_Option *option_widget = CreateWidget<UBase_Dialogue_Option>(this, Option_Widget_Class) )
			{
				option_widget->Setup_Option(option.Option_Text.ToString(), option.Next_Node_ID, this);

				Options_Container->AddChild(option_widget);
			}
		}

		if (Options_Container->GetChildrenCount() > 0)
		{
			if (UWidget *first_child = Options_Container->GetChildAt(0) )
				first_child->SetKeyboardFocus();
		}
	}
}
//------------------------------------------------------------------------------------------------------------
void UDialogue_Widget::Select_Option(int32 next_node_id)
{
	On_Option_Selected.Broadcast(next_node_id);
}
//------------------------------------------------------------------------------------------------------------
void UDialogue_Widget::End_Dialogue()
{
	On_Dialogue_Ended.Broadcast();
	RemoveFromParent();
}
//------------------------------------------------------------------------------------------------------------
