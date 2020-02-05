#pragma once
#include"Ground_Pop_Base.h"

class C_Ground_Pop_New {
public:
	C_Ground_Pop_New();
	C_Ground_Pop_New(const int GroundNo);
	C_Ground_Pop_New(C_Ground_Pop_Base* Pop);
	~C_Ground_Pop_New();

	//���n��
	S_GROUND_INIT_DATA Get_Pop_Data_N(void);
	//�o����̏���
	void Ground_Pop_Rear_N(void);

	//�V�K
	void New_Pop(C_Ground_Pop_Base* Pop);
	void New_Pop(const int *GroundNo);

	//�n�ʔԍ��̎擾
	int Get_GroundNo(void) {
		return M_GroundNo;
	}

protected:

	//�폜
	void Delete_C_Ground_Pop(void);

private:
	C_Ground_Pop_Base* M_C_Ground_Pop;

	//�n�ʔԍ�
	int M_GroundNo;

	//������
	void Init(void);
};