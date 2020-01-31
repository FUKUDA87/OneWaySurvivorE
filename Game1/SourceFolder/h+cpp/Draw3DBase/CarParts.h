#pragma once
#include"PartsBase.h"
#include<vector>
#include"BaseDataManager/CarDataManager.h"
#include"../Draw3DBase/Draw3DManager/TireMeshManager.h"
#include"../Draw3DBase/Draw3DManager/StandMeshManager.h"
#include"../Draw3DBase/TireParts.h"
#include"../GameSource/Judgment.h"
#include"Draw3DManager/PartsMeshManager.h"
#include"EnemyParts.h"
#include"../EnemyData/Base&Manager/EnemyDataManager.h"
#include"Car_Parts_Data.h"
#include"Car_Parts_Joint.h"
#include"../Const/Const_PartsTypeNo.h"

class C_CarParts:public C_Car_Parts_Data {
public:
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

protected:
	//パーツ表示変数
	std::vector<C_Car_Parts_Joint*>M_Car_Parts;

	BODYDATA BodyData;

	//パーツの初期化
	virtual void New_Set_Car_Parts(const BODYDATA *CarData, const bool *SaveFlg,const bool *Data_DeleteFlg);

	//パーツの全削除
	void Delete_ALL_Parts(void);

	//パーツの初期化(プレイヤー)
	void New_CarParts(const BODYDATA *CarData, const bool *SaveFlg);
	//パーツの初期化(エネミー)

private:

};