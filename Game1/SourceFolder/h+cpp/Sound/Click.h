#pragma once
#include"../GameSource/Struct.h"

class C_ClickSound {
public:
	C_ClickSound();
	~C_ClickSound();
	//初期化
	void InitCli(void);
	//アップデート
	bool UpdateCli(const bool *Flg);
	//停止
	void StopSoundCli(const int *No);
private:
	//サウンド数
	int SoundNum;
	//今のサウンド
	int NowSound;
	//サウンド変数
	SoundCol *soundCol;
	//音量
	int SoundSize;
};