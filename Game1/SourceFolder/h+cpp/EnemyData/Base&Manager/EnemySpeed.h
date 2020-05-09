#pragma once
#include<d3dx9.h>
#include"../EnemyConst/PhaseConst.h"

class C_Speed_Update {
public:
	virtual C_Speed_Update* Update(int *Now_Speed, const bool *Car_Flg,
		const unsigned int *Now_GroNo, const int *Now_Phase,
		const int *Target_Speed, const unsigned int *Target_GroNo,const bool *UpdateStop_Flg) = 0;
protected:
	//アップタイミング
	int CountDown, CountDownNow;
	bool CountUpdate(void);
	int NowPhase;


};