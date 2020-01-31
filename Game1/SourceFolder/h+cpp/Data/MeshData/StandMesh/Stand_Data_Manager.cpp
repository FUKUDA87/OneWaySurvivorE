#include "Stand_Data_Manager.h"
#include"Stand_Data_No1.h"
#include"Stand_Data_No0.h"
#include"../../../GameSource/Const.h"

C_Mesh_Data_Base * C_Stand_Data_Manager::Get_Mesh_Data(const int * MeshNo)
{
	if (*MeshNo == StandNo1)return new C_Stand_Data_No1();
	return new C_Stand_Data_No0();
}
