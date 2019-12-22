#include "GunManager.h"
#include"../../Gun/GunDraw/GunPA.h"

//GunBase * C_GunManager::GetGun(int GunNo)
//{
//	if (GetGun1(GunNo) == true)return new GunPA();
//
//	return new GunBase();
//}

GunBase * C_GunManager::GetGun(int GunNo, D3DXMATRIX Mat)
{
	if (GetGun1(GunNo) == true)return new GunPA(Mat);

	return new GunBase();
}

bool C_GunManager::GetGun1(int GunNo)
{
	if (GunNo != 1)return false;

	return true;
}
