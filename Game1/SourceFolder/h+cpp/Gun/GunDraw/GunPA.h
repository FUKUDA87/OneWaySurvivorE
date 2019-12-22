#pragma once
#include<d3dx9.h>
#include"GunBase.h"
#include"../Bullet/BulletPA.h"
#include"../Muz/MuzFlaPA.h"


class GunPA:public GunBase{
protected:
public:
	void Init();
	GunPA();
	GunPA(D3DXMATRIX Mat);
	~GunPA();
	void Draw3D();
	bool Update(float AngX,float AngY, D3DXMATRIX Mat);
	bool Update(const D3DXMATRIX *CamMat, D3DXMATRIX Mat);
	bool Update(D3DXMATRIX Mat);
	//PFlgがtrueなら変化
	BulletPA* GetBullet(D3DXVECTOR3 Pos,bool PFlg) {
		return new BulletPA(gun.Base.Mat,GetGmMat(),Pos,PFlg);
	}
	//マゼルフラッシュ
	MuzFlaPA* GetMuzFla() {
		return new MuzFlaPA(gun.Base.Mat,GetGmMat());
	}
};