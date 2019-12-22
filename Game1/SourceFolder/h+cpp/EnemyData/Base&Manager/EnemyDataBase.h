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

class C_EnemyDataBase {
public:
	//Ôî•ñ“n‚µ‚ÆŒŸõ
	virtual S_ENEMYBODYDATA GetBodyData(void) = 0;
	//•W€ƒp[ƒcî•ñ“n‚µ‚ÆŒŸõ
	virtual C_PartsMoveBase* GetPartsData(const int *PartsNo) = 0;
	//•W€ƒp[ƒcî•ñ“n‚µ‚ÆŒŸõ
	virtual XFILE GetPartsMesh(const int *PartsNo) = 0;
	//e‚Ìî•ñ“n‚µ‚ÆŒŸõ
	virtual C_E_GunMoveBase* GetGunData(const int *GunNo,S_ENEMYGUNDATA *s_Data) = 0;
	//ÔˆÚ“®“n‚µ
	virtual Speed* GetSpeed(void) = 0;
	//Ai“n‚µ
	virtual C_E_AiPhaseBase* GetAiPhase(void) = 0;
protected:

private:

};