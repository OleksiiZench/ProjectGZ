#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

#include "Base_Dialogue_Camera.h"
#include "Dialogue_Manager.h"

#include "Base_NPC.generated.h"

//------------------------------------------------------------------------------------------------------------
UCLASS(Abstract)
class PROJECT_GZ_API ABase_NPC : public ACharacter
{
	GENERATED_BODY()

public:
	ABase_NPC();

	virtual void BeginPlay() override;

	UFUNCTION() void On_Begin_Overlap(AActor *overlapped_actor, AActor *other_actor);
	UFUNCTION() void On_End_Overlap(AActor *overlapped_actor, AActor *other_actor);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue") ABase_Dialogue_Camera *Dialogue_Camera;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Widgets") UWidgetComponent *Can_Interact_Widget_Component;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Widgets") TSubclassOf<UUserWidget> Can_Interact_Widget_Class;
	UPROPERTY(VisibleAnywhere, Category = "Components") USphereComponent *Sphere_Component;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue") UDataTable *Dialogue_Table;

private:
	ACharacter *Main_Character;
};
//------------------------------------------------------------------------------------------------------------
