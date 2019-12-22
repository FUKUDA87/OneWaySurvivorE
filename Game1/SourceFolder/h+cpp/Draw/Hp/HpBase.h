#pragma once
#include<d3dx9.h>
#include"../../GameSource/Judgment.h"
#include"../../GameSource/Struct.h"

class C_HpBase {
public:
	virtual void Draw2DAll(const int *NowHp, const int *MaxHp) = 0;
	virtual void Draw3DAll(const int *NowHp, const int *MaxHp, const D3DXVECTOR3 *CamPos, const D3DXMATRIX *Mat, const float UpY) = 0;
protected:
	void GetGage(const int *NowHp, const int *MaxHp);
	D3DXVECTOR3 GetTexPos(const D3DXVECTOR2*TexPos, const D3DXVECTOR3*TransPos, const D3DXVECTOR3*ScalPos);
	BASE3D m_Hp;
	float Per;//äÑçá
	Judg judg;
private:

};