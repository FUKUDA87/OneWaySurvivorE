#pragma once
#include<d3dx9.h>
#include"../Base&Manager/EnemyDataBase.h"
#include"GunMove/EnemyNo1GunNo1_Attack.h"
#include"SpeedData/SpeedUp.h"
#include"EnemyAi/ENo1_AiPhase.h"


class C_EnemyDataNo1 :public C_EnemyDataBase {
public:
	//車情報渡しと検索
	S_ENEMYBODYDATA GetBodyData(void);
	//標準パーツ情報渡しと検索
	C_PartsMoveBase* GetPartsData(const int *PartsNo);
	//標準パーツ情報渡しと検索
	XFILE GetPartsMesh(const int *PartsNo);
	//銃の情報渡しと検索
	C_E_GunMoveBase* GetGunData(const int *GunNo, S_ENEMYGUNDATA *s_Data);
	//車移動渡し
	Speed* GetSpeed(void);
	//Ai渡し
	C_E_AiPhaseBase* GetAiPhase(void);
protected:

private:
	/*パーツ情報*/

};