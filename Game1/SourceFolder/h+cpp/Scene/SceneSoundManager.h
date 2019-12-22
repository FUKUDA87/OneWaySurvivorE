#pragma once
#include<d3dx9.h>

//#define TitleNo 1
//#define StageNo 2
//#define GameNo 3

class C_SceneSoundManager{
public:
	C_SceneSoundManager() {
		InitSSM();
	}
	~C_SceneSoundManager() {
		EndSSM();
	}
	//サウンドのアップデート
	virtual bool UpdateSSM(void) {
		return false;
	}
protected:
	//サウンドマネージャーの関数
	//サウンドの初期化
	virtual void InitSSM(void) {};
	//サウンドの終了処理
	virtual void EndSSM(void) {};
private:
	//サウンドマネージャーの変数

	//サウンドのクラス

};