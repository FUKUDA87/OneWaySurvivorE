#pragma once
#include"Car_Pop_Base.h"

class C_Car_Pop_Update_1 :public C_Car_Pop_Base {
public:
	//�X�V����
	C_Car_Pop_Base *Update(const bool *Update_MoveFlg);
protected:
	//���̃t�F�[�Y��
	C_Car_Pop_Base *Next_Pop(void);

	//�Ԃ̃f�[�^�̏�����
	void New_All_Pop(void);
};