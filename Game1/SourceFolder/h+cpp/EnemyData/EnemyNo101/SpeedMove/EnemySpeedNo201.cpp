#include "EnemySpeedNo201.h"

C_EnemySpeedNo201::C_EnemySpeedNo201()
{
	GroNo = 1;
	InitFlg = true;
}

Speed * C_EnemySpeedNo201::Action(int * NowSpeed, const int * TargetSpeed, const unsigned int * EneGroNo, const unsigned int * TarGroNo, int *NowPhase)
{
	if (*EneGroNo > *TarGroNo + GroNo) {
		*NowSpeed = *TargetSpeed;
		if(InitFlg==true){
			*NowPhase = Phase1;
			InitFlg = false;
		}
		return nullptr;
	}
	if (CountUpdate() == true) return nullptr;
	*NowSpeed += SpeedUpNum;
	if (*NowSpeed > *TargetSpeed + 25) *NowSpeed = *TargetSpeed + 25;

	return nullptr;
}
