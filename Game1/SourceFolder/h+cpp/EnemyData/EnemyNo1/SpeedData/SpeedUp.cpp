#include "SpeedUp.h"
#include"SpeedDown.h"

SpeedUp1::SpeedUp1()
{
	SpeedUpNum = 2;
	CountDownNow = 0;
	CountDown = rand() % 10 + 20;
}

Speed * SpeedUp1::Action(int * NowSpeed, const int *TargetSpeed, const unsigned int * EneGroNo, const unsigned int * TarGroNo, int *NewPhase)
{
	if (*EneGroNo > *TarGroNo - 2) *NewPhase = Phase1;
	if (*EneGroNo > *TarGroNo - 1) return new SpeedDown1();
	if (CountUpdate() == true) return nullptr;
	*NowSpeed += SpeedUpNum;
	if (*NowSpeed > *TargetSpeed + 20) *NowSpeed=*TargetSpeed +20;
	
	return nullptr;
}

//¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦

SpeedUp2::SpeedUp2()
{
	SpeedUpNum = 1;
	CountDown = rand() % 20 + 20;
}

Speed * SpeedUp2::Action(int * NowSpeed, const int *TargetSpeed, const unsigned int * EneGroNo, const unsigned int * TarGroNo, int *NewPhase)
{
	if (*EneGroNo > *TarGroNo ) return new SpeedDown2();
	
	if (CountUpdate() == true) return nullptr;
	*NowSpeed += SpeedUpNum;
	if (*NowSpeed > *TargetSpeed + 5) *NowSpeed = *TargetSpeed + 5;
	return nullptr;
}
