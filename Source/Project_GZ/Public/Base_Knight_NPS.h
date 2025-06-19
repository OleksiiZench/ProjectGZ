#pragma once

#include "Blueprint/UserWidget.h"
#include "Components/SphereComponent.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/Character.h"
#include "CoreMinimal.h"
#include "Kismet/GameplayStatics.h"

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

	UFUNCTION() void On_Begin_Overlap(AActor *overlapped_actor, AActor *other_actor);
	UFUNCTION() void On_End_Overlap(AActor *overlapped_actor, AActor *other_actor);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Widgets") UWidgetComponent *Can_Interact_Widget_Component;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Widgets") TSubclassOf<UUserWidget> Can_Interact_Widget_Class;
	UPROPERTY(VisibleAnywhere, Category = "Components") USphereComponent *Sphere_Component;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue") UDataTable *Dialogue_Table;

private:
	bool Is_Overlaping;
	bool Was_Previously_Overlapping;
	ACharacter *Main_Character;
};
//------------------------------------------------------------------------------------------------------------
