#include "Stage_No1_3.h"

C_Stage_No1_3::C_Stage_No1_3()
{
	M_Stage_Data.Phase_Type = Co_Phase_Type_Boss;

	New_Car_Data(co_EnemyCar, 101, 0, -10, 2);
}

C_Car_Pop_Base * C_Stage_No1_3::Next_Pop(void)
{
	M_Stage_Data.Phase_Type = Co_Phase_Type_End;
	return nullptr;
}
