#pragma once
#include"GunMove_Manager_Base.h"

//�e�̓����̃^�C�vA�̒ʏ�^�C�v
class C_GunMove_A_Manager_1 :public C_GunMove_A_Manager_Base {
public:
	C_GunMoveBase_A*Get_GunMove_A(const int *MoveNo);
};