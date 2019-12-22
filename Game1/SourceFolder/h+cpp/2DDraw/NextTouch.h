#pragma once
#include"Window.h"
#include"../GameSource/Judgment.h"

class C_NextTouch:public Window {
public:
	C_NextTouch();
	~C_NextTouch();
	//初期化
	void InitTouch();
	//アップデート
	virtual bool UpdateAll(void);
	//表示
	virtual void Draw2DAll(void);
	//タッチの確認
	virtual int TouchNow(void);

	//今のモード渡し
	int GetMenuMode(void) {
		return MenuMode;
	}
	
	//タッチ時に画像の変化
	virtual int TouchNow2(void);

protected:
	//文字表示数
	int DrawNum;

	//今のモード
	int MenuMode;

	//便利関数
	Judg judg;
private:

};