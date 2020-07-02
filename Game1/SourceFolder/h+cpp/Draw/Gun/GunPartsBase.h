#pragma once
#include<d3dx9.h>
#include"../../GameSource/Struct.h"

class c_GunPartsBase
{
public:

	// 更新処理
	bool Update(const D3DXMATRIX *BaseMat,const bool *ShotFlg);

	// 表示
	void Draw3D(void);
protected:
	D3DXMATRIX mat;

	XFILE mesh;
};