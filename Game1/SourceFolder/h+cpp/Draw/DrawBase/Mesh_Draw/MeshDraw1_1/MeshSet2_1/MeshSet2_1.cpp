#include "MeshSet2_1.h"

C_MeshSet_No2_1::C_MeshSet_No2_1(const int * MeshNo, C_MeshManager * MeshManager)
{
	C_MeshManager *L_MeshManager;
	L_MeshManager = MeshManager;

	M_Mesh = L_MeshManager->GetMesh(*MeshNo);
}
