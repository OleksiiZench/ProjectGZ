#include "Base_Starting_Location_Game_Mode.h"

//------------------------------------------------------------------------------------------------------------
ABase_Starting_Location_Game_Mode::ABase_Starting_Location_Game_Mode()
{
	DefaultPawnClass = ABase_Main_Character::StaticClass();
	PlayerControllerClass = ABase_Player_Controller::StaticClass();
}
//------------------------------------------------------------------------------------------------------------
