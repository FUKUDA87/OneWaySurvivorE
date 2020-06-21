#pragma once
#include"HpBase.h"
#include"../../GameSource/Struct.h"


class C_HpbarDraw
{
public:
	~C_HpbarDraw();

	// èâä˙âª
	void Init(C_HpBase* InitHpBase);

	// 2Dï\é¶
	void Draw2D(const CHARABASE *CharaBase);
	// 3Dï\é¶
	void Draw3D(const CHARABASE *CharaBase,const D3DXVECTOR3 *CamPos, const D3DXMATRIX *Mat, const float UpY);
private:
	C_HpBase *HpBase;

	// çÌèú
	void Delete(void);
};