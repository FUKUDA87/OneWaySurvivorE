#pragma once
#include"SceneSoundManager.h"
//サウンド
#include"../Sound/SoundGun1.h"

class C_GameSSM :public C_SceneSoundManager {
public:
	C_GameSSM();
	~C_GameSSM();

	//クラス
	//銃声
	C_SoundGun *SoundGun;

protected:

private:
	void InitSSM(void);
	void EndSSM(void);
};