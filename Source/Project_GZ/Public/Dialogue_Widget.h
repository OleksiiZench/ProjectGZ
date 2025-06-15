#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"
#include "Components/Button.h"

#include "Dialogue_Structs.h"

#include "Dialogue_Widget.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnOptionSelected, int32, Nex_Node_ID);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDialogueEnded);

//------------------------------------------------------------------------------------------------------------
UCLASS()
class PROJECT_GZ_API UDialogue_Widget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable) void Initialize_Dialogue(const FDialogue_Node &node);
	UFUNCTION(BlueprintCallable) void Select_Option(int32 next_node_id);
	
	UPROPERTY(BlueprintAssignable) FOnOptionSelected On_Option_Selected;
	UPROPERTY(BlueprintAssignable) FOnDialogueEnded On_Dialogue_Ended;

protected:
	UFUNCTION(BlueprintCallable) void End_Dialogue();

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget) ) UTextBlock *Speaker_Name_Text; 
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget) ) UTextBlock *Dialogue_Text;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget) ) UVerticalBox *Options_Container;
	UPROPERTY(EditAnywhere, Category = "Dialogue") TSubclassOf<UUserWidget> Option_Widget_Class;
};
//------------------------------------------------------------------------------------------------------------
