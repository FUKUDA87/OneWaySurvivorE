#pragma once
#include"ButtonBase.h"

class c_ButtonGameScene:public c_ButtonBase
{
public:
	c_ButtonGameScene();

	// 表示
	void Draw2D(void);

	bool GetDrawChangeFlg(void) { return DrawChangeFlg; }
	void SetDrawChangeFlg(const bool Flg) { DrawChangeFlg = Flg; }
protected:
	LPDIRECT3DTEXTURE9 buttonTex[2];

	int width2, height2;  // 画像サイズ

	// 文字のサイズを平均のサイズに初期化する
	void InitScal(const int ChaNum, const float Size);

private:
	bool DrawChangeFlg;  // 表示変更Fl
};