#pragma once
#include<d3dx9.h>
#include"GunE.h"
#include"../Ground/BillBase.h"
#include<vector>
#include"../EnemyData/Base&Manager/EnemySpeed.h"

class MoveE:public GunE{
public:
	//Moveの確認
	void Move();
	void ChaFlg(bool *NowFlg, bool *NextFlg);
	//初期化
	void InitM();
	//EndFlg初期化
	void InitEndF();
	MoveE() { InitM(); };
	MoveE(D3DXMATRIX GroundMat, float *TransX);
	~MoveE();
	bool UpdateAI(CHARAData cd[], unsigned int NUM,std::vector<BillBase*>ground);
	//Enemyカーブ
	//Gun回転初期化
	void ResGunAng();
	//Gun回転
	D3DXMATRIX LocAMove();
	//enemy移動
	D3DXMATRIX EneMove(std::vector<BillBase*>ground);
	//gun固定
	D3DXMATRIX GunMove();
	//発射
	bool UpdateBul(void);
	//bool SetParts(std::vector<BillBase*>ground);
	//アップデート
	bool UpdateAll(std::vector<BillBase*>ground);
	//アップデートEnd
	bool UpdateEnd();
	//弾の移動
	bool UpdateEndBullet();
	void SetPlaRayFlg(bool Flg) {
		plaJugFlg = Flg;
	}
	bool GetLaserFlg(void) {
		return laserMan->GetLFlg();
	}
	//ターゲットの初期化
	void SetPlaEnd(bool Flg, D3DXVECTOR3 Speed);
	//前進判定用関数-----------------------------------------------
	//移動の情報を渡す
	QuaForMove GetQuaForMove(void);
	//移動ベクトルの長さ入れ
	void SetQuaVecSize(float size) {
		enemy.CH.Con.SpeedMulJudg = size;
	}
	//前進判定用の移動ベクトル渡し
	D3DXVECTOR3 GetForMoveVec(int i) {
		return ForMoveVec[i];
	}
	//前進判定用の移動ベクトル入れ
	void SetForMoveVec(D3DXVECTOR3 Vec,int i) {
		ForMoveVec[i] = Vec;
	}
	//前進判定用の移動後Mat渡し
	D3DXMATRIX GetForMoveEndMat(void) {
		return ForMoveEndMat;
	}
	//前進判定用の移動後Mat入れ
	void SetForMoveEndMat(D3DXMATRIX Mat) {
		ForMoveEndMat = Mat;
	}
	//攻撃命令
	bool AttaFlg(unsigned int PlaNo);

	//--------------------------------------------------------------
private:
	//Flg
	bool MoveFlg;//動いているかどうか
	bool EneMovEndFlg;
	bool GunMovFlg;//銃の移動
	bool GunMovEndFlg;
	bool CurAFlg;//車線変更
	bool LocAFlg;//ロックオン
	bool LocAEndFlg;
	int CouLok;
	bool AttFlg;
	bool GunAFlg;
	bool AttAFlg;//攻撃命令
	bool AttAEndFlg;
	int AttCount;
	bool GunRotFlg;

	int LocCouEnd;//
	int AttCouEnd;//

	bool plaJugFlg;//playerにレイが当たっているかどうか
	int countRay;//plaRayFlgがtrueの時、カウント
	D3DXMATRIX StartRotX, StartRotY, EndRotX, EndRotY;//GunA

	bool PlaEndFlg;//playerが死んだ確認

	D3DXVECTOR3 NowGunVec;

	D3DXVECTOR3 NowMoveVec;

	//クォータニオン前進用
	float Anime;
	D3DXMATRIX SqMat, EqMat;
	bool qFlg, qGFlg, cFlg;
	unsigned int GroNo;
	float NowSpeed;
	int Count;
	D3DXVECTOR3 qVec, cVec;
	D3DXMATRIX MoveMat;
	//前進判定用--------------
	QuaForMove Q;//前進判定用クォータニオン
	D3DXMATRIX ForMoveEndMat;//前進完了時のMat
	D3DXVECTOR3 ForMoveVec[3];//移動前から移動後のVec
	//------------------------
	//スピード管理
	//SpeedMove EneSpe;
	Speed *speed;
	float SpeedMul;
	int NowCount, MaxCount;
	//------------------------
};