#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/WidgetComponent.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SphereComponent.h"

#include "IInteractable.h"

#include "Base_Knight_NPS.generated.h"

//------------------------------------------------------------------------------------------------------------
UCLASS()
class PROJECT_GZ_API ABase_Knight_NPS : public ACharacter, public IInteractable
{
	GENERATED_BODY()

public:
	ABase_Knight_NPS();

	virtual void Tick(float Delta_Time) override;

	virtual void Interact() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Widgets") UWidgetComponent* Can_Interact_Widget_Component;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Widgets") TSubclassOf<UUserWidget> Can_Interact_Widget_Class;
	UPROPERTY(VisibleAnywhere, Category = "Components") USphereComponent *Sphere_Component;

private:
	bool Is_Overlaping;
	ACharacter *Main_Character;
};
//------------------------------------------------------------------------------------------------------------
