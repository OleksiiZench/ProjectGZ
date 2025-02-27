#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"

#include "Base_Pause_Menu.generated.h"

//------------------------------------------------------------------------------------------------------------
UCLASS()
class PROJECT_GZ_API UBase_Pause_Menu : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual FReply NativeOnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;
};
//------------------------------------------------------------------------------------------------------------
