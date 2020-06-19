#include "DrawTextureManager_Base.h"
#include"../../MaterialManager/TextureManager.h"

extern TextureManager textureManager;

TEXTURE C_DrawTextureManager_Base::Texture_Load(std::string FileName, const int Width, const int Height)
{
	TEXTURE M_Tex;
	M_Tex = { NULL,Width,Height,NULL,NULL,NULL };
	M_Tex.Tex = textureManager.GetTexture(FileName, M_Tex.Width, M_Tex.Height, NULL);

	return M_Tex;
}

TEXTURE C_DrawTextureManager_Base::Texture_Load(std::string FileName, const int Width, const int Height, const int r, const int g, const int b)
{
	TEXTURE M_Tex;
	M_Tex = { NULL,Width,Height,r,g,b };
	M_Tex.Tex = textureManager.GetTexture(FileName, M_Tex.Width, M_Tex.Height, D3DCOLOR_XRGB(M_Tex.r, M_Tex.g, M_Tex.b));

	return M_Tex;
}
