#pragma once
#include"ENo101_GNo0_MoveBase.h"

class C_ENo101_GNo0_Attack :public C_ENo101_GNo0_MoveBase {
public:
	C_ENo101_GNo0_Attack(S_ENEMYGUNDATA* s_Data);
	C_ENo101_GNo0_Attack();
	C_E_GunMoveBase* Move(S_ENEMYGUNDATA* s_Data, int *NowPhase);
protected:

private:
	S_ENEMYGUNDATA InitData(void);
	void Init(void);
	void InitRot(S_ENEMYGUNDATA * s_Data);
	bool Ray(S_ENEMYGUNDATA * s_Data);
	bool InitFlg;
	QUAMAT Start, End;
	float NowAnime, FrameAnime;
	int RayCount, RayCountMax;
};