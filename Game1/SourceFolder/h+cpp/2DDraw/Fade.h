#pragma once
#include<d3dx9.h>
#include"../GameSource/Struct.h"
#include"../GameSource/TextureManager.h"
#include"FadeMove.h"
#include"FadeOut.h"
#include"FadeIn.h"

extern TextureManager textureManager;
extern LPD3DXSPRITE lpSprite;	// スプライト

#define	SCRW		1280	// ウィンドウ幅（Width
#define	SCRH		720		// ウィンドウ高さ（Height

class Fade {
public:
	void Init();
	Fade();
	~Fade();
	virtual bool Update();
	void ChaFlg(bool b);
	bool GetFlg() {
		return out;
	}
	void Draw();
	void Draw(int Color);

	//動きのフラグ入れ
	void SetIn(void) {
		MoveFlg = true;
	}
	void SetIn(bool BlackFlg) {
		MoveFlg = true;
		SetColor(BlackFlg, true);
	}
	//色変え
	void SetColor(bool BlackFlg, bool FlgChangeFlg) {
		static bool ColorFlg = true;
		if (FlgChangeFlg == true) ColorFlg = BlackFlg;
		if (ColorFlg == false) {
			FadeColor = 255;
		}
		else {
			FadeColor = 0;
		}
	}
	//動きのフラグ渡し
	bool GetMoveFlg(void) {
		return MoveFlg;
	}
	//Move完了Flg渡し
	bool GetMoveEndFlg(void) {
		return MoveEndFlg;
	}

protected:
	CHARA2D fade;
	int alpha;
	bool out;//outがtrueなら黒
	//フェードのFlg;
	bool MoveFlg,MoveEndFlg;
	//フェード色
	int FadeColor;
private:
	C_FadeMove *FadeMove;
};