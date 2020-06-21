#pragma once
#include<d3dx9.h>
#include"../GameSource/Struct.h"
#include<vector>
#include"../Ground/Ground_Object.h"
#include"../Draw3DBase/Draw3DManager/CarMeshManager.h"
#include"../GameSource/CharaBase.h"
#include"../GameSource/Const.h"

class C_CarBase:public C_CharaBase {
public:
	C_CarBase();

	//初期化
	void InitCar(void);

	//アップデート
	virtual bool UpdateCar(void);
	//前進アップデート
	virtual bool UpdateCarFM(std::vector<C_Ground_Object*>ground);

	//3D表示
	virtual void Draw3DCar(void);

	//パーツの位置調整
	virtual void SetParts(std::vector<C_Ground_Object*>ground);

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
	void SetGroNum(const unsigned int *GroundNo) {
		Car.Con.GroNum = *GroundNo; 
	};
	
	//死亡確認(trueで死)
	bool Dead(void);

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
	void SetFlgCar(const bool *Flg) {
		Car.Base.Flg=*Flg;
	}
	//当たり判定の半径渡し
	float GetBodRadCar(void) {
		return Car.Base.BodRad;
	}
	
	//playerのTransMat渡し
	D3DXMATRIX GetTransMatCar(void) {
		return Car.Base.Trans;
	}
	//playerのTransMat入れ
	void SetTransMatCar(const D3DXMATRIX *TransMat) {
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
	
	//スピード入れ
	void SetSpeedCar(const D3DXVECTOR3 *spe) {
		Car.Con.Speed = *spe;
	}
	
	//スピード入れ
	void SetNowSpeedCar(int spe) {
		Car.Con.NowSpeed = spe;
	}


	//衝突判定の状態の渡し
	int Get_JudgeType(void) {
		return M_JudgeType;
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
	void SetQuaVecSize(const float *size) {
		CarFM.SpeedMulJudg = *size;
	}
	//前進判定用の移動ベクトル渡し
	D3DXVECTOR3 GetForMoveVec(const int *i) {
		return ForMoveVec[*i];
	}
	//前進判定用の移動ベクトル入れ
	void SetForMoveVec(const D3DXVECTOR3 *Vec,const int *i) {
		ForMoveVec[*i] = *Vec;
	}
	//前進判定用の移動後Mat渡し
	D3DXMATRIX GetForMoveEndMat(void) {
		return ForMoveEndMat;
	}
	//前進判定用の移動後Mat入れ
	void SetForMoveEndMat(const D3DXMATRIX *Mat) {
		ForMoveEndMat = *Mat;
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

	//操作・動作できるまでの時間の渡し
	int Get_Move_Stop_Time(void) {
		return MMove_Stop_Time;
	}

	//操作・動作できるまでの時間の入れ
	void Set_Move_Stop_Time(const int *Time, const int *Speed);

	//車の操作者の渡し
	int Get_DriverNo(void) {
		return M_Driver;
	}

	/*衝突判定の状態の関数*/

	//衝突判定することを許可するフラグの渡し
	bool Get_CollisionJudg_TrueFlg(void) {
		return M_CollisionJudg_TrueFlg;
	}

	//衝突判定することを許可するフラグのセット
	void Set_CollisionJudg_TrueFlg(const bool *Flg) {
		M_CollisionJudg_TrueFlg = *Flg;
	}

	//手動と自動の操作情報を入れるクラス
	S_GUN_UPDATE_DATA Get_Gun_Update_Data(void) {
		return M_S_Gun_Update_Data;
	}

protected:
	//車のデータ
	BODYDATA BodyData;

	//車のモデル入れ
	void SetMeshCar(int MeshNo);

	//車の情報
	CHARA3D Car;

	QuaForMove CarFM;

	D3DXMATRIX PlaMovMat;//playerの移動前のMat

	//バレット用
	BULLETRAYJUDG brj;

	Judg judg;

	//手動と自動の操作情報を入れるクラス
	S_GUN_UPDATE_DATA M_S_Gun_Update_Data;

	//車の操作者
	int M_Driver;

	//銃の情報の更新
	void Update_Gun_Data(void);

	//操作・動作できるまでの時間を減らす更新の処理
	void Update_Move_Stop_Time(void);

	//銃の動きの停止判定
	bool Get_Stop_Flg(void);

	//衝突判定の状態のセット
	void Set_JudgeType(const int *Type) {
		M_JudgeType = *Type;
	}

private:
	//衝突判定の状態
	int M_JudgeType;

	//操作・動作できるまでの時間
	int MMove_Stop_Time;

	//衝突判定することを許可するフラグ
	bool M_CollisionJudg_TrueFlg;

	//前進クォータニオン用
	D3DXMATRIX ForMoveEndMat;//前進完了時のMat
	D3DXVECTOR3 ForMoveVec[3];//移動前から移動後のVec
	QuaForMove Q;//前進判定用クォータニオン

	//無敵タイム
	int CountMNum,CountMStart;

	//操作の構造体の初期化
	void Init_S_Gun_Update_Data(void);

};