#include "SpeedDown.h"
#include"SpeedUp.h"
#include"../../../Move/Speed/Speed_Dead_A.h"

SpeedDown1::SpeedDown1()
{
	SpeedDownNum = -1;
	CountDownNow = 0;
	CountDown = rand() % 10 + 20;
}

Speed * SpeedDown1::Action(const bool *Car_Flg, int * NowSpeed, const int *TargetSpeed, const unsigned int * EneGroNo, const unsigned int * TarGroNo, const int *NewPhase)
{
	if (*Car_Flg != true)return new Speed_Dead_A();

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

Speed * SpeedDown2::Action(const bool *Car_Flg, int * NowSpeed, const int *TargetSpeed, const unsigned int * EneGroNo, const unsigned int * TarGroNo, const int *NewPhase)
{
	if (*Car_Flg != true)return new Speed_Dead_A();

	if (*EneGroNo < *TarGroNo) return new SpeedUp2();
	if (CountUpdate() == true)return nullptr;
	*NowSpeed += SpeedDownNum;
	if (*NowSpeed < *TargetSpeed-5) *NowSpeed = *TargetSpeed-5;
	return nullptr;
}
