#include "PartsBase_1.h"
#include"../../../GameSource/Judgment.h"

C_PartsBase_1::C_PartsBase_1()
{
	
}

C_PartsBase_1::~C_PartsBase_1()
{
	
}

void C_PartsBase_1::Set_ScalPos(const D3DXVECTOR3 * s_ScalPos)
{
	Judg judg;
	M_ScalPos = judg.GetVecVec(&M_Base.ScaPos, s_ScalPos);
}

D3DXMATRIX C_PartsBase_1::Get_DrawMat(void)
{
	Judg judg;
	D3DXMATRIX Mat = judg.GetDrawMat(&M_Base.Mat, &M_Base.Scal, &M_ScalPos);
	return Mat;
}
