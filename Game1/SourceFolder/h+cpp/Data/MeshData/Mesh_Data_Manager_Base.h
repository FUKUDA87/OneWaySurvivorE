#pragma once
#include"Mesh_Data_Base.h"

class C_Mesh_Data_Manager_Base {
public:
	virtual C_Mesh_Data_Base* Get_Mesh_Data(const int *MeshNo) = 0;
};