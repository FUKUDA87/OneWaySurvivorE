#include "GunPM_1_1.h"

C_GunPartsDraw_1_1::C_GunPartsDraw_1_1(const int * DrawMeshType, const int * MeshNo, const int * MeshPartsNo)
	:C_PartsMeshDraw_1(DrawMeshType, MeshNo, MeshPartsNo)
{

}

bool C_GunPartsDraw_1_1::Update(const D3DXMATRIX * Mat)
{
	M_Base.Mat = *Mat;
	M_ScalPos = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	return true;
}

void C_GunPartsDraw_1_1::Draw(void)
{
	if (Dead() != false)return;

	M_C_Draw->Draw(&Get_DrawMat());
}
