#pragma once
#include"../EffectVector.h"
#include"../../GameSource/Struct.h"

class c_EffectVectorCar :public c_EffectVector
{
public:
	// �X�V����
	virtual bool Update(const s_CarEffectUpdateData *updateData);
};