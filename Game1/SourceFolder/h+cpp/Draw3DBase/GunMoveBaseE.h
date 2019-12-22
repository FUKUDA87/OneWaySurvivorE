#pragma once
#include<d3dx9.h>
#include"../Gun/Bullet/EBulletManager.h"
#include"../Gun/GunDraw/GunBase.h"
#include"Draw3DManager/GunManager.h"
#include"../Gun/GunDraw/GunEA.h"
#include"../Move/GunMove/GunLockonA.h"


class C_GunMoveBaseE{
public:
	C_GunMoveBaseE();
	~C_GunMoveBaseE();
	//‰Šú‰»
	void InitGun(void);
	//e‚Ì‰ñ“]‰Šú‰»
	void InitGunMove(void);

	//e‚ÌƒAƒbƒvƒf[ƒg
	virtual bool UpdateGun(void);

	//e‚Ìs—ñ“n‚µ
	D3DXMATRIX GetGunMatB(void){
		return gunEA->GetGMat();
	}
	//e‚Ìî•ñ“n‚µ
	GUNAI GetGunAi(void) {
		return gun;
	}

	//ƒŒƒC”»’è‚ÌƒJƒEƒ“ƒg‚ğ‚·‚é
	void CountRay(const bool *JudgFlg);
	//
	
protected:
	//SetMat
	void SetGunMatT(const D3DXMATRIX *Mat);

	GunEA *gunEA;

	GUNAI gun;

	C_GunMove* GunMove;
private:
	C_GunManager gunManager;

	Judg judgg;

};