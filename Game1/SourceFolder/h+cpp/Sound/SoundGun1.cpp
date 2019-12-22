#include "SoundGun1.h"
#include"../GameSource/SoundManager.h"

extern SoundManager soundManager;
extern LPDIRECTSOUNDBUFFER lpSPrimary;


extern LPDIRECTSOUND8 lpDSound;	//DirectSoundオブジェクト

extern LPDIRECTSOUND3DLISTENER8 lpSListener;


C_SoundGun::C_SoundGun()
{
	Init();
}

C_SoundGun::~C_SoundGun()
{
	delete[] soundCol;

}

void C_SoundGun::Init(void)
{
	

	SoundNum = 1;
	soundCol = new SoundCol[SoundNum];
	SoundSize = -2000;

	soundManager.GetSound(&soundCol[0].Sound, &soundCol[0].Sound3D, "../GameFolder/Material/wav/Gun4.wav");
	LPDIRECTSOUNDBUFFER lpSTmp;
	for (int i = 1; i < SoundNum; i++) {
		/*lpDSound->DuplicateSoundBuffer(Sound[0], &lpSTmp);
		lpSTmp->QueryInterface(IID_IDirectSoundBuffer8, (LPVOID*)&Sound[i]);
		Sound[i]->QueryInterface(IID_IDirectSound3DBuffer8, (LPVOID*)&Sound3D[i]);
		Sound3D[i]->SetMode(DS3DMODE_NORMAL, DS3D_IMMEDIATE);
		lpSTmp->Release();*/
		lpDSound->DuplicateSoundBuffer(soundCol[0].Sound, &lpSTmp);
		lpSTmp->QueryInterface(IID_IDirectSoundBuffer8, (LPVOID*)&soundCol[i].Sound);
		soundCol[i].Sound->QueryInterface(IID_IDirectSound3DBuffer8, (LPVOID*)&soundCol[i].Sound3D);
		soundCol[i].Sound3D->SetMode(DS3DMODE_DISABLE, DS3D_IMMEDIATE);
		lpSTmp->Release();
	}

	for (int i = 0; i < SoundNum; i++) {
		StopSound(&i);
	}

}

bool C_SoundGun::Update(const D3DXVECTOR3 *SoundPos, const D3DXVECTOR3 *CamPos, const D3DXVECTOR3 *CamLook, const D3DXVECTOR3 *CamHead)
{
	DWORD SFlg;
	for (int i = 0; i < SoundNum; i++) {
		soundCol[i].Sound3D->SetPosition(SoundPos->x, SoundPos->y, SoundPos->z, DS3D_IMMEDIATE);//音源の位置
		lpSListener->SetPosition(CamPos->x, CamPos->y, CamPos->z, DS3D_IMMEDIATE);//リスナーの位置
		//リスナーが見ている方向計算
		D3DXVECTOR3 Vec;
		Vec = *CamLook - *CamPos;
		D3DXVec3Normalize(&Vec, &Vec);

		lpSListener->SetOrientation(Vec.x, Vec.y, Vec.z, CamHead->x, CamHead->y, CamHead->z, DS3D_IMMEDIATE);//リスナーが見ている方向とリスナーの頭の方向
		soundCol[i].Sound->GetStatus(&SFlg);
		if ((SFlg&DSBSTATUS_PLAYING) == 0) {
			soundCol[i].Sound->Play(0, 0, 0);
			soundCol[i].Sound->SetVolume(SoundSize);
			break;
		}
	}
	return true;
}

bool C_SoundGun::Update(const bool *Flg)
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

void C_SoundGun::ChangeBgm(int Noo)
{

}

void C_SoundGun::StopSound(const int * No)
{
	if ((*No < 0) || (*No > SoundNum-1))return;

	DWORD SFlg;
	if (soundCol[*No].Sound != nullptr) {
		soundCol[*No].Sound->GetStatus(&SFlg);
		if ((SFlg&DSBSTATUS_PLAYING) != 0) {
			soundCol[*No].Sound->Stop();
			soundCol[*No].Sound->SetCurrentPosition(0);
		}
	}
}

