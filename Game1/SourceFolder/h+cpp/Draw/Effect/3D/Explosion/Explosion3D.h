#pragma once
#include<d3dx9.h>
#include"../../EffectBase.h"
#include"../../../../GameSource/Struct.h"
#include"../../../../GameSource/Countdown.h"

class c_Explosion3D:public c_EffectBase {
public:
	c_Explosion3D(const D3DXMATRIX *Mat);
	~c_Explosion3D();
	
	// �X�V����
	virtual bool Update(void);
	
	// �\��
	virtual void Draw3D(const D3DXVECTOR3 *CameraPos);

private:
	Pol expl;
	
	Cou *cou;
	void Init();
};