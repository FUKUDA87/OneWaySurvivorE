#pragma once
#include<d3dx9.h>
#include<vector>
#include"GunPartsBase.h"
#include"../../GameSource/CharaBase.h"

class c_GunBase :public C_CharaBase
{
public:
	c_GunBase();
	~c_GunBase();

	// •\¦
	void Draw3D(void);

	// XVˆ—
	bool Update(const D3DXMATRIX *BaseMat);

	unsigned int GetNum(void) { return gunParts.size(); }
protected:
	D3DXMATRIX mat;
	float scalSize;
	bool shotFlg;

	std::vector<c_GunPartsBase*>gunParts;


};