#pragma once
#include"../../Enemy/Enemy_No/Enemy_No1.h"

class C_Enemy_Manager {
public:
	C_EnemyAi* Get_Enemy(const int *EnemyNo, const D3DXMATRIX * GroundMat, const float * TransX);
};