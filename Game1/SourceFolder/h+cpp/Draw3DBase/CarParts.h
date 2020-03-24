#pragma once
#include"PartsBase.h"
#include<vector>
#include"BaseDataManager/CarDataManager.h"
#include"../GameSource/Judgment.h"
#include"Car_Parts_Data.h"
#include"Car_Parts_Joint.h"
#include"../Const/Const_PartsTypeNo.h"
#include"../GameSource/StructClass/Parts_Set_Data.h"
#include"Car_Parts_Size.h"

class C_CarParts:public C_Car_Parts_Size {
public:
	C_CarParts();
	~C_CarParts();

	//パーツの表示
	void Draw_Car_Parts(const D3DXVECTOR3* CameraPos);
	//パーツの更新
	bool Update_Car_Parts(void);
	//パーツの情報渡し

	//パーツの削除
	void Delete_Parts(unsigned int *PartsNo);

	//パーツにダメージ

	//カメラに行列渡し
	D3DXMATRIX Get_Camera_Mat(void);

	//パーツ数渡し
	unsigned int Get_Car_Parts_Num(void) {
		return M_Car_Parts.size();
	}

	/*
	判定
	*/

	//表示物Flg
	int Get_Parts_Draw_Draw_JudgFlg(const unsigned int *M_Car_PartsNo);

	//ポリゴンの頂点
	D3DXVECTOR3 Get_Parts_Draw_Pol_Pos(const unsigned int *M_Car_PartsNo,const int *PosNo);

	//メッシュ
	LPD3DXMESH Get_Parts_Draw_Mesh(const unsigned int *M_Car_PartsNo);

	//IdenFlg
	bool Get_Parts_Draw_Iden_Flg(const unsigned int *M_Car_PartsNo);

	//表示行列渡し
	D3DXMATRIX Get_Parts_Draw_DrawMat(const unsigned int *M_Car_PartsNo);

	//パーツのHpを減らす処理
	bool Damage_CarParts(const unsigned int *M_CarPartsNo, const int *Damage);

	//表示行列渡し
	float Get_Parts_Draw_Dis(const unsigned int *M_Car_PartsNo);

	BODYDATA Get_BODYDATA(void) {
		return BodyData;
	}

	/*パーツのサウンドデータの取得*/

protected:
	//パーツ表示変数
	std::vector<C_Car_Parts_Joint*>M_Car_Parts;

	//車のデータ
	BODYDATA BodyData;
	//車のパーツ情報上書きFlg
	bool M_Parts_Save_Flg;

	//パーツの初期化
	virtual void New_Set_Car_Parts(const BODYDATA *CarData);
	virtual void New_Set_Car_Parts(const int *CarNo,std::vector<C_Parts_Set_Data*>M_Set_Data);

	//パーツの全削除
	void Delete_ALL_Parts(void);

	//パーツの初期化(プレイヤー)
	void New_CarParts(const BODYDATA *CarData);
	void New_CarParts(std::vector<C_Parts_Set_Data*>M_Set_Data);
	S_CAR_PARTS_DATA* Get_Data_CarParts(const int *TypeNo,const int JointNo);
	//パーツの初期化(エネミー)

	//車のパーツの情報入手
	void New_Car_Parts_Data(const int *CarNo);

	//車の当たり判定用の情報の初期化
	virtual void New_Car_Judg_Parts(void);
private:

};