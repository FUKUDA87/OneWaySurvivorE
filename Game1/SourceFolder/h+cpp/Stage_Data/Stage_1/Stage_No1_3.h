#pragma once
#include"Stage_No1_1.h"

class C_Stage_No1_3 :public C_Car_Pop_Update_1 {
public:
	C_Stage_No1_3();

	//�o�����Ă���Ԃ̂�����̏o�����̍쐬
	void M_Car_Pop_Update(std::vector<C_EnemyAi*>enemy);

protected:
	//���̎�
	C_Car_Pop_Base *Next_Pop(void);
private:

	//�{�X�̒n�ʔԍ�
	int M_BossWay_Number;

	//�{�X�ȊO�̃f�[�^�폜
	void M_EnemyCar_Delete(void);
};