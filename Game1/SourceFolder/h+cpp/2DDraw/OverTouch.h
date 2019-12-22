#pragma once
#include"ClearTouch.h"

class C_OverTouch :public C_ClearTouch {
public:
	C_OverTouch(const D3DXVECTOR3 *WindPos, const D3DXVECTOR3 *WindScal, const D3DXVECTOR3 *CharScal, const float *yUp, const int *Mode);
	~C_OverTouch();

	//表示
	void Draw2DAll(void);
	//タッチの確認
	int TouchNow(void);

	//表示
	void Draw2DRetry(void);

	//タッチ時に画像の変化
	int TouchNow2(void);

protected:

private:
	//ポーズに戻る-------------------
	CHARA2D2 Retry;
	//初期化
	void InitRetry(void);

	//アップデート
	bool UpdateRetry(void);
};