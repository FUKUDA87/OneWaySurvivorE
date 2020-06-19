#include "Hp3DEnemy.h"
#include"../../MaterialManager/TextureManager.h"

extern TextureManager textureManager;
extern LPDIRECT3DDEVICE9		lpD3DDevice;
#define	FVF_VERTEX (D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1)

C_Hp3D::C_Hp3D(const D3DXVECTOR2 * TransPos)
{
	m_Hp.TraPos.x = TransPos->x;
	if (m_Hp.TraPos.x < 0.0f)m_Hp.TraPos.x *= -1.0f;
	m_Hp.TraPos.y = TransPos->y;
	if (m_Hp.TraPos.y < 0.0f)m_Hp.TraPos.y *= -1.0f;
	m_Hp.TraPos.z = 0.0f;

	Init();
}

void C_Hp3D::Draw3DAll(const int * NowHp, const int * MaxHp, const D3DXVECTOR3 * CamPos, const D3DXMATRIX * Mat, const float UpY)
{
	if (*NowHp <= 0)return;
	if ((m_Hp.DrawFlg == false) && (*NowHp < *MaxHp)) {
		m_Hp.DrawFlg = true;
	}

	if (m_Hp.DrawFlg !=true)return;

	GetGage(NowHp, MaxHp);

	for (int p = 0; p < 4; p++) {
		v[p].Color= D3DCOLOR_ARGB(255, 255, 255, 255);
	}

	Per = 0.5f*Per;
	v[0].Tex = D3DXVECTOR2(0.5f - Per, 0.0f);
	v[1].Tex = D3DXVECTOR2(1.0f - Per, 0.0f);
	v[2].Tex = D3DXVECTOR2(1.0f - Per, 1.0f);
	v[3].Tex = D3DXVECTOR2(0.5f - Per, 1.0f);

	D3DXMATRIX TmpMat;
	float y = UpY;
	if (y < 0.0f)y *= -1.0f;
	D3DXMatrixTranslation(&TmpMat, 0.0f, y, 0.0f);
	TmpMat = TmpMat * (*Mat);
	judg.SetPosM(&m_Hp.Pos, &TmpMat);
	D3DXVECTOR3 PosS, PosE, vec;
	PosS = m_Hp.Pos + D3DXVECTOR3(0.0f, m_Hp.TraPos.y, 0.0f);
	PosE = m_Hp.Pos + D3DXVECTOR3(0.0f, -m_Hp.TraPos.y, 0.0f);
	vec = judg.Billboard(&PosS, &PosE, CamPos, &m_Hp.TraPos.x);
	v[0].Pos = PosS + vec;
	v[1].Pos = PosS - vec;
	v[2].Pos = PosE - vec;
	v[3].Pos = PosE + vec;

	lpD3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	lpD3DDevice->SetTexture(0, m_PolTex.Tex);
	D3DXMATRIX IdenMat;
	D3DXMatrixIdentity(&IdenMat);
	lpD3DDevice->SetTransform(D3DTS_WORLD, &IdenMat);
	lpD3DDevice->SetFVF(FVF_VERTEX);//ƒoƒO
	lpD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, v, sizeof(VERTEX));//2‚Íƒ|ƒŠƒSƒ“”
	lpD3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

}

void C_Hp3D::Init(void)
{
	m_Hp.DrawFlg = false;

	m_PolTex = { NULL,200,100,NULL,NULL,NULL };
	m_PolTex.Tex = textureManager.GetTexture("HpE5.png", m_PolTex.Width, m_PolTex.Height, NULL);
}
