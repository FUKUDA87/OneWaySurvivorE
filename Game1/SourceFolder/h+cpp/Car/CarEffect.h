#pragma once
#include"CarBase.h"
#include"../Draw/Effect/Car/EffectVectorCar.h"
#include"../Draw/Effect/Car/Ball/Ball3DEffect.h"

class C_CarEffect:public C_CarBase
{
public:
	C_CarEffect();
	~C_CarEffect();

	// 表示
	void DrawCarEffect(const D3DXVECTOR3 *CameraPos);

	// 更新処理
	bool UpdateCarEffect(void);
protected:
	// 追加
	void NewEffect(c_EffectVectorCar *newEffect) { m_EffectManager.push_back(newEffect); }
	void NewEffect(c_EffectBase *newEffect) { m_Effect.push_back(newEffect); }
private:
	// エフェクトの管理
	std::vector<c_EffectVectorCar*>m_EffectManager;
	std::vector<c_EffectBase*>m_Effect;

	// 削除
	void DeleteCarEffect(void);
	void DeleteCarEffect(unsigned int *count);
	void DeleteEffect(void);
	void DeleteEffect(unsigned int *count);
};