#pragma once
#include<d3dx9.h>
#include"../Gun/Bullet/BulletManager.h"
#include"../Gun/GunDraw/GunBase.h"
#include"Draw3DManager/GunManager.h"

class C_GunMoveBase :public BulletManager{
public:
	C_GunMoveBase();
	~C_GunMoveBase();
	//‰Šú‰»
	virtual void InitGun(void);
	//ŽÔ‚ÉŒp³‚µ‚½Û‚ÉƒI[ƒo[ƒ‰ƒCƒh
	virtual bool UpdateGun();
	virtual bool UpdateGun(float AngX,float AngY);
	virtual bool UpdateGun(const D3DXMATRIX *CamMat);

	//’e‚ð‘Å‚Â
	virtual bool UpdateBullet(const BULLETRAYJUDG *BRJ);
	//’e‚ð‘Å‚ÂŽ~‚ß‚é
	virtual bool UpdateBullet(const BULLETRAYJUDG *BRJ,const bool *BirthFlg);
	//’e‚ðŒ‚‚Â‚Æ‰¹
	virtual bool UpdateBullet(const BULLETRAYJUDG *BRJ,const bool *BirthFlg, const SoundCamera *sc);
	//’e‚ðŒ‚‚Â‚Æ‰¹‚ÆKey
	virtual bool UpdateBullet(const BULLETRAYJUDG *BRJ,const bool *KeyFlg, const bool *BirthFlg, const SoundCamera *sc);
	//’e‚ÌˆÚ“®
	virtual bool UpdateBulletMove(void);

	//•\Ž¦
	void Draw3DGun();

	//•\Ž¦—ps—ñ“n‚µ
	//virtual D3DXMATRIX GetDrawMatGun(void);

	//e‚Ìs—ñ“n‚µ
	D3DXMATRIX GetMatGun(void) {
		return gunBase->GetGMat();
	}

	//ƒXƒ^ƒ“ƒh‚ÌMesh‚Ì“ü‚ê‘Ö‚¦
	void SetGun(int GunNo);

protected:
	D3DXMATRIX ConnectGunMat;

	GunBase *gunBase;
private:
	C_GunManager gunManager;

	XFILE GunMesh;
};