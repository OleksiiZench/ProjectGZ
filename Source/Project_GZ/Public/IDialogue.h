#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "IDialogue.generated.h"

//------------------------------------------------------------------------------------------------------------
UINTERFACE(MinimalAPI)
class UDialogue : public UInterface
{
	GENERATED_BODY()
};
//------------------------------------------------------------------------------------------------------------




// IDialogue
//------------------------------------------------------------------------------------------------------------
class PROJECT_GZ_API IDialogue
{
	GENERATED_BODY()

public:
	virtual void Func_In_Speak_Zone(bool is_speak_zone) = 0;
};
//------------------------------------------------------------------------------------------------------------
