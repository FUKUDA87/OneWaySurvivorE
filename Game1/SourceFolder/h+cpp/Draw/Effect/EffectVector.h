#pragma once
#include<d3dx9.h>
#include"EffectBase.h"
#include<vector>

class c_EffectVector
{
public:
	~c_EffectVector();

	// 更新処理
	virtual bool Update(void);

	// 表示
	virtual void Draw3D(const D3DXVECTOR3 *CameraPos);

protected:
	std::vector<c_EffectBase*>m_Effect;

	// 削除
	void Delete(void);
	void Delete(unsigned int *count);
};