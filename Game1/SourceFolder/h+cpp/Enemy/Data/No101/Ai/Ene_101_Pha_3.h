#pragma once
#include"../../Base&Manager/EnemyAiPhaseBase.h"

class C_EnemyNo101_Phase3 :public C_E_AiPhaseBase {
public:
	C_EnemyNo101_Phase3();
	C_E_AiPhaseBase* Action(const CHARABASE *Chara, std::vector<C_Car_Parts_Joint*>M_Car_Parts, std::vector<C_GunLaser*>M_Gun, S_GUN_UPDATE_DATA* s_Update, const unsigned int *GroNo, const unsigned int *Traget_GroNo);
protected:
	bool InitFlg;
	unsigned int GunNo0;
};