#pragma once
#include"HpBase.h"
#include"../../GameSource/Struct.h"


class C_HpbarDraw
{
public:
	~C_HpbarDraw();

	// ������
	void Init(C_HpBase* InitHpBase);

	// 2D�\��
	void Draw2D(const CHARABASE *CharaBase);
	// 3D�\��
	void Draw3D(const CHARABASE *CharaBase,const D3DXVECTOR3 *CamPos, const D3DXMATRIX *Mat, const float UpY);
private:
	C_HpBase *HpBase;

	// �폜
	void Delete(void);
};