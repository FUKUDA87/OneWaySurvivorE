#pragma once
#include<d3dx9.h>
#include"Struct.h"
#include"../Ground/Ground_Object.h"
#include<vector>
#include"Judgment.h"
#include"../Key/Key.h"
#include<math.h>

extern Key key;

class Motion {
public:
	Motion();
	//自分ベジェ曲線
	bool Formove(const CONSTITUTION *Con, D3DXMATRIX *Car_Mat, float *Anime, std::vector<C_Ground_Object*>ground, bool *QuaInitFlg,
		bool *QuaMatInitFlg, float *SpeedMul,float SpeedMul2, D3DXMATRIX *StartMat, D3DXMATRIX *EndMat,
		D3DXVECTOR3 *WayVec, bool *CurFlg, D3DXVECTOR3 *CurVec,float BodyHeight);
private:
	float CurSize;//ベジェ曲線の長さ１に対しての長さ

	//カーブMove
	bool CurveMove(D3DXMATRIX *TransMat, D3DXMATRIX StartMat, D3DXMATRIX EndMat, float *AnimeFarme, float Up);
	//playerを傾かせる
	bool CurveMove(D3DXMATRIX *TransMat, D3DXMATRIX StartMat, D3DXMATRIX RotMat, D3DXMATRIX EndMat, float *AnimeFarme, float Up, bool *Reverse);

	float CurveFloat(float A, float B, float C, float AnimeFlame);
	D3DXVECTOR3 CurvePos(D3DXMATRIX MatS, D3DXVECTOR3 PosV, D3DXMATRIX MatE, float AnimeFlame);
};