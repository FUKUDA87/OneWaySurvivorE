#include "GameSystem.h"
#include"Judgment.h"

bool C_GameSystem::JudgNowGround(unsigned int * GroundNumber, float * Dis, 
	const D3DXMATRIX Mat, std::vector<C_Ground_Object*> ground)
{
	if (ground.size() <= 0) { return false; }

	float size;
	// 地面レイ判定
	for (unsigned int g = 0; g < ground.size(); g++) {

		float L_Radius = 40.0f;

		Judg judg;

		// 自分の周囲の地面だけを判定
		if (judg.BallJudg(&judg.SetPosM(&Mat), &judg.SetPosM(&ground[g]->GetMat()), &L_Radius) != true) continue;

		// 地面の4頂点作成
		D3DXVECTOR3 v[4];
		for (int i = 0; i < 4; i++) v[i] = ground[g]->GetVer(i);

		// 地面の板ポリゴンの生成方法を取得
		bool L_IdenFlg = ground[g]->GetIdenFlg();

		// レイ判定
		if (judg.RayJudg_Polygon(&judg.SetPosM(&Mat), &D3DXVECTOR3(0.0f, -1.0f, 0.0f), &ground[g]->GetMat(),
			&v[0], &v[1], &v[2], &v[3], &size, &L_IdenFlg) != true) continue;

		// レイが当たった時の処理

		*GroundNumber = g;
		*Dis = size;

		return true;

	}

	return false;
}
