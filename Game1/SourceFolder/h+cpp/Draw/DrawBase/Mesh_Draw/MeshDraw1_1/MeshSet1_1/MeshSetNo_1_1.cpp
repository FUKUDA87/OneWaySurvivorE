#include "MeshSetNo_1_1.h"

C_MeshSetNo_1_1::C_MeshSetNo_1_1(const int * MeshNo, C_MeshManager * s_MeshManager)
{
	ManagerSet(s_MeshManager);
	MeshChange(MeshNo);
}

C_MeshSetNo_1_1::~C_MeshSetNo_1_1()
{
	DeleteManager();
}

void C_MeshSetNo_1_1::ManagerSet(C_MeshManager * s_MeshManager)
{
	DeleteManager();

	M_MeshManager = s_MeshManager;
}

void C_MeshSetNo_1_1::MeshChange(const int * MeshNo)
{
	if (M_MeshManager == nullptr)return;

	M_Mesh = M_MeshManager->GetMesh(*MeshNo);
}

void C_MeshSetNo_1_1::DeleteManager(void)
{
	if (M_MeshManager == nullptr)return;

	delete M_MeshManager;
}
