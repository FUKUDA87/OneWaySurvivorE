#pragma once
#include"../../Base&Manager/PartsMoveBase.h"

class C_EnemyNo1_StandMove :public C_PartsMoveBase {
public:
	C_PartsMoveBase* Move(PARTS *Parts, const D3DXMATRIX *Mat, const int *Speed, const int *MaxSpeed, int *NowPhase);
private:

};