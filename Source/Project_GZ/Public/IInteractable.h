#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "IInteractable.generated.h"

// UInteractable
//------------------------------------------------------------------------------------------------------------
UINTERFACE(MinimalAPI)
class UInteractable : public UInterface
{
	GENERATED_BODY()
};
//------------------------------------------------------------------------------------------------------------




// IInteractable
//------------------------------------------------------------------------------------------------------------
class PROJECT_GZ_API IInteractable
{
	GENERATED_BODY()

public:
	virtual void Interact() = 0;
};
//------------------------------------------------------------------------------------------------------------
