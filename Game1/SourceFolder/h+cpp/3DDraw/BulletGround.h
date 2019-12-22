#pragma once
#include"Spark.h"

class C_BulGro :public C_Spark {
public:
	C_BulGro(const D3DXMATRIX *Mat,const D3DXVECTOR3 *Pos);
	~C_BulGro();
	//初期化
	void InitBG(void);
	//アップデート
	bool Update(void);
	//表示
	void Draw3D(void);
protected:

private:
	//煙昇の表示
	Pol Smoke;
	float SmoUpY;
	//煙サイドの表示
	Pol SmokeS[2];
	int SmokeNum;
	//アスファルトの欠片
	XFILE AspMesh;
	BASE3D *AspMat;
	int AspNum;

	//表示の薄れ
	int NowAlpha,AlphaDown;
	//スモークの拡大
	float ScaSmo;
};