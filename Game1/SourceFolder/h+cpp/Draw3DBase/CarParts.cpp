#include "CarParts.h"
#include"../Draw/Tire/Car_Tire_No1.h"
#include"../Draw/Stand/Stand_No1.h"
#include"../Draw/Tire/Tire_DrawManager.h"
#include"../Draw/Door/Door_DrawManager.h"
#include"../Draw/Stand/Stand_DrawManager.h"

C_CarParts::~C_CarParts()
{
	Delete_ALL_Parts();
}

void C_CarParts::Draw_Car_Parts(const D3DXVECTOR3 * CameraPos)
{
	if (M_Car_Parts.size() < 1)return;

	for (auto && p : M_Car_Parts) {
		p->Draw_Parts(CameraPos);
	}
}

bool C_CarParts::Update_Car_Parts(void)
{
	if (M_Car_Parts.size() < 1)return false;

	Judg judg_a;

	D3DXVECTOR3 ScalPos;
	for (auto && p : M_Car_Parts) {

		ScalPos = Get_Car_Parts_Size(&Get_Data_No(p->Get_Parts_Data().MeshTypeNo, p->Get_Parts_Data().MeshJointNo));

		p->UpdateParts(&GetMatCar(), &Car.Con.NowSpeed,&Car.Con.MaxSpeed,&Car.Base.ScaPos,&ScalPos);
	}
	return true;
}

void C_CarParts::Delete_Parts(unsigned int * PartsNo)
{
	if (M_Car_Parts.size() < 1)return;

	unsigned int i = M_Car_Parts.size();
	if (judg.Hit_No(PartsNo, &i) != true)return;

	delete M_Car_Parts[*PartsNo];
	M_Car_Parts.erase(M_Car_Parts.begin() + (*PartsNo));
	*PartsNo -= 1;
}

D3DXMATRIX C_CarParts::Get_Camera_Mat(void)
{
	D3DXMATRIX Mat = GetMatCar();
	D3DXMATRIX tMat;
	D3DXMatrixTranslation(&tMat, 0.0f, 0.2f, 0.0f);
	Mat = tMat * Mat;

	if (M_Data.size() < 1)return Mat;

	for (unsigned int d = 0; d < M_Data.size(); d++) {
		if (M_Data[d]->MeshTypeNo == Co_Parts_Gun) {
			D3DXMATRIX TmpMat;
			Judg judg_a;
			judg_a.SetTransMat(&TmpMat, &M_Data[d]->TransPos);
			Mat = TmpMat * Mat;
			break;
		}
	}

	return Mat;
}

int C_CarParts::Get_Parts_Draw_Draw_JudgFlg(const unsigned int * M_Car_PartsNo)
{
	if ((M_Car_Parts.size() < 1) || (*M_Car_PartsNo < 0) || (*M_Car_PartsNo >= M_Car_Parts.size()))return 0;
	return M_Car_Parts[*M_Car_PartsNo]->Get_Draw_Draw_JudgFlg();
}

D3DXVECTOR3 C_CarParts::Get_Parts_Draw_Pol_Pos(const unsigned int * M_Car_PartsNo, const int * PosNo)
{
	if ((M_Car_Parts.size() < 1) || (*M_Car_PartsNo < 0) || (*M_Car_PartsNo >= M_Car_Parts.size()))return D3DXVECTOR3(0.0f,0.0f,0.0f);
	return M_Car_Parts[*M_Car_PartsNo]->Get_Draw_Pol_Pos(PosNo);
}

LPD3DXMESH C_CarParts::Get_Parts_Draw_Mesh(const unsigned int * M_Car_PartsNo)
{
	return M_Car_Parts[*M_Car_PartsNo]->Get_Draw_Mesh();
}

bool C_CarParts::Get_Parts_Draw_Iden_Flg(const unsigned int * M_Car_PartsNo)
{
	if ((M_Car_Parts.size() < 1) || (*M_Car_PartsNo < 0) || (*M_Car_PartsNo >= M_Car_Parts.size()))return false;
	return M_Car_Parts[*M_Car_PartsNo]->Get_Draw_Iden_Flg();
}

D3DXMATRIX C_CarParts::Get_Parts_Draw_DrawMat(const unsigned int * M_Car_PartsNo)
{
	return M_Car_Parts[*M_Car_PartsNo]->Get_Draw_DrawMat();
}

void C_CarParts::Damage_CarParts(const unsigned int * M_CarPartsNo, const int * Damage)
{
	M_Car_Parts[*M_CarPartsNo]->HpDamage(Damage);

	int Flg = M_Car_Parts[*M_CarPartsNo]->Get_Parst_DamageSet_Flg();
	if (Flg <= 0)return;

	HpDamage(&Flg, Damage);
}

float C_CarParts::Get_Parts_Draw_Dis(const unsigned int * M_Car_PartsNo)
{
	if ((M_Car_Parts.size() < 1) || (*M_Car_PartsNo < 0) || (*M_Car_PartsNo >= M_Car_Parts.size()))return 0.0f;
	return M_Car_Parts[*M_Car_PartsNo]->Get_Draw_Dis();
}


void C_CarParts::New_CarParts(const BODYDATA * CarData)
{
	Delete_ALL_Parts();

	C_Tire_DrawManager Tire_Manager;
	C_Door_DrawManager Door_Manager;
	C_Stand_DrawManager Stand_Manager;


	//部位にパーツのセット
	/*
	※jointNoがマイナスの時は動きをリバース
	*/
	for (unsigned int d = 0; d < M_Data.size(); d++) {
		if (M_Data[d]->MeshTypeNo == Co_Parts_Tire)M_Car_Parts.push_back(Tire_Manager.Get_Draw_Tire(&CarData->TireNo,M_Data[d]));
		if(M_Data[d]->MeshTypeNo == Co_Parts_Gun)M_Car_Parts.push_back(Stand_Manager.Get_Draw_Stop(&CarData->StandNo, M_Data[d]));
		float Ang = 135.0f;
		if (M_Data[d]->MeshTypeNo == Co_Parts_Door)M_Car_Parts.push_back(Door_Manager.Get_Draw_Door(&CarData->TireNo, M_Data[d],&Ang));
	}


}

void C_CarParts::New_CarParts(std::vector<C_Parts_Set_Data*> M_Set_Data)
{
	Delete_ALL_Parts();

	C_Tire_DrawManager Tire_Manager;
	C_Door_DrawManager Door_Manager;
	C_Stand_DrawManager Stand_Manager;


	//部位にパーツのセット
	/*
	※jointNoがマイナスの時は動きをリバース
	*/

	if ((M_Data.size() < 1) || (M_Set_Data.size() < 1))return;

	for (auto && d : M_Data) {
		for (auto && s : M_Set_Data) {

			int JointNo = d->MeshJointNo;
			if (JointNo < 0)JointNo *= -1;

			if ((d->MeshTypeNo == s->Get_Data().MeshTypeNo) && (JointNo == s->Get_Data().MeshJointNo)) {

				int DrawNo = s->Get_Data().DrawNo;
				float Ang = 135.0f;

				switch (d->MeshTypeNo)
				{
				//タイヤ
				case Co_Parts_Tire:
					M_Car_Parts.push_back(Tire_Manager.Get_Draw_Tire(&DrawNo, d));
					break;
				//スタンド
				case Co_Parts_Gun:
					M_Car_Parts.push_back(Stand_Manager.Get_Draw_Stop(&DrawNo,d));
					break;
				//ドア
				case Co_Parts_Door:
					M_Car_Parts.push_back(Door_Manager.Get_Draw_Door(&DrawNo, d, &Ang));
					break;

				default:
					break;
				}

			}
		}
	}
}

S_CAR_PARTS_DATA* C_CarParts::Get_Data_CarParts(const int * TypeNo, const int JointNo)
{
	for (auto && d : M_Data) {
		int L_JointNo = d->MeshJointNo;
		if (L_JointNo < 0)L_JointNo *= -1;
		if ((d->MeshTypeNo == *TypeNo) && (L_JointNo == JointNo))return d;
	}

	return nullptr;
}

void C_CarParts::New_Car_Parts_Data(const int * CarNo, const bool * SaveFlg)
{
	Delete_ALL_Data();

	C_CarDataManager Manager;

	int PartsNum = Manager.GetDrawNum(*CarNo, *SaveFlg);

	for (int i = 0; i < PartsNum; i++) {
		Set_Data(&Manager.GetDrawSet(*CarNo, &i, SaveFlg));
	}
}

void C_CarParts::New_Set_Car_Parts(const BODYDATA * CarData, const bool * SaveFlg, const bool *Data_DeleteFlg)
{
	New_Car_Parts_Data(&CarData->CarBodyNo, SaveFlg);

	New_CarParts(CarData);

	if (*Data_DeleteFlg == true)Delete_ALL_Data();
}

void C_CarParts::New_Set_Car_Parts(const int * CarNo, std::vector<C_Parts_Set_Data*> M_Set_Data, const bool * SaveFlg, const bool * Data_DeleteFlg)
{
	New_Car_Parts_Data(CarNo, SaveFlg);

	New_CarParts(M_Set_Data);

	if (*Data_DeleteFlg == true)Delete_ALL_Data();
}

void C_CarParts::Delete_ALL_Parts(void)
{
	if (M_Car_Parts.size() < 1)return;

	for (unsigned int p = 0; p < M_Car_Parts.size(); p++) {
		delete M_Car_Parts[p];
		M_Car_Parts.erase(M_Car_Parts.begin() + p);
		p--;
	}
}

