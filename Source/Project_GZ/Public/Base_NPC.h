#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "Base_Dialogue_Camera.h"

#include "Base_NPC.generated.h"

UCLASS(Abstract)
class PROJECT_GZ_API ABase_NPC : public ACharacter
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue") ABase_Dialogue_Camera *Dialogue_Camera;
};
