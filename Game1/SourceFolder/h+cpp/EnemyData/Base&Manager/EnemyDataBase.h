#pragma once
#include<d3dx9.h>
#include"../../GameSource/Struct.h"
#include"EnemyDataNoConst.h"
#include"EnemyGunMoveBase.h"
#include"EnemySpeed.h"
#include"../Base&Manager/PartsMoveBase.h"
#include"../../Draw3DBase/Draw3DManager/TireMeshManager.h"
#include"../../Draw3DBase/Draw3DManager/StandMeshManager.h"
#include"../../Draw3DBase/Draw3DManager/PartsMeshManager.h"
#include"EnemyAiPhaseBase.h"
#include"../../Gun/GunDraw/NewGun/GunLaser.h"

class C_EnemyDataBase {
public:
	C_EnemyDataBase();

	//車情報渡しと検索
	virtual S_ENEMYBODYDATA GetBodyData(void) = 0;
	//標準パーツ情報渡しと検索
	virtual C_PartsMoveBase* GetPartsData(const int *PartsNo) = 0;
	//標準パーツ情報渡しと検索
	virtual XFILE GetPartsMesh(const int *PartsNo) = 0;
	//銃の情報渡しと検索
	virtual C_E_GunMoveBase* GetGunData(const int *GunNo,S_ENEMYGUNDATA *s_Data) = 0;
	//車移動渡し
	virtual Speed* GetSpeed(void) = 0;
	//Ai渡し
	virtual C_E_AiPhaseBase* GetAiPhase(void) = 0;
	//銃数
	int Get_GunNum(void) {
		return GunNum;
	}
	//銃の表示渡し
	virtual C_GunLaser*Get_Gun(const int *EnemyGunNo)=0;
protected:
	int GunNum;
private:

};