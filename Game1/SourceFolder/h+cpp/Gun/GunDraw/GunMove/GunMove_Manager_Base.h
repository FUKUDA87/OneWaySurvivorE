#pragma once
#include"GunMoveBase_A.h"

//�e�̓����̌����̃x�[�X
class C_GunMove_A_Manager_Base {
public:
	virtual C_GunMoveBase_A*Get_GunMove_A(const int *MoveNo)=0;
};