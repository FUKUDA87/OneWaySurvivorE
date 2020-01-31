#include "Gun_Gatling_1.h"
#include"../GunMove/GunStopMove_1.h"
#include"../../../Draw/DrawBase2/Draw_Mesh_Base_A.h"
#include"../Gun_Trigger/Gun_Trigger_1.h"

C_Gun_Gatling::C_Gun_Gatling(C_GunMoveBase_A * Move)
{
	//銃の情報の初期化
	M_S_GunData.Depar.Bullet_Gun_Mode = 3;
	M_S_GunData.Depar.Count_Departure = 120;
	//中心の行列の動きの初期化
	New_GunMove(Move);
	//パーツの初期化
	M_GunParts.push_back(new C_PartsDraw_Gun(new C_Draw_Mesh_Base("../GameFolder/Material/XFile/gun1.x")
		, &Get_Data_Set(true, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.8f), 10, 1, 0)));
	//カテゴリーの初期化
	int i = 0;
	M_Category_Data.push_back(new C_Gun_Parts_Category(&i));
	//引き金の初期化
	M_C_Trigger = new C_Gun_Trigger_1();
}

S_Gun_Parts_Data C_Gun_Gatling::Get_Data_Set(const bool BulletFlg, const D3DXVECTOR3 * TransPos, const D3DXVECTOR3 * MouthPos, const int Rate, const int BulletNo, const int CategoryNo)
{
	S_Gun_Parts_Data Data;
	Data.BulletFlg = BulletFlg;
	Data.TarnsPos = *TransPos;
	Data.Rate = Rate;
	Data.BulletNo = BulletNo;
	Data.MouthPos = *MouthPos;
	Data.CategoryNo = CategoryNo;
	return Data;
}
