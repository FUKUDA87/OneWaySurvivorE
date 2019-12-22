#include "ENo101_AiPhase_1.h"
/*
フェーズ０：準備
Speed側で所定の位置に着くとフェーズ１
フェーズ１：銃(1)の回転
銃(1)のHpが０になるとフェーズ２
フェーズ２：ドアのオープン、銃(２)の回転、本体HP減少true
本体Hpが６６％以下になればフェーズ３
フェーズ３：フェーズ１と同じ
フェーズ４で本体Hpが33％以下になればフェーズ５
フェーズ6で本体Hpが0％以下になればフェーズ７

*/

C_E_No101_AiPhase_1::C_E_No101_AiPhase_1()
{
	InitFlg = true;
}

C_E_AiPhaseBase * C_E_No101_AiPhase_1::Action(const CHARABASE * Chara, int * NewPhase)
{
	float Hp=(float)Chara->NowHp, MaxHp = (float)Chara->MaxHp;
	float S = Hp / MaxHp;
	if (S < 0.67f) {
		if (S < 0.34f) {
			if (Chara->NowHp <= 0) {
				*NewPhase = Phase7;
				return nullptr;
			}
			else {
				if (*NewPhase == Phase4)*NewPhase = Phase5;
				return nullptr;
			}
		}
		else {
			if (*NewPhase == Phase2)*NewPhase = Phase3;
			return nullptr;
		}
	}
	return nullptr;
}
