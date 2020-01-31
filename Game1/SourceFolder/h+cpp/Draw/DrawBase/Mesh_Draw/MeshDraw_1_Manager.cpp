#include "MeshDraw_1_Manager.h"

C_MeshDraw_1 * C_DrawMesh_1_Manager::Get_MeshDraw(const int * DrawNo, C_MeshManager * MeshManager, const int * MeshNo)
{
	if (*DrawNo == 1)return new C_MeshSet_No2_1(MeshNo, MeshManager);

	return new C_MeshSet_No2_1(MeshNo, MeshManager);
}
