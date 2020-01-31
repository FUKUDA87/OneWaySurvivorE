#pragma once
#include"MeshDraw1_1/MeshSet2_1/MeshSet2_1.h"

class C_DrawMesh_1_Manager {
public:
	C_MeshDraw_1* Get_MeshDraw(const int *DrawNo, C_MeshManager *MeshManager, const int *MeshNo);
};