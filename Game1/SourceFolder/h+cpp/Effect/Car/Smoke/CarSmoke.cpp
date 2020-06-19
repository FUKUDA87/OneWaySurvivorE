#include "CarSmoke.h"
#include"../../../Draw3DBase/Draw3DManager/CarSmogManager.h"
#include"../../../GameSource/Judgment.h"
#include"../../3D/Smoke/Smoke.h"

bool c_CarSmoke::Update(const s_CarEffectUpdateData * updateData)
{
	if (m_Effect.size() > 0) {
		for (unsigned int ec = 0; ec < m_Effect.size(); ec++) {
			if (m_Effect[ec]->Update(updateData) != true)Delete(&ec);
		}
	}

	// ‰Œ‚ÌoŒ»
	float L_Per = (float)updateData->CharaBase.NowHp / (float)updateData->CharaBase.MaxHp;
	if (L_Per < 0.3f) {
		float L_Num = 30.0f;
		if (rand() % 100 < 20 + (int)(L_Num*0.3f - L_Num * L_Per)) {
			D3DXMATRIX TmpMat;
			C_CarSmogManager L_CarSmogManager;
			D3DXVECTOR3 Vec = L_CarSmogManager.GetPos(updateData->CarNo);
			Judg judg;
			judg.Set_TransMat(&TmpMat, &Vec);
			TmpMat = TmpMat * (updateData->Mat);
			S_Smog s = L_CarSmogManager.GetSmog(updateData->CarNo);
			if (L_Per < 0.3f)s.Draw_No = 53;
			if (L_Per < 0.2f)s.Draw_No = 50;
			if (L_Per < 0.1f)s.Draw_No = 47;
			m_Effect.push_back(new c_Smoke(&TmpMat, &s));
		}
	}

	return true;
}
