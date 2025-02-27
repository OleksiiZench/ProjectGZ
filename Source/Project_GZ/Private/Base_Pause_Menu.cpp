// Fill out your copyright notice in the Description page of Project Settings.


#include "Base_Pause_Menu.h"

FReply UBase_Pause_Menu::NativeOnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent)
{
	APlayerController *player_controller;

   if (InKeyEvent.GetKey() == EKeys::Escape)
   {
		GEngine->GameViewport->RemoveAllViewportWidgets();

		UGameplayStatics::SetGamePaused(GetWorld(), false);

		player_controller = GetWorld()->GetFirstPlayerController();
		if (player_controller)
		{
			player_controller->bShowMouseCursor = false;
			//EnableInput(GetWorld()->GetFirstPlayerController());
			player_controller->SetInputMode(FInputModeGameOnly() );
		}
      return FReply::Handled();
   }
   return FReply::Unhandled();
}
