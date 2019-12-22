#pragma once
#include<d3dx9.h>
#include"../../GameSource/Struct.h"
#include"../Bullet/BulletBase.h"
#include"../../GameSource/XfileManager.h"
#include"../Muz/MuzFlaBase.h"
#include"../Laser/LaserBase.h"
#include"../../GameSource/Judgment.h"

extern XfileManager xfileManager;
extern LPDIRECT3DDEVICE9 lpD3DDevice;
void DrawMesh(XFILE *XFile);

class GunBase {
public:
	virtual void Init();
	GunBase();
	~GunBase();
	virtual void Draw3D();
	virtual bool Update();
	virtual bool Update(D3DXMATRIX Mat);
	virtual bool Update(float AngX,float AngY, D3DXMATRIX Mat);
	virtual bool Update(const D3DXMATRIX *CamMat, D3DXMATRIX Mat);
	//çsóÒìnÇµ
	D3DXMATRIX GetGMat() {
		return gun.Base.Mat;
	}
	//ï\é¶ópçsóÒÇÃìnÇµ
	D3DXMATRIX GetDrawMatGun(void) {
		return judg.GetDrawMat(&gun.Base.Mat, &gun.Base.Scal, &gun.Base.ScaPos);
	}

	//èeå˚TransMatìnÇµ
	D3DXMATRIX GetGmMat(void);

	//ägëÂì¸ÇÍ
	void SetScalPos(const D3DXVECTOR3 *sPos) {
		gun.Base.ScaPos = *sPos;
	}

	virtual BulletBase* GetBullet() {
		return new BulletBase();
	}
	virtual BulletBase* GetBullet(D3DXVECTOR3 Pos, bool PFlg) {
		return new BulletBase();
	}
	virtual MuzFlaBase* GetMuzFla() {
		return new MuzFlaBase();
	}
	virtual LaserBase* GetLaser() {
		return new LaserBase();
	}
protected:
	Object3D gun;
	D3DXVECTOR3 Pos;
	D3DXMATRIX GmMat;//èeå˚

	Judg judg;
};