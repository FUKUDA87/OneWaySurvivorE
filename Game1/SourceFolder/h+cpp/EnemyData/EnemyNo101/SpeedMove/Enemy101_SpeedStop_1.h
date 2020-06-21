#pragma once
#include"../../EnemyNo1/SpeedData/SpeedUp.h"

class C_Enemy101_SpeedStop_1:public C_Speed_Update {
public:
	C_Speed_Update* Update(int *Now_Speed, const s_AISpeedUpdateData *UpdateData);
};