#pragma once
#include"GunBase2.h"
#include"../../Bullet/BulletMesh.h"
#include"../../Bullet/BulletDraw3DManager.h"
#include"../../../Effect/Effect_Base.h"
#include"../../../Effect/Gun/No1/Shot/Gun_No1_Shot_Effect.h"

class C_GunBullet :public C_GunBase2 {
public:
	C_GunBullet();
	int Get_BulletNo(void) {
		return BulletNo;
	}

	//銃の数渡し
	unsigned int Get_CategoryNum(void) {
		return M_Category_Data.size();
	}

	//発射後のエフェクト渡し
	virtual C_Effect_Base * Get_Bullet_Shot_Effect(const unsigned int *MouthNo) {
		return new C_Gun_No1_Shot_1_Effect(&Get_GunMouth_Mat(MouthNo),&M_S_GunData.DrawBase.Mat);
	}

	//トリガー
	bool Get_TriggerFlg(const unsigned int *MouthNo);

	void Bullet_Shot_Update(const unsigned int *MouthNo);
protected:
	//弾の表示番号
	int BulletNo;
private:
	bool Judg_MouthNo(const unsigned int *MouthNo);
};