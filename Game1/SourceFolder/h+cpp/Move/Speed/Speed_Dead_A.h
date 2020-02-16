#pragma once
#include"../../EnemyData/Base&Manager/EnemySpeed.h"

class Speed_Dead_A :public Speed {
public:
	Speed_Dead_A();
	virtual Speed* Action(const bool *Car_Flg, int *NowSpeed
		, const int *TargetSpeed, const unsigned int *EneGroNo, const unsigned int *TarGroNo, const int *NewPhase);
protected:

private:
	int Count_Now, Count_Start;
	bool InitFlg;
};