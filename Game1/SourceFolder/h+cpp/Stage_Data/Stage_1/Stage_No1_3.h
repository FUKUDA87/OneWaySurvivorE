#pragma once
#include"Stage_No1_1.h"

class C_Stage_No1_3 :public C_Car_Pop_Update_1 {
public:
	C_Stage_No1_3();

	//地面情報 
	int Get_GroundNo(void);
protected:
	//次の車
	C_Car_Pop_Base *Next_Pop(void);
};