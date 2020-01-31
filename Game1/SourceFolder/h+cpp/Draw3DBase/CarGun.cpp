#include "CarGun.h"
#include"../Gun/GunDraw/GunMove/GunMove_A_Manager_1.h"
#include"../Const/Const_PartsTypeNo.h"
#include"../Gun/GunDraw/Gun_Type/Gun_Gatling_1.h"
#include"../Gun/GunDraw/Gun_Draw_Manager.h"

C_CarGun::C_CarGun()
{
	
}

C_CarGun::~C_CarGun()
{
	AllDelete_Gun();
}

void C_CarGun::Draw_Gun(const D3DXVECTOR3 * CameraPos)
{
	if (M_Gun.size() < 1)return;

	for (unsigned int g = 0; g < M_Gun.size(); g++) {
		M_Gun[g]->Draw(CameraPos);
	}
}

void C_CarGun::Update_Gun(void)
{
	if (M_Gun.size() < 1)return;

	for (unsigned int g = 0; g < M_Gun.size(); g++) {
		M_S_Gun_Update_Data.StandMat = Get_Joint_Mat();
		M_Gun[g]->Set_ScalPos(&Car.Base.ScaPos);
		M_Gun[g]->Update(&M_S_Gun_Update_Data);
	}
}

C_GunMoveBase_A * C_CarGun::Get_GunMove(const int * MoveNo)
{
	C_GunMove_A_Manager_Base *Manager;
	Manager = new C_GunMove_A_Manager_1();

	return Manager->Get_GunMove_A(MoveNo);
}

void C_CarGun::Set_GunMove_Player(const unsigned int * GunNo)
{
	if (Judg_GunNo(GunNo) != true)return;

	if (M_Gun[*GunNo]->Get_S_GUN_DATA().PlayerFlg != false)return;

	int i = 1;
	M_Gun[*GunNo]->New_GunMove(Get_GunMove(&i));

}

void C_CarGun::New_Set_Car_Parts(const BODYDATA * CarData, const bool * SaveFlg, const bool *Data_DeleteFlg)
{
	New_CarParts(CarData, SaveFlg);

	New_Car_Parts_Gun(CarData);

	if(*Data_DeleteFlg==true)Delete_ALL_Data();
}

void C_CarGun::New_Car_Parts_Gun(const BODYDATA * CarData)
{
	if (M_Data.size() < 1)return;

	C_Gun_Darw_Manager Manager;

	for (unsigned int d = 0; d < M_Data.size(); d++) {
		if (M_Data[d]->MeshTypeNo == Co_Parts_Gun)M_Gun.push_back(Manager.Get_Gun_Stop(&CarData->GunNo));
	}
}

void C_CarGun::Delete_Gun(unsigned int * GunNo)
{
	if (M_Gun.size() < 1)return;
	unsigned int No = *GunNo;
	if ((No < 0) || (No >= M_Gun.size()))return;

	delete M_Gun[No];
	M_Gun.erase(M_Gun.begin() + No);
	No--;
	*GunNo = No;

	return;
}

bool C_CarGun::Judg_GunNo(const unsigned int * GunNo)
{
	if (M_Gun.size() < 1)return false;

	if (*GunNo < 0)return false;
	if (*GunNo >= M_Gun.size())return false;

	return true;
}

void C_CarGun::Set_Gun_Trigger(const unsigned int * GunNo, const bool * TriggerFlg)
{
	if (*GunNo < 0)return;

	if (*GunNo >= M_Gun.size())return;

	M_Gun[*GunNo]->Update_Trigger(TriggerFlg);
}

D3DXMATRIX C_CarGun::Get_Joint_Mat(void)
{
	D3DXMATRIX Mat=GetMatCar();

	if (M_Car_Parts.size() < 1)return Mat;

	for (unsigned int p = 0; p < M_Car_Parts.size(); p++){
		if (M_Car_Parts[p]->Get_Parts_Data().MeshTypeNo == Co_Parts_Gun) {
			Mat = M_Car_Parts[p]->Get_Draw_Mat();
			if (M_Car_Parts[p]->Get_Juint_Data_Num() > 0) {
				for (unsigned int d = 0; d < M_Car_Parts[p]->Get_Juint_Data_Num(); d++) {
					D3DXMATRIX TmpMat;
					Judg judg_a;
					D3DXVECTOR3 Vec= M_Car_Parts[p]->Get_Joint_Data(&d).TransPos;
					Vec = judg_a.GetVecVec(&M_Car_Parts[p]->Get_Draw_ScalPos(), &Vec);
					judg_a.SetTransMat(&TmpMat,&Vec);
					Mat = TmpMat * Mat;
					return Mat;
				}
			}
		}
	}

	return Mat;
}

S_GUN_DATA C_CarGun::Get_Gun_Data(const unsigned int * DrawGunNo)
{
	return M_Gun[*DrawGunNo]->Get_S_GUN_DATA();
}

int C_CarGun::Get_Gun_Draw_Parts_Draw_JudgFlg(const unsigned int * M_GunNo, const unsigned int * PartsNo)
{
	if ((M_Gun.size() < 1) || (*M_GunNo < 0) || (*M_GunNo >= M_Gun.size()))return 0;
	return M_Gun[*M_GunNo]->Get_Draw_Parts_Draw_JudgFlg(PartsNo);
}

D3DXVECTOR3 C_CarGun::Get_Gun_Draw_Parts_Pol_Pos(const unsigned int * M_GunNo, const unsigned int * PartsNo, const int * PolNo)
{
	if ((M_Gun.size() < 1) || (*M_GunNo < 0) || (*M_GunNo >= M_Gun.size()))return D3DXVECTOR3(0.0f,0.0f,0.0f);
	return M_Gun[*M_GunNo]->Get_Draw_Parts_Pol_Pos(PartsNo,PolNo);
}

LPD3DXMESH C_CarGun::Get_Gun_Draw_Parts_Mesh(const unsigned int * M_GunNo, const unsigned int * PartsNo)
{
	//if ((M_Gun.size() < 1) || (*M_GunNo < 0) || (*M_GunNo >= M_Gun.size()))return false;
	return M_Gun[*M_GunNo]->Get_Draw_Parts_Mesh(PartsNo);
}

bool C_CarGun::Get_Gun_Draw_Parts_Iden_Flg(const unsigned int * M_GunNo, const unsigned int * PartsNo)
{
	if ((M_Gun.size() < 1) || (*M_GunNo < 0) || (*M_GunNo >= M_Gun.size()))return false;
	return M_Gun[*M_GunNo]->Get_Draw_Parts_Iden_Flg(PartsNo);
}

D3DXMATRIX C_CarGun::Get_Gun_Draw_Parts_Draw_Mat(const unsigned int * M_GunNo, const unsigned int * PartsNo)
{
	//if ((M_Gun.size() < 1) || (*M_GunNo < 0) || (*M_GunNo >= M_Gun.size()))return false;
	return M_Gun[*M_GunNo]->Get_Draw_Parts_Draw_Mat(PartsNo);
}

void C_CarGun::Damage_Gun(const unsigned int * M_GunNo, const int * Damage)
{
	M_Gun[*M_GunNo]->HpDamage(Damage);
}

bool C_CarGun::Ray_Judg_Gun_Flg(const unsigned int * M_GunNo)
{
	if ((M_Gun.size() < 1) || (*M_GunNo < 0) || (*M_GunNo >= M_Gun.size()))return false;
	Judg L_judg;
	bool Flg = M_Gun[*M_GunNo]->Dead();
	return L_judg.ReverseFlg2(&Flg);
}

void C_CarGun::AllDelete_Gun(void)
{
	if (M_Gun.size() < 1)return;

	for (unsigned int g = 0; g < M_Gun.size(); g++) {
		Delete_Gun(&g);
	}
}
