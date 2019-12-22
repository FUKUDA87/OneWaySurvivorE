#include "GunBullet.h"

C_GunBullet::C_GunBullet(const GUNINITDATA * GunInitDataS):C_GunBase2(GunInitDataS)
{
}

C_BulletDraw3DBase * C_GunBullet::GetBullet()
{
	C_BulletDraw3DManager B_Manager;
	return B_Manager.GetBullet(s_Data.DrawNo.BulletNo,&Gun.Base.Mat);
}
