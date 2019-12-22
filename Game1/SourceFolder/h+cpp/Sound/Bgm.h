#pragma once
#include<d3dx9.h>
#include<dsound.h>
#include"../GameSource/Struct.h"

class C_Bgm {
public:
	C_Bgm();
	~C_Bgm();
	//初期化
	void Init(void);
	//アップデート
	bool Update(const bool *Flg);

	bool Update(const bool *Flg,const SoundCamera *sc);

	//ストップ音
	void StopSound(void);
	//スタート音
	void StartSound(void);
	//チェンジBGM
	void ChangeBgm(int Noo);

protected:
	//今のサウンド
	int NowSound;
private:
	//サウンド数
	int SoundNum;
	//サウンド変数
	LPDIRECTSOUNDBUFFER8 SoundB[3];
	LPDIRECTSOUND3DBUFFER8 Sound3DB[3];

	//音量
	int *SoundSize;
	bool StopFlg;
};