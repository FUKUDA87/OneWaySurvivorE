#include "BulletData_No1.h"
#include"../../../Draw/DrawBase2/DrawPolMat/PolMat_Bullet_No1.h"
#include"../../../Manager/DrawTextureManager/DrawTextureManager_Manager.h"

S_BULLET_DATA C_BullteData_No1::Get_Data(void)
{
	S_BULLET_DATA L_Data;
	L_Data.BULLET.Damage = 1;
	L_Data.BULLET.Speed = 1.1f;
	return L_Data;
}

int C_BullteData_No1::Get_DrawNum(void)
{
	return 1;
}

C_Draw3D_Base2 * C_BullteData_No1::Get_Draw(const int * BulletDrawNo, const D3DXMATRIX *Mat)
{
	if (*BulletDrawNo == 0)return DrawNo0(Mat);
	
	return DrawNo0(Mat);
}

C_Draw3D_Base2 * C_BullteData_No1::DrawNo0(const D3DXMATRIX * Mat)
{
	int i = 0;
	return new C_PolMat_Bullet_No1("../GameFolder/Material/Texture/Bullet1-1-1.png", &Get_Tex_Pos(100,100),&Get_Init_S_PolMat_INIT(Mat,1,4,0.1f));
}
