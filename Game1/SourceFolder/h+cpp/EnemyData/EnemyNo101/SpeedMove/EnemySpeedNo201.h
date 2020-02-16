#pragma once
#include"../../EnemyNo1/SpeedData/SpeedUp.h"


class C_EnemySpeedNo201 :public  SpeedUp1{
public:
	C_EnemySpeedNo201();
	Speed* Action(const bool *Car_Flg, int *NowSpeed, const int *TargetSpeed, const unsigned int *EneGroNo, const unsigned int *TarGroNo, const int *NowPhase);
protected:
	int GroNo;
	bool InitFlg;
};