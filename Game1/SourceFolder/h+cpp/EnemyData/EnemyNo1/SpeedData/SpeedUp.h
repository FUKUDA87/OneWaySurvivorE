#pragma once
#include"../../Base&Manager/EnemySpeed.h"

class SpeedUp1:public C_Speed_Update {
public:
	SpeedUp1();
	C_Speed_Update* Update(int *Now_Speed, const bool *Car_Flg,
		const unsigned int *Now_GroNo, const int *Now_Phase,
		const int *Target_Speed, const unsigned int *Target_GroNo, const bool *UpdateStop_Flg);
protected:
	//•Ï‰»—Ê
	int SpeedUpNum;
};

class SpeedUp2 :public SpeedUp1 {
public:
	SpeedUp2();
	C_Speed_Update* Update(int *Now_Speed, const bool *Car_Flg,
		const unsigned int *Now_GroNo, const int *Now_Phase,
		const int *Target_Speed, const unsigned int *Target_GroNo, const bool *UpdateStop_Flg);
private:
};