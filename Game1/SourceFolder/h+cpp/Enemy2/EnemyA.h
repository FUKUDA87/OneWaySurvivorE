#pragma once
#include"EnemyAi.h"
#include"../GameSource/Const.h"
#include"../Draw3DBase/TireParts.h"
#include"../GameSource/CharaBase.h"
#include"../EnemyData/Base&Manager/EnemyDataManager.h"

class C_EnemyA :public C_EnemyAi {
public:
	C_EnemyA(D3DXMATRIX GroundMat, float *TransX);
	C_EnemyA(const int * EnemyNo,D3DXMATRIX GroundMat, float *TransX);
	C_EnemyA(D3DXMATRIX GroundMat, float * TransX, const BODYDATA * IniteData);
	C_EnemyA(D3DXMATRIX GroundMat, float * TransX, const BODYDATACar * IniteData,Speed* GetSpeed);
protected:
	//初期化
	void EnemyA(void);
	//初期化ボディ
	void InitBody(void);
	//初期化標準パーツ
	void InitParts(void);

	//初期位置
	void InitPos(D3DXMATRIX GroundMat, float *TransX);
private:

};