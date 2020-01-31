#include "Enemy_Manager.h"
#include"../../Enemy2/Enemy_No/Enemy_No101.h"

C_EnemyAi * C_Enemy_Manager::Get_Enemy(const int * EnemyNo, D3DXMATRIX GroundMat, float * TransX)
{
	if (*EnemyNo == 1)return new C_Enemy_No1(GroundMat, TransX);
	if (*EnemyNo == 101)return new C_Enemy_No101(GroundMat, TransX);


	return new C_Enemy_No1(GroundMat,TransX);
}
