#include "PartsMeshDraw_1.h"
#include"../../../Draw/DrawBase/Mesh_Draw/MeshDraw_1_Manager.h"
#include"../../../Draw3DBase/Draw3DManager/MeshManager_Manager.h"

C_PartsMeshDraw_1::C_PartsMeshDraw_1(const int *DrawMeshType, const int *MeshNo, const int *MeshPartsNo)
{
	Init_C_Draw(DrawMeshType, MeshNo,MeshPartsNo);
}

C_PartsMeshDraw_1::~C_PartsMeshDraw_1()
{
	Delete_C_Draw();
}

void C_PartsMeshDraw_1::Init_C_Draw(const int *DrawMeshType, const int *MeshNo, const int *MeshPartsNo)
{
	Delete_C_Draw();

	C_DrawMesh_1_Manager Manager;
	int i = 0;
	C_MeshManager_Manager MeshManager;
	S_CategoryNo No;
	No.a = *DrawMeshType;
	No.b = *MeshNo;
	M_C_Draw = Manager.Get_MeshDraw(&i, MeshManager.Get_MeshManager(&No), MeshPartsNo);

}

void C_PartsMeshDraw_1::Delete_C_Draw(void)
{
	if (M_C_Draw == nullptr)return;

	delete M_C_Draw;

}
