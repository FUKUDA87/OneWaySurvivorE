#pragma once
#include"HpBase.h"
#include"../../GameSource/Struct.h"


class C_HpbarDraw
{
public:
	~C_HpbarDraw();

	// 初期化
	void Init(C_HpBase* InitHpBase);

	// 2D表示
	void Draw2D(const CHARABASE *CharaBase);
	// 3D表示
	void Draw3D(const CHARABASE *CharaBase,const D3DXVECTOR3 *CamPos, const D3DXMATRIX *Mat, const float UpY);
private:
	C_HpBase *HpBase;

	// 削除
	void Delete(void);
};