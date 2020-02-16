#pragma once
#include<d3dx9.h>
#include"../../GameSource/Struct.h"
#include"../../GameSource/Judgment.h"
#include"../../GameSource/Const.h"
#include"../EnemyConst/PhaseConst.h"
#include"../../Gun/Bullet/Const_Bullet_No.h"

class C_E_GunMoveBase {
public:
	virtual C_E_GunMoveBase* Move(S_ENEMYGUNDATA* s_Data, int *NowPhase)=0;
protected:
	void InitRayFlg(S_ENEMYGUNDATA *s_Data) {
		s_Data->RayHitFlg = s_Data->RayJudgFlg = false;
	}
	Judg judg;
private:
	
};