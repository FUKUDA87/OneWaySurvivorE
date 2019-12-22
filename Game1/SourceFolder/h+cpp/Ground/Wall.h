#pragma once
#include<d3dx9.h>
#include"ground.h"
#include"../GameSource/Struct.h"
#include"../3DDraw/Light3D.h"
#include<vector>

const int WNum = 2;
class Wall :public C_Ground {
public:
	void InitW() ;
	Wall() ;
	Wall(int i);
	Wall(D3DXMATRIX Mat3, D3DXMATRIX Mat4, int gType, float Ang, float Length, bool LengthAuto);
	~Wall();
	bool WaUpdate();
	void WaDraw();
	//Lightの初期化
	void InitLight(const int *wNum);
	//左が０、右が１
	D3DXMATRIX GetWaMat(int i) {
		return Wall3D[i].Base.Mat;
	}

	//表示のポリゴンを弱くする入れ
	void SetDoawRadFlg(const bool *Flg) {
		DrawRadFlg=*Flg;
	}

	void SuperUpdate();
	void SuperDraw();
	//壁のコリジョンモデル渡し
	LPD3DXMESH GetColModWall(const bool *LeftFlg);
	//壁3Dの行列渡し
	D3DXMATRIX GetWaMat(const bool *LeftFlg);
	//壁3Dの行列渡し(拡大抜き)
	D3DXMATRIX GetWaMat(const bool *LeftFlg,int i);

	//外灯の表示数渡し
	unsigned int GetLightNum(void) {
		return light.size();
	}

protected:

private:
	//表示用のFlg
	bool WallDrawFlg;
	//壁3D用
	Object3D2 Wall3D[2];
	//外灯3D用
	std::vector<C_Light *>light;

	XFILE Wall3DS;
	bool DrawRadFlg;

	//ライト---------------------------------
	//片方だけ表示
	void InitLightOne(const int *wNum);
	//サイド出現
	void InitLightW(const int *wNum);
};