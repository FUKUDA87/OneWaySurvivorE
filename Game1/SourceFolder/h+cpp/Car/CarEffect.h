#pragma once
#include"CarBulletManager.h"
#include"../Effect/Car/EffectVectorCar.h"

/*
�G�t�F�N�g��Vector��
�폜
�ǉ�
�X�V
�\��
*/
/*
�Ԃ̃G�t�F�N�g�̗~�������
HP
�ړ��x�N�g��
�ʒu
*/

class C_CarEffect :public C_CarBulletManager
{
public:
	~C_CarEffect();
protected:

private:
	std::vector<c_EffectVectorCar*>m_EffectManager;// �G�t�F�N�g�̊Ǘ�

	// �\��
	void DrawCarEffect(void);

	// �X�V����
	bool UpdateCarEffect(void);

	// �폜
	void DeleteCarEffect(void);
	void DeleteCarEffect(unsigned int *count);
};