#include "SpeedDown.h"
#include"SpeedUp.h"
#include"../../../Move/Speed/Speed_Dead_A.h"
#include"../../../Move/Speed/Speed_Stop_A.h"

SpeedDown1::SpeedDown1()
{
	SpeedDownNum = -1;
	CountDownNow = 0;
	CountDown = rand() % 10 + 20;
}

C_Speed_Update * SpeedDown1::Update(int * Now_Speed, const bool * Car_Flg,
	const unsigned int * Now_GroNo, const int * Now_Phase, const int * Target_Speed,
	const unsigned int * Target_GroNo, const bool *UpdateStop_Flg)
{
	//車のHpがゼロの場合
	if (*Car_Flg != true)return new Speed_Dead_A();

	//更新が止まっていた場合に更新しない
	if (*UpdateStop_Flg == true)return new C_Speed_Stop_A();

	//ターゲットの後ろ過ぎた場合
	if (*Now_GroNo < *Target_GroNo - 3)return new SpeedUp1();

	if (CountUpdate() == false) {
		*Now_Speed += SpeedDownNum;
		if (*Now_Speed < *Target_Speed - 5) *Now_Speed = *Target_Speed - 5;
	}
	if (*Now_GroNo < *Target_GroNo) return new SpeedUp2();

	return nullptr;
}

//※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※

SpeedDown2::SpeedDown2()
{
	SpeedDownNum = -2;
	CountDown = rand() % 20 + 20;
}

C_Speed_Update * SpeedDown2::Update(int * Now_Speed, const bool * Car_Flg,
	const unsigned int * Now_GroNo, const int * Now_Phase, const int * Target_Speed,
	const unsigned int * Target_GroNo, const bool *UpdateStop_Flg)
{
	//車のHpがゼロの場合
	if (*Car_Flg != true)return new Speed_Dead_A();

	//更新が止まっていた場合に更新しない
	if (*UpdateStop_Flg == true)return new C_Speed_Stop_A();

	//ターゲットの後ろ過ぎた場合
	if (*Now_GroNo < *Target_GroNo - 3)return new SpeedUp1();

	if (*Now_GroNo < *Target_GroNo) return new SpeedUp2();

	if (CountUpdate() == true)return nullptr;

	*Now_Speed += SpeedDownNum;

	if (*Now_Speed < *Target_Speed - 5) *Now_Speed = *Target_Speed - 5;

	return nullptr;
}
