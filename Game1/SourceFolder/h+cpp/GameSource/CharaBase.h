#pragma once
#include<d3dx9.h>
#include"Struct.h"
#include"../Const/Const_Damage.h"
#include"../Sound/vector/Sound_Data_Vector.h"
#include"../Draw/Hp/HpbarDraw.h"

class C_CharaBase:public C_Sound_Data_Vector {
public:
	C_CharaBase();
	~C_CharaBase();
	
	//���S�m�F(true�Ŏ�)
	virtual bool Dead(void);
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

	//MaxHp�̏�����
	void SetNowHp(const int *Hp);

	//�\���̓n��
	CHARABASE GetCharaBase(void);

protected:

	C_HpbarDraw *Hpbar;

	//����Hp�n��
	int GetHp(void);

	//�\���̑��
	void SetCharaBase(const CHARABASE *CharaBaseS);

	//MaxHp�̏�����
	virtual void SetHp(const int *MaxHp);

	CHARABASE CharaBase;

	//�_���[�W���󂯂�����Flg
	bool Body_DamageFlg;

	//�_���[�W���󂯂�����Flg�̔���
	void Judg_Body_DamageFlg(void);
private: 
	//�������n��
	CHARABASE GetInitAll(const int MaxHp, const int DFlg);
	//�_���[�W���󂯂��ԓn��
	bool GetDamageFlg(void);
	//�\���̏�����
	CHARABASE GetInitCharaBase(void);
	//�ʂ̍\���̑��
	void SetCharaBase(const STATUS* S);
};