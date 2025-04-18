#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"

#include "Base_Main_Character.h"

#include "Base_Player_Controller.generated.h"

//------------------------------------------------------------------------------------------------------------
UCLASS()
class PROJECT_GZ_API ABase_Player_Controller : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	virtual void Tick(float Delta_Time) override;

	void Set_View_Pitch();

private:
	ABase_Main_Character *Main_Character;
};
//------------------------------------------------------------------------------------------------------------
