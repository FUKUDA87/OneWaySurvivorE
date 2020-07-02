#pragma once
#include<d3dx9.h>
#include"../../GameSource/Struct.h"

class c_GunPartsBase
{
public:

	// XVˆ—
	bool Update(const D3DXMATRIX *BaseMat,const bool *ShotFlg);

	// •\¦
	void Draw3D(void);
protected:
	D3DXMATRIX mat;

	XFILE mesh;
};