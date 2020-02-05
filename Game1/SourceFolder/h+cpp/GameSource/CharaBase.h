#pragma once
#include<d3dx9.h>
#include"Struct.h"
#include"../Draw/Hp/HpBase.h"
#include"../Const/Const_Damage.h"
#include"../Sound/vector/Sound_Data_Vector.h"

class C_CharaBase:public C_Sound_Data_Vector {
public:
	C_CharaBase();
	
	//���S�m�F(true�Ŏ�)
	bool Dead(void);
	//�_���[�W�ɂ��Hp���(����Hp������������true)
	bool HpDamage(const int *Damage);
	//�_���[�W�ɂ��Hp���(����Hp������������true)
	bool HpDamage(const int *DamageSetFlg, const int *Damage);

	//�������P
	void Init_Hp(const int MaxHp, const int *DamageFlg);

	//�_���[�W���󂯂�Flg�̃Z�b�g
	void SetDamageFlg(const int *DamageFlg);

	//�p�[�c�̃_���[�W��{�̂ɗ^���邩���߂�Flg
	int Get_Parst_DamageSet_Flg(void);

protected:
	//����Hp�n��
	int GetHp(void);

	//�\���̓n��
	CHARABASE GetCharaBase(void);

	//�\���̑��
	void SetCharaBase(const CHARABASE *CharaBaseS);

	//MaxHp�̏�����
	virtual void SetHp(const int *MaxHp);

	CHARABASE CharaBase;
private: 
	//�������n��
	CHARABASE GetInitAll(const int MaxHp, const int DFlg);
	//MaxHp�̏�����
	virtual void SetNowHp(const int *Hp);
	//�_���[�W���󂯂��ԓn��
	bool GetDamageFlg(void);
	//�\���̏�����
	CHARABASE GetInitCharaBase(void);
	//�ʂ̍\���̑��
	void SetCharaBase(const STATUS* S);
};