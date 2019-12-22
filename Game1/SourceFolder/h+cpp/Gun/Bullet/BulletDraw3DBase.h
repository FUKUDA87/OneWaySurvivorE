#pragma once
#include<d3dx9.h>
#include"../../GameSource/Judgment.h"
#include"../../GameSource/Struct.h"
#include"BulletTexManager.h"

class C_BulletDraw3DBase {
public:
	C_BulletDraw3DBase(const GETGUNDATA* GetGunData);
	virtual bool Update(void)=0;
	virtual bool UpdateSet(const D3DXVECTOR3 *Vec)=0;
	virtual void Draw3DAll(const D3DXVECTOR3 *CamPos) = 0;

	//s—ñ“n‚µ
	virtual D3DXMATRIX GetMat(void) = 0;
	virtual D3DXMATRIX GetDrawMat(void) = 0;

	float GetBulletSpeed(void) {
		return 0.9f;
	}

protected:
	//ƒŒƒC”»’è‚Å“–‚½‚Á‚½‚Æ‚±‚ë‚É’e‚ğˆÚ“®‚³‚¹‚é‚½‚ß‚Ì‰ñ“]
	void InitHitRayPos(const bool *HitRayFlg, const D3DXVECTOR3 *HitRayPos);
	//ŒÀ®
	void InitCount(const int *InitCountMax);
	bool CountUpdate(void);
	int NowCount, CountMax;

	Judg judg;

	BASE3D Bullet;

	float Speed;

private:

};