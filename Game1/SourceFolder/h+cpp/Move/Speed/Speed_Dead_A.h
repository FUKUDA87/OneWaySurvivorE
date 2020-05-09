#pragma once
#include"../../EnemyData/Base&Manager/EnemySpeed.h"

class Speed_Dead_A :public C_Speed_Update {
public:
	Speed_Dead_A();
	C_Speed_Update* Update(int *Now_Speed, const bool *Car_Flg,
		const unsigned int *Now_GroNo, const int *Now_Phase,
		const int *Target_Speed, const unsigned int *Target_GroNo, const bool *UpdateStop_Flg);
protected:

private:
	int Count_Now, Count_Start;
	bool InitFlg;
};