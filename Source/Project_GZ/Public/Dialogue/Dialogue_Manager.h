#pragma once

#include "CoreMinimal.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/NoExportTypes.h"

#include "MC/Base_Main_Character.h"
#include "Dialogue/Dialogue_Structs.h"
#include "Dialogue/Dialogue_Widget.h"

#include "Dialogue_Manager.generated.h"

//------------------------------------------------------------------------------------------------------------
UCLASS(Blueprintable)
class PROJECT_GZ_API UDialogue_Manager : public UObject
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable) void Start_Dialogue(ABase_NPC *npc, UDataTable *dialogue_table);
	UFUNCTION(BlueprintCallable) void Advance_Dialogue(int32 next_node_id);
	UFUNCTION(BlueprintCallable) void End_Dialogue();

	UPROPERTY(EditAnywhere, Category = "Dialogue") TSubclassOf<UDialogue_Widget> Dialogue_Widget_Class;

private:
	void Show_Dialogue_Node(int32 node_id);

	UPROPERTY() UDialogue_Widget *Dialogue_Widget;
	UPROPERTY() UDataTable *Current_Dialogue_Table;
	UPROPERTY() ABase_NPC *Current_NPC;
};
//------------------------------------------------------------------------------------------------------------
