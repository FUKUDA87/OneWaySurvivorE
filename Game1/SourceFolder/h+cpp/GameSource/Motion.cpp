#include "Motion.h"
#include"../GameSource/Judgment.h"

Motion::Motion()
{
	CurSize = 0.0365f;
}

float Motion::CurveFloat(float A, float B, float C, float AnimeFlame)
{
	return (pow((1.0f - AnimeFlame), 2.0f)*A + 2 * (1.0f - AnimeFlame)*AnimeFlame*B + pow(AnimeFlame, 2.0f)*C);
}

D3DXVECTOR3 Motion::CurvePos(D3DXMATRIX MatS, D3DXVECTOR3 PosV, D3DXMATRIX MatE, float AnimeFlame)
{
	D3DXVECTOR3 Pos;
	Pos.x = CurveFloat(MatS._41, PosV.x, MatE._41, AnimeFlame);
	Pos.y = CurveFloat(MatS._42, PosV.y, MatE._42, AnimeFlame);
	Pos.z = CurveFloat(MatS._43, PosV.z, MatE._43, AnimeFlame);
	return Pos;
}

bool Motion::Formove(const CONSTITUTION *Con, D3DXMATRIX * Car_Mat, float * Anime, std::vector<C_Ground_Object*> ground,
	bool * QuaInitFlg, bool * QuaMatInitFlg ,float *SpeedMul, float SpeedMul2 , D3DXMATRIX * StartMat,
	D3DXMATRIX * EndMat, D3DXVECTOR3 * WayVec,bool *CurFlg,D3DXVECTOR3 *CurVec, float BodyHeight)
{
	Judg judg;

	bool OverFlg = false;//クォータニオンの1.0fを超えたときのFlg

	bool EndFlg = false;//クォータニオン終了Flg

	float VecSize,CurDrawSpeed=1.0f;

	while (EndFlg != true) {
		//地面のナンバーと次のナンバー
		unsigned int GNo = Con->GroNum, NextGNo = GNo + 1;
		//AnimeFrameが1.0fを超えていた判定
		if (OverFlg == true) {
			//地面が有無確認
			if (ground.size() <= 0) {
				return false;
			}
			//レイ判定時のレイの長さ入れ用
			float Dis;
			//地面レイ判定
			bool JudgFlg = false;
			for (unsigned int g = 0; g < ground.size(); g++) {

				float L_Radius = 40.0f;
				//自分の周囲の地面だけを判定
				if (judg.BallJudg(&judg.SetPosM(Car_Mat), &judg.SetPosM(&ground[g]->GetMat()), &L_Radius) != true) continue;
					D3DXVECTOR3 v[4];
					for (int i = 0; i < 4; i++) {
						v[i] = ground[g]->GetVer(i);
					}

					bool L_IdenFlg = ground[g]->GetIdenFlg();

					//レイ判定
					if (judg.RayJudg_Polygon(&judg.SetPosM(Car_Mat), &D3DXVECTOR3(0.0f, -1.0f, 0.0f), &ground[g]->GetMat(),
						&v[0], &v[1], &v[2], &v[3], &Dis, &L_IdenFlg) == true) {

						//レイが当たった時の処理

						GNo = g;
						NextGNo = GNo + 1;
						JudgFlg = true;
						break;

					}
				
			}
			//判定
			if (JudgFlg == false) {
				//当たっていない
				return false;
			}
		}
		//次の地面の有無
		if (ground.size() - 1 < (unsigned int)(NextGNo)) {
			//無いとき
			return false;
		}
		bool CurInitFlg = false,CurveFlg=true;
		//地面の形
		unsigned int Type = ground[GNo]->GetWay().WayType;
		//初期化
		if (*QuaInitFlg == false) {
			//初期化した
			*QuaInitFlg = true;
			//Flg = true;
			D3DXVECTOR3 Vec;
			//カーブ判定Flg
			bool CurHeikinFlg = false;
			//カーブの速度調整判定
			if ((Type == 0) && (ground[NextGNo]->GetWay().WayType == 0)) {
				CurveFlg = false;
			}
			//カーブの判定
			if (CurveFlg == true) {
				float Ang;
				if (Type != 0) {
					Ang = ground[GNo]->GetWay().Ang;
				}
				else {
					Ang = 0.0f;
				}
				bool NoFlg = false;
				//カーブの探索
				for (unsigned int g = NextGNo; g < ground.size(); g++) {
					if ((ground[g]->GetWay().WayType == Type) || (Type == 0)) {
						Type = ground[g]->GetWay().WayType;
					}
					else {
						NextGNo = g;
						NoFlg = true;
						break;
					}
					if(Ang < 90.0f) {
						Ang += ground[g]->GetWay().Ang;
						if (Ang > 90.0f) {
							NextGNo = g-1;
							NoFlg = true;
							break;
						}
					}
				}
				//見つからなかった時
				if (NoFlg == false) {
					return false;
				}
			}
			//カーブの速度調整
			if(Type!=0){
				//カーブ
				*SpeedMul = 1.1f;
			}
			else {
				//ストレート
				*SpeedMul = 1.0f;
			}
			//startからendまでのVec計算
			judg.MatMatVec(&Vec, ground[GNo]->GetWay().StartMat, ground[NextGNo]->GetWay().StartMat);
			*WayVec = Vec;
			//ベジェ曲線の判定
			if (Type!=0) {
				*CurFlg = true;
				CurInitFlg = true;
			}
			else {
				*CurFlg = false;
			}
		}
		//startMatとendMatのセット
		if (*QuaMatInitFlg == false) {
			*StartMat = ground[GNo]->GetWay().StartMat;
			*EndMat = ground[NextGNo]->GetWay().StartMat;
			*QuaMatInitFlg = true;
		}
		//ベジェ曲線の計算
		if (CurInitFlg == true) {
			D3DXMATRIX Mat, MatE, RotX, RotY;
			D3DXVECTOR3 wVec = *WayVec / 2.0f, wPos;
			D3DXMatrixTranslation(&Mat, 0.0f, 0.0f, 0.0f);
			judg.TarEndMat(&MatE, Mat, &RotX, &RotY, *WayVec, D3DXVECTOR3(0.0f, 0.0f, 1.0f));
			judg.SetPosM(&wPos, StartMat);
			judg.SetMatP(&MatE, &(wPos + wVec));
			float Size=0.0f,LR=1.0f;
			if (Type==1) {
				LR *= -1.0f;
			}
			D3DXVECTOR3 Vec;
			for (unsigned int i = GNo; i < NextGNo; i++) {
				judg.MatMatVec(&Vec, ground[i]->GetWay().StartMat, ground[i + 1]->GetWay().StartMat);
				Size += D3DXVec3Length(&Vec);
			}
			Size += D3DXVec3Length(WayVec);
			D3DXVec3TransformCoord(CurVec, &D3DXVECTOR3(CurSize*(float)(NextGNo-GNo)*Size*LR, 0.0f, 0.0f), &MatE);
		}
		//スピードの計算
		if (OverFlg ==false) {
			if (*CurFlg == true) {//カーブ時にスピードを遅くする
				CurDrawSpeed = 0.8f;
			}
			else {
				CurDrawSpeed = 1.0f;
			}
			float Size = D3DXVec3Length(WayVec),NowSpeed= D3DXVec3Length(&Con->Speed)*SpeedMul2;
			Size *= *SpeedMul;
			float Speed =NowSpeed*CurDrawSpeed / Size;
			*Anime += Speed;
		}
		else {
			//オーバー時の処理
			float wVec;
			wVec = D3DXVec3Length(WayVec);
			wVec *= *SpeedMul;
			wVec = VecSize / wVec;
			*Anime += wVec;
		}
		bool qeFlg = false;
		//オーバー時の計算
		if (*Anime > 1.0f) {
			D3DXVECTOR3 Vec;
			Vec = *WayVec;
			VecSize = D3DXVec3Length(&(Vec*(*Anime) - Vec));
			*Anime = 1.0f;
			OverFlg = true;
			qeFlg = true;
		}
		else {
			EndFlg = true;
		}
		//クォータニオン
		judg.AnimeProc(Car_Mat, *StartMat, *EndMat, *Anime);
		//ベジェ曲線のクォータニオン
		if (*CurFlg == true) {
			D3DXVECTOR3 Pos;
			Pos = CurvePos(*StartMat, *CurVec, *EndMat, *Anime);
			judg.SetMatP(Car_Mat, &Pos);
		}
		//クォータニオンの終了処理
		if (qeFlg == true) {//前進
			*QuaInitFlg = false;
			*QuaMatInitFlg = false;
			*Anime = 0.0f;
		}
		//高さ処理
		D3DXMATRIX Tmp;
		D3DXMatrixTranslation(&Tmp, 0,BodyHeight, 0);
		*Car_Mat = Tmp * (*Car_Mat);
		//終了処理
		if (EndFlg == true) {
			break;
		}
	}
	return true;
}

bool Motion::CurveMove(D3DXMATRIX * TransMat, D3DXMATRIX StartMat, D3DXMATRIX EndMat, float * AnimeFarme, float Up)
{
	Judg judg;
	bool MoveFlg = true;
	*AnimeFarme += Up;
	if (*AnimeFarme > 1.0f) {
		*AnimeFarme = 1.0f;
		MoveFlg = false;
	}
	judg.AnimeProc(TransMat, StartMat, EndMat, *AnimeFarme);
	if (MoveFlg == false) {
		*AnimeFarme = 0.0f;
	}
	return MoveFlg;
}

bool Motion::CurveMove(D3DXMATRIX * TransMat, D3DXMATRIX StartMat, D3DXMATRIX RotMat, D3DXMATRIX EndMat, float * AnimeFarme, float Up, bool * Reverse)
{
	Judg judg;
	bool MoveFlg = true;
	*AnimeFarme += Up;
	if (*AnimeFarme > 1.0f) {
		*AnimeFarme = 1.0f;
		MoveFlg = false;
	}
	if (*Reverse == false) {
		judg.AnimeProc(TransMat, StartMat, RotMat, *AnimeFarme);
	}
	else {
		judg.AnimeProc(TransMat, RotMat, EndMat, *AnimeFarme);
	}
	if (MoveFlg == false) {
		*AnimeFarme = 0.0f;
		if (*Reverse == false) {
			MoveFlg = true;
			*Reverse = true;
		}
		else {
			*Reverse = false;
		}
	}
	return MoveFlg;
}
