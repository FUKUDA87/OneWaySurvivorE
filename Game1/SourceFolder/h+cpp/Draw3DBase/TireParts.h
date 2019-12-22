#pragma once
#include"PartsBase.h"

class C_TireParts :public C_PartsBase {
public:
	C_TireParts(const PARTS *InitGetParts,const float *GetAngXMaxUp);
	bool UpdateParts(const D3DXMATRIX * Mat);
	//アップデート＋拡大の変化
	bool UpdateParts(const D3DXMATRIX *Mat, const D3DXVECTOR3 *ScalPos);
private:
	float AngXMaxUp;
};