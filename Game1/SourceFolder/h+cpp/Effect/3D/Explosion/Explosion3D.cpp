#include "Explosion3D.h"
#include"../../../MaterialManager/TextureManager.h"
#include"../../../GameSource/Judgment.h"

extern LPDIRECT3DDEVICE9		lpD3DDevice;
extern TextureManager textureManager;

#define	FVF_VERTEX (D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1)

c_Explosion3D::c_Explosion3D(const D3DXMATRIX * Mat)
{
	Init();
	expl.Base.Pos = D3DXVECTOR3(Mat->_41, Mat->_42, Mat->_43);

	D3DXMatrixTranslation(&expl.Base.Mat, expl.Base.Pos.x, expl.Base.Pos.y, expl.Base.Pos.z);

}

c_Explosion3D::~c_Explosion3D()
{
	delete cou;
}

bool c_Explosion3D::Update(void)
{

	//�J�E���g
	int num = cou->GetNum();

	expl.v[0].Tex = D3DXVECTOR2(32.0f*(num % 8) / 256.0f, 32.0f*(num / 8) / 256.0f);
	expl.v[1].Tex = D3DXVECTOR2(32.0f*(num % 8 + 1) / 256.0f, 32.0f*(num / 8) / 256.0f);
	expl.v[2].Tex = D3DXVECTOR2(32.0f*(num % 8 + 1) / 256.0f, 32.0f*(num / 8 + 1) / 256.0f);
	expl.v[3].Tex = D3DXVECTOR2(32.0f*(num % 8) / 256.0f, 32.0f*(num / 8 + 1) / 256.0f);

	if (cou->CouJudge() == true) {
		return false;
	}
	else {
		cou->CouUpd();
	}
	return true;
}

void c_Explosion3D::Draw3D(const D3DXVECTOR3 * CameraPos)
{
	Judg judg;
	D3DXVECTOR3 bbVec, vec = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	vec += expl.Base.Pos;
	float vecSize = 4.0f;
	bbVec = judg.Billboard(&expl.Base.Pos, &vec, CameraPos, &vecSize);
	expl.v[0].Pos = D3DXVECTOR3(-bbVec.x, vecSize, -bbVec.z);//x,y,z
	expl.v[1].Pos = D3DXVECTOR3(bbVec.x, vecSize, bbVec.z);
	expl.v[2].Pos = D3DXVECTOR3(bbVec.x, -vecSize, bbVec.z);
	expl.v[3].Pos = D3DXVECTOR3(-bbVec.x, -vecSize, -bbVec.z);

	lpD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	lpD3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	lpD3DDevice->SetTexture(0, expl.TEX.Tex);
	lpD3DDevice->SetTransform(D3DTS_WORLD, &expl.Base.Mat);
	lpD3DDevice->SetFVF(FVF_VERTEX);//�o�O
	lpD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, expl.v, sizeof(VERTEX));//2�̓|���S����
	lpD3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	lpD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
}

void c_Explosion3D::Init()
{
	expl.TEX = { NULL,256,256,NULL,NULL,NULL };
	expl.TEX.Tex = textureManager.GetTexture("Smoke.png", expl.TEX.Width, expl.TEX.Height, NULL);
	cou = new Cou(0, 63, 1, false, false);

	//���_�̐ݒ�
	D3DXVECTOR3 Pos(4.0f, 4.0f, 0.0f);
	expl.v[0].Pos = D3DXVECTOR3(-Pos.x, Pos.y, 0.0f);
	expl.v[1].Pos = D3DXVECTOR3(Pos.x, Pos.y, 0.0f);
	expl.v[2].Pos = D3DXVECTOR3(Pos.x, -Pos.y, 0.0f);
	expl.v[3].Pos = D3DXVECTOR3(-Pos.x, -Pos.y, 0.0f);

	expl.v[0].Color = D3DCOLOR_ARGB(255, 255, 255, 255);
	expl.v[1].Color = D3DCOLOR_ARGB(255, 255, 255, 255);
	expl.v[2].Color = D3DCOLOR_ARGB(255, 255, 255, 255);
	expl.v[3].Color = D3DCOLOR_ARGB(255, 255, 255, 255);
}
