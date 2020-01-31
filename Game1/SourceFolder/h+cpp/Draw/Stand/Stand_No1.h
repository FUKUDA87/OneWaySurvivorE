#pragma once
#include"../../Draw3DBase/Car_Parts_Joint.h"

class C_Stand_No1 :public C_Car_Parts_Joint
{
public:
	C_Stand_No1(const S_CAR_PARTS_DATA *Data/*,const bool *Joint_Reverse_Flg*/);
private:
	void Init_Joint_Data(const bool *Joint_Reverse_Flg);
};