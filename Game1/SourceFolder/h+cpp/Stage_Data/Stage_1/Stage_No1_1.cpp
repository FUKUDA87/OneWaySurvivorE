#include "Stage_No1_1.h"
#include"Stage_No1_2.h"

C_Stage_No1_1::C_Stage_No1_1()
{
	int Time = 0
		,Up=180;

	int Start = -1;

	for (int i = 0; i < 5; i++) {

		New_Car_Data(co_EnemyCar, 1, Time, Start, 0);
		Time += Up;
		if (Time > Up)Time = Up;
	}
}

int C_Stage_No1_1::Get_GroundNo(void)
{
	return 0;
}

C_Car_Pop_Base * C_Stage_No1_1::Next_Pop(void)
{
	return new C_Stage_No1_2();
}
