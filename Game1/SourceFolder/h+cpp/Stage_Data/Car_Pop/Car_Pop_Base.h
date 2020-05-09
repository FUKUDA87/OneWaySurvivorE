#pragma once
#include<d3dx9.h>
#include"../../GameSource/Struct.h"
#include"Car_Pop_Data.h"
#include<vector>
#include"../../GameSource/Const.h"
#include"../../Const/Const_Wave_Type.h"
#include"../../Const/Const_Rail_Type.h"
#include"../../Enemy/EnemyAi.h"

class C_Car_Pop_Base {
public:
	C_Car_Pop_Base();
	~C_Car_Pop_Base();

	//�X�V����
	virtual C_Car_Pop_Base *Update(const bool *Update_MoveFlg)=0;

	//�o�����Ă���Ԃ̂�����̏o�����̍쐬
	virtual void M_Car_Pop_Update(std::vector<C_EnemyAi*>enemy) {};

	//�n�ʏ�� 
	virtual int Get_GroundNo(void) {
		return M_Ground_Type;
	}

	//�Ԃ̏o���̏��n��
	S_CAR_INIT_DATA Get_Next_Car_Data(void);

	//�Ԃ̏o���\�n��
	bool Get_Car_Pop_Flg(void);

	//�Ԃ��o���������ɂ��鏈��
	void Car_Init_Rear(void);

	//�X�e�[�W�̍\�����n��
	S_NOW_WAVE_DATA Get_Stage_Phase_Data(void) {
		return M_Stage_Data;
	}

	//���̓G���̎擾
	void Set_Now_Enemy_Num(const int * Enemy_Num) {
		M_Stage_Data.Enemy_Alive_Num = *Enemy_Num;
	}
protected:
	//���̃t�F�[�Y��
	virtual C_Car_Pop_Base *Next_Pop(void) = 0;

	//�Ԃ̏��̒ǉ�
	void New_Car_Data(const int CarType, const int CarNo, const int Count, const unsigned int GroundNo, const int WayNo);
	void New_Car_Data(const int CarType, const int CarNo, const int Count, const unsigned int GroundNo);

	//�������Ԃ̃J�E���g�_�E��
	bool Update_Car_Count(void);

	//�Ԃ̃f�[�^�̏�����
	virtual void New_All_Pop(void)=0;

	//�Ō�̎Ԃ��o����Flg
	bool M_Car_Pop_EndFlg;

	unsigned int Get_Pop_Data_Num(void) {
		return M_Car_Data.size();
	}

	//�X�e�[�W�̃f�[�^
	S_NOW_WAVE_DATA M_Stage_Data;

	//�Ԃ̏o���\
	bool M_Car_Pop_Flg;

	//���������n�ʂ̃^�C�v
	int M_Ground_Type;

	//�Ԃ̃f�[�^
	std::vector<C_Car_Pop_Data*>M_Car_Data;

private:
	//�S�폜
	void Delete_All_Car(void);

	//�Ԃ̔ԍ�
	const unsigned int Car_PopNo;

	//�X�e�[�W�̏��̏�����
	void Init_Stage_Data(void);
};