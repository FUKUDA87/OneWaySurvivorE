#include"StartTex.h"

StartTex::StartTex()
{
	mod.TEX = { NULL,300,50,NULL,NULL };
	mod.TEX.Tex = textureManager.GetTexture("CharStart1.png", mod.TEX.Width, mod.TEX.Height, NULL);
	mod.Base.Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	mod.Base.ScaPos = D3DXVECTOR3(1.0f, 1.0f, 0.0f);
	wind.Base.ScaPos= D3DXVECTOR3(1.0f*0.3f, 1.0f*0.11f, 0.0f);
	wind.Base.Pos=D3DXVECTOR3((float)SCRW/2.0f+5, (float)SCRH*0.85f, 0.0f);
}

StartTex::~StartTex()
{
}

