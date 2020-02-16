#include "Sound_Manager_Game.h"
#include"SE/Sound_2D_Gun_1.h"
#include"BGM/Sound_BGM_Manager.h"
C_Sound_Manager_Game::C_Sound_Manager_Game()
{
	/*New_Sound_2D(new C_Sound_2D_Gun_1());

	C_Sound_BGM_Manager BGM_Manager;

	for (int i = 1; i <= BGM_Manager.Get_BGM_Num();i++) {
		New_Sound_2D(BGM_Manager.Get_BGM(&i));
	}*/
}

//bool C_Sound_Manager_Game::Set_Sound(const S_SOUND_DATA * Data)
//{
//	bool Flg = true;
//
//	if (Data->SoundType == Co_Sound_Type_2D) {
//		if (Data->CategoryNo == Co_Sound_Category_Bullet) {
//			New_Sound_2D(new C_Sound_2D_Gun_1());
//			M_Sound_2D_Manager[M_Sound_2D_Manager.size() - 1]->Update(&Flg);
//			return true;
//		}
//	}
//
//	if (Set_Sound_2D(Data) == true)return true;
//
//	return false;
//}
