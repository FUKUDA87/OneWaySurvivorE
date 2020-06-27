#pragma once
#include"CarBase.h"
#include"../Draw/Effect/Car/EffectVectorCar.h"

class C_CarEffect:public C_CarBase
{
public:
	C_CarEffect();
	~C_CarEffect();

	// �\��
	void DrawCarEffect(const D3DXVECTOR3 *CameraPos);

	// �X�V����
	bool UpdateCarEffect(void);

private:
	std::vector<c_EffectVectorCar*>m_EffectManager;// �G�t�F�N�g�̊Ǘ�

	// �폜
	void DeleteCarEffect(void);
	void DeleteCarEffect(unsigned int *count);
};