#pragma once
#include"../Mesh_Data_Manager_Base.h"

class C_Stand_Data_Manager :public C_Mesh_Data_Manager_Base {
public:
	C_Mesh_Data_Base* Get_Mesh_Data(const int *MeshNo);
};