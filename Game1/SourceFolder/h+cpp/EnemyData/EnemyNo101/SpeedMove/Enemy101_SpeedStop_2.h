#pragma once
#include"../../EnemyNo1/SpeedData/SpeedUp.h"

class C_Enemy101_SpeedStop_2 :public C_Speed_Update {
public:
	C_Speed_Update* Update(int *Now_Speed, const bool *Car_Flg,
		const unsigned int *Now_GroNo, const int *Now_Phase,
		const int *Target_Speed, const unsigned int *Target_GroNo, const bool *UpdateStop_Flg);
};