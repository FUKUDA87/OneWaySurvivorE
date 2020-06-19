#include "Stand_No101.h"
#include"../DrawBase2/Draw_Mesh_Base_A.h"

C_Stand_No101::C_Stand_No101(const S_CAR_PARTS_DATA * Data, C_Move_Parts_Base * Move):C_Car_Parts_Joint(Data)
{
	Draw_New(new C_Draw_Mesh_Base("Stand_O_101.x"));
	New_Move(Move);
	bool Flg = false;
	Init_Joint_Data(&Flg);
}

void C_Stand_No101::Init_Joint_Data(const bool * Joint_Reverse_Flg)
{
	float f = 1.0f;
	if (*Joint_Reverse_Flg == true)f = -1.0f;

	New_Joint_Data(&Get_S_PARTS_DATA(D3DXVECTOR3(0.0f, 0.24f, 0.0f)*f, D3DXVECTOR3(0.0f, 0.0f, 0.0f)*f));
}
