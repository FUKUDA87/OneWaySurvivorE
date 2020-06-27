#pragma once
#include"CarMeshManager.h"

class C_CarSmogManager {
public:
	//煙の出現位置
	D3DXVECTOR3 GetPos(const int CarNo);
	//煙のアニメーション方法
	S_Smog GetSmog(const int CarNo);
	
};