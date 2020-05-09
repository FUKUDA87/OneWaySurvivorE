#include "Speed_Dead_A.h"

Speed_Dead_A::Speed_Dead_A()
{
	Count_Now = Count_Start = 20;
	InitFlg = true;
}

C_Speed_Update * Speed_Dead_A::Update(int * Now_Speed, const bool * Car_Flg,
	const unsigned int * Now_GroNo, const int * Now_Phase,
	const int * Target_Speed, const unsigned int * Target_GroNo, const bool *UpdateStop_Flg)
{
	if (InitFlg == true) {

		InitFlg = false;

		if (*Now_Speed > *Target_Speed)*Now_Speed = *Target_Speed;

	}

	Count_Now--;

	if (Count_Now > 0)return nullptr;

	Count_Now = Count_Start;

	*Now_Speed -= 1;

	if (*Now_Speed < 0)*Now_Speed = 0;

	return nullptr;
}


