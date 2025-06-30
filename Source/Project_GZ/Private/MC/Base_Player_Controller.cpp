#include "MC/Base_Player_Controller.h"

//------------------------------------------------------------------------------------------------------------
void ABase_Player_Controller::BeginPlay()
{
	Super::BeginPlay();

	Main_Character = Cast<ABase_Main_Character>(GetPawn() );
}
//------------------------------------------------------------------------------------------------------------
void ABase_Player_Controller::Tick(float Delta_Time)
{
	Super::Tick(Delta_Time);
}
//------------------------------------------------------------------------------------------------------------
void ABase_Player_Controller::Set_View_Pitch()
{
	if (Main_Character->Is_Crawling && PlayerCameraManager)
	{
		PlayerCameraManager->ViewPitchMin = -89.0f;
		PlayerCameraManager->ViewPitchMax = 42.0f;
	}
	else if ((!Main_Character->Is_Crawling) && PlayerCameraManager)
	{
		PlayerCameraManager->ViewPitchMin = -89.0f;
		PlayerCameraManager->ViewPitchMax = 89.0f;
	}
}
//------------------------------------------------------------------------------------------------------------
