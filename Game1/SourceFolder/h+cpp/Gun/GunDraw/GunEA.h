#pragma once
#include"../Bullet/BulletEA.h"
#include"GunPA.h"
#include<d3dx9.h>
#include"../Laser/Laser.h"

class GunEA :public GunPA {
private:
protected:
public:
	virtual void InitE();
	GunEA(D3DXMATRIX Mat);
	bool Update(D3DXMATRIX Mat);
	virtual D3DXVECTOR3 GetPos() {
		return Pos;
	}
	virtual D3DXMATRIX GetMat() {
		return gun.Base.Mat;
	}
	BulletEA* GetBullet();
	LaserA* GetLaser() {
		return new LaserA(20.0f);
	}
};