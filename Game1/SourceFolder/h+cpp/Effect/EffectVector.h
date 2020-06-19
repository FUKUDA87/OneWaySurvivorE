#pragma once
#include<d3dx9.h>
#include"EffectBase.h"
#include<vector>

class c_EffectVector
{
public:
	~c_EffectVector();

	// �X�V����
	virtual bool Update(void);

	// �\��
	virtual void Draw3D(const D3DXVECTOR3 *CameraPos);

protected:
	std::vector<c_EffectBase*>m_Effect;

	// �폜
	void Delete(void);
	void Delete(unsigned int *count);
};