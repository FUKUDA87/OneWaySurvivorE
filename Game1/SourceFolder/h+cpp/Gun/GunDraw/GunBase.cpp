#include "GunBase.h"

void GunBase::Init()
{
}

GunBase::GunBase()
{
	gun.Base.ScaPos = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
}

GunBase::~GunBase()
{
}

void GunBase::Draw3D()
{
}

bool GunBase::Update()
{
	return true;
}

bool GunBase::Update(D3DXMATRIX Mat)
{
	return false;
}

bool GunBase::Update(float AngX, float AngY, D3DXMATRIX Mat)
{
	return true;
}

bool GunBase::Update(const D3DXMATRIX * CamMat, D3DXMATRIX Mat)
{
	return false;
}

D3DXMATRIX GunBase::GetGmMat(void)
{
	D3DXMATRIX Tmp;
	Tmp = GmMat;
	Tmp._43 *= gun.Base.ScaPos.z;
	return Tmp;
}
