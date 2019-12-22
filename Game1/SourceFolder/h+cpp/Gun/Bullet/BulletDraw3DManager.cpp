#include "BulletDraw3DManager.h"
#include"BulletConst.h"
#include"BulletPol.h"
#include"BulletMesh.h"

C_BulletDraw3DManager::C_BulletDraw3DManager()
{
	GetGunData.TexNo = 1;
	GetGunData.MeshNo = 1;
	GetGunData.PolNum = 5;
	GetGunData.InitCountMax = 60 * 2;
	GetGunData.PolSize = 0.1f;
	GetGunData.MeshScalPos = D3DXVECTOR3(0.1f, 0.1f, 0.1f);
	GetGunData.Speed = 0.9f;
}

C_BulletDraw3DBase * C_BulletDraw3DManager::GetBullet(const int BulletNo,const D3DXMATRIX *Mat)
{
	GetGunData.Mat = *Mat;

	if (BulletNo == BulletNo01)return new C_BulletPol(&GetGunData);
	if (BulletNo == BulletNo101)return new C_BulletMesh(&GetGunData);

	//åüçıÇ…à¯Ç¡Ç©Ç©ÇÁÇ»Ç¢éû
	return new C_BulletPol(&GetGunData);
}
