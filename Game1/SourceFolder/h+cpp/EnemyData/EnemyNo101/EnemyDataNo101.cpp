#include "EnemyDataNo101.h"
#include"GunMove/ENo101_GNo0_Attack.h"
#include"PartsMove/ENo101_DoorMove.h"
#include"PartsMove/ENo101_StandMove.h"
#include"GunMove/ENo101_GNo1_Attack.h"
#include"../../Gun/GunDraw/Gun_Type/Gun_Gatling_1.h"
#include"../../Gun/GunDraw/Gun_Draw_Manager.h"
#include"../EnemyNo1/GunMove2/Enemy_No1_Gun_1_Lockon.h"

C_EnemyDataNo101::C_EnemyDataNo101()
{
	GunNum = 2;
}

S_ENEMYBODYDATA C_EnemyDataNo101::GetBodyData(void)
{
	S_ENEMYBODYDATA l_EBD;
	l_EBD.Body.CarBodyNo = CarNo201;
	l_EBD.Body.TireNo = TireNo201;
	l_EBD.Body.StandNo = StandNo101;
	l_EBD.Body.GunNo = 1;
	l_EBD.CharaBase.NowHp = l_EBD.CharaBase.MaxHp = 100;
	l_EBD.CharaBase.DamageSetFlg = false;
	l_EBD.ScalPos = D3DXVECTOR3(2.0f, 2.0f, 2.0f);
	l_EBD.GroundHeight = 0.5f;
	return l_EBD;
}

C_PartsMoveBase * C_EnemyDataNo101::GetPartsData(const int * PartsNo)
{
	//検索
	if ((*PartsNo > -1) && (*PartsNo < 6))return new C_EnemyNo1_TireMove();
	if (*PartsNo == 6)return new C_EnemyNo1_StandMove();
	if (*PartsNo == 7)return new C_ENo101_DoorMove();
	if (*PartsNo == 8)return new C_ENo101_DoorMove();
	if (*PartsNo == 9)return new C_ENo101_Judg1Move();
	if (*PartsNo == 10)return new C_ENo101_StandMove();
	//検索に引っかからない場合
	return new C_EnemyNo1_TireMove();
}

XFILE C_EnemyDataNo101::GetPartsMesh(const int * PartsNo)
{
	//タイヤマネージャー
	C_TireMeshManager TireMeshManager;
	//スタンドマネージャー
	C_StandMeshManager StandMeshManager;
	//パーツマネージャー
	C_PartsMeshManager PartsMeshManager;
	if ((*PartsNo > -1) && (*PartsNo < 6))return TireMeshManager.GetMesh(TireNo201);
	if (*PartsNo ==6)return StandMeshManager.GetMesh(StandNo101);
	if (*PartsNo ==7)return PartsMeshManager.GetMesh(1);
	if (*PartsNo == 8)return PartsMeshManager.GetMesh(2);
	if (*PartsNo == 9)return PartsMeshManager.GetMesh(3);
	return TireMeshManager.GetMesh(TireNo201);
}

C_E_GunMoveBase * C_EnemyDataNo101::GetGunData(const int * GunNo, S_ENEMYGUNDATA *s_Data)
{
	//検索
	if (*GunNo == co_E_DataNo0)return new C_ENo101_GNo0_Attack(s_Data);
	if (*GunNo == co_E_DataNo1)return new C_ENo101_GNo1_Attack(s_Data);

	//検索に引っかからない場合
	return new C_ENo101_GNo0_Attack(s_Data);
}

Speed * C_EnemyDataNo101::GetSpeed(void)
{
	return new C_EnemySpeedNo201();
}

C_E_AiPhaseBase * C_EnemyDataNo101::GetAiPhase(void)
{
	return new C_E_No101_AiPhase_1();
}

C_GunLaser * C_EnemyDataNo101::Get_Gun(const int * EnemyGunNo)
{
	C_Gun_Darw_Manager Manager;
	int g = 101;
	return Manager.Get_Gun(&g,new C_Enemy_No1_Gun_1_Lockon());
}
