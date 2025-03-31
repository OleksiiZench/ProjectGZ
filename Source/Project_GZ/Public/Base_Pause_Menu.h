#pragma once

#include "Blueprint/UserWidget.h"
#include "CoreMinimal.h"
#include "Kismet/GameplayStatics.h"

#include "Base_Pause_Menu.generated.h"

//------------------------------------------------------------------------------------------------------------
UCLASS()
class PROJECT_GZ_API UBase_Pause_Menu : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "UI") void Close_Pause_Menu();

	virtual FReply NativeOnKeyDown(const FGeometry& My_Geometry, const FKeyEvent& In_Key_Event) override;
	void Pause_Game(UUserWidget *pause_menu_instance, UWorld* world, TSubclassOf<UUserWidget> crosshair_widget_class);

	UPROPERTY(EditDefaultsOnly, Category = "UI") TSubclassOf<UUserWidget> Crosshair_Widget_Class;
};
//------------------------------------------------------------------------------------------------------------
