#pragma once
#include"Stage_No1_1.h"

class C_Stage_No1_3 :public C_Car_Pop_Update_1 {
public:
	C_Stage_No1_3();

	//’n–Êî•ñ 
	int Get_GroundNo(void);
protected:
	//Ÿ‚ÌÔ
	C_Car_Pop_Base *Next_Pop(void);
};