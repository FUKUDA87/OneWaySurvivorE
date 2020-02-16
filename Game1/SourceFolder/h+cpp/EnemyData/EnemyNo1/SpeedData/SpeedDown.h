#pragma once
#include"../../Base&Manager/EnemySpeed.h"

class SpeedDown1 :public Speed {
public:
	SpeedDown1();
	Speed* Action(const bool *Car_Flg, int *NowSpeed, const int *TargetSpeed, const unsigned int *EneGroNo, const unsigned int *TarGroNo, const int *NewPhase);
protected:
	//•Ï‰»—Ê
	int SpeedDownNum;
};

class SpeedDown2 :public SpeedDown1 {
public:
	SpeedDown2();
	Speed* Action(const bool *Car_Flg, int *NowSpeed, const int *TargetSpeed, const unsigned int *EneGroNo, const unsigned int *TarGroNo, const int *NewPhase);
private:
};