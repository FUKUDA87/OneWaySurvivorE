#pragma once
#include<d3dx9.h>
#include"Struct.h"
#include"../Draw/Hp/HpBase.h"
#include"../Const/Const_Damage.h"

class C_CharaBase {
public:
	C_CharaBase();
	~C_CharaBase();
	//構造体代入
	void SetCharaBase(const CHARABASE *CharaBaseS);
	//初期化渡し
	CHARABASE GetInitAll(const int MaxHp, const int DFlg);
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
	void SetDamageFlg(const int *DamageFlg);
	//ダメージを受ける状態渡し
	bool GetDamageFlg(void);
	//構造体初期化
	CHARABASE GetInitCharaBase(void);
	//構造体渡し
	CHARABASE GetCharaBase(void);
	//別の構造体代入
	void SetCharaBase(const STATUS* S);

	//初期化１
	void Init_Hp(const int MaxHp, const int *DamageFlg);
protected:
	//Hp表示渡し
	void Hp_Init(C_HpBase* InitHpBase);
	//Hp削除
	void Hp_Delete(void);
	//Hp２D表示
	void Hp_Draw2D(void);
	//Hp3D表示
	void Hp_Draw3D(const D3DXVECTOR3 *CamPos, const D3DXMATRIX *Mat, const float UpY);

	CHARABASE CharaBase;
private: 
	C_HpBase *HpBase;
};