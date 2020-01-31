#include "CarParts.h"
#include"../Data/MeshData/StandMesh/Stand_Data_Manager.h"
#include"../Draw/Tire/Car_Tire_No1.h"
#include"../Draw/Stand/Stand_No1.h"
#include"../Draw/Tire/Tire_DrawManager.h"
#include"../Draw/Door/Door_DrawManager.h"

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

	for (auto && p : M_Car_Parts) {
		p->UpdateParts(&GetMatCar(), &Car.Con.NowSpeed,&Car.Con.MaxSpeed,&Car.Base.ScaPos);
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

void C_CarParts::New_CarParts(const BODYDATA * CarData, const bool * SaveFlg)
{
	Delete_ALL_Data();

	C_CarDataManager Manager;

	int PartsNum = Manager.GetDrawNum(CarData->CarBodyNo, *SaveFlg);

	for (int i = 0; i < PartsNum; i++) {
		Set_Data(&Manager.GetDrawSet(CarData->CarBodyNo, &i, SaveFlg));
	}

	C_Tire_DrawManager Tire_Manager;
	C_Door_DrawManager Door_Manager;


	//部位にパーツのセット
	/*
	※jointNoがマイナスの時は動きをリバース
	*/
	for (unsigned int d = 0; d < M_Data.size(); d++) {
		if (M_Data[d]->MeshTypeNo == Co_Parts_Tire)M_Car_Parts.push_back(Tire_Manager.Get_Draw_Tire(&CarData->TireNo,M_Data[d]));
		if(M_Data[d]->MeshTypeNo == Co_Parts_Gun)M_Car_Parts.push_back(new C_Stand_No1(M_Data[d]));
		float Ang = 135.0f;
		if (M_Data[d]->MeshTypeNo == Co_Parts_Door)M_Car_Parts.push_back(Door_Manager.Get_Draw_Door(&CarData->TireNo, M_Data[d],&Ang));
	}


}

void C_CarParts::New_Set_Car_Parts(const BODYDATA * CarData, const bool * SaveFlg, const bool *Data_DeleteFlg)
{
	New_CarParts(CarData, SaveFlg);

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

