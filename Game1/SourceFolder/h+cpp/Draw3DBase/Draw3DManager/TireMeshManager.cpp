#include "TireMeshManager.h"
#include"../../GameSource/XfileManager.h"

extern XfileManager xfileManager;


XFILE C_TireMeshManager::GetMesh(int MeshNo)
{

	//åüçı
	if (GetMeshJudg(MeshNo)== false) {
		sprintf_s(MeshName, sizeof(MeshName), "../GameFolder/Material/XFile/tireP5.x");
	}

	XFILE Mesh;
	xfileManager.GetXfile(&Mesh, MeshName);

	return Mesh;
}

bool C_TireMeshManager::GetMeshJudg(int MeshNo)
{
	if (GetTire1(MeshNo) == true)return true;
	if (GetTire101(MeshNo) == true)return true;
	if (GetTire201(MeshNo) == true)return true;
	return false;
}

bool C_TireMeshManager::GetTire1(int MeshNo)
{
	if (MeshNo != TireNo1)return false;
	sprintf_s(MeshName, sizeof(MeshName), "../GameFolder/Material/XFile/tireP5.x");
	return true;
}

bool C_TireMeshManager::GetTire101(int MeshNo)
{
	if (MeshNo != TireNo101)return false;
	sprintf_s(MeshName, sizeof(MeshName), "../GameFolder/Material/XFile/tire2-2.x");
	return true;
}

bool C_TireMeshManager::GetTire201(int MeshNo)
{
	if (MeshNo != TireNo201)return false;
	sprintf_s(MeshName, sizeof(MeshName), "../GameFolder/Material/XFile/CarTire1-3-1.x");
	return true;
}
