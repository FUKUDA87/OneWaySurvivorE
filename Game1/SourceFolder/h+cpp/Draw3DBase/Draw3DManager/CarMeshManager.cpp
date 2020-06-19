#include "CarMeshManager.h"
#include"../../MaterialManager/XfileManager.h"

extern XFileManager xfileManager;

XFILE3 C_CarMeshManager::GetMesh(int MeshNo)
{
	//検索
	if (GetMeshJudg(MeshNo) == false) {
		//検索失敗用
		sprintf_s(MeshName[0], sizeof(MeshName[0]), "car1.x");
		sprintf_s(MeshName[1], sizeof(MeshName[1]), "PlayerCar1CM3.x");
		sprintf_s(MeshName[2], sizeof(MeshName[2]), "Car_No1_Dead.x");
	}

	//メッシュのロード
	XFILE3 Mesh;
	Mesh.Mesh1 = xfileManager.GetMesh(MeshName[0]);
	Mesh.Mesh2 = xfileManager.GetMesh(MeshName[1]);
	Mesh.Mesh3 = xfileManager.GetMesh(MeshName[2]);

	return Mesh;
}

bool C_CarMeshManager::GetMeshJudg(int MeshNo)
{
	//検索
	//プレイヤー
	if (GetCar1(MeshNo) == true)return true;
	if (GetCar2(MeshNo) == true)return true;
	//敵
	if (GetCar101(MeshNo) == true)return true;
	//ボス
	if (GetCar201(MeshNo) == true)return true;
	return false;
}

bool C_CarMeshManager::GetCar1(int MeshNo)
{
	if (MeshNo != CarNo1)return false;
	sprintf_s(MeshName[0], sizeof(MeshName[0]), "car1.x");
	sprintf_s(MeshName[1], sizeof(MeshName[1]), "PlayerCar1CM3.x");
	sprintf_s(MeshName[2], sizeof(MeshName[2]), "Car_No1_Dead.x");
	return true;
}

bool C_CarMeshManager::GetCar2(int MeshNo)
{
	if (MeshNo != CarNo2)return false;
	sprintf_s(MeshName[0], sizeof(MeshName[0]), "Car3.x");
	sprintf_s(MeshName[1], sizeof(MeshName[1]), "Car3CM1.x");
	sprintf_s(MeshName[2], sizeof(MeshName[2]), "Car3.x");
	return true;
}

bool C_CarMeshManager::GetCar101(int MeshNo)
{
	if (MeshNo != CarNo101)return false;
	sprintf_s(MeshName[0], sizeof(MeshName[0]), "EnemyCar2.x");
	sprintf_s(MeshName[1], sizeof(MeshName[1]), "EnemyCar1CM2.x");
	sprintf_s(MeshName[2], sizeof(MeshName[2]), "EnemyCar1Dead.x");
	return true;
}

bool C_CarMeshManager::GetCar201(int MeshNo)
{
	if (MeshNo != CarNo201)return false;
	sprintf_s(MeshName[0], sizeof(MeshName[0]), "Car3-1.x");
	sprintf_s(MeshName[1], sizeof(MeshName[1]), "EnemyCar1CM2.x");
	sprintf_s(MeshName[2], sizeof(MeshName[2]), "EnemyCar1Dead.x");
	return true;
}
