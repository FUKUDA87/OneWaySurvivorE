#include "Gun_No101.h"
#include"../../../Draw/DrawBase2/Draw_Mesh_Base_A.h"
#include"../Gun_Trigger/Gun_Trigger_1.h"

C_Gun_No101::C_Gun_No101(C_GunMoveBase_A * Move)
{
	//�e�̏��̏�����
	M_S_GunData.Depar.Bullet_Gun_Mode = 1;
	M_S_GunData.Depar.Count_Departure = 1;
	//���S�̍s��̓����̏�����
	New_GunMove(Move);
	//�p�[�c�̏�����
	M_GunParts.push_back(new C_PartsDraw_Gun(new C_Draw_Mesh_Base("../GameFolder/Material/XFile/gun2EC.x")
		, &Get_Data_Set(true, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.8f), 180, 1, 0)));
	//�J�e�S���[�̏�����
	int i = 0;
	M_Category_Data.push_back(new C_Gun_Parts_Category(&i));
	//�������̏�����
	M_C_Trigger = new C_Gun_Trigger_1();
}
