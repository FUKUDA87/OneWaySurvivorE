#pragma once
#include"NextTouch.h"

class C_PauseTouch :public C_NextTouch {
public:
	C_PauseTouch(const D3DXVECTOR3 *WindPos, const D3DXVECTOR3 *WindScal, const D3DXVECTOR3 *CharScal,const float *yUp,const int *Mode);
	~C_PauseTouch();

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
	//表示
	void Draw2DPause(void);
	//表示
	void Draw2DStage(void);

	//タッチ時に画像の変化
	int TouchNow2(void);

protected:

private:
	//ポーズに戻る-------------------
	CHARA2D2 Pause;
	//初期化
	void InitPause(void);
	
	//アップデート
	bool UpdatePause(void);

	//ステージ選択に戻る---------------
	CHARA2D2 Stage;
	//初期化
	void InitStage(void);
	
	//アップデート
	bool UpdateStage(void);
};