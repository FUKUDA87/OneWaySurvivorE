#pragma once
#include"CarBase.h"
#include"../Draw/Effect/Car/EffectVectorCar.h"

class C_CarEffect:public C_CarBase
{
public:
	C_CarEffect();
	~C_CarEffect();

	// 表示
	void DrawCarEffect(const D3DXVECTOR3 *CameraPos);

	// 更新処理
	bool UpdateCarEffect(void);

private:
	std::vector<c_EffectVectorCar*>m_EffectManager;// エフェクトの管理

	// 削除
	void DeleteCarEffect(void);
	void DeleteCarEffect(unsigned int *count);
};