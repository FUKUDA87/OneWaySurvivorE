#pragma once
#include<d3dx9.h>

class C_Gun_Parts_Category {
public:
	C_Gun_Parts_Category(const int *set_CategoryNo);

	//�X�V
	bool Update(void);

	//�e�����n��
	bool Get_Bullet_Shot_Flg(void);

	//���̃��[�g���n��
	int Get_NowRate(void) {
		return NowRate;
	}

	//���̃��[�g���ɓ����
	void Set_NowRate(const int *Rate) {
		NowRate = *Rate;
	}

	//�J�e�S���[���n��
	int Get_CategoryNo(void) {
		return CategoryNo;
	}

	//�����̓n��
	float Get_Move_f(void) {
		return Move_f;
	}

	//�����̓���
	void Set_Move_f(const float *Flg) {
		Move_f = *Flg;
	}

	//�����̓n��(0����~�A1�����쒆�A�Q�����슮��)
	int Get_MoveFlg(void) {
		return MoveFlg;
	}

	//�������n��
	bool Get_TriggerFlg(void) {
		return TriggerFlg;
	}

	//�������̓���
	void Set_TriggerFlg(const bool *Flg) {
		TriggerFlg = *Flg;
	}

protected:
	//���̃��[�g��
	int NowRate;

	//�J�e�S���[No
	int CategoryNo;

	//����Flg(0�ȉ�������,0�ȏオ����,1�ȏオ���슮��)
	float Move_f;

	//������Flg(0�������A1�����쒆�A�Q�����슮��)
	int MoveFlg;
	//������
	bool TriggerFlg;
private:
	//�J�e�S���[������
	void Set_CategoryNo(const int *No) {
		CategoryNo = *No;
	}

	//������
	void Init_C_Gun_Parts_Category(void);

	//�����̔���
	void Judg_MoveFlg(void);

	//������Flg�̓���
	void Set_MoveFlg(const int Flg) {
		MoveFlg = Flg;
	}
};