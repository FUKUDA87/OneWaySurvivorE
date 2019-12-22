#include "SpeedDown.h"
#include"SpeedUp.h"

SpeedDown1::SpeedDown1()
{
	SpeedDownNum = -1;
	CountDownNow = 0;
	CountDown = rand() % 10 + 20;
}

Speed * SpeedDown1::Action(int * NowSpeed, const int *TargetSpeed, const unsigned int * EneGroNo, const unsigned int * TarGroNo, int *NewPhase)
{
	//if (*EneGroNo > *TarGroNo + 1) return new SpeedDown2();
	if (CountUpdate() == false) {
		*NowSpeed += SpeedDownNum;
		if (*NowSpeed < *TargetSpeed-5) *NowSpeed = *TargetSpeed-5;
	}
	if (*EneGroNo < *TarGroNo) return new SpeedUp2();
	return nullptr;
}

//¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦

SpeedDown2::SpeedDown2()
{
	SpeedDownNum = -2;
	CountDown = rand() % 20 + 20;
}

Speed * SpeedDown2::Action(int * NowSpeed, const int *TargetSpeed, const unsigned int * EneGroNo, const unsigned int * TarGroNo, int *NewPhase)
{
	if (*EneGroNo < *TarGroNo) return new SpeedUp2();
	if (CountUpdate() == true)return nullptr;
	*NowSpeed += SpeedDownNum;
	if (*NowSpeed < *TargetSpeed-5) *NowSpeed = *TargetSpeed-5;
	return nullptr;
}
