#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "Base_NPC.h"
#include "IInteractable.h"

#include "Base_Temp_NPC.generated.h"

//------------------------------------------------------------------------------------------------------------
UCLASS()
class PROJECT_GZ_API ABase_Temp_NPC : public ABase_NPC, public IInteractable
{
	GENERATED_BODY()

public:
	virtual void Interact() override;
};
//------------------------------------------------------------------------------------------------------------
