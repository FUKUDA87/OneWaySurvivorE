#pragma once
#include"MeshManager.h"

class C_MeshManager_Manager {
public:
	C_MeshManager *Get_MeshManager(const S_CategoryNo *No);
private:
	C_MeshManager *Get_GunMeshManager(const int *MeshNo);
};