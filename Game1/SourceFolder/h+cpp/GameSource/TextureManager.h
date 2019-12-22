#pragma once
#include<d3dx9.h>
#include<string>
#include<map>
class TextureManager {
private:
	std::map<std::string,LPDIRECT3DTEXTURE9>TextureList;
public:
	~TextureManager();
	LPDIRECT3DTEXTURE9 GetTexture(std::string FileName, int Wibth, int Height, D3DCOLOR ColorKey);
	void AllDelete(void);
};

/*
#include"TextureManager.h"

extern TextureManager *textureManager;
*/