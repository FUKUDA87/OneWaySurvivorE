#pragma once
#include<d3dx9.h>

class c_EffectBase
{
public:
	// �X�V����
	virtual bool Update(void) { return false; };

	// �\��
	virtual void Draw3D(void) {};
};