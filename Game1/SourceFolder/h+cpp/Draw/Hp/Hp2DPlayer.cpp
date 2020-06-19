#include "Hp2DPlayer.h"
#include"../../MaterialManager/TextureManager.h"

extern TextureManager textureManager;
extern LPD3DXSPRITE lpSprite;	// スプライト

C_Hp2D::C_Hp2D(const D3DXVECTOR3 * ScalPos, const D3DXVECTOR3 * TransPos)
{
	m_Hp.ScaPos = *ScalPos;
	m_Hp.ScaPos.z = 0.0f;
	m_Hp.TraPos = *TransPos;
	m_Hp.TraPos.z = 0.0f;
	Init();
}

void C_Hp2D::Draw2DAll(const int * NowHp, const int * MaxHp)
{
	GetGage(NowHp, MaxHp);
	Draw2D();
}

void C_Hp2D::Draw2D(void)
{
	RECT rcAim = { 0,0,m_HpTex[0].Width,m_HpTex[0].Height };
	D3DXVECTOR3 Pos = GetTexPos(&D3DXVECTOR2((float)m_HpTex[0].Width, (float)m_HpTex[0].Height), &m_Hp.TraPos, &m_Hp.ScaPos);
	D3DXMatrixTranslation(&m_Hp.Mat, Pos.x, Pos.y, NULL);
	D3DXVECTOR3 ScalPos = m_Hp.ScaPos;
	judg.ScalingMat(&m_Hp.Scal, &ScalPos);
	D3DXMATRIX tmp;
	tmp = m_Hp.Scal * m_Hp.Mat;
	lpSprite->SetTransform(&tmp);
	lpSprite->Draw(m_HpTex[0].Tex, &rcAim, &D3DXVECTOR3(0, 0, 0), NULL, D3DCOLOR_ARGB(20, 255, 255, 255));

	RECT rcAime = { 0,0,m_HpTex[1].Width,m_HpTex[1].Height };
	Pos = GetTexPos(&D3DXVECTOR2((float)m_HpTex[1].Width, (float)m_HpTex[1].Height), &m_Hp.TraPos, &m_Hp.ScaPos);
	D3DXMatrixTranslation(&m_Hp.Mat, Pos.x, Pos.y, NULL);
	ScalPos = m_Hp.ScaPos;
	ScalPos.x *= Per;
	judg.ScalingMat(&m_Hp.Scal, &ScalPos);
	tmp = m_Hp.Scal * m_Hp.Mat;
	lpSprite->SetTransform(&tmp);
	lpSprite->Draw(m_HpTex[1].Tex, &rcAime, &D3DXVECTOR3(0, 0, 0), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
}

void C_Hp2D::Init(void)
{
	TexNum = 2;
	//緑バー
	m_HpTex[1] = { NULL,1,1,NULL,NULL,NULL };
	m_HpTex[1].Tex = textureManager.GetTexture("plaHp.png", m_HpTex[1].Width, m_HpTex[1].Height, NULL);
	//白いバー
	m_HpTex[0] = { NULL,1,1,NULL,NULL,NULL };
	m_HpTex[0].Tex = textureManager.GetTexture("HpH.png", m_HpTex[0].Width, m_HpTex[0].Height, NULL);
	
}
