#pragma once
#include"../../EnemyNo1/SpeedData/SpeedUp.h"

class C_Enemy101_Speed_2 :public SpeedUp1 {
public:
	C_Enemy101_Speed_2();
	C_Speed_Update* Update(int *Now_Speed, const bool *Car_Flg,
		const unsigned int *Now_GroNo, const int *Now_Phase,
		const int *Target_Speed, const unsigned int *Target_GroNo, const bool *UpdateStop_Flg);
protected:

	//�^�[�Q�b�g����̒n�ʂ̍�
	int M_Ground_Number;
};