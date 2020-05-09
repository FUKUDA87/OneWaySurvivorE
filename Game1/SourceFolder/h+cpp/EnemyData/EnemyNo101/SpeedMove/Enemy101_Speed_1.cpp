#include "Enemy101_Speed_1.h"
#include"../../../Move/Speed/Speed_Dead_A.h"
#include"Enemy101_SpeedStop_1.h"

C_Speed_Update * C_Enemy101_Speed_1::Update(int * Now_Speed,
	const bool * Car_Flg, const unsigned int * Now_GroNo,
	const int * Now_Phase, const int * Target_Speed, 
	const unsigned int * Target_GroNo, const bool * UpdateStop_Flg)
{
	//HPがゼロになった時
	if (*Car_Flg != true)return new Speed_Dead_A();

	//ターゲットの前に移動した時
	if (*Now_GroNo > *Target_GroNo-1) {

		//ターゲットと同じにする
		*Now_Speed = *Target_Speed;

		//次の動きに移動する
		return new C_Enemy101_SpeedStop_1();
	}
	if (CountUpdate() == true) return nullptr;
	*Now_Speed += SpeedUpNum;
	if (*Now_Speed > *Target_Speed + 25) *Now_Speed = *Target_Speed + 25;

	return nullptr;
}
