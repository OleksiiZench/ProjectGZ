#pragma once

#include "Blueprint/UserWidget.h"
#include "GameFramework/Character.h"
#include "CoreMinimal.h"

#include "Base_NPC.h"
//#include "Dialogue_Manager.h" //перенесено до Base_Knight_NPS.h
#include "IInteractable.h"

#include "Base_Knight_NPS.generated.h"

//------------------------------------------------------------------------------------------------------------
UCLASS()
class PROJECT_GZ_API ABase_Knight_NPS : public ABase_NPC, public IInteractable
{
	GENERATED_BODY()

public:
	ABase_Knight_NPS();

	virtual void BeginPlay() override;
	virtual void Tick(float Delta_Time) override;

	virtual void Interact() override;

	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue") UDataTable *Dialogue_Table;

private:
	bool Is_Overlaping;
	bool Was_Previously_Overlapping;
};
//------------------------------------------------------------------------------------------------------------
