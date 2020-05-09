#pragma once
#include"../../EnemyData/Base&Manager/EnemySpeed.h"

class C_Speed_Stop_A :public C_Speed_Update {
public:
	C_Speed_Update* Update(int *Now_Speed, const bool *Car_Flg,
		const unsigned int *Now_GroNo, const int *Now_Phase,
		const int *Target_Speed, const unsigned int *Target_GroNo, const bool *UpdateStop_Flg);
};