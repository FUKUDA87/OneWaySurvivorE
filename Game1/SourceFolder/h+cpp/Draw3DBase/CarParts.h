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

class C_CarParts {
public:
	~C_CarParts();
	//パーツ削除
	void DeleteParts(void);
	//パーツの位置情報の読み込みとパーツをセットする
	void SetCarParts(const BODYDATA * Data, const bool SaveFlg);
	//パーツ数渡し
	unsigned int GetPartsNum(void) {
		return Parts.size();
	}
	//パーツの情報渡し
	PARTS GetPartsData(unsigned int *No);
	//パーツの表示行列渡し
	D3DXMATRIX GetPartsMat(unsigned int *No);
	//パーツのダメージ処理
	bool SetDamageParts(const unsigned int *pNo, const int *Damage);
	//パーツの生存確認(0で死、１で生、２は判別不能)
	int PartsDeadFlg(unsigned int *pNo);
protected:
	BODYDATA BodyData;
	//標準パーツ用
	std::vector<C_PartsBase*>Parts;
	//車パーツ用情報マネージャー
	C_CarDataManager CarDataManager;
	//タイヤマネージャー
	C_TireMeshManager TireMeshManager;
	//スタンドマネージャー
	C_StandMeshManager StandMeshManager;
	//パーツマネージャー
	C_PartsMeshManager PartsMeshManager;

	//パーツの位置情報の読み込みとパーツをセットする
	void SetCarParts(const BODYDATA * Data,const int *EnemyNo, const int *MaxHp, const bool SaveFlg);

private:
	//タイヤのパーツセット
	void SetTireParts(const BODYDATA * Data, const PARTSBASE *PBase);
	//スタンドのパーツセット
	void SetStandParts(const BODYDATA * Data, const PARTSBASE *PBase);
	//カーパーツのパーツセット
	void SetCarParts(const BODYDATA * Data, const PARTSBASE *PBase);	//パーツの構造体変換渡し
	PARTS GetPartsData(const PARTSBASE *PBase);

	Judg judgCP;
};