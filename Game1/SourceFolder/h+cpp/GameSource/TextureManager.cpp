#include"TextureManager.h"
void LoadTexture(LPDIRECT3DTEXTURE9 *lpTex, const char fname[], int W, int H, D3DCOLOR Color);

LPDIRECT3DTEXTURE9 TextureManager::GetTexture(std::string FileName, int Width, int Height, D3DCOLOR ColorKey) {
	LPDIRECT3DTEXTURE9 Tmp;
	if (TextureList.find(FileName)==TextureList.end()) {
		LoadTexture(&Tmp, &FileName[0], Width, Height, ColorKey);
		TextureList[FileName] = Tmp;
	}
	else {
		Tmp=TextureList[FileName];
	}
	return Tmp;
}
TextureManager::~TextureManager() {
	AllDelete();
}
void TextureManager::AllDelete(void) {
	for (auto itr = TextureList.begin(); itr != TextureList.end(); itr++) {
		itr->second->Release();
	}
	TextureList.clear();
}