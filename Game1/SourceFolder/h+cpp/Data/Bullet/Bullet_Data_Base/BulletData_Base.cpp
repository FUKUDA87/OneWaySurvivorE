#include "BulletData_Base.h"

S_PolMat_INIT C_BulletData_Base::Get_Init_S_PolMat_INIT(const D3DXMATRIX * Mat, const int TexNo, const int PolNum, const float PolSize)
{
	S_PolMat_INIT Init;
	Init.Mat = *Mat;
	Init.PolSize = PolSize;
	Init.TexNo = TexNo;
	Init.PolNum = PolNum;
	return Init;
}

S_TEX_POS C_BulletData_Base::Get_Tex_Pos(const int W, const int H)
{
	S_TEX_POS Pos;
	Pos.Width = W;
	Pos.Height = H;
	return Pos;
}
