#pragma once
#include<d3dx9.h>

class c_EffectBase
{
public:
	// 更新処理
	virtual bool Update(void) { return false; };

	// 表示
	virtual void Draw3D(void) {};
};