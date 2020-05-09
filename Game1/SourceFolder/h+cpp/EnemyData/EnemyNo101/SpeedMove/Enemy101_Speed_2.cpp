#include "Enemy101_Speed_2.h"
#include"../../../Move/Speed/Speed_Dead_A.h"
#include"Enemy101_SpeedStop_2.h"

C_Enemy101_Speed_2::C_Enemy101_Speed_2()
{
	M_Ground_Number = 1;
}

C_Speed_Update * C_Enemy101_Speed_2::Update(int * Now_Speed,
	const bool * Car_Flg, const unsigned int * Now_GroNo,
	const int * Now_Phase, const int * Target_Speed,
	const unsigned int * Target_GroNo, const bool * UpdateStop_Flg)
{
	//HP���[���ɂȂ�����
	if (*Car_Flg != true)return new Speed_Dead_A();

	//�^�[�Q�b�g�̑O�Ɉړ�������
	if (*Now_GroNo > *Target_GroNo+M_Ground_Number) {

		//�^�[�Q�b�g�Ɠ����ɂ���
		*Now_Speed = *Target_Speed;

		//���̓����Ɉړ�����
		return new C_Enemy101_SpeedStop_2();
	}
	if (CountUpdate() == true) return nullptr;
	*Now_Speed += SpeedUpNum;
	if (*Now_Speed > *Target_Speed + 25) *Now_Speed = *Target_Speed + 25;

	return nullptr;
}
