#pragma once
#include"../GameSource/Struct.h"
#include<d3dx9.h>
#include"../GameSource/TextureManager.h"

extern TextureManager textureManager;
extern LPD3DXSPRITE lpSprite;	// スプライト

class Warning {
public:
	Warning();
	~Warning() {};
	bool Update(void);
	void SetFlg(bool Flg) {
		warFlg = Flg;
	}
	bool GetFlg(void) {
		return warFlg;
	}
	void Draw2D(void);
protected:
	CHARA2D war, yel;
	bool warFlg;
	int count, countEnd, alphaW, alphaY, k;//kは＋－のため。
	int MaxAlphaW, SmallAlphaW;//制限
};