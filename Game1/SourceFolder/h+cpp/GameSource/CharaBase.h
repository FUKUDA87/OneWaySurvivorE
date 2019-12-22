#pragma once
#include<d3dx9.h>
#include"Struct.h"

class C_CharaBase {
public:
	C_CharaBase();
	//構造体代入
	void SetCharaBase(const CHARABASE *CharaBaseS);
	//初期化渡し
	CHARABASE GetInitAll(const int MaxHp, const bool DFlg);
	//MaxHpの初期化
	virtual void SetHp(const int *MaxHp);
	//MaxHpの初期化
	virtual void SetNowHp(const int *Hp);
	//今のHp渡し
	int GetHp(void);
	//死亡確認(trueで死)
	bool Dead(void);
	//ダメージによるHp削り(今のHpが増減したらtrue)
	bool HpDamage(const int *Damage);
	//ダメージを受けるFlgのセット
	void SetDamageFlg(const bool *DamageFlg);
	//ダメージを受ける状態渡し
	bool GetDamageFlg(void);
	//構造体初期化
	CHARABASE GetInitCharaBase(void);
	//構造体渡し
	CHARABASE GetCharaBase(void);
	//別の構造体代入
	void SetCharaBase(const STATUS* S);

protected:

private: 
	CHARABASE CharaBase;
};