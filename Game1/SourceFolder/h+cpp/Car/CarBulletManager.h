#pragma once
#include"CarGun.h"
#include"../Gun/Bullet/BulletBase/Bullet_Base.h"
#include"../Draw/Effect/Effect_Base.h"
#include"../GameSource/Count.h"

class C_CarBulletManager :public C_CarGun {
public:
	~C_CarBulletManager();

	//’e‚ÌXV
	bool Update_ALL_Bullet(void);

	//‘SÁ‚µ
	void AllDelete(void);
	//‚Ð‚Æ‚Âíœ
	void Delete_Bullet(unsigned int *NowBulletNo);
	//’e”“n‚µ
	unsigned int Get_BulletNum(void) {
		return M_Bullet.size();
	}

	//‚»‚Ì”Ô†‚Ì’e‚ª‚ ‚é‚©”»’è
	bool Bullet_NoJudg(const unsigned int *NowBulletNo);

	//•\Ž¦s—ñ“n‚µ

	//ˆÊ’us—ñ“n‚µ
	D3DXMATRIX Get_Bullet_Mat(const unsigned int *BulletNo);

	//ˆÚ“®—Ê“n‚µ
	float Get_Bullet_MoveDis(const unsigned int *NowBulletNo) {
		return M_Bullet[*NowBulletNo]->Get_S_BULLET().Speed;
	}

	//ƒgƒŠƒK[
	virtual void Init_Bullet(void);

	//ƒgƒŠƒK[‚Q

	//MoveVec“ü‚ê

	//XV
	bool Update_Bullet(void);

	//•\Ž¦
	void Draw_Bullet(const D3DXVECTOR3 *CameraPos);

	//ˆÚ“®—Ê‚¸‚ç‚µ
	void MoveVec_Bullet(void);

	//’e‚ª•Ç‚Æ’n–Ê‚Ì”»’è‚ð‚·‚é‚©Flg“n‚µ
	bool Get_Bullet_GroWal_Judg_Flg(const unsigned int *BulletNo);

	//’e‚ª•Ç‚Æ’n–Ê‚Ì”»’è‚ð‚·‚é‚©Flg‘ã“ü
	void Set_Bullet_GroWal_Judg_Flg(const unsigned int *BulletNo,const bool *Flg);

	//ƒ_ƒ[ƒW”“n‚µ
	int Get_Bullet_Damage(const unsigned int *NowBulletNo) {
		return M_Bullet[*NowBulletNo]->Get_S_BULLET().Damage;
	}

	RAYDATA GetBulletJudgData(const unsigned int *bc);

protected:
	std::vector<C_Bullet_Base*>M_Bullet;
};