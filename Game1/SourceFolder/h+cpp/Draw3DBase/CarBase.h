#pragma once
#include<d3dx9.h>
#include"../GameSource/Struct.h"
#include<vector>
#include"../Ground/BillBase.h"
#include"../Draw3DBase/Draw3DManager/CarMeshManager.h"
#include"../GameSource/CharaBase.h"
#include"../Draw/Hp/Hp_New.h"

class C_CarBase:public C_Hp_Draw_New {
public:
	C_CarBase();
	~C_CarBase();

	//初期化
	void InitCar(void);

	//アップデート
	virtual bool UpdateCar(void);
	//前進アップデート
	virtual bool UpdateCarFM(std::vector<BillBase*>ground);

	//3D表示
	virtual void Draw3DCar(void);

	//パーツの位置調整
	virtual void SetParts(std::vector<BillBase*>ground);

	//==========================================
	//Get・Set
	//==========================================
	//車体行列渡し
	D3DXMATRIX GetMatCar(void) {
		return Car.Base.Mat;
	}
	//車体行列入れ
	void SetMatCar(const D3DXMATRIX *Mat) {
		Car.Base.Mat = *Mat;
	}
	//車の表示行列渡し
	virtual D3DXMATRIX GetDrawMatCar(void) {
		return judg.GetDrawMat(&Car.Base.Mat, &Car.Base.Scal, &Car.Base.ScaPos);
	}
	//今いる地面のNo入れ
	void SetGroNum(unsigned int GroundNo) {
		Car.Con.GroNum = GroundNo; 
	};
	//今いる地面のNo渡し
	unsigned int GetGroNum(void) {
		return Car.Con.GroNum; 
	};
	////今のHp渡し
	//int GetHP(void) {
	//	return Car.Sta.NowHp; 
	//};
	//今のHp入れ
	virtual bool SetHP(int Damage);

	//今のHp入れ(壁と弾の区別付)
	virtual bool SetHP(int Damage,bool WallFlg);

	//車のモデル渡し
	LPD3DXMESH GetMeshCar() {
		return Car.Mesh.lpMesh;
	}
	//車の存在Flg渡し
	bool GetFlgCar(void) {
		return Car.Base.Flg;
	}
	//車の存在Flg入れ
	void SetFlgCar(bool *Flg) {
		Car.Base.Flg=*Flg;
	}
	//当たり判定の半径渡し
	float GetBodRadCar(void) {
		return Car.Base.BodRad;
	}
	//当たり判定用のMat渡し
	D3DXMATRIX GetJudgMatCar() {
		return Car.Con.JudgMat;
	}
	//playerのTransMat渡し
	D3DXMATRIX GetTransMatCar(void) {
		return Car.Base.Trans;
	}
	//playerのTransMat入れ
	void SetTransMatCar(D3DXMATRIX *TransMat) {
		Car.Base.Trans = *TransMat;
	}
	//コリジョンモデル渡し
	LPD3DXMESH GetColMod(void) {
		return Car.Con.ColModMesh.lpMesh;
	}
	//移動の情報渡し
	CONSTITUTION GetCon(void) {
		return Car.Con;
	}
	//スピード渡し
	D3DXVECTOR3 GetSpeedCar(void) {
		return Car.Con.Speed;
	}
	//スピード入れ
	void SetSpeedCar(D3DXVECTOR3 spe) {
		Car.Con.Speed = spe;
	}
	//スピード渡し
	int GetNowSpeedCar(void) {
		return Car.Con.NowSpeed;
	}
	//スピード入れ
	void SetNowSpeedCar(int spe) {
		Car.Con.NowSpeed = spe;
	}


	//空中の敵Flg渡し
	bool GetSkyType(void) {
		return SkyType;
	}

	//弾出現情報入れ
	void SetBPos(D3DXVECTOR3 RayPos, bool RayJudgFlg);

	//player情報
	CHARAData GetData(void);

	//拡大渡し
	D3DXVECTOR3 GetScalPosCar(void) {
		return Car.Base.ScaPos;
	}

	//前進判定用関数-----------------------------------------------
	//移動の情報を渡す
	QuaForMove GetQuaForMove(void);
	//移動ベクトルの長さ入れ
	void SetQuaVecSize(float size) {
		Car.Con.SpeedMulJudg = size;
	}
	//前進判定用の移動ベクトル渡し
	D3DXVECTOR3 GetForMoveVec(int i) {
		return ForMoveVec[i];
	}
	//前進判定用の移動ベクトル入れ
	void SetForMoveVec(D3DXVECTOR3 Vec, int i) {
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

	//無敵アップデート
	bool UpdateCountM(void);

	//矢印作成に必要な情報の取得とアップデート
	virtual void GetPos2DSet(const D3DXMATRIX *mProj, const D3DXMATRIX *mView, const D3DVIEWPORT9 *Viewport) {};

	//移動ベクトル渡し
	D3DXVECTOR3 GetMoveVec(void) {
		return brj.MoveVec;
	}

	//前の車の位置のセット
	void SetCarMoveMat(void) {
		PlaMovMat = Car.Base.Trans*Car.Con.JudgMat;
	}

	//カメラの行列のセット
	virtual void Set_CameraMat(const D3DXMATRIX *CameraMat) {
		M_S_Gun_Update_Data.CameraMat = *CameraMat;
	}

protected:
	//車のモデル入れ
	void SetMeshCar(int MeshNo);

	//車の情報
	CHARA3D Car;

	//ダメージフラグ
	bool DamageFlg;

	QuaForMove CarFM;

	//空中の敵か判定用Flg
	bool SkyType;

	D3DXMATRIX PlaMovMat;//playerの移動前のMat

	//バレット用
	BULLETRAYJUDG brj;

	Judg judg;

	//手動と自動の操作情報を入れるクラス
	S_GUN_UPDATE_DATA M_S_Gun_Update_Data;

private:
	C_CarMeshManager carMeshManager;

	//前進クォータニオン用
	D3DXMATRIX ForMoveEndMat;//前進完了時のMat
	D3DXVECTOR3 ForMoveVec[3];//移動前から移動後のVec
	QuaForMove Q;//前進判定用クォータニオン

	//無敵タイム
	int CountMNum,CountMStart;

	//操作の構造体の初期化
	void Init_S_Gun_Update_Data(void);

};