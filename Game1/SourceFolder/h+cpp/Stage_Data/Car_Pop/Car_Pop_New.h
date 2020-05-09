#pragma once
#include"Car_Pop_Base.h"

class C_Car_Pop_New {
public:
	C_Car_Pop_New(const int *StageNo);
	~C_Car_Pop_New();

	//�X�V����
	bool Update(const bool *MoveFlg);

	//�Ԃ̏o���̏��n��
	S_CAR_INIT_DATA Get_Next_Car_Data_N(void);

	//�X�e�[�W�̍\�����n��
	S_NOW_WAVE_DATA Get_Now_Wave_Data_N(void);

	//�Ԃ̏o���\�n��
	bool Get_Car_Pop_Flg_N(void);

	//�Ԃ��o���������ɂ��鏈��
	void Car_Init_Rear_N(void);

	//���̓G���̎擾
	void Set_Now_Enemy_Num_N(const int * Enemy_Num);

	//�N���X���ύX�����m�F
	bool Get_Change_Class_EndFlg(void) {
		return Change_Class_EndFlg;
	}

	//�n�ʏ�� 
	int Get_GroundNo(void);

	//�o�����Ă���Ԃ̂�����̏o�����̍쐬
	void M_Car_Pop_Update_N(std::vector<C_EnemyAi*>enemy);


protected:
	C_Car_Pop_Base* M_C_Car_Pop_Base;

	//�N���X���ς��������Flg
	bool Change_Class_EndFlg;
private:

};