#pragma once
#include<d3dx9.h>
#include<dsound.h>


class C_BombSound {
public:
	C_BombSound();
	~C_BombSound();
	//初期化
	void Init(void);
	//アップデート
	virtual bool Update(const D3DXVECTOR3 *SoundPos, const D3DXVECTOR3 *CamPos, const D3DXVECTOR3 *CamLook, const D3DXVECTOR3 *CamHead);
	//チェンジBGM
	void ChangeBgm(int Noo);
protected:
	//サウンド数
	int SoundNum;
	//今のサウンド
	int NowSound;
	//サウンド変数
	LPDIRECTSOUNDBUFFER8 SoundE[10];
	LPDIRECTSOUND3DBUFFER8 Sound3DE[10];
	//音量
	int SoundSize;

private:
};