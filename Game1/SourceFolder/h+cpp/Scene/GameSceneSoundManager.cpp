#include "GameSceneSoundManager.h"

C_GameSSM::C_GameSSM()
{
	InitSSM();
}

C_GameSSM::~C_GameSSM()
{
	EndSSM();
}

void C_GameSSM::InitSSM(void)
{
	if (SoundGun == nullptr) {
		SoundGun = new C_SoundGun();
	}
}

void C_GameSSM::EndSSM(void)
{
	if (SoundGun != nullptr) {
		delete SoundGun;
	}
}
