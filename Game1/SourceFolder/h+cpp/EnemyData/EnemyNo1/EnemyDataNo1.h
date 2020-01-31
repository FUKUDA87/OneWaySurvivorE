#pragma once
#include<d3dx9.h>
#include"../Base&Manager/EnemyDataBase.h"
#include"GunMove/EnemyNo1GunNo1_Attack.h"
#include"SpeedData/SpeedUp.h"
#include"EnemyAi/ENo1_AiPhase.h"


class C_EnemyDataNo1 :public C_EnemyDataBase {
public:
	C_EnemyDataNo1();
	//Ôî•ñ“n‚µ‚ÆŒŸõ
	S_ENEMYBODYDATA GetBodyData(void);
	//•W€ƒp[ƒcî•ñ“n‚µ‚ÆŒŸõ
	C_PartsMoveBase* GetPartsData(const int *PartsNo);
	//•W€ƒp[ƒcî•ñ“n‚µ‚ÆŒŸõ
	XFILE GetPartsMesh(const int *PartsNo);
	//e‚Ìî•ñ“n‚µ‚ÆŒŸõ
	C_E_GunMoveBase* GetGunData(const int *GunNo, S_ENEMYGUNDATA *s_Data);
	//ÔˆÚ“®“n‚µ
	Speed* GetSpeed(void);
	//Ai“n‚µ
	C_E_AiPhaseBase* GetAiPhase(void);
	//e‚Ì•\¦“n‚µ
	C_GunLaser*Get_Gun(const int *EnemyGunNo);
protected:

private:
	/*ƒp[ƒcî•ñ*/

};