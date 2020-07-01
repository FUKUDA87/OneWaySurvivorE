#include "Screen.h"
#include"../../../GameSource/Judgment.h"
#include"../../../Key/Key.h"

extern LPD3DXSPRITE lpSprite;	// �X�v���C�g

#define	SCRW		1280	// �E�B���h�E���iWidth
#define	SCRH		720		// �E�B���h�E�����iHeight

c_Screen::c_Screen()
{
	// �~�j��ʂ̏�����
	M_S_Screen.DrawFlg = false;
	lpD3DDevice->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &M_S_Screen.lpBackBuffer);
	lpD3DDevice->GetDepthStencilSurface(&M_S_Screen.lpZBuffer);//DepthStencilSurface=Z�o�b�t�@
	D3DXCreateTexture(lpD3DDevice, 2048, 1024, 1, D3DUSAGE_RENDERTARGET, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &M_S_Screen.lpTmpTex);//X=2048,Y=1024,���o�b�N�o�b�t�@���Q�ׂ̂���T�C�Y
	M_S_Screen.lpTmpTex->GetSurfaceLevel(0, &M_S_Screen.lpTmpBackBuffer);
	lpD3DDevice->CreateDepthStencilSurface(2048, 1024, D3DFMT_D16, D3DMULTISAMPLE_NONE, 0, FALSE, &M_S_Screen.lpTmpZBuffer, NULL);
}

c_Screen::~c_Screen()
{
	M_S_Screen.lpBackBuffer->Release();
	M_S_Screen.lpZBuffer->Release();
	M_S_Screen.lpTmpBackBuffer->Release();
	M_S_Screen.lpTmpZBuffer->Release();
	M_S_Screen.lpTmpTex->Release();
}

bool c_Screen::Update(void)
{
	Key key;
	Judg judg;

	// �~�j��ʂ̕\���ύX
	if (key.Num1_Key_F())judg.ReverseFlg(&M_S_Screen.DrawFlg);

	return true;
}

void c_Screen::Draw2D(void)
{
	// �~�j��ʂ̕\��
	if (M_S_Screen.DrawFlg != true)return;
	
	RECT rcTmp = { 0,0,1280,720 };
	D3DXMATRIX tmp;
	D3DXMatrixTranslation(&tmp, 0.0f, 0.0f, NULL);
	lpSprite->SetTransform(&tmp);
	lpSprite->Draw(M_S_Screen.lpTmpTex, &rcTmp, &D3DXVECTOR3(0, 0, 0), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));//�Q�T�T�`�P�O�c�����ł���
}

bool c_Screen::RenderStart(const D3DXMATRIX *Mat)
{
	if (M_S_Screen.DrawFlg != true)return false;

	lpD3DDevice->SetRenderTarget(0, M_S_Screen.lpTmpBackBuffer);
	lpD3DDevice->SetDepthStencilSurface(M_S_Screen.lpTmpZBuffer);
	D3DVIEWPORT9 Viewport;
	Viewport.X = 0;
	Viewport.Y = 0;
	Viewport.Width = 1280 / 2;
	Viewport.Height = 720 / 2;
	Viewport.MinZ = 0;
	Viewport.MaxZ = 1;
	lpD3DDevice->SetViewport(&Viewport);
	// �o�b�N�o�b�t�@�� Z �o�b�t�@���N���A
	lpD3DDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 255), 1.0f, 0);
	//    �o�b�N�o�b�t�@�@�@�@Z�o�b�N�o�b�t�@

	D3DXMATRIX mView, mProj;

	//�J�����̈ʒu�̍s��쐬
	D3DXMATRIX CamMat;
	D3DXMatrixTranslation(&CamMat, 45.0f, 50.0f, -1.0f);
	CamMat = CamMat * (*Mat);

	Judg judg;

	// ���_�s��̐ݒ�
	D3DXMatrixLookAtLH(&mView,
		&judg.SetPosM(&CamMat),	// �J�����̈ʒu
		&judg.SetPosM(Mat),	// �J�����̎��_
		&D3DXVECTOR3(0.0f, 1.0f, 0.0f)	// �J�����̓��̕���
	);

	// ���e�s��̐ݒ�
	D3DXMatrixPerspectiveFovLH(&mProj, D3DXToRadian(60), (float)SCRW / (float)SCRH, 0.1f, 600.0f);

	//�s��ݒ�
	lpD3DDevice->SetTransform(D3DTS_VIEW, &mView);
	lpD3DDevice->SetTransform(D3DTS_PROJECTION, &mProj);

	// ���̌��Render3D

	return true;
}

void c_Screen::RenderEnd(void)
{
	// ���̑O��Render3D

	lpD3DDevice->SetRenderTarget(0, M_S_Screen.lpBackBuffer);
	lpD3DDevice->SetDepthStencilSurface(M_S_Screen.lpZBuffer);
}
