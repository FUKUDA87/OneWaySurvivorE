#include "Car_Pop_Manager.h"
#include"../Stage_1/Stage_No1_1.h"

C_Car_Pop_Base * C_Car_Pop_Manager::Get_Pop(const int * StageNo)
{
	return new C_Stage_No1_1();
}
