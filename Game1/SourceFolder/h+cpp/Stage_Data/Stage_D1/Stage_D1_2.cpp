#include "Stage_D1_2.h"

C_Stage_D1_2::C_Stage_D1_2()
{
	M_Stage_Data.Phase_Type = Co_Phase_Type_Boss;

	New_Car_Data(co_EnemyCar, 101, 0, -10, 2);
}

int C_Stage_D1_2::Get_GroundNo(void)
{
	return 0;
}

C_Car_Pop_Base * C_Stage_D1_2::Next_Pop(void)
{
	M_Stage_Data.Phase_Type = Co_Phase_Type_End;
	return nullptr;
}
