#include "Speed_Stop_A.h"
#include"Speed_Dead_A.h"
#include"../../Enemy/Data/No1/Speed/SpeedUp.h"

C_Speed_Update * C_Speed_Stop_A::Update(int * Now_Speed, const s_AISpeedUpdateData * UpdateData)
{
	//�Ԃ�Hp���[���̏ꍇ
	if (UpdateData->AliveFlg != true)return new Speed_Dead_A();

	//������悤�ɂȂ���
	if (UpdateData->UpdateStopFlg != true)return new SpeedUp1();

	return nullptr;
}
