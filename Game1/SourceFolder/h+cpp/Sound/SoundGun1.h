#pragma once
#include<d3dx9.h>
#include<dsound.h>
#include"../GameSource/Struct.h"


class C_SoundGun {
public:
	C_SoundGun();
	~C_SoundGun();
	//初期化
	void Init(void);
	//アップデート
	virtual bool Update(const D3DXVECTOR3 *SoundPos,const D3DXVECTOR3 *CamPos, const D3DXVECTOR3 *CamLook, const D3DXVECTOR3 *CamHead);
	bool Update(const bool *Flg);
	//チェンジBGM
	void ChangeBgm(int Noo);
	//停止
	void StopSound(const int *No);
protected:
	//サウンド数
	int SoundNum;
	//今のサウンド
	int NowSound;
	//サウンド変数
	SoundCol *soundCol;
	//音量
	int SoundSize;
private:
};