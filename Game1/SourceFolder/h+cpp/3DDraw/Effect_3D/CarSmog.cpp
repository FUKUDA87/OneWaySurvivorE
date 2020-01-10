#include "CarSmog.h"
#include"../../Draw3DBase/Draw3DManager/CarSmogManager.h"
#include"../../GameSource/Judgment.h"

C_SmokeCar::C_SmokeCar()
{
}

C_SmokeCar::~C_SmokeCar()
{
	AllDelete_Smoke();
}

bool C_SmokeCar::Update_CS(const CHARABASE* CharaBase,const int *CarNo,const D3DXMATRIX *CarMat,const D3DXVECTOR3* CarMoveVec)
{
	//
	float L_Per = (float)CharaBase->NowHp / (float)CharaBase->MaxHp;
	if (L_Per < 0.3f) {
		float L_Num = 30.0f;
		if (rand() % 100 < 20 + (int)(L_Num*0.3f - L_Num * L_Per)) {
			D3DXMATRIX TmpMat;
			C_CarSmogManager L_CarSmogManager;
			D3DXVECTOR3 Vec = L_CarSmogManager.GetPos(*CarNo);
			Judg judg;
			judg.SetTransMat(&TmpMat, &Vec);
			TmpMat = TmpMat * (*CarMat);
			S_Smog s = L_CarSmogManager.GetSmog(*CarNo);
			if (L_Per < 0.3f)s.Draw_No = 53;
			if (L_Per < 0.2f)s.Draw_No = 50;
			if (L_Per < 0.1f)s.Draw_No = 47;
			M_C_Smoke.push_back(new C_Smog(&TmpMat, &s));
		}
	}

	if (M_C_Smoke.size() <= 0) return false;

	//スモッグのアップデート
	for (unsigned int s = 0; s < M_C_Smoke.size(); s++) {
		if (CharaBase->NowHp >0) {
			M_C_Smoke[s]->PosMoveVec(CarMoveVec);
		}

		if (M_C_Smoke[s]->Update() == false) {
			delete M_C_Smoke[s];
			M_C_Smoke.erase(M_C_Smoke.begin() + s);
			s--;
		}
	}

	return true;
}

void C_SmokeCar::Draw3D_CS(const D3DXVECTOR3 *CamPos)
{
	if (M_C_Smoke.size() < 1)return;

	for (unsigned int s = 0; s < M_C_Smoke.size(); s++) {
		M_C_Smoke[s]->Draw3D(*CamPos);
	}
}

void C_SmokeCar::AllDelete_Smoke(void)
{
	if (M_C_Smoke.size() < 1)return;

	for (unsigned int s = 0; s < M_C_Smoke.size(); s++) {
		delete M_C_Smoke[s];
		M_C_Smoke.erase(M_C_Smoke.begin() + s);
		s--;
	}
}
