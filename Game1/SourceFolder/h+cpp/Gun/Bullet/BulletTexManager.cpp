#include "BulletTexManager.h"
#include"../../GameSource/TextureManager.h"

extern TextureManager textureManager;

LPDIRECT3DTEXTURE9 C_BulletTexManager::GetTex(int MeshNo)
{
	//No1
	//if (MeshNo == 1)return textureManager.GetTexture("../GameFolder/Material/Texture/Bullet1-1-1.png", 100, 100, NULL);
	LPDIRECT3DTEXTURE9 Tex = textureManager.GetTexture("../GameFolder/Material/Texture/Bullet1-1-1.png", 100, 100, NULL);
	return Tex;// textureManager.GetTexture("../GameFolder/Material/Texture/Bullet1-1-1.png", 100, 100, NULL);
}
