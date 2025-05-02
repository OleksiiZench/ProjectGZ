#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "IInteractable.h"

#include "Base_Knight_NPS.generated.h"

//------------------------------------------------------------------------------------------------------------
UCLASS()
class PROJECT_GZ_API ABase_Knight_NPS : public ACharacter, public IInteractable
{
	GENERATED_BODY()

public:
	ABase_Knight_NPS();

	virtual void Interact() override;
};
//------------------------------------------------------------------------------------------------------------
