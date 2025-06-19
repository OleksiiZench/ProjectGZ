#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"

#include "Dialogue_Structs.generated.h"

// FDialogue_Option
//------------------------------------------------------------------------------------------------------------
USTRUCT(BlueprintType)
struct FDialogue_Option
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 Next_Node_ID;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) FText Option_Text;
};
//------------------------------------------------------------------------------------------------------------




// FDialogue_Node
//------------------------------------------------------------------------------------------------------------
USTRUCT(BlueprintType)
struct FDialogue_Node : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite) bool bIs_Conditional;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 Node_ID;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) FText Speaker_Name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) FText Dialogue_Text;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) TArray<FDialogue_Option> Options;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditConditoin = "bIs_Conditional") ) FName Condition_Tag;
};
//------------------------------------------------------------------------------------------------------------
