#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Dialogue_Widget.h"

#include "Base_Dialogue_Option.generated.h"

//------------------------------------------------------------------------------------------------------------
UCLASS()
class PROJECT_GZ_API UBase_Dialogue_Option : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable) void Setup_Option(const FString &option_text, int32 node_id, UDialogue_Widget *parent_widget);

protected:
	UFUNCTION() void On_Button_Clicked();

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget) ) UTextBlock *Option_Text;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget) ) UButton *Option_Button;

private:
	int32 Next_Node_ID;
	UDialogue_Widget *Parent_Dialogue_Widget;
};
//------------------------------------------------------------------------------------------------------------
