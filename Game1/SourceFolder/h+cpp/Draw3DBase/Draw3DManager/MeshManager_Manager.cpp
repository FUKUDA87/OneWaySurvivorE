#include "MeshManager_Manager.h"
#include"../../GameSource/Const.h"
#include"GunMeshManager.h"

C_MeshManager * C_MeshManager_Manager::Get_MeshManager(const S_CategoryNo *No)
{
	if (No->a == co_Gun)return  Get_GunMeshManager(&No->b);


	return Get_GunMeshManager(&No->b);
}

C_MeshManager * C_MeshManager_Manager::Get_GunMeshManager(const int * MeshNo)
{
	if(*MeshNo==GunNo1)return new C_GunMeshManager();


	return new C_GunMeshManager();
}
