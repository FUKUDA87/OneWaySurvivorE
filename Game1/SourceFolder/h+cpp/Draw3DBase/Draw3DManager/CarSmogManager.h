#pragma once
#include"CarMeshManager.h"

class C_CarSmogManager {
public:
	D3DXVECTOR3 GetPos(const int CarNo);

	S_Smog GetSmog(const int CarNo);
	
};