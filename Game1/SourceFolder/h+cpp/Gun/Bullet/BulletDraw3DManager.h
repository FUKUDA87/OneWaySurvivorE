#pragma once
#include<d3dx9.h>
#include"BulletDraw3DBase.h"
#include"../../GameSource/Struct.h"

class C_BulletDraw3DManager {
public:
	C_BulletDraw3DManager();
	C_BulletDraw3DBase *GetBullet(const int BulletNo, const D3DXMATRIX *Mat);
protected:

private:
	GETGUNDATA GetGunData;
};