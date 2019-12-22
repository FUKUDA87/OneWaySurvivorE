#include "MoveE.h"
#include"../GameSource/Motion.h"
#include"../EnemyData/EnemyNo1/SpeedData/SpeedUp.h"
#include"../GameSource/Judgment.h"

extern Judg judg;
extern Motion motion;

void MoveE::Move()
{
	if (EneMovEndFlg == false) {
		MoveFlg = false;
		return;
	}
	MoveFlg = true;
}

void MoveE::ChaFlg(bool * NowFlg, bool * NextFlg)
{
	*NowFlg = false;
	*NextFlg = true;
}

void MoveE::InitM()
{
	GunMovFlg = false;

	GunAFlg = false;
	countRay = 0;//plaRayFlgがtrueの時、カウント

	LocAFlg = false;
	CouLok = 0;

	AttAFlg = false;
	AttFlg = false;
	AttCount = 0;
	Count = 0;
	GunRotFlg = false;
}

void MoveE::InitEndF()
{
	EneMovEndFlg = false;
	GunMovEndFlg = false;
	LocAEndFlg = false;
	AttAEndFlg = false;
}

MoveE::MoveE(D3DXMATRIX GroundMat, float *TransX):GunE(GroundMat,TransX)
{
	InitM();
	InitEndF();
	Move();
	plaJugFlg = false;

	LocCouEnd = 20;
	AttCouEnd = 1;

	PlaEndFlg = false;
	NowGunVec = D3DXVECTOR3(0.0f, 0.0f, 1.0f);

	Anime = 0.0f;
	qFlg = qGFlg = false;
	cFlg = false;
	//SpeB = new float[5];
	//enemy.CH.Con.Speed = 10.0f;
	//スピード管理の初期化
	/*EneSpe.NowSpeedMul = 1.0f;
	EneSpe.MaxSpeed = 1.2f;
	EneSpe.StopSpeed = 0.9f;*/
	NowCount = MaxCount = 1;
	speed = new SpeedUp1();
	SpeedMul = 1.0f;
}

MoveE::~MoveE()
{
	delete speed;
}

void MoveE::ResGunAng()
{
	fAnim = 0.0f;
	LocAEndFlg = false;
	laserMan->SetLFlg(true);
	D3DXVECTOR3 FrontVec(0.0f, 0.0f, 1.0f),tmpVec;
	D3DXMATRIX Mat;
	Mat = gun.Base.Trans*stand.Base.Mat;
	//judg.SetPosM(&tmpVec, Mat);
	//D3DXVec3TransformNormal(&FrontVec, &D3DXVECTOR3(0.0f, 0.0f, 1.0f), &Mat);
	D3DXVec3TransformNormal(&tmpVec, &D3DXVECTOR3(0.0f, 0.0f, 1.0f), &gun.Base.Mat);
	tmpVec = D3DXVECTOR3(Mat._41 + tmpVec.x, Mat._42 + tmpVec.y, Mat._43 + tmpVec.z);
	judg.TarEndMat(&StartMat, Mat, &gun.Base.RotX, &gun.Base.RotY, tmpVec, FrontVec);
	StartRotY = gun.Base.RotY;
	StartRotX = gun.Base.RotX;
	judg.SetMatP(&StartMat, judg.SetPosM(Mat));
	//StartMat = StartRotX * (StartRotY*(Mat));
	judg.TarEndMat(&EndMat, Mat, &EndRotX, &EndRotY, targetPos, FrontVec);
}

bool MoveE::UpdateAI(CHARAData cd[], unsigned int NUM, std::vector<BillBase*>ground)
{
		if (NUM <= 0) {
			return false;
		}
		if (enemy.CH.Base.Flg == true) {
			judg.SetPosM(&targetPos, cd[0].NowMat);
			//銃の回転の初期化していいかの確認


			if (judg.ball(gun.Base.Mat, gun.Base.Trans*stand.Base.Mat, 2.0f) == false) {//バグ解決済み（首が無くなるバグ）
				gun.Base.AngX = 0.0f;
				gun.Base.AngY = 0.0f;
				D3DXMatrixRotationX(&gun.Base.RotX, D3DXToRadian((float)gun.Base.AngX));
				D3DXMatrixRotationY(&gun.Base.RotY, D3DXToRadian((float)gun.Base.AngY));
				NowGunVec = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
				gun.Base.Mat = gun.Base.Trans*stand.Base.Mat;
			}

			//攻撃命令
			if (AttaFlg(cd[0].NowGround) == false) {
				EneMovEndFlg = false;
			}
			//スピード管理
			//Speed *NextSpeed;
			////NextSpeed = speed->Action(&SpeedMul, &enemy.CH.Con.GroNum, &cd[0].NowGround);
			//if (NextSpeed != nullptr) {
			//	delete speed;
			//	speed = NextSpeed;
			//}
			//enemy.CH.Con.Speed = cd[0].Speed*SpeedMul;

			//回転
			if (EneMovEndFlg == true) {
				if ((GunMovEndFlg == false) && (GunMovFlg == false)) {
					GunMovFlg = true;
					GunAFlg = true;
					Move();
					GunRotFlg = true;
				}
			}
			if (GunAFlg == true) {//ロックオン
				if (plaJugFlg == true) {//レイがあたってたら
					countRay += 1;
				}
				else {
					if (LocAEndFlg == true) {
						GunRotFlg = true;
					}
				}
				if (countRay > LocCouEnd) {
					//スタンバイ
					ChaFlg(&GunAFlg, &LocAFlg);
					laserMan->SetLFlg(false);
					ChaFlg(&GunMovFlg, &GunMovEndFlg);
				}
			}
			if (LocAFlg == true) {//発射前
				CouLok += 1;
				if (CouLok > AttCouEnd) {
					InitM();
					InitEndF();
					AttFlg = true;
					countRay = 0;
					CouLok = 0;
				}
			}

			if (AttAEndFlg == true) {//発射後
				AttCount += 1;
				/*if ((AttCount > 10)&&(bul->GetBulFlg()==false)) {
					Move();
			        InitM();
			        InitEndF();
			        EneMovEndFlg = true;
				}*/
			}

			Move();

			if (GunRotFlg == true) {
				//銃の回転初期化
				ResGunAng();
				GunRotFlg = false;
			}

			if (MoveFlg == false) {

			}
			if (MoveFlg == true) {

			}
		}

		return true;
}

D3DXMATRIX MoveE::LocAMove()
{
	//銃をplayerに向ける処理
	D3DXMATRIX Mat,GunTmp;
	D3DXVECTOR3 Pos;
	Pos = gunEA->GetPos();
	D3DXMatrixTranslation(&gun.Base.Trans, Pos.x, Pos.y, Pos.z);
	GunTmp = gun.Base.Trans*stand.Base.Mat;
	D3DXVECTOR3 FrontVec(0.0f, 0.0f, 1.0f);
	StartMat = StartRotX * (StartRotY*(GunTmp));
	EndMat = EndRotX * (EndRotY*(GunTmp));
	if (judg.Quaternion(&Mat, StartMat, EndMat, &fAnim, 0.05f, GunAFlg) == false) {
		LocAEndFlg = true;
	}
	//Rotの計算
	D3DXVECTOR3 gunPos;
	D3DXVec3TransformNormal(&NowGunVec, &FrontVec, &Mat);
	D3DXVec3Normalize(&NowGunVec, &NowGunVec);
	judg.SetPosM(&gunPos, GunTmp);
	gunPos += NowGunVec;
	judg.TarEndMat(&GunTmp, GunTmp, &gun.Base.RotX, &gun.Base.RotY, gunPos, FrontVec);
	return Mat;
}

D3DXMATRIX MoveE::EneMove(std::vector<BillBase*>ground)
{
	D3DXMATRIX Mat;
	bool Flg = qGFlg;
	//if (Count == 60) {
	if (motion.Formove(enemy.CH.Con, &Mat, &Anime, ground, &qGFlg, &qFlg, &enemy.CH.Con.SpeedMul,enemy.CH.Con.SpeedMulJudg, &SqMat, &EqMat, &qVec, &cFlg, &cVec,CarFM.BodyHeight) == false) {
		Mat = enemy.CH.Base.Mat;
		}
	/*	Count = 1;
	}
	else {
		Count += 1;
		D3DXMATRIX Inv;
		D3DXMatrixInverse(&Inv, NULL, &enemy.CH.Base.Trans);
		Mat=Inv*enemy.CH.Base.Mat;
	}*/
	//Mat = enemy.CH.Base.Mat;
	//AngD = Anime;
	//当たり判定用のMat入れ
	enemy.CH.Con.JudgMat = Mat;
	Mat = enemy.CH.Base.Trans*Mat;
	return Mat;
}

D3DXMATRIX MoveE::GunMove()
{
	D3DXMATRIX Mat;
	D3DXVECTOR3 Pos;
	Pos = gunEA->GetPos();
	D3DXMatrixTranslation(&gun.Base.Trans, Pos.x, Pos.y, Pos.z);
	if (GunMovFlg == true) {
		if (GunAFlg == true) {
			return LocAMove();
		}
	}
	Mat = gun.Base.RotX*(gun.Base.RotY*(gun.Base.Trans*stand.Base.Mat));
	return Mat;
}

bool MoveE::UpdateBul(void)
{
	if (enemy.CH.Base.Flg == false) {
		AttFlg = false;
	}
	bool tmpFlg;
	tmpFlg = AttFlg;
	//bul->UpdateBME(NowMoveVec, gunEA->GetBullet(), &AttFlg);
	if ((tmpFlg == true) && (AttFlg == false)) {
		AttAEndFlg = true;
	}
	return true;
}

//bool MoveE::SetParts(std::vector<BillBase*> ground)
//{
//	if (enemy.CH.Base.Flg == true) {
//		judg.MatMatVec(&NowMoveVec, MoveMat, enemy.CH.Base.Mat);//MoveVec作成
//		EneUpdate();
//		D3DXMATRIX Pmat;//enemyから見た敵のMat
//		D3DXMatrixTranslation(&Pmat, targetPos.x, targetPos.y, targetPos.z);//作成
//		Pos2D = judg.Pos2DPE(enemy.CH.Base.Mat, Pmat);//矢印Pos作成
//		VectorUpdate();
//		UpdateTiM();
//		StaUpdate();
//		gun.Base.Mat = gun.Base.RotX*(gun.Base.RotY*(gun.Base.Trans*stand.Base.Mat));
//		//銃にMatを入れる
//		gunEA->Update(gun.Base.Mat);
//		//レーザー
//		D3DXMATRIX tmp;
//		D3DXMatrixTranslation(&tmp, 0.1f, 0.15f, 0.2f);
//		laserMan->UpdateS(gun.Base.Mat, tmp);
//	}
//	return true;
//}

bool MoveE::UpdateAll(std::vector<BillBase*> ground)
{
	if (enemy.CH.Base.Flg == true) {
		MoveMat = enemy.CH.Base.Mat;//移動前のMat代入
		enemy.CH.Base.Mat = EneMove(ground);
		judg.MatMatVec(&NowMoveVec, MoveMat, enemy.CH.Base.Mat);//MoveVec作成
		EneUpdate();
		D3DXMATRIX Pmat;//enemyから見た敵のMat
		D3DXMatrixTranslation(&Pmat, targetPos.x, targetPos.y, targetPos.z);//作成
		Pos2D = judg.Pos2DPE(enemy.CH.Base.Mat, Pmat);//矢印Pos作成
		VectorUpdate();
		TiUpdate();
		StaUpdate();
		gun.Base.Mat = GunMove();
		//銃にMatを入れる
		gunEA->Update(gun.Base.Mat);
		//レーザー
		D3DXMATRIX tmp;
		D3DXMatrixTranslation(&tmp, 0.1f, 0.15f, 0.2f);
		laserMan->UpdateS(gun.Base.Mat, tmp);
	}
	return true;
}

bool MoveE::UpdateEnd()
{
	if (enemy.CH.Base.Flg == true) {
		LaserUpdate();
	}
	//弾の移動補正
	if (UpdateBul() == false) {
	}
	return true;
}

bool MoveE::UpdateEndBullet()
{
	bul->UpdateBME();
	return true;
}

void MoveE::SetPlaEnd(bool Flg, D3DXVECTOR3 Speed)
{
	InitM();
	InitEndF();
	Move();
	PlaEndFlg = Flg;
}

QuaForMove MoveE::GetQuaForMove(void)
{
	Q.AnimeFrame = Anime;
	Q.BodyHeight = 0.7f;
	Q.CurFlg = cFlg;
	Q.CurVec = cVec;
	Q.EndMat = EqMat;
	Q.NowMat = enemy.CH.Base.Mat;
	Q.QuaInitFlg = qGFlg;
	Q.QuaMatInitFlg = qFlg;
	Q.SpeedMul = enemy.CH.Con.SpeedMul;
	Q.SpeedMul2 = enemy.CH.Con.SpeedMulJudg;
	Q.StartMat = SqMat;
	Q.WayVec = qVec;
	return Q;
}

bool MoveE::AttaFlg(unsigned int PlaNo)
{
	if ((enemy.CH.Con.GroNum <= PlaNo - 2))return false;
	if ((enemy.CH.Con.GroNum >= PlaNo + 2)) return false;
	EneMovEndFlg = true;
	return true;
}
