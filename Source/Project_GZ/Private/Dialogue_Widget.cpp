#include "Dialogue_Widget.h"

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
			if (UUserWidget *option_widget = CreateWidget<UUserWidget>(this, Option_Widget_Class) )
			{
				if (UTextBlock *option_text_block = Cast<UTextBlock>(option_widget->GetWidgetFromName("Option_Text") ) ) // ???????
				{// Припускаємо, що WBP_DialogueOption має TextBlock з назвою OptionText
					option_text_block->SetText(option.Option_Text);
				}

				if (UButton *option_button = Cast<UButton>(option_widget->GetWidgetFromName("Option_Button") ) ) // ???????
				{// Прив'язуємо кнопку до вибору опції
					//option_button->OnClicked.AddDynamic(this, &UDialogue_Widget::Select_Option, option.Nex_Node_ID);
				}

				Options_Container->AddChild(option_widget);
			}
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
