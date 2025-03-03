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
	virtual FReply NativeOnKeyDown(const FGeometry& My_Geometry, const FKeyEvent& In_Key_Event) override;
};
//------------------------------------------------------------------------------------------------------------
