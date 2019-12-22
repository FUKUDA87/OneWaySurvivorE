#pragma once
#include<d3dx9.h>
#include"../GameSource/Struct.h"
#include"../GameSource/Judgment.h"

class C_BulHol3D {
public:
	C_BulHol3D(const D3DXMATRIX *Mat, const D3DXVECTOR3 *Pos, int TypeNo);
	~C_BulHol3D();
	//初期化
	void InitHol3D(void);
	//アップデート
	bool UpdateHol3D(void);
	//表示
	void Draw3DHol3D(void);
	//時限式
	bool CountUpdate(void);
protected:

private:
	Pol Hole;
	Judg judg;
	//判定
	//壁判定
	void InitWall(int TypeNo);
	//地面判定
	void InitGround(int TypeNo);
	//時限
	int NowCount;
};