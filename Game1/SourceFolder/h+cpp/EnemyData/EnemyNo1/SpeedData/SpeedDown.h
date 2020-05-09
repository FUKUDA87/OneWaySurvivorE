#pragma once
#include"../../Base&Manager/EnemySpeed.h"

class SpeedDown1 :public C_Speed_Update {
public:
	SpeedDown1();
	C_Speed_Update* Update(int *Now_Speed, const bool *Car_Flg,
		const unsigned int *Now_GroNo, const int *Now_Phase,
		const int *Target_Speed, const unsigned int *Target_GroNo, const bool *UpdateStop_Flg);
protected:
	//•Ï‰»—Ê
	int SpeedDownNum;
};

class SpeedDown2 :public SpeedDown1 {
public:
	SpeedDown2();
	C_Speed_Update* Update(int *Now_Speed, const bool *Car_Flg,
		const unsigned int *Now_GroNo, const int *Now_Phase,
		const int *Target_Speed, const unsigned int *Target_GroNo, const bool *UpdateStop_Flg);
private:
};