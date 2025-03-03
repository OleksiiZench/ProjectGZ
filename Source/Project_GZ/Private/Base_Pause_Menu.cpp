#include "Base_Pause_Menu.h"

//------------------------------------------------------------------------------------------------------------
FReply UBase_Pause_Menu::NativeOnKeyDown(const FGeometry& My_Geometry, const FKeyEvent& In_Key_Event)
{
	APlayerController *player_controller;

   if (In_Key_Event.GetKey() == EKeys::Escape)
   {
		GEngine->GameViewport->RemoveAllViewportWidgets();

		UGameplayStatics::SetGamePaused(GetWorld(), false);

		player_controller = GetWorld()->GetFirstPlayerController();
		
		if (player_controller)
		{
			player_controller->bShowMouseCursor = false;
			player_controller->SetInputMode(FInputModeGameOnly() );
		}

      return FReply::Handled();
   }
   return FReply::Unhandled();
}
//------------------------------------------------------------------------------------------------------------
