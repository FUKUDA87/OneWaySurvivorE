#pragma once
#include"Smog.h"
#include<vector>

class C_Smoke2 :public C_Smog {
public:
	C_Smoke2(const D3DXVECTOR3 *Pos);
	~C_Smoke2();
	//初期化
	void InitS(void);
	//アップデート
	bool Update(const int *NowHp,const int *MaxHp,const D3DXVECTOR3 *NowPos);
	//アップデートクォータニオン
	bool UpdateQua(void);
	//表示
	void Draw3D(const D3DXVECTOR3 *CamPos);

protected:

private:
	//位置の格納
	D3DXVECTOR3 *SmokePos;
	//位置の数
	int SmokeNum;
	int SmokeNumDraw;
	//スモック
	std::vector<PolQuaAni*>smoke;
};