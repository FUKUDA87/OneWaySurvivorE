#include "NumA.h"

NumA::NumA()
{
	Num.TEX = { NULL,500,50,NULL,NULL };
	Num.TEX.Tex = textureManager.GetTexture("CharNum2.png", Num.TEX.Width, Num.TEX.Height, NULL);
}
