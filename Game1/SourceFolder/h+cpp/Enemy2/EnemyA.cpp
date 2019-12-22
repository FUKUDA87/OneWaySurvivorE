#include "EnemyA.h"
#include"../Draw/Hp/Hp2DEnemy.h"
#include"../Draw/Hp/Hp3DEnemy.h"

C_EnemyA::C_EnemyA(D3DXMATRIX GroundMat, float * TransX)
{
	
	InitPos(GroundMat, TransX);

	EnemyA();
	InitBody();
	InitParts();
}

C_EnemyA::C_EnemyA(const int * EnemyNo, D3DXMATRIX GroundMat, float * TransX)
{
	InitPos(GroundMat, TransX);

	m_EnemyNo = *EnemyNo;
	C_EnemyDataManager e_DM;
	C_EnemyDataBase *e_DB=e_DM.GetEnemyData(&m_EnemyNo);
	//車の初期化
	S_ENEMYBODYDATA l_EBD= e_DB->GetBodyData();
	SetCharaBase(&l_EBD.CharaBase);
	BodyData = l_EBD.Body;
	CarFM.BodyHeight = l_EBD.GroundHeight;
	Car.Base.ScaPos = l_EBD.ScalPos;
	SetMeshCar(BodyData.CarBodyNo);
	//スピードセット
	InitSpeedMove(e_DB->GetSpeed());
	//パーツの初期化
	int l_MaxHp = GetCharaBase().MaxHp;
	SetCarParts(&BodyData,EnemyNo,&l_MaxHp, false);

	//銃の初期化
	int i = 0;
	for (unsigned int s = 0; s < Parts.size(); s++) {
		if (Parts[s]->GetParts().GunFlg>0)i++;
	}
	if (i <= 0)return;
	for (int g = 0; g < i; g++) {
		m_Gun.push_back(new C_EnemyGun(m_EnemyNo, g));
	}

	//Aiの初期化
	m_Ai = e_DB->GetAiPhase();

	if (*EnemyNo > 100) {
		m_HpBase = new C_Hp2DEnemy(&D3DXVECTOR3(800.0f,30.0f,1.0f),&D3DXVECTOR3(1280.0f/2.0f,720.0f*0.1f,0.0f));
	}
	else {
		m_HpBase = new C_Hp3D(&D3DXVECTOR2(0.7f,0.1f));
	}
}

C_EnemyA::C_EnemyA(D3DXMATRIX GroundMat, float * TransX, const BODYDATA * IniteData)
{
	InitPos(GroundMat, TransX);

	//車初期化
	BodyData = *IniteData;
	SetMeshCar(BodyData.CarBodyNo);

	SetCarParts(&BodyData, true);
}

C_EnemyA::C_EnemyA(D3DXMATRIX GroundMat, float * TransX, const BODYDATACar * IniteData, Speed* GetSpeed)
{
	InitPos(GroundMat, TransX);

	//車初期化
	BodyData = IniteData->Body;
	Car.Base.ScaPos = IniteData->ScalPos;
	SetHp(&IniteData->MaxHp);
	SetMeshCar(BodyData.CarBodyNo);

	SetCarParts(&BodyData, true);

	//スピードセット
	InitSpeedMove(GetSpeed);

	if (BodyData.CarBodyNo == 101) {
		CarFM.BodyHeight = 0.75f;
	}

	/*GUNINITDATA InitGun;
	C_CharaBase c;
	InitGun.CharaBase = c.GetInitAll(1, true);
	InitGun.DrawNo.GunNo = 2;
	InitGun.InitGun = judg.InitSetPartsData(0.0f, 0.0f, 0.0f, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), true);
	InitGun.LaserSize = 40.0f;
	InitSetGun(&InitGun);*/

	m_Gun.push_back(new C_EnemyGun(IniteData->EnemyNo,0));
}



void C_EnemyA::EnemyA(void)
{

}

void C_EnemyA::InitBody(void)
{
	SetMeshCar(CarNo101);
	CarFM.BodyHeight = 0.7f;
}

void C_EnemyA::InitParts(void)
{
	//タイヤの初期化------------------------------------------------------------------------
	//初期化用変数
	PARTS P;
	float AngXMaxUp = 35.0f;
	P.GunFlg = false;
	P.JudgFlg = false;
	P.MoveFlg = true;
	P.MeshDrawFlg = 1;
	P.Mesh.DrawMesh = TireMeshManager.GetMesh(TireNo101);
	//初期位置
	//左側1の初期化
	P.Base.AngX = 0.0f;
	D3DXVECTOR3 tPos = D3DXVECTOR3(0.65f, -0.5f, 0.55f);
	D3DXMatrixTranslation(&P.Base.Trans, -tPos.x, tPos.y, tPos.z);
	D3DXMatrixRotationY(&P.Base.RotY, D3DXToRadian(180.0f));
	P.Base.ScaPos = D3DXVECTOR3(0.75f, 1.0f, 1.0f);
	//出現させる
	Parts.push_back(new C_TireParts(&P, &AngXMaxUp));

	//左側2の初期化
	D3DXVECTOR3 ttPos = D3DXVECTOR3(0.65f, -0.5f, -0.75f);
	D3DXMatrixTranslation(&P.Base.Trans, -ttPos.x, ttPos.y, ttPos.z);
	//出現させる
	Parts.push_back(new C_TireParts(&P, &AngXMaxUp));

	//右側1の初期化
	D3DXMatrixTranslation(&P.Base.Trans, tPos.x, tPos.y, tPos.z);
	D3DXMatrixRotationY(&P.Base.RotY, D3DXToRadian(0.0f));
	AngXMaxUp *= -1.0f;
	//出現させる
	Parts.push_back(new C_TireParts(&P, &AngXMaxUp));

	//右側2の初期化
	D3DXMatrixTranslation(&P.Base.Trans, ttPos.x, ttPos.y, ttPos.z);
	//出現させる
	Parts.push_back(new C_TireParts(&P, &AngXMaxUp));


	//スタンドの初期化---------------------------------------------------------
	P.GunFlg = true;
	P.Mesh.DrawMesh = StandMeshManager.GetMesh(StandNo101);
	//初期位置
	tPos = D3DXVECTOR3(0.0f, 0.72f, -0.2f);
	D3DXMatrixTranslation(&P.Base.Trans, tPos.x, tPos.y, tPos.z);
	P.Base.ScaPos = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	//出現させる
	Parts.push_back(new C_PartsBase(&P));

	//銃の初期化-----------------------------------------------------------
}

void C_EnemyA::InitPos(D3DXMATRIX GroundMat, float * TransX)
{
	D3DXMATRIX tmp;
	D3DXMatrixTranslation(&Car.Base.Trans, *TransX, 0.0f, 0.0f);
	D3DXMatrixTranslation(&tmp, 0.0f, 0.5f, 0.0f);
	Car.Base.Mat = tmp * Car.Base.Trans*GroundMat;
}
