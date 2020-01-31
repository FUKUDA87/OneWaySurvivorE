#include "Enemy_No101.h"
#include"../../Draw/Hp/Hp2DEnemy.h"
#include"../../Draw/Hp/Hp3DEnemy.h"
#include"../../EnemyData/EnemyNo1/EnemyAi/Enemy_No1_Phase0.h"
#include"../../Gun/GunDraw/Gun_Draw_Manager.h"
#include"../../EnemyData/EnemyNo1/GunMove2/Enemy_No1_Gun_1_Lockon.h"

C_Enemy_No101::C_Enemy_No101(D3DXMATRIX GroundMat, float * TransX):C_EnemyA(GroundMat,TransX)
{
	S_ENEMYBODYDATA l_EBD;
	l_EBD.Body.CarBodyNo = CarNo201;
	l_EBD.Body.TireNo = TireNo201;
	l_EBD.Body.StandNo = StandNo101;
	l_EBD.Body.GunNo = 1;
	l_EBD.CharaBase.NowHp = l_EBD.CharaBase.MaxHp = 100;
	l_EBD.CharaBase.DamageSetFlg = Co_Damage_Yes_Parts;
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
	bool Flg = false, Flg2 = true;
	New_Set_Car_Parts(&BodyData, &Flg, &Flg2);

	//Aiの初期化
	m_Ai = new C_E_No101_AiPhase_1();

	Hp_Init(new C_Hp2DEnemy(&D3DXVECTOR3(800.0f, 30.0f, 1.0f), &D3DXVECTOR3(1280.0f / 2.0f, 720.0f*0.1f, 0.0f)));

	//銃の初期化
	C_Gun_Darw_Manager Manager;
	int g = 101;
	M_Gun.push_back(Manager.Get_Gun(&g, new C_Enemy_No1_Gun_1_Lockon()));
}
