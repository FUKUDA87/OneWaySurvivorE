#pragma once
#include"../../GameSource/TexManagerBase.h"

class C_BulletTexManager :public C_TexManagerBase {
public:
	LPDIRECT3DTEXTURE9 GetTex(int MeshNo);
private:
	
};