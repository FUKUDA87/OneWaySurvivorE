#pragma once
#include"../Draw3DBase/Car.h"
#include"../2DDraw/HpD.h"

class C_PlayerBase :public C_Car {
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
	virtual void Draw3DAll(void);
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

protected:

private:
	HpD *hp;
	FILE* fp;
	//地面の表示範囲
	float RadField;
	//カーブ角度
	float CurAng;
	D3DXMATRIX CurRotMatY;

};