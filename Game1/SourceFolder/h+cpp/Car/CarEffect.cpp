#include "CarEffect.h"

C_CarEffect::~C_CarEffect()
{
	DeleteCarEffect();
}

void C_CarEffect::DrawCarEffect(void)
{
	if (m_EffectManager.size() < 1)return;

	for (auto && e : m_EffectManager)e->Draw3D();
}

bool C_CarEffect::UpdateCarEffect(void)
{
	return false;
}

void C_CarEffect::DeleteCarEffect(void)
{
	if (m_EffectManager.size() < 1)return;

	//‘S‚Äíœ
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

	//1‚Âíœ
	delete m_EffectManager[*count];
	m_EffectManager.erase(m_EffectManager.begin() + (*count));
	*count--;
}
