#include "GunMeshManager.h"
#include"../../GameSource/XfileManager.h"
extern XfileManager xfileManager;
//èeå˚
#include"../../Gun/GunDraw/GunData/GunDataNo2.h"
#include"../../Gun/GunDraw/GunData/GunDataNo0.h"


XFILE C_GunMeshManager::GetMesh(int MeshNo)
{
	//åüçı
	if (GetMeshJudg(MeshNo) == false) {
		sprintf_s(MeshName, sizeof(MeshName), "../GameFolder/Material/XFile/gun1.x");
	}

	XFILE Mesh;
	xfileManager.GetXfile(&Mesh, MeshName);

	return Mesh;
}

C_GunDataBase * C_GunMeshManager::GetGunData(const int MeshNo)
{
	//åüçı
	//No2
	if (MeshNo == GunNo2)return new C_GunDataNo2();

	//åüçıé∏îs
	return new C_GunDataNo0();
}

bool C_GunMeshManager::GetMeshJudg(int MeshNo)
{
	if (GetGunNo1(MeshNo) == true)return true;
	if (GetGunNo2(MeshNo) == true)return true;
	if (GetGunNo3(MeshNo) == true)return true;
	return false;
}

bool C_GunMeshManager::GetGunNo1(int MeshNo)
{
	if (MeshNo != GunNo1)return false;
	sprintf_s(MeshName, sizeof(MeshName), "../GameFolder/Material/XFile/gun1.x");
	return true;
}

bool C_GunMeshManager::GetGunNo2(int MeshNo)
{
	if (MeshNo != GunNo2)return false;
	sprintf_s(MeshName, sizeof(MeshName), "../GameFolder/Material/XFile/gun2EC.x");
	return true;
}

bool C_GunMeshManager::GetGunNo3(int MeshNo)
{
	if (MeshNo != GunNo3)return false;
	sprintf_s(MeshName, sizeof(MeshName), "../GameFolder/Material/XFile/gun1.x");
	return true;
}
