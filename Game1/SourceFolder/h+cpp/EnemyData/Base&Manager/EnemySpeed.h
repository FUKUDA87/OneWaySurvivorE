#pragma once
#include<d3dx9.h>
#include"../EnemyConst/PhaseConst.h"

class Speed {
public:
	virtual Speed* Action(int *NowSpeed,const int *TargetSpeed,const unsigned int *EneGroNo, const unsigned int *TarGroNo,int *NewPhase) = 0;//=0:純粋仮想関数にする（必ず継承し、派生クラス側でオーバーライドしないといけない関数
protected:
	//アップタイミング
	int CountDown, CountDownNow;
	bool CountUpdate(void);
	int NowPhase;
};