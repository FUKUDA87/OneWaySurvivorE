#pragma once
#include"../EffectVectorCar.h"

class c_CarSmoke:public c_EffectVectorCar
{
public:
	// XVˆ—
	bool Update(const s_CarEffectUpdateData *updateData);
};