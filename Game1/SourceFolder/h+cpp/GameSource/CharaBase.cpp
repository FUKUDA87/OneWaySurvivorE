#include "CharaBase.h"

C_CharaBase::C_CharaBase()
{
	SetCharaBase(&GetInitCharaBase());
}

C_CharaBase::~C_CharaBase()
{
	Hp_Delete();
}

void C_CharaBase::SetCharaBase(const CHARABASE * CharaBaseS)
{
	CharaBase = *CharaBaseS;
}

CHARABASE C_CharaBase::GetInitAll(const int MaxHp, const int DFlg)
{
	CHARABASE c;
	c.NowHp=c.MaxHp = MaxHp;
	c.DamageSetFlg = DFlg;
	return c;
}

void C_CharaBase::SetHp(const int * MaxHp)
{
	CharaBase.NowHp=CharaBase.MaxHp = *MaxHp;
}

void C_CharaBase::SetNowHp(const int * Hp)
{
	CharaBase.NowHp = *Hp;
	if (CharaBase.NowHp < 0)CharaBase.NowHp = 0;
	if (CharaBase.NowHp > CharaBase.MaxHp)CharaBase.NowHp = CharaBase.MaxHp;
}

int C_CharaBase::GetHp(void)
{
	return CharaBase.NowHp;
}

bool C_CharaBase::Dead(void)
{
	if (CharaBase.NowHp <= 0)return true;
	return false;
}

bool C_CharaBase::HpDamage(const int * Damage)
{
	if (CharaBase.DamageSetFlg%2==0)return false;

	if (*Damage == 0)return false;

	int Hp = CharaBase.NowHp;
	CharaBase.NowHp -= *Damage;
	if (CharaBase.NowHp <= 0)CharaBase.NowHp = 0;

	if((Hp> CharaBase.NowHp)||(Hp < CharaBase.NowHp))return true;
	return false;
}

void C_CharaBase::SetDamageFlg(const int * DamageFlg)
{
	CharaBase.DamageSetFlg = *DamageFlg;
}

bool C_CharaBase::GetDamageFlg(void)
{
	return CharaBase.DamageSetFlg;
}

CHARABASE C_CharaBase::GetInitCharaBase(void)
{
	CHARABASE c;
	c.NowHp=c.MaxHp= 1;
	c.DamageSetFlg = Co_Damage_No;
	return c;
}

CHARABASE C_CharaBase::GetCharaBase(void)
{
	return CharaBase;
}

void C_CharaBase::SetCharaBase(const STATUS * S)
{
	/*SetHp(&S->MaxHp);
	SetDamageFlg(&S->DamageSetFlg);*/
}

void C_CharaBase::Init_Hp(const int MaxHp, const int *DamageFlg)
{
	SetHp(&MaxHp);

	SetDamageFlg(DamageFlg);
}

void C_CharaBase::Hp_Init(C_HpBase * InitHpBase)
{
	Hp_Delete();

	HpBase = InitHpBase;
}

void C_CharaBase::Hp_Delete(void)
{
	if (HpBase != nullptr) {
		delete HpBase;
	}
}

void C_CharaBase::Hp_Draw2D(void)
{
	if (HpBase != nullptr) {
		HpBase->Draw2DAll(&CharaBase.NowHp, &CharaBase.MaxHp);
	}
}

void C_CharaBase::Hp_Draw3D(const D3DXVECTOR3 *CamPos, const D3DXMATRIX *Mat, const float UpY)
{
	if (HpBase != nullptr) {
		HpBase->Draw3DAll(&CharaBase.NowHp, &CharaBase.MaxHp, CamPos, Mat, UpY);
	}
}
