#pragma once
#include"CarGun.h"
#include"../Gun/Bullet/BulletBase/Bullet_Base.h"
#include"../Effect/Effect_Base.h"
#include"../GameSource/Count.h"

class C_CarBulletManager :public C_CarGun {
public:
	C_CarBulletManager();
	~C_CarBulletManager();

	//弾の更新
	bool Update_ALL_Bullet(void);

	//全消し
	void AllDelete(void);
	//ひとつ削除
	void Delete_Bullet(unsigned int *NowBulletNo);
	//弾数渡し
	unsigned int Get_BulletNum(void) {
		return M_Bullet.size();
	}

	//その番号の弾があるか判定
	bool Bullet_NoJudg(const unsigned int *NowBulletNo);

	//表示行列渡し

	//位置行列渡し
	D3DXMATRIX Get_Bullet_Mat(const unsigned int *BulletNo);

	//移動量渡し
	float Get_Bullet_MoveDis(const unsigned int *NowBulletNo) {
		return M_Bullet[*NowBulletNo]->Get_S_BULLET().Speed;
	}

	//トリガー
	virtual void Init_Bullet(void);

	//トリガー２

	//MoveVec入れ

	//更新
	bool Update_Bullet(void);

	//表示
	void Draw_Bullet(const D3DXVECTOR3 *CameraPos);

	//移動量ずらし
	void MoveVec_Bullet(void);

	//弾が壁と地面の判定をするかFlg渡し
	bool Get_Bullet_GroWal_Judg_Flg(const unsigned int *BulletNo);

	//弾が壁と地面の判定をするかFlg代入
	void Set_Bullet_GroWal_Judg_Flg(const unsigned int *BulletNo,const bool *Flg);

	//ダメージ数渡し
	int Get_Bullet_Damage(const unsigned int *NowBulletNo) {
		return M_Bullet[*NowBulletNo]->Get_S_BULLET().Damage;
	}

protected:
	std::vector<C_Bullet_Base*>M_Bullet;

	std::vector<C_Effect_Base*>M_Effect;

	//エフェクトの全削除
	void Delete_All_Effect(void);

	//エフェクトの表示
	void Draw_Effect(const D3DXVECTOR3 *CameraPos);

	//エフェクトに移動量の加算
	void Set_MoveVec_Effect(const D3DXVECTOR3 *MoveVec);

	//エフェクトの更新
	bool Update_Effect(void);

private:
	
};