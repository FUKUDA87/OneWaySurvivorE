#include "Speed_Stop_A.h"
#include"Speed_Dead_A.h"
#include"../../EnemyData/EnemyNo1/SpeedData/SpeedUp.h"

C_Speed_Update * C_Speed_Stop_A::Update(int * Now_Speed, const bool * Car_Flg,
	const unsigned int * Now_GroNo, const int * Now_Phase, const int * Target_Speed,
	const unsigned int * Target_GroNo, const bool * UpdateStop_Flg)
{
	//�Ԃ�Hp���[���̏ꍇ
	if (*Car_Flg != true)return new Speed_Dead_A();

	//������悤�ɂȂ���
	if (*UpdateStop_Flg != true)return new SpeedUp1();

	return nullptr;
}
