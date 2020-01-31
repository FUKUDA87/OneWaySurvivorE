#include "E_101_Phase_0.h"
#include"ENo101_AiPhase_1.h"

C_E_No101_Phase_0::C_E_No101_Phase_0()
{
}

C_E_AiPhaseBase * C_E_No101_Phase_0::Action(const CHARABASE * Chara, std::vector<C_Car_Parts_Joint*> M_Car_Parts, std::vector<C_GunLaser*> M_Gun, S_GUN_UPDATE_DATA * s_Update, const unsigned int * GroNo, const unsigned int * Traget_GroNo)
{
	s_Update->NowPhase = 0;

	if (*GroNo > *Traget_GroNo + 1)return new C_E_No101_AiPhase_1();

	return nullptr;
}
