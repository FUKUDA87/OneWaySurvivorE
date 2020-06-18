#pragma once
#include"CarBulletManager.h"
#include"../Effect/Car/EffectVectorCar.h"

/*
エフェクトのVector化
削除
追加
更新
表示
*/
/*
車のエフェクトの欲しい情報
HP
移動ベクトル
位置
*/

class C_CarEffect :public C_CarBulletManager
{
public:
	~C_CarEffect();
protected:

private:
	std::vector<c_EffectVectorCar*>m_EffectManager;// エフェクトの管理

	// 表示
	void DrawCarEffect(void);

	// 更新処理
	bool UpdateCarEffect(void);

	// 削除
	void DeleteCarEffect(void);
	void DeleteCarEffect(unsigned int *count);
};