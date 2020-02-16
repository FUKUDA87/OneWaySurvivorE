#include "Speed_Dead_A.h"

Speed_Dead_A::Speed_Dead_A()
{
	Count_Now = Count_Start = 20;
	InitFlg = true;
}

Speed * Speed_Dead_A::Action(const bool * Car_Flg, int * NowSpeed, const int * TargetSpeed, const unsigned int * EneGroNo, const unsigned int * TarGroNo, const int * NewPhase)
{
	if (InitFlg == true) {
		InitFlg = false;

		*NowSpeed = *TargetSpeed;
	}

	Count_Now--;

	if (Count_Now > 0)return nullptr;

	Count_Now = Count_Start;

	*NowSpeed -= 1;

	return nullptr;
}
