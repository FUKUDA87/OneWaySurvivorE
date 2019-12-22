#pragma once
#include<d3dx9.h>
#include<dsound.h>
#include<string>
#include<map>
#include "wavread.h"

class SoundManager {
private:
	std::map<std::string, LPDIRECTSOUNDBUFFER8>SoundList;
	std::map<std::string, LPDIRECTSOUND3DBUFFER8>Sound3DList;
public:
	~SoundManager();
	void GetSound(LPDIRECTSOUNDBUFFER8 *pDSData, LPDIRECTSOUND3DBUFFER8 *pDSData3D, std::string FileName);
	void AllDelete(void);
};