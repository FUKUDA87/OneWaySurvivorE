#pragma once
#include"../../EnemyData/Base&Manager/EnemySpeed.h"

class SpeedDownDead1 :public Speed {
public:
	SpeedDownDead1();
	Speed* Action(int *NowSpeed, const int *TargetSpeed, const unsigned int *EneGroNo, const unsigned int *TarGroNo);
protected:
	//•Ï‰»—Ê
	int SpeedDownNum;
};