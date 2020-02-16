#include "Enemy_No101.h"
#include"../../Draw/Hp/Hp2DEnemy.h"
#include"../../Draw/Hp/Hp3DEnemy.h"
#include"../../EnemyData/EnemyNo1/EnemyAi/Enemy_No1_Phase0.h"
#include"../../Gun/GunDraw/Gun_Draw_Manager.h"
#include"../../EnemyData/EnemyNo1/GunMove2/Enemy_No1_Gun_1_Lockon.h"
#include"../../Draw/Polygon/Polygon_Judg.h"
#include"../../Draw/Judg/Car_Parts_Judg_Mesh.h"
#include"../../Draw/Judg/Car_Parts_Judg_Ball.h"

C_Enemy_No101::C_Enemy_No101(D3DXMATRIX GroundMat, float * TransX):C_EnemyA(GroundMat,TransX)
{
	S_ENEMYBODYDATA l_EBD;
	l_EBD.Body.CarBodyNo = CarNo201;
	l_EBD.CharaBase.NowHp = l_EBD.CharaBase.MaxHp = 100;
	l_EBD.CharaBase.DamageSetFlg = Co_Damage_No;
	l_EBD.ScalPos = D3DXVECTOR3(2.0f, 2.0f, 2.0f);
	l_EBD.GroundHeight = 0.5f;

	SetCharaBase(&l_EBD.CharaBase);
	BodyData = l_EBD.Body;
	CarFM.BodyHeight = l_EBD.GroundHeight;
	Car.Base.ScaPos = l_EBD.ScalPos;
	SetMeshCar(BodyData.CarBodyNo);
	//スピードセット
	InitSpeedMove(new C_EnemySpeedNo201());
	//パーツの初期化
	int l_MaxHp = GetCharaBase().MaxHp;

	//パーツのセット

	M_Parts_Set_Data.push_back(new C_Parts_Set_Data(Co_Parts_Tire, 1, TireNo201));
	M_Parts_Set_Data.push_back(new C_Parts_Set_Data(Co_Parts_Gun, 1, 101));
	M_Parts_Set_Data.push_back(new C_Parts_Set_Data(Co_Parts_Gun, 2, 0));
	M_Parts_Set_Data.push_back(new C_Parts_Set_Data(Co_Parts_Door, 1, 1));

	//New_Set_Car_Parts(&BodyData.CarBodyNo, M_Parts_Set_Data, &Flg, &Flg2);
	New_Car_Parts_Data(&BodyData.CarBodyNo);

	New_CarParts(M_Parts_Set_Data);

	M_Car_Parts.push_back(new C_Car_Parts_Judg_Polygon(Get_Data_CarParts(&Co_Parts_Judg,1),&D3DXVECTOR3(-0.3f,0.25f,0.0f),
		&D3DXVECTOR3(0.3f, 0.25f, 0.0f), &D3DXVECTOR3(0.3f, -0.25f, 0.0f), &D3DXVECTOR3(-0.3f, -0.25f, 0.0f)));

	M_Car_Parts.push_back(new C_Car_Parts_Judg_Mesh(Get_Data_CarParts(&Co_Parts_Judg, 2), "../GameFolder/Material/XFile/Car_O_201_Judg_1.x"));

	M_Car_Parts.push_back(new C_Car_Parts_Judg_Ball(Get_Data_CarParts(&Co_Parts_Judg, 1), 0.3f));

	New_Car_Parts_Gun(M_Parts_Set_Data);

	if (M_DriverNo!=co_PlayerCar)Delete_ALL_Data();

	//Aiの初期化
	m_Ai = new C_E_No101_AiPhase_1();

	Hp_Init(new C_Hp2DEnemy(&D3DXVECTOR3(800.0f, 30.0f, 1.0f), &D3DXVECTOR3(1280.0f / 2.0f, 720.0f*0.1f, 0.0f)));

	//銃の初期化
	C_Gun_Darw_Manager Manager;
	int g = 101;
	M_Gun.push_back(Manager.Get_Gun(&g, new C_Enemy_No1_Gun_1_Lockon()));
	g = 201;
	M_Gun.push_back(Manager.Get_Gun(&g, new C_Enemy_No1_Gun_1_Lockon()));

	//車のパーツのサイズ変更
	New_Car_Parts_Size(Co_Parts_Gun, 1, 0.7f);

	Delete_All_Parts_Set_Data();
}
