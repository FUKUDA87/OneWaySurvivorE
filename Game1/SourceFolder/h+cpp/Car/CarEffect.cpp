#include "CarEffect.h"
#include"../Draw/Effect/Car/Smoke/CarSmoke.h"

C_CarEffect::C_CarEffect()
{
	m_EffectManager.push_back(new c_CarSmoke());
}

C_CarEffect::~C_CarEffect()
{
	DeleteCarEffect();
	DeleteEffect();
}

void C_CarEffect::DrawCarEffect(const D3DXVECTOR3 *CameraPos)
{
	if (m_EffectManager.size() > 0)
	{
		for (auto && e : m_EffectManager)e->Draw3D(CameraPos);
	}

	if (m_Effect.size() > 0)
	{
		for (auto && e : m_Effect)e->Draw3D(CameraPos);
	}
}

bool C_CarEffect::UpdateCarEffect(void)
{
	// 更新に必要な情報作成
	s_CarEffectUpdateData updateData;
	updateData.CharaBase = CharaBase;
	updateData.CarNo = BodyData.CarBodyNo;
	updateData.Mat = Car.Base.Mat;
	updateData.MoveVec = brj.MoveVec;
	updateData.ScalMat = Car.Base.Scal;
	updateData.Scal = Car.Base.ScaPos;

	// 更新
	if (m_EffectManager.size() > 0)
	{
		for (unsigned int ec = 0; ec < m_EffectManager.size(); ec++) {
			if (m_EffectManager[ec]->Update(&updateData) != true) {
				DeleteCarEffect(&ec);
			}
		}
	}

	if (m_Effect.size() > 0)
	{
		for (unsigned int ec = 0; ec < m_Effect.size(); ec++) {
			if (m_Effect[ec]->Update(&updateData) != true) {
				DeleteEffect(&ec);
			}
		}
	}

	return true;
}

void C_CarEffect::DeleteCarEffect(void)
{
	if (m_EffectManager.size() < 1)return;

	//全て削除
	for (unsigned int ec = 0; ec < m_EffectManager.size(); ec++) {
		delete m_EffectManager[ec];
		m_EffectManager.erase(m_EffectManager.begin() + (ec));
		ec--;
	}
}

void C_CarEffect::DeleteCarEffect(unsigned int * count)
{
	if (m_EffectManager.size() < 1)return;
	if ((*count < 0) || (*count > m_EffectManager.size()))return;

	//1つ削除
	delete m_EffectManager[*count];
	m_EffectManager.erase(m_EffectManager.begin() + (*count));
	*count--;
}

void C_CarEffect::DeleteEffect(void)
{
	if (m_Effect.size() <= 0)return;

	//全て削除
	for (unsigned int ec = 0; ec < m_Effect.size(); ec++) {
		delete m_Effect[ec];
		m_Effect.erase(m_Effect.begin() + (ec));
		ec--;
	}
}

void C_CarEffect::DeleteEffect(unsigned int * count)
{
	if (m_Effect.size() < 1)return;
	if ((*count < 0) || (*count > m_Effect.size()))return;

	//1つ削除
	delete m_EffectManager[*count];
	m_Effect.erase(m_Effect.begin() + (*count));
	*count--;
}
