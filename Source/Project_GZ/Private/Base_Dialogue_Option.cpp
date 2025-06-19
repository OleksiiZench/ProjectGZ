#include "Base_Dialogue_Option.h"

//------------------------------------------------------------------------------------------------------------
void UBase_Dialogue_Option::Setup_Option(const FString &option_text, int32 node_id, UDialogue_Widget *parent_widget)
{
	if (Option_Text)
		Option_Text->SetText(FText::FromString(option_text) );

	Next_Node_ID = node_id;
	Parent_Dialogue_Widget = parent_widget;

	if (Option_Button)
		Option_Button->OnClicked.AddDynamic(this, &UBase_Dialogue_Option::On_Button_Clicked);
}
//------------------------------------------------------------------------------------------------------------
void UBase_Dialogue_Option::On_Button_Clicked()
{
	if (Parent_Dialogue_Widget)
		Parent_Dialogue_Widget->Select_Option(Next_Node_ID);
}
//------------------------------------------------------------------------------------------------------------
