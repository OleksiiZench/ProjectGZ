﻿#include "Base_Pause_Menu.h"

//------------------------------------------------------------------------------------------------------------
void UBase_Pause_Menu::Close_Pause_Menu()
{
	APlayerController *player_controller;
	UUserWidget *crosshair = nullptr;

	GEngine->GameViewport->RemoveAllViewportWidgets();

	UGameplayStatics::SetGamePaused(GetWorld(), false);

	player_controller = GetWorld()->GetFirstPlayerController();

	if (player_controller)
	{
		player_controller->bShowMouseCursor = false;
		player_controller->SetInputMode(FInputModeGameOnly() );
	}

	if (Crosshair_Widget_Class)
	{// Додаємо точку по центру екрану
		crosshair = CreateWidget<UUserWidget>(GetWorld(), Crosshair_Widget_Class);
		if (crosshair)
			crosshair->AddToViewport();
	}
}
//------------------------------------------------------------------------------------------------------------
FReply UBase_Pause_Menu::NativeOnKeyDown(const FGeometry& My_Geometry, const FKeyEvent& In_Key_Event)
{

   if (In_Key_Event.GetKey() == EKeys::Escape)
   {
		Close_Pause_Menu();

      return FReply::Handled();
   }
   return FReply::Unhandled();
}
//------------------------------------------------------------------------------------------------------------
void UBase_Pause_Menu::Pause_Game(UUserWidget *pause_menu_instance, UWorld* world, TSubclassOf<UUserWidget> crosshair_widget_class)
{
	APlayerController *player_controller;

	Crosshair_Widget_Class = crosshair_widget_class;

	if (pause_menu_instance)
	{
		pause_menu_instance->AddToViewport();
		pause_menu_instance->SetIsFocusable(true);
	}

	UGameplayStatics::SetGamePaused(world, true);

	player_controller = world->GetFirstPlayerController();

	if (player_controller)
	{
		player_controller->bShowMouseCursor = true;
		player_controller->SetInputMode(FInputModeUIOnly() );
		pause_menu_instance->SetKeyboardFocus();
	}
}
//------------------------------------------------------------------------------------------------------------
