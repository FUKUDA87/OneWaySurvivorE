#pragma once
#include"../../Base&Manager/EnemyAiPhaseBase.h"

class C_E_No101_AiPhase_1 :public C_E_AiPhaseBase {
public:
	C_E_No101_AiPhase_1();
	C_E_AiPhaseBase* Action(const CHARABASE *Chara, int *NewPhase);
protected:
	bool InitFlg;
};