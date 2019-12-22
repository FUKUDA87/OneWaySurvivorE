#include "StandMeshManager.h"
#include"../../GameSource/XfileManager.h"

extern XfileManager xfileManager;

XFILE C_StandMeshManager::GetMesh(int MeshNo)
{
	//åüçı
	if (GetMeshJudg(MeshNo) == false) {
		//åüçıé∏îs
		sprintf_s(MeshName, sizeof(MeshName), "../GameFolder/Material/XFile/stand1.x");
	}

	XFILE Mesh;
	xfileManager.GetXfile(&Mesh, MeshName);

	return Mesh;
}

bool C_StandMeshManager::GetMeshJudg(int MeshNo)
{
	if (GetStand1(MeshNo) == true)return true;
	if (GetStand101(MeshNo) == true)return true;
	return false;
}

bool C_StandMeshManager::GetStand1(int MeshNo)
{
	
	if (MeshNo != StandNo1)return false;
	sprintf_s(MeshName, sizeof(MeshName), "../GameFolder/Material/XFile/stand1.x");
	return true;
}

bool C_StandMeshManager::GetStand101(int MeshNo)
{
	
	if (MeshNo != StandNo101)return false;
	sprintf_s(MeshName, sizeof(MeshName), "../GameFolder/Material/XFile/stand2e.x");
	return true;
}
