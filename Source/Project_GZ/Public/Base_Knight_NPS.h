#pragma once

#include "Blueprint/UserWidget.h"
#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "Base_NPC.h"
#include "IInteractable.h"

#include "Base_Knight_NPS.generated.h"

//------------------------------------------------------------------------------------------------------------
UCLASS()
class PROJECT_GZ_API ABase_Knight_NPS : public ABase_NPC, public IInteractable
{
	GENERATED_BODY()

public:
	ABase_Knight_NPS();

	virtual void Interact() override;
};
//------------------------------------------------------------------------------------------------------------
