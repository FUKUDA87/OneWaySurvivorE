#include "EffectVectorCar.h"

bool c_EffectVectorCar::Update(const s_CarEffectUpdateData * updateData)
{
	if (m_Effect.size() < 1)return false;

	for (unsigned int ec = 0; ec < m_Effect.size(); ec++) {
		if (m_Effect[ec]->Update(updateData) != true)Delete(&ec);
	}

	return true;
}
