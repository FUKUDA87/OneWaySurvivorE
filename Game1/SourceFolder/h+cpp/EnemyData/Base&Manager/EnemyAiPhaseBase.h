#pragma once
#include<d3dx9.h>
#include"../../GameSource/Struct.h"
#include"../EnemyConst/PhaseConst.h"

class C_E_AiPhaseBase {
public:
	virtual C_E_AiPhaseBase* Action(const CHARABASE *Chara,int *NewPhase) = 0;//=0:純粋仮想関数にする（必ず継承し、派生クラス側でオーバーライドしないといけない関数
protected:
	int NowPhase;
};