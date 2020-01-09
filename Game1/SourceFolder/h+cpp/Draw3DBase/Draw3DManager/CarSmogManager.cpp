#include "CarSmogManager.h"
#include"../../GameSource/Judgment.h"

D3DXVECTOR3 C_CarSmogManager::GetPos(const int CarNo)
{

	if (CarNo == CarNo1)return D3DXVECTOR3(0.0f,0.38f,0.75f);

	return D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

S_Smog C_CarSmogManager::GetSmog(const int CarNo)
{
	Judg judg;
	if (CarNo == CarNo1)return judg.GetInitSmog(&D3DXVECTOR3(0.0f, 6.0f, 1.0f), &D3DXVECTOR3(100.0f, 100.0f, 10.0f),
		255, 1000, 2, 0.8f, 0.8f, 0.02f,&judg.GetInitRand(25,10,5));

	return judg.GetInitSmog(&D3DXVECTOR3(0.0f, 8.0f, 1.0f), &D3DXVECTOR3(100.0f, 100.0f, 10.0f),
		255, 1000, 2, 0.8f, 0.0f, 0.0f, &judg.GetInitRand(25, 10, 5));
}
