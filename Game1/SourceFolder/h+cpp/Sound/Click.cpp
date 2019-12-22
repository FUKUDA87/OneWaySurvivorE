#include "Click.h"
#include"../GameSource/SoundManager.h"

extern SoundManager soundManager;
extern LPDIRECTSOUND8 lpDSound;	//DirectSoundオブジェクト

C_ClickSound::C_ClickSound()
{
	InitCli();
}

C_ClickSound::~C_ClickSound()
{
	delete[] soundCol;
}

void C_ClickSound::InitCli(void)
{
	SoundNum = 1;
	soundCol = new SoundCol[SoundNum];
	SoundSize = -2000;

	soundManager.GetSound(&soundCol[0].Sound, &soundCol[0].Sound3D, "../GameFolder/Material/wav/decision18.wav");//decision20//f1-pass1C1
	/*LPDIRECTSOUNDBUFFER lpSTmp;
	for (int i = 1; i < SoundNum; i++) {
		lpDSound->DuplicateSoundBuffer(soundCol[0].Sound, &lpSTmp);
		lpSTmp->QueryInterface(IID_IDirectSoundBuffer8, (LPVOID*)&soundCol[i].Sound);
		soundCol[i].Sound->QueryInterface(IID_IDirectSound3DBuffer8, (LPVOID*)&soundCol[i].Sound3D);
		soundCol[i].Sound3D->SetMode(DS3DMODE_DISABLE, DS3D_IMMEDIATE);
		lpSTmp->Release();
	}*/

	for (int i = 0; i < SoundNum; i++) {
		StopSoundCli(&i);
	}
}

bool C_ClickSound::UpdateCli(const bool *Flg)
{
	for (int i = 0; i < SoundNum; i++) {
		soundCol[i].Sound3D->SetMode(DS3DMODE_DISABLE, DS3D_IMMEDIATE);
		DWORD SFlg;
		soundCol[i].Sound->GetStatus(&SFlg);
		if ((SFlg&DSBSTATUS_PLAYING) == 0) {
			if (*Flg == true) {
				soundCol[i].Sound->Play(0, 0, 0);
				soundCol[i].Sound->SetVolume(SoundSize);
				break;
			}
		}
	}
	return true;
}

void C_ClickSound::StopSoundCli(const int *No)
{
	if ((*No < 0) || (*No > SoundNum - 1))return;

	DWORD SFlg;
	if (soundCol[*No].Sound != nullptr) {
		soundCol[*No].Sound->GetStatus(&SFlg);
		if ((SFlg&DSBSTATUS_PLAYING) != 0) {
			soundCol[*No].Sound->Stop();
			soundCol[*No].Sound->SetCurrentPosition(0);
		}
	}
}

