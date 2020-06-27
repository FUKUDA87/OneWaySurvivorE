#pragma once
#include"HpbarBase.h"
#include"../../GameSource/Struct.h"

class C_HpbarDraw
{
public:
	~C_HpbarDraw();

	// ������
	void Init(C_HpbarBase* InitHpBase);

	// 2D�\��
	void Draw2D(const CHARABASE *CharaBase);
	// 3D�\��
	void Draw3D(const CHARABASE *CharaBase, const D3DXMATRIX *Mat
		,const D3DXVECTOR3 *CamPos,const D3DXVECTOR3 *ScalPos);
private:
	C_HpbarBase *HpbarBase;

	// �폜
	void Delete(void);
};