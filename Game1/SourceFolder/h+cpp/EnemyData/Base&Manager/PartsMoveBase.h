#pragma once
#include<d3dx9.h>
#include"../EnemyConst/PhaseConst.h"
#include"../../GameSource/Struct.h"
#include"../../\/GameSource/Judgment.h"

class C_PartsMoveBase {
public:
	virtual C_PartsMoveBase* Move(PARTS *Parts,const D3DXMATRIX *Mat, const int *Speed, const int *MaxSpeed,int *NowPhase)=0;
protected:
	Judg judg;
private:
};