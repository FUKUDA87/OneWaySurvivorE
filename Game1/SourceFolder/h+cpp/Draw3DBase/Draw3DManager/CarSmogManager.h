#pragma once
#include"CarMeshManager.h"

class C_CarSmogManager {
public:
	//���̏o���ʒu
	D3DXVECTOR3 GetPos(const int CarNo);
	//���̃A�j���[�V�������@
	S_Smog GetSmog(const int CarNo);
	
};