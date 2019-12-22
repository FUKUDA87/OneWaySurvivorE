#include "EnemyDeadSpeed.h"

SpeedDownDead1::SpeedDownDead1()
{
	SpeedDownNum = -1;
	CountDownNow = 0;
	CountDown = rand() % 1 + 10;
}

Speed * SpeedDownDead1::Action(int * NowSpeed, const int * TargetSpeed, const unsigned int * EneGroNo, const unsigned int * TarGroNo)
{
	if (CountUpdate() == true) return nullptr;
		*NowSpeed += SpeedDownNum;
		if (*NowSpeed <=0) *NowSpeed=0;
	return nullptr;
}
