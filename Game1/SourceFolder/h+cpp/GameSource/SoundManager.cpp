#include "SoundManager.h"

extern LPDIRECTSOUND8 lpDSound;	//DirectSoundオブジェクト
void LoadWAVE3D(LPDIRECTSOUNDBUFFER8 &pDSData, LPDIRECTSOUND3DBUFFER8 &pDSData3D, const char *fname);

SoundManager::~SoundManager()
{
	AllDelete();
}

 void SoundManager::GetSound(LPDIRECTSOUNDBUFFER8 *pDSDataT, LPDIRECTSOUND3DBUFFER8 *pDSData3DT, std::string FileName)
{
	 if ((SoundList.find(FileName)==SoundList.end())|| (Sound3DList.find(FileName)==Sound3DList.end())) {
		 LPDIRECTSOUNDBUFFER8 pDSDataTZ;
		 LPDIRECTSOUND3DBUFFER8 pDSData3DTZ;
		 LoadWAVE3D(pDSDataTZ, pDSData3DTZ, &FileName[0]);
		 SoundList[FileName]= pDSDataTZ;
		 Sound3DList[FileName]= pDSData3DTZ;
	 }
	// else {
		 *pDSDataT = SoundList[FileName];
		 *pDSData3DT = Sound3DList[FileName];
	// }
	 return;
}

void SoundManager::AllDelete(void)
{
	for (auto itr = SoundList.begin(); itr != SoundList.end(); itr++) {
		if (itr->second != nullptr) {
			//*itr->second->Release()
		}
	}
	SoundList.clear();
	for (auto itr = Sound3DList.begin(); itr != Sound3DList.end(); itr++) {
		if (itr->second != nullptr) {
			//itr->second->Release();
		}
		//delete itr->second;
	}
	Sound3DList.clear();

}
