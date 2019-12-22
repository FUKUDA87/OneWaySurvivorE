#pragma once
#include<d3dx9.h>
#include"../GameSource/Struct.h"
#include"../GameSource/TextureManager.h"
#include"../GameSource/Judgment.h"

extern TextureManager textureManager;
extern LPD3DXSPRITE lpSprite;	// スプライト
extern Judg judg;

#define	SCRW		1280	// ウィンドウ幅（Width
#define	SCRH		720		// ウィンドウ高さ（Height

class GameOver {
public:
	GameOver();
	~GameOver() {};
	void Draw2D();
	bool Update(bool CLEor, bool Flg);
	//どちらのになったかFlg渡し
	bool GetFlg(void);

protected:
	CHARA2D gaov;
	CHARA2D stcl;
};