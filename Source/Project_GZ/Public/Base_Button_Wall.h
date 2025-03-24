#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "IInteractable.h"

#include "Base_Button_Wall.generated.h"

//------------------------------------------------------------------------------------------------------------
UCLASS()
class PROJECT_GZ_API ABase_Button_Wall : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:	
	ABase_Button_Wall();

	virtual void Interact() override;
};
//------------------------------------------------------------------------------------------------------------
