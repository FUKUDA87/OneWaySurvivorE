#pragma once
#include"../../No1/Speed/SpeedUp.h"

class C_Enemy101_Speed_2 :public SpeedUp1 {
public:
	C_Enemy101_Speed_2();
	C_Speed_Update* Update(int *Now_Speed, const s_AISpeedUpdateData * UpdateData);
protected:

	//�^�[�Q�b�g����̒n�ʂ̍�
	int M_Ground_Number;
};