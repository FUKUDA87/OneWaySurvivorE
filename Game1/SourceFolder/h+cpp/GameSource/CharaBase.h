#pragma once
#include<d3dx9.h>
#include"Struct.h"
#include"../Draw/Hp/HpBase.h"
#include"../Const/Const_Damage.h"
#include"../Sound/vector/Sound_Data_Vector.h"

class C_CharaBase:public C_Sound_Data_Vector {
public:
	C_CharaBase();
	
	//死亡確認(trueで死)
	bool Dead(void);
	//ダメージによるHp削り(今のHpが増減したらtrue)
	bool HpDamage(const int *Damage);
	//ダメージによるHp削り(今のHpが増減したらtrue)
	bool HpDamage(const int *DamageSetFlg, const int *Damage);

	//初期化１
	void Init_Hp(const int MaxHp, const int *DamageFlg);

	//ダメージを受けるFlgのセット
	void SetDamageFlg(const int *DamageFlg);

	//パーツのダメージを本体に与えるか決めるFlg
	int Get_Parst_DamageSet_Flg(void);

protected:
	//今のHp渡し
	int GetHp(void);

	//構造体渡し
	CHARABASE GetCharaBase(void);

	//構造体代入
	void SetCharaBase(const CHARABASE *CharaBaseS);

	//MaxHpの初期化
	virtual void SetHp(const int *MaxHp);

	CHARABASE CharaBase;
private: 
	//初期化渡し
	CHARABASE GetInitAll(const int MaxHp, const int DFlg);
	//MaxHpの初期化
	virtual void SetNowHp(const int *Hp);
	//ダメージを受ける状態渡し
	bool GetDamageFlg(void);
	//構造体初期化
	CHARABASE GetInitCharaBase(void);
	//別の構造体代入
	void SetCharaBase(const STATUS* S);
};