#pragma once
#include"EnemyAi.h"
#include"../GameSource/Const.h"
#include"../Draw3DBase/TireParts.h"
#include"../GameSource/CharaBase.h"
#include"../EnemyData/Base&Manager/EnemyDataManager.h"

class C_EnemyA :public C_EnemyAi {
public:
	C_EnemyA(D3DXMATRIX GroundMat, float *TransX);
protected:
	//初期化ボディ
	void InitBody(void);

	//銃のくっつけ
	void New_Car_Parts_Gun(const BODYDATA *CarData) {
		return;
	}

	//初期位置
	void InitPos(D3DXMATRIX GroundMat, float *TransX);
private:

};