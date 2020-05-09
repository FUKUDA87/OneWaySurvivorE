#include "SpeedUp.h"
#include"SpeedDown.h"
#include"../../../Move/Speed/Speed_Dead_A.h"
#include"../../../Move/Speed/Speed_Stop_A.h"

SpeedUp1::SpeedUp1()
{
	SpeedUpNum = 2;
	CountDownNow = 0;
	CountDown = rand() % 10 + 20;
}

C_Speed_Update * SpeedUp1::Update(int * Now_Speed, const bool * Car_Flg,
	const unsigned int * Now_GroNo, const int * Now_Phase, const int * Target_Speed,
	const unsigned int * Target_GroNo, const bool *UpdateStop_Flg)
{
	//車のHpがゼロの場合
	if (*Car_Flg != true)return new Speed_Dead_A();

	//更新が止まっていた場合に更新しない
	if (*UpdateStop_Flg == true)return new C_Speed_Stop_A();

	if (*Now_GroNo >= *Target_GroNo) return new SpeedDown1();
	
	if (CountUpdate() == true) return nullptr;

	*Now_Speed += SpeedUpNum;

	if (*Now_Speed > *Target_Speed + 20) *Now_Speed = *Target_Speed + 20;

	return nullptr;
}

//※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※

SpeedUp2::SpeedUp2()
{
	SpeedUpNum = 1;
	CountDown = rand() % 20 + 20;
}

C_Speed_Update * SpeedUp2::Update(int * Now_Speed, const bool * Car_Flg,
	const unsigned int * Now_GroNo, const int * Now_Phase, const int * Target_Speed,
	const unsigned int * Target_GroNo, const bool *UpdateStop_Flg)
{
	//車のHpがゼロの場合
	if (*Car_Flg != true)return new Speed_Dead_A();

	//更新が止まっていた場合に更新しない
	if (*UpdateStop_Flg == true)return new C_Speed_Stop_A();

	//ターゲットの後ろ過ぎた場合
	if (*Now_GroNo < *Target_GroNo - 3)return new SpeedUp1();

	if (*Now_GroNo > *Target_GroNo) return new SpeedDown2();

	if (CountUpdate() == true) return nullptr;
	*Now_Speed += SpeedUpNum;
	if (*Now_Speed > *Target_Speed + 5) *Now_Speed = *Target_Speed + 5;
	return nullptr;
}
