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

	NowPhase = Phase0;

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
		targetPos= judg.SetPosM(cd[0].NowMat);
		GetTargetPos(&targetPos);
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

		//攻撃命令
		//if ((gun.GunMoveEndFlg == true) || (gun.EndFlg == true)||(Flg==true)) {
		//	//InitGunMove();
		//}

		//スピード管理
		Speed *NextSpeed;
		NextSpeed = speed->Action(&Car.Con.NowSpeed,&cd[0].Speed, &Car.Con.GroNum, &cd[0].NowGround,&NowPhase);
		if (NextSpeed != nullptr) {
			delete speed;
			speed = NextSpeed;
		}
		Car.Con.Speed = D3DXVECTOR3(0.0f, 0.0f, (float)Car.Con.NowSpeed / 100.0f);

		if (m_Ai != nullptr) {
			m_Ai->Action(&GetCharaBase(), &NowPhase);
		}
		
	}

	return true;
}

bool C_EnemyAi::UpdateAll(std::vector<BillBase*> ground)
{
	if (Car.Base.Flg == true) {
		UpdateCarFM(ground);
		//銃のくっつく行列探し
		D3DXMATRIX GunMat = GetMatCar();
		//標準パーツのアップデート
		if (Parts.size() > 0) {
			for (unsigned int p = 0; p < Parts.size(); p++) {
				Parts[p]->SetSpeed(&Car.Con.NowSpeed, &Car.Con.MaxSpeed);
				Parts[p]->UpdateParts(&GetMatCar(), &Car.Base.ScaPos);
				//銃のくっつき判定
				if (Parts[p]->GetParts().GunFlg >0) {
					GunMat = Parts[p]->GetParts().Base.Mat;
				}
			}
		}

		//SetGunMatT(&GunMat);
	}
	return true;
}

void C_EnemyAi::SetParts(std::vector<BillBase*> ground)
{
	if (Car.Base.Flg == true) {
		judg.MatMatVec(&brj.MoveVec, PlaMovMat, Car.Base.Mat);//MoveVec作成
		UpdateCar();

		//無敵のアップデート
		UpdateCountM();
		
		//標準パーツのアップデート
		if (Parts.size() > 0) {
			bool l_Flg=false;
			for (unsigned int p = 0; p < Parts.size(); p++) {
				Parts[p]->SetSpeed(&Car.Con.NowSpeed, &Car.Con.MaxSpeed);
				Parts[p]->UpdateParts(&GetMatCar(),&Car.Base.ScaPos,&NowPhase);
				if ((Parts[p]->GetParts().HpLinkFlg == true) && (l_Flg == false)) {
					int l_Hp = Parts[p]->GetHp();
					SetNowHp(&l_Hp);
					l_Flg = true;
				}
			}
		}

		/*UpdateGun();

		SetGunMatT(&GunMat);*/
		D3DXMATRIX GunMat;
		if (m_Gun.size() > 0) {
			for (unsigned int g = 0; g < m_Gun.size(); g++) {
				//銃のくっつく行列探し
				GunMat = GetMatCar();
				//スタンドの検索
				for (unsigned int p = 0; p < Parts.size(); p++) {
					if((unsigned int)Parts[p]->GetParts().GunFlg-1 ==g)GunMat = Parts[p]->GetParts().Base.Mat;
				}
				m_Gun[g]->Update_Gun(&GunMat,&NowPhase);
			}
		}

		UpdateBullet2(&brj.MoveVec);
		//UpdateBullet();
	}
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
