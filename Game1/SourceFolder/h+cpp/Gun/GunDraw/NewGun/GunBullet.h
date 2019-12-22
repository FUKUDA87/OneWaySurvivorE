#pragma once
#include"GunBase2.h"
#include"../../Bullet/BulletMesh.h"
#include"../../Bullet/BulletDraw3DManager.h"

class C_GunBullet :public C_GunBase2 {
public:
	C_GunBullet() {};
	C_GunBullet(const GUNINITDATA* GunInitDataS);
	virtual C_BulletDraw3DBase* GetBullet();
protected:

private:

};