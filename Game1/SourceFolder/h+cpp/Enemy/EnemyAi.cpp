#include "EnemyAi.h"
#include"../EnemyData/EnemyNo1/SpeedData/SpeedUp.h"

C_EnemyAi::C_EnemyAi()
{
	NowCount = MaxCount = 1;
	InitSpeedMove(new SpeedUp1());
	SpeedMul = 1.0f;

	//スピードの初期化
	Car.Con.NowSpeed = 80;
	Car.Con.MaxSpeed = 150;

	DeadFlg = false;
}

C_EnemyAi::~C_EnemyAi()
{
	if (speed != nullptr) {
		delete speed;
	}
	if (m_Ai != nullptr) {
		delete m_Ai;
	}
}

bool C_EnemyAi::UpdateAi(CHARAData cd[], unsigned int NUM, std::vector<BillBase*> ground)
{
	if (NUM <= 0) {
		return false;
	}
	if (GetHp() <= 0)Car.Base.Flg = false;

	if (Car.Base.Flg == true) {
		if (m_Ai != nullptr) {
			C_E_AiPhaseBase *L_Ai;
			L_Ai=m_Ai->Action(&GetCharaBase(),M_Car_Parts, M_Gun, &M_S_Gun_Update_Data, &Car.Con.GroNum, &cd[0].NowGround);
			if (L_Ai != nullptr) {
				delete m_Ai;
				m_Ai = L_Ai;
			}
		}

		M_S_Gun_Update_Data.TargetPos = judg.SetPosM(cd[0].NowMat);

		//GetTargetPos(&targetPos);
		//judg.SetPosM(&gun.TragetPos, cd[0].NowMat);
		//銃の回転の初期化していいかの確認


		//if (judg.ball(gun.NowBase.DrawMat, gun.NowBase.Trans*gun.ConnectMat, 2.0f) == false) {//バグ解決済み（首が無くなるバグ）
		//	gun.NowBase.AngX = 0.0f;
		//	gun.NowBase.AngY = 0.0f;
		//	D3DXMatrixRotationX(&gun.NowBase.RotX, D3DXToRadian((float)gun.NowBase.AngX));
		//	D3DXMatrixRotationY(&gun.NowBase.RotY, D3DXToRadian((float)gun.NowBase.AngY));
		//	/*NowGunVec = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
		//	gun.Base.Mat = gun.Base.Trans*stand.Base.Mat;*/
		//}

		unsigned int GNo = cd[0].NowGround - 5;
		bool Flg=StartAi(&GNo);
		
	}

	M_S_Gun_Update_Data.Car_Alive_Flg = GetFlgCar();

	//スピード管理
	Speed *NextSpeed;
	bool CarFlg = GetFlgCar();
	NextSpeed = speed->Action(&CarFlg,&Car.Con.NowSpeed, &cd[0].Speed, &Car.Con.GroNum, &cd[0].NowGround, &M_S_Gun_Update_Data.NowPhase);
	if (NextSpeed != nullptr) {
		delete speed;
		speed = NextSpeed;
	}
	Car.Con.Speed = D3DXVECTOR3(0.0f, 0.0f, (float)Car.Con.NowSpeed / 100.0f);

	return true;
}

bool C_EnemyAi::UpdateAll(std::vector<BillBase*> ground)
{
	UpdateCarFM(ground);

	return true;
}

void C_EnemyAi::SetParts(std::vector<BillBase*> ground)
{
		judg.MatMatVec(&brj.MoveVec, PlaMovMat, Car.Base.Mat);//MoveVec作成
		UpdateCar();
		//標準パーツのアップデート
		Update_Car_Parts();

		Update_Gun();
	if (Car.Base.Flg == true) {
		//無敵のアップデート
		UpdateCountM();
		
		
	}

	Update_Effect();
	Set_MoveVec_Effect(&brj.MoveVec);
}



void C_EnemyAi::SetPlaEnd(bool Flg)
{
	/*if (Flg == true) {
		gun.AIFlg = false;
		gun.RayJudgFlg = false;
	}
	else {
		gun.AIFlg = true;
	}*/
}

bool C_EnemyAi::StartAi(const unsigned int * GNo)
{
	if (Car.Base.Flg != true) return false;
	//if (gun.AIFlg != false) return false;
	if (Car.Con.GroNum < *GNo) return false;
	
	//gun.AIFlg = true;
	return true;
}

void C_EnemyAi::InitSpeedMove(Speed * Initspeed)
{
	if (speed != nullptr) {
		delete speed;
	}
	speed = Initspeed;
}
