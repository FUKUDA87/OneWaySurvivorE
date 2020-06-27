#pragma once
#include"../Car/CarBulletManager.h"

class C_PlayerBase :public C_CarBulletManager {
public:
	C_PlayerBase();
	~C_PlayerBase();
	//初期化
	void InitPlayer(void);
	//アップデート
	virtual bool UpdatePlayer(void);
	//継承のアップデート
	virtual bool UpdateAll(void);
	virtual bool UpdateAll(const D3DXMATRIX *CamMat);
	virtual bool UpdateEndAll(void);
	virtual bool UpdateDeadAll(void);

	//継承の表示
	virtual void Draw3DAll(const D3DXVECTOR3 *CameraPos);
	virtual void Draw2DAll(void);

	float GetRadF(void) {
		return RadField;
	}
	void SetRadF(float rad) {
		RadField = rad;
	}

	//カーブのAngいれ
	void SetRodAngY(float Inc, bool KeyFlg);
	//CurEnd
	void SetCurRotMat(void);

	//銃の処理変更
	//弾を撃つと音とKey
	bool UpdateBulPla(const bool *KeyFlg, const bool *BirthFlg, const SoundCamera *sc);

	//カメラの行列のセット
	void Set_CameraMat(const D3DXMATRIX *CameraMat);

	//レイの座標渡し
	S_RAY_HIT_JUDG_DATA Get_Gun_Ray_Data(void) {
		return M_Gun_Ray_Data;
	}

	//レイの情報入れ
	void Set_Gun_Ray_Data(const S_RAY_HIT_JUDG_DATA *Data) {
		M_Gun_Ray_Data = *Data;
	}

	//弾の出現
	void Init_Bullet(void);

private:
	
	FILE* fp;
	//地面の表示範囲
	float RadField;
	//カーブ角度
	float CurAng;
	D3DXMATRIX CurRotMatY;

	//レイ判定銃の座標の取得
	S_RAY_HIT_JUDG_DATA M_Gun_Ray_Data;

	//初期化
	void Init_Ray_Data(void);
};