#pragma once
#include"GunMoveBaseE.h"
#include"../Gun/GunDraw/NewGun/GunLaser.h"
#include"../Gun/GunDraw/NewGun/EnemyGun.h"
#include"CarParts.h"
#include<vector>

class C_GunMoveBaseE2 :public C_CarParts {
public:
	~C_GunMoveBaseE2();
	//初期化
	void InitSetGun(const GUNINITDATA* GunInitDataS);
	//削除
	void DeleteGun(void);
	//銃の表示数渡し
	unsigned int GetGunNum(void) {
		return m_Gun.size();
	}
	//銃の情報渡し
	GUNDATA GetGunData(unsigned int *No);
	//パーツの表示行列渡し
	D3DXMATRIX GetGunMat(unsigned int *No);
	//パーツのダメージ処理
	bool SetDamageGun(const unsigned int *gNo, const int *Damage);
	//パーツの生存確認(0で死、１で生、２は判別不能)
	int GunDeadFlg(unsigned int *gNo);

	void GetTargetPos(const D3DXVECTOR3 *Pos);

	S_ENEMYGUNDATA GetEnemyGunData(const unsigned int *gNo);

	void SetHitRayFlg(const unsigned int *gNo, const bool *Flg);

	bool UpdateBullet2(const D3DXVECTOR3 *mVec);

	void Draw3D_Laser(const D3DXVECTOR3 *CamPos);

	void GetRayHitDis(const unsigned int *gNo,const float *Dis);
protected:
	std::vector<C_GunLaser*>m_Gun;
private:

};