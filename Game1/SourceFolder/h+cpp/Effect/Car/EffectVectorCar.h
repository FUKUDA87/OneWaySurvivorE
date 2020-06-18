#pragma once
#include"../EffectVector.h"
#include"../../GameSource/Struct.h"

class c_EffectVectorCar :public c_EffectVector
{
public:
	virtual bool Update(const s_CarEffectUpdateData *updateData) { return false; };
};