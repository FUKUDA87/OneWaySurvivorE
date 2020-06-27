#include "EffectVector.h"

c_EffectVector::~c_EffectVector()
{
	Delete();
}

bool c_EffectVector::Update(void)
{
	if (m_Effect.size() < 1)return false;

	for (unsigned int ec = 0; ec < m_Effect.size(); ec++) {
		if (m_Effect[ec]->Update() != true)Delete(&ec);
	}

	return true;
}

void c_EffectVector::Draw3D(const D3DXVECTOR3 *CameraPos)
{
	if (m_Effect.size() < 1)return;

	for (auto && e : m_Effect)e->Draw3D(CameraPos);
}

void c_EffectVector::Delete(void)
{
	if (m_Effect.size() < 1)return;

	//ëSÇƒçÌèú
	for (unsigned int ec = 0; ec < m_Effect.size(); ec++) {
		delete m_Effect[ec];
		m_Effect.erase(m_Effect.begin() + (ec));
		ec--;
	}
}

void c_EffectVector::Delete(unsigned int * count)
{
	if (m_Effect.size() < 1)return;
	if ((*count < 0) || (*count > m_Effect.size()))return;

	//1Ç¬çÌèú
	delete m_Effect[*count];
	m_Effect.erase(m_Effect.begin() + (*count));
	*count--;
}
