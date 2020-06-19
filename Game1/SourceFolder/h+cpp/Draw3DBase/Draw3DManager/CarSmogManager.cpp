#include "CarSmogManager.h"
#include"../../GameSource/Judgment.h"

D3DXVECTOR3 C_CarSmogManager::GetPos(const int CarNo)
{
	//1
	if (CarNo == CarNo1)return D3DXVECTOR3(0.0f,0.38f,0.75f);
	//2
	if (CarNo == CarNo2)return D3DXVECTOR3(0.0f, 0.33f, 0.66f);

	if (CarNo == CarNo101)return D3DXVECTOR3(0.0f, 0.14f, 0.82f);

	if (CarNo == CarNo201)return D3DXVECTOR3(0.0f, 0.37f, 0.56f);

	return D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

S_Smog C_CarSmogManager::GetSmog(const int CarNo)
{
	Judg judg;
	//1
	if (CarNo == CarNo1)return judg.GetInitSmog(&D3DXVECTOR3(0.0f, 6.0f, 1.0f), &D3DXVECTOR3(100.0f, 100.0f, 10.0f),
		255, 1000, 2, 0.8f, 0.8f, 0.02f,&judg.GetInitRand(25,10,5));
	//2
	if (CarNo == CarNo2)return judg.GetInitSmog(&D3DXVECTOR3(0.0f, 6.0f, 1.0f), &D3DXVECTOR3(100.0f, 100.0f, 10.0f),
		255, 1000, 2, 0.8f, 0.8f, 0.02f, &judg.GetInitRand(25, 10, 5));

	return judg.GetInitSmog(&D3DXVECTOR3(0.0f, 5.0f, 1.0f), &D3DXVECTOR3(100.0f, 100.0f, 10.0f),
		255, 1000, 2, 0.8f, 0.8f, 0.02f, &judg.GetInitRand(25, 10, 5));
}
