#pragma once
#include<d3dx9.h>
#include"Struct.h"

#ifndef Judgm_H
#define Judgm_H

extern LPDIRECT3DDEVICE9 lpD3DDevice;


class Judg {
private:
	//pos2D用
	D3DXMATRIX SmProj;
	D3DXMATRIX SmView;
	D3DVIEWPORT9 SViewport;
	bool D2Flg;
public:
	void Init(){ D2Flg = false; }
	Judg() { Init(); };
	//距離判定
	bool ball(D3DXMATRIX mat1, D3DXMATRIX mat2,float rad);
	bool ball(D3DXVECTOR3 PosA, D3DXMATRIX MatB, float Rad);
	//距離判定+球と球
	bool ball(D3DXMATRIX mat1, D3DXMATRIX mat2, float rad, D3DXMATRIX *Trans1, D3DXMATRIX *Trans2);
	//距離判定+距離取得
	float ball(D3DXMATRIX mat1, D3DXMATRIX mat2);
	//距離判定+Hp
	bool ball(judgDeta *jd, D3DXMATRIX matB, float radB, int damB);
	//Hpの処理
	bool HPj(int *NowHp, int *NowMaxHp);
	//レイと四角ポリゴン判定M
	bool RayPolM(D3DXMATRIX mat,D3DXVECTOR3 v0, D3DXVECTOR3 v1, D3DXVECTOR3 v2, D3DXVECTOR3 v3, D3DXMATRIX pmat, D3DXVECTOR3 ray, float *Dis);
	//レイと四角ポリゴン判定P
	bool RayPolP(D3DXVECTOR3 Pos, D3DXVECTOR3 v0, D3DXVECTOR3 v1, D3DXVECTOR3 v2, D3DXVECTOR3 v3, D3DXMATRIX pmat, D3DXVECTOR3 ray, float *Dis);
	bool RayPolP(D3DXVECTOR3 Pos, D3DXVECTOR3 v0, D3DXVECTOR3 v1, D3DXVECTOR3 v2, D3DXVECTOR3 v3, D3DXVECTOR3 ray, float *Dis);
	bool RayPolM(D3DXMATRIX Mat, D3DXVECTOR3 v0, D3DXVECTOR3 v1, D3DXVECTOR3 v2, D3DXVECTOR3 v3, D3DXVECTOR3 ray, float * Dis);
	//3Dから2Dの座標取得
	D3DXVECTOR3 Pos2D(D3DXVECTOR3 pos3D);
	///3Dから2Dのため
	void Pos2Dpvv(D3DXMATRIX mProj, D3DXMATRIX mView, D3DVIEWPORT9 Viewport);
	//3Dから2Dの座標取得+playerとenemyの逆位置作成
	D3DXVECTOR3 Pos2DPE(D3DXMATRIX eMat,D3DXMATRIX pMat);
	//Ang計算
	double Ang(D3DXVECTOR3 pla, D3DXVECTOR3 tar, D3DXVECTOR3 vec);
	//レイMesh
	bool Mesh(D3DXVECTOR3 pos, D3DXVECTOR3 vec, D3DXMATRIX mat,LPD3DXMESH mesh, float *Dis);
	//int Vec=前なら０、後ろなら１、左なら２、右なら３
	bool Mesh(D3DXMATRIX MatA,int VecNumA, float BodyRadA,D3DXMATRIX MatB, LPD3DXMESH MeshB);
	bool Mesh(D3DXVECTOR3 pos, D3DXVECTOR3 vec, D3DXMATRIX mat, LPD3DXMESH mesh, float *Dis, int m);
	//外積内積
	bool CroDot(D3DXMATRIX mat, D3DXMATRIX *rot, D3DXVECTOR3 targetPos, D3DXVECTOR3 FrontVec, double *Ang,double ang, bool angF);
	//tragetX回転用(ミサイル回転)
	bool TarRotX(D3DXMATRIX mat, D3DXMATRIX * rotX, D3DXVECTOR3 targetPos, D3DXVECTOR3 FrontVec);
	//tragetY回転用(カツオ回転)
	bool TarRotY(D3DXMATRIX mat,D3DXMATRIX *rotY,  D3DXVECTOR3 targetPos, D3DXVECTOR3 FrontVec);
	//tragetEndMat作成
	bool TarEndMat(D3DXMATRIX *mat,D3DXMATRIX TransMat, D3DXMATRIX * RotXMat, D3DXMATRIX *RotYMat, D3DXVECTOR3 TargetPos, D3DXVECTOR3 FrontVec);
	//Pos<-Mat
	D3DXVECTOR3 SetPosM(D3DXMATRIX Mat);
	bool SetPosM(D3DXVECTOR3 *Pos,D3DXMATRIX Mat);
	//Mat<-Pos
	D3DXMATRIX SetMatP(D3DXVECTOR3 Pos);
	bool SetMatP(D3DXMATRIX *Mat, D3DXVECTOR3 Pos);
	//クォータニオン==============================================================================================
	//アニメーション
	bool AnimeProc(D3DXMATRIX *NowMat, D3DXMATRIX StartMat, D3DXMATRIX EndMat, float AnimeFrame);
	bool AnimeProc(D3DXVECTOR3 *NowPos, D3DXVECTOR3 StartPos, D3DXVECTOR3 EndPos, float AnimeFrame);
	//AnimeFrame+=
	bool AnimeFrameInc(float *AnimeFrame, float up, bool upFlg);
	//アニメーション+AnimeFrame+=
	bool Quaternion(D3DXMATRIX *NowMat, D3DXMATRIX StartMat, D3DXMATRIX EndMat, float *AnimeFrame, float up, bool upFlg);
	bool Quaternion(D3DXVECTOR3 *NowPos, D3DXVECTOR3 StartPos, D3DXVECTOR3 EndPos, float *AnimeFrame, float up, bool upFlg);
	//レイ判定のDisをPos変換
	D3DXVECTOR3 DisPos(D3DXVECTOR3 PosA, D3DXVECTOR3 PosB, float Dis);
	//ビルボード
	D3DXVECTOR3 Billboard(const D3DXVECTOR3 OldPos, const D3DXVECTOR3 NowPos, const D3DXVECTOR3 camPos, const float Size);
	//ビルボード＋板ポリ対応
	D3DXVECTOR3 Billboard(const D3DXVECTOR3 OldPos, const D3DXVECTOR3 NowPos,const float Size,const bool Reverse);
	//線とレイ2D
	bool LineLine(const D3DXVECTOR2 PosA, const D3DXVECTOR2 VecA, const D3DXVECTOR2 PosB, const D3DXVECTOR2 VecB, float *Dis);
	//画像の半分サイズ
	D3DXVECTOR2 HalfSize(const D3DXVECTOR3 sPos, const int Width, const int Height);
	//2Dの画像の枠計算
	bool PlaneP(RECT *rc, const D3DXVECTOR3 PosA, const D3DXVECTOR3 sPos, const int Width, const int Height);
	//2D画像クリック(四角形)
	bool PlaneCri(const D3DXVECTOR3 PosA, const D3DXVECTOR3 sPos, const int Width, const int Height);
	bool PlaneCri(const D3DXMATRIX MatA, const D3DXVECTOR3 sPos, const int Width, const int Height);
	//マウス位置
	POINT GetPoint(void);
	//rayray3D
	bool LineLine3D(D3DXVECTOR3 *GetPos, D3DXVECTOR3 PosA1, D3DXVECTOR3 PosA2, D3DXVECTOR3 PosB1, D3DXVECTOR3 PosB2);
	//vectorPos
	D3DXVECTOR3 VecPos(D3DXMATRIX MatA, D3DXVECTOR3 PosB);
	//vectorTrans
	D3DXMATRIX VecTransMat(D3DXVECTOR3 VecA);
	//**Mat入れ
	bool SetppMat(D3DXMATRIX *Mat, D3DXVECTOR3 PosA, D3DXVECTOR3 PosB, D3DXVECTOR3 PosC, int RailNum, bool bc);
	//Vec=MatB-MatA
	bool MatMatVec(D3DXVECTOR3*Vec, D3DXMATRIX MatA, D3DXMATRIX MatB);
	D3DXVECTOR3 MatMatVec(D3DXMATRIX MatA, D3DXMATRIX MatB);
	bool VecMatIn(D3DXMATRIX *Mat, D3DXVECTOR3 Vec);
	//Speedクォータニオン変数
	bool SetFloatQ(float *f);
	bool SetFloatQ(D3DXVECTOR3 *Pos);
	float SlashFloat(float fA, float fB);
	//floatの大きい比較
	bool BigFloat(float *fA, float fB);
	//floatの小さい比較
	bool SmallFloat(float *fA, float fB);
	//半径を求める
	float GetRad(XFILE *Mesh, DWORD *NumVertex, D3DXVECTOR3 *PosBig, D3DXVECTOR3 *PosSmall);
	float GetRad(XFILE *Mesh, DWORD *NumVertex, D3DXVECTOR3 *PosBig, D3DXVECTOR3 *PosSmall,bool a);
	//リバースFlg
	void ReverseFlg(bool *Flg);
	//リバースFlg
	bool ReverseFlg2(const bool *Flg);
	//スケイリングMat入れ
	void ScalingMat(D3DXMATRIX *ScalMat, const D3DXVECTOR3 *Pos);
	//RotXの初期化
	void InitRotX(const D3DXMATRIX * Mat,D3DXMATRIX*RotX);
	//クォータニオン構造体の初期化関数
	QuaAnimeC InitQuaAnime(const D3DXMATRIX *StartMat, const D3DXMATRIX *EndMat, const float *NowAnime, const float *AnimeFrame);
	//初期化１
	void InitMatPos(D3DXMATRIX *Mat, D3DXVECTOR3 *TransPos, D3DXVECTOR3 *ScalPos);
	//移動行列のセット
	void SetTransMat(D3DXMATRIX *TransMat, const D3DXVECTOR3 *TransPos);
	//表示用の行列作成
	D3DXMATRIX GetDrawMat(const D3DXMATRIX *Mat,D3DXMATRIX *ScalMat, const D3DXVECTOR3 *ScalPos);
	D3DXMATRIX GetDrawMat(const D3DXMATRIX *Mat,const D3DXVECTOR3 *ScalPos);
	//初期化２
	BASE3D GetInitBase3D(const D3DXVECTOR3 *InitPos, const D3DXVECTOR3 *TransPos, const D3DXVECTOR3 *ScalPos, const double * AngX, const  double * AngY, const  double * AngZ);
	//判定用の拡大を含めた移動行列の作成
	D3DXMATRIX GetTransMatScal(const D3DXVECTOR3 *TransPos, const D3DXVECTOR3* ScalPos);
	//行列の合成(MatA*MatB)
	D3DXMATRIX GetMatY(const D3DXMATRIX *MatA, const D3DXMATRIX *MatB);
	//ベクトルの掛け算
	D3DXVECTOR3 GetVecVec(const D3DXVECTOR3 *VecA, const D3DXVECTOR3 *VecB);
	//ベクトルの割り算
	D3DXVECTOR3 GetVecVec_S(const D3DXVECTOR3 *VecA, const D3DXVECTOR3 *VecB);
	//位置の初期化(Gunバージョン)
	BASE3D InitGunParts(const Object3DGun* Init);
	//位置の初期化(Gunバージョン)
	Object3DGun InitSetPartsData(const float AngX,const float AngY,const float AngZ,const D3DXVECTOR3 *TransPos, const D3DXVECTOR3 *ScalPos,const bool DrawFlg);
	//初期化構造体
	S_GUN_DRAW_NO GetInitGUNDRAWNOS(const int GunNo, const int BulletNo, const int MuzFlaNo, const int LaserNo);
	//煙の構造体の初期化
	S_Smog GetInitSmog(const D3DXVECTOR3 *MoveVec,const D3DXVECTOR3 *Frame,const int Alpha, const int AStart, const int AUp,const float PolSize, const float PolBit,const float PolBitUp,const S_Random *Random);
	//乱数の初期化
	S_Random GetInitRand(const int x, const int y, const int z);
	//単位行列渡し
	D3DXMATRIX Get_IdenMat(void);
	//初期化行列渡し
	D3DXMATRIX Get_Mat_Init(void);
	//送られてきた番号の検索
	bool Hit_No(const unsigned int *No,const unsigned int *NoNum);
};

#endif // !Judgm_H

/*
#include"Judgment.h"

extern Judg *judg;
*/