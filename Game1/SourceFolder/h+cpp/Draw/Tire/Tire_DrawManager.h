#pragma once
#include"Car_Tire_No1.h"

class C_Tire_DrawManager {
public:
	//�\���n��
	C_Car_Parts_Joint* Get_Draw(const int *TireNo, const S_CAR_PARTS_DATA *Data, C_Move_Parts_Base *Move);

	//�����Z�b�g
	C_Car_Parts_Joint* Get_Draw_Stop(const int *TireNo, const S_CAR_PARTS_DATA *Data);

	//�����Z�b�g
	C_Car_Parts_Joint* Get_Draw_Tire(const int *TireNo, const S_CAR_PARTS_DATA *Data);
private:
	
};