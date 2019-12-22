#pragma once
#include<d3dx9.h>
#include"../Base&Manager/EnemyDataBase.h"
#include"../EnemyNo1/PartsMove/EnemyNo1_TireMove.h"
#include"../EnemyNo1/PartsMove/EnemyNo1_StandMove.h"
#include"SpeedMove/EnemySpeedNo201.h"
#include"EnemyAi/ENo101_AiPhase_1.h"
#include"PartsMove/ENo101_Judg1Move.h"


class C_EnemyDataNo101 :public C_EnemyDataBase {
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