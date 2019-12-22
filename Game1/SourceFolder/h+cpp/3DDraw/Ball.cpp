#include "Ball.h"

extern LPDIRECT3DDEVICE9		lpD3DDevice;	// Direct3DDeviceインターフェイス

void Ball::Init()
{
	BallMaterial.Diffuse.r = 0.0f;//Red
	BallMaterial.Diffuse.g = 1.0f;//Green
	BallMaterial.Diffuse.b = 1.0f;//Blue
	BallMaterial.Diffuse.a = 0.5f;//Alpha(不透明度)0～1の小数
}

Ball::Ball(float radius)
{
	D3DXCreateSphere(lpD3DDevice, radius, 10, 10, &lpBall, NULL);
	Init();
}

Ball::~Ball()
{
	lpBall->Release();
}

void Ball::Draw()
{
	lpD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);
	lpD3DDevice->SetTransform(D3DTS_WORLD, &BaMat);
	lpD3DDevice->SetMaterial(&BallMaterial);
	lpBall->DrawSubset(0);//メッシュの表示
	lpD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}

bool Ball::Update(D3DXMATRIX mat)
{
	BaMat = mat;
	return true;
}
