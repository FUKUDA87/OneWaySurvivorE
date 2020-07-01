#include "Ball3D.h"
#include"../../../Key/Key.h"

extern LPDIRECT3DDEVICE9		lpD3DDevice;	// Direct3DDevice�C���^�[�t�F�C�X

c_Ball3D::c_Ball3D(float Radius)
{
	radius = Radius;
	Init();
}

c_Ball3D::c_Ball3D(float Radius, float alpha)
{
	radius = Radius;
	D3DXCreateSphere(lpD3DDevice, radius, 10, 10, &lpBall, NULL);
	BallMaterial.Diffuse.r = 1.0f;//Red
	BallMaterial.Diffuse.g = 1.0f;//Green
	BallMaterial.Diffuse.b = 0.0f;//Blue
	float a = alpha;
	if (a < 0.0f)a = 0.0f;
	if (a > 1.0f)a = 1.0f;
	BallMaterial.Diffuse.a = a;//Alpha(�s�����x)0�`1�̏���
}

c_Ball3D::~c_Ball3D()
{
	Release();
}

void c_Ball3D::Draw()
{
	lpD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);
	D3DXMATRIX tmpMat;
	D3DXMatrixTranslation(&tmpMat, pos.x, pos.y, pos.z);
	lpD3DDevice->SetTransform(D3DTS_WORLD, &tmpMat);
	lpD3DDevice->SetMaterial(&BallMaterial);
	lpBall->DrawSubset(0);//���b�V���̕\��
	lpD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}

void c_Ball3D::DrawB()
{
	//lpD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);
	D3DXMATRIX tmpMat;
	D3DXMatrixTranslation(&tmpMat, pos.x, pos.y, pos.z);
	lpD3DDevice->SetTransform(D3DTS_WORLD, &tmpMat);
	lpD3DDevice->SetMaterial(&BallMaterial);
	lpBall->DrawSubset(0);//���b�V���̕\��
	//lpD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}

void c_Ball3D::SetRadius(void)
{
	Key key;

	float Num = 0.5f;

	if (key.UPKeyF()) {
		radius += Num;
		Release();
		Init();
		return;
	}

	if (key.DOWNKeyF()) {
		radius -= Num;
		if (radius < 0.1f)radius = 0.1f;
		Release();
		Init();
		return;
	}
}

void c_Ball3D::Init(void)
{
	D3DXCreateSphere(lpD3DDevice, radius, 10, 10, &lpBall, NULL);
	BallMaterial.Diffuse.r = 0.0f;//Red
	BallMaterial.Diffuse.g = 1.0f;//Green
	BallMaterial.Diffuse.b = 1.0f;//Blue
	BallMaterial.Diffuse.a = 0.5f;//Alpha(�s�����x)0�`1�̏���
}

void c_Ball3D::Release(void)
{
	lpBall->Release();
}
