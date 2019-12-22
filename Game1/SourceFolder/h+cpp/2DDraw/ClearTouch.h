#pragma once
#include"NextTouch.h"

class C_ClearTouch :public C_NextTouch {
public:
	C_ClearTouch(const D3DXVECTOR3 *WindPos, const D3DXVECTOR3 *WindScal, const D3DXVECTOR3 *CharScal, const float *yUp,const int *Mode);
	~C_ClearTouch();

	//アップデート
	bool UpdateAll(void);
	//表示
	void Draw2DAll(void);
	//タッチの確認
	int TouchNow(void);

	//表示数渡し
	int GetDrawNum(void) {
		return DrawNum;
	}

	//タッチ時に画像の変化
	int TouchNow2(void);

protected:

	//ポーズに戻る-------------------
	CHARA2D2 Title;
	//初期化
	void InitTitle(void);

	//アップデート
	bool UpdateTitle(void);

	//表示
	void Draw2DTitle(void);

	//ステージ選択に戻る---------------
	CHARA2D2 Stage;
	//初期化
	void InitStage(void);

	//アップデート
	bool UpdateStage(void);

	//表示
	void Draw2DStage(void);

private:
};