#include "EnemyA.h"

C_EnemyA::C_EnemyA(D3DXMATRIX GroundMat, float * TransX)
{
	InitPos(GroundMat, TransX);

}

C_EnemyA::~C_EnemyA()
{
	Delete_All_Parts_Set_Data();
}

void C_EnemyA::InitBody(void)
{
	SetMeshCar(CarNo101);
	CarFM.BodyHeight = 0.7f;
}


void C_EnemyA::InitPos(D3DXMATRIX GroundMat, float * TransX)
{
	D3DXMATRIX tmp;
	D3DXMatrixTranslation(&Car.Base.Trans, *TransX, 0.0f, 0.0f);
	D3DXMatrixTranslation(&tmp, 0.0f, 0.5f, 0.0f);
	Car.Base.Mat = tmp * Car.Base.Trans*GroundMat;
}

void C_EnemyA::Delete_All_Parts_Set_Data(void)
{
	if (M_Parts_Set_Data.size() <= 0)return;

	for (unsigned int p = 0; p < M_Parts_Set_Data.size(); p++) {
		delete M_Parts_Set_Data[p];
		M_Parts_Set_Data.erase(M_Parts_Set_Data.begin() + p);
		p--;
	}
}
