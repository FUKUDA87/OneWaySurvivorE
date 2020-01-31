#include "BulletData_Manager.h"
#include"../Bullet_No1/BulletData_No1.h"

C_BulletData_Base * C_BulletData_Manager::Get_Data(const int * BulletNo)
{
	if (*BulletNo == 1)return new C_BullteData_No1();

	return new C_BullteData_No1();
}
