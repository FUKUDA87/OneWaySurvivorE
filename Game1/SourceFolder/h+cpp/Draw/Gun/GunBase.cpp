#include "GunBase.h"

c_GunBase::c_GunBase()
{
	shotFlg = false;
}

c_GunBase::~c_GunBase()
{
	if (gunParts.size() > 0)
	{
		for (unsigned int gc = 0; gc < gunParts.size(); gc++)
		{
			delete gunParts[gc];
			gunParts.erase(gunParts.begin() + gc);
			gc--;
		}
	}
}

void c_GunBase::Draw3D(void)
{
	if (gunParts.size() <= 0)return;

	for (auto && g : gunParts)g->Draw3D();
}

bool c_GunBase::Update(const D3DXMATRIX * BaseMat)
{
	mat = *BaseMat;

	if (gunParts.size() > 0)
	{
		for (auto && g : gunParts)g->Update(&mat, &shotFlg);
	}

	return true;
}
