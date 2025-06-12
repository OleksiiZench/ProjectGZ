#pragma once

#include "Blueprint/UserWidget.h"
#include "Components/SphereComponent.h"
#include "Components/WidgetComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

#include "IInteractable.h"

#include "Base_Knight_NPS.generated.h"

//------------------------------------------------------------------------------------------------------------
UCLASS()
class PROJECT_GZ_API ABase_Knight_NPS : public ACharacter, public IInteractable
{
	GENERATED_BODY()

public:
	ABase_Knight_NPS();

	virtual void BeginPlay() override;
	virtual void Tick(float Delta_Time) override;

	virtual void Interact() override;

	UFUNCTION() void On_Begin_Overlap(AActor *overlapped_actor, AActor *other_actor);
	UFUNCTION() void On_End_Overlap(AActor *overlapped_actor, AActor *other_actor);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Widgets") UWidgetComponent* Can_Interact_Widget_Component;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Widgets") TSubclassOf<UUserWidget> Can_Interact_Widget_Class;
	UPROPERTY(VisibleAnywhere, Category = "Components") USphereComponent *Sphere_Component;

private:
	bool Is_Overlaping;
	bool Was_Previously_Overlapping;
	ACharacter *Main_Character;
};
//------------------------------------------------------------------------------------------------------------
