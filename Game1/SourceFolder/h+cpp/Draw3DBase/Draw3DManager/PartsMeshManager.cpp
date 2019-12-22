#include "PartsMeshManager.h"
#include"../../GameSource/XfileManager.h"

extern XfileManager xfileManager;


XFILE C_PartsMeshManager::GetMesh(int MeshNo)
{
	//åüçı
	if (GetMeshJudg(MeshNo) == false) {
		sprintf_s(MeshName, sizeof(MeshName), "../GameFolder/Material/XFile/tireP5.x");
	}

	XFILE Mesh;
	xfileManager.GetXfile(&Mesh, MeshName);

	return Mesh;
}

bool C_PartsMeshManager::GetMeshJudg(int MeshNo)
{
	if (GetParts1(MeshNo) == true)return true;
	if (GetParts2(MeshNo) == true)return true;
	if (GetParts3(MeshNo) == true)return true;	
	return false;
}

bool C_PartsMeshManager::GetParts1(int MeshNo)
{
	if (MeshNo != 1)return false;
	sprintf_s(MeshName, sizeof(MeshName), "../GameFolder/Material/XFile/CarDoorA1-3-1.x");
	return true;
}

bool C_PartsMeshManager::GetParts2(int MeshNo)
{
	if (MeshNo != 2)return false;
	sprintf_s(MeshName, sizeof(MeshName), "../GameFolder/Material/XFile/CarDoorB1-3-1.x");
	return true;
}

bool C_PartsMeshManager::GetParts3(int MeshNo)
{
	if (MeshNo != 3)return false;
	sprintf_s(MeshName, sizeof(MeshName), "../GameFolder/Material/XFile/CarJudg1-3-1.x");
	return true;
}
