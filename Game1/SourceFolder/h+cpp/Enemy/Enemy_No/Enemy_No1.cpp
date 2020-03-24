#include "Enemy_No1.h"
#include"../../Draw/Hp/Hp2DEnemy.h"
#include"../../Draw/Hp/Hp3DEnemy.h"
#include"../../EnemyData/EnemyNo1/EnemyAi/Enemy_No1_Phase0.h"
#include"../../Gun/GunDraw/Gun_Draw_Manager.h"
#include"../../EnemyData/EnemyNo1/GunMove2/Enemy_No1_Gun_1_Lockon.h"
#include"../../Const/Const_PartsTypeNo.h"
#include"../../EnemyData/EnemyNo1/SpeedData/SpeedUp.h"

C_Enemy_No1::C_Enemy_No1(const D3DXMATRIX * GroundMat, const float * TransX):C_EnemyA(GroundMat,TransX)
{
	S_ENEMYBODYDATA l_EBD;
	l_EBD.Body.CarBodyNo = CarNo101;
	l_EBD.CharaBase.NowHp = l_EBD.CharaBase.MaxHp = 20;
	l_EBD.CharaBase.DamageSetFlg = Co_Damage_Yes;
	l_EBD.ScalPos = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	l_EBD.GroundHeight = 0.75f;

	SetCharaBase(&l_EBD.CharaBase);
	BodyData = l_EBD.Body;
	CarFM.BodyHeight = l_EBD.GroundHeight;
	Car.Base.ScaPos = l_EBD.ScalPos;
	SetMeshCar(BodyData.CarBodyNo);
	//スピードセット
	InitSpeedMove(new SpeedUp1());
	//パーツの初期化
	int l_MaxHp = GetCharaBase().MaxHp;

	/*パーツのセット*/

	M_NewSet_CarPartsData(&Co_Parts_Tire, 1, TireNo101);
	M_NewSet_CarPartsData(&Co_Parts_Gun, 1, 101);

	New_Set_EnemyCar_Parts(&BodyData.CarBodyNo);

	/*Aiの初期化*/
	m_Ai = new C_E_No1_Phase0();

	Hp_Init(new C_Hp3D(&D3DXVECTOR2(0.7f, 0.1f)));

	/*銃の初期化*/
	C_Gun_Darw_Manager Manager;
	int g = 101;
	M_Gun.push_back(Manager.Get_Gun(&g, new C_Enemy_No1_Gun_1_Lockon()));
}
