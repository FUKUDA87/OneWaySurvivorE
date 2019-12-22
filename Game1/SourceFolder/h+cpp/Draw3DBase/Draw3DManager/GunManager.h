#pragma once
#include<d3dx9.h>
#include"../../Gun/GunDraw/GunBase.h"

class C_GunManager {
public:
	GunBase* GetGun(int GunNo,D3DXMATRIX Mat);
protected:

private:
	bool GetGun1(int GunNo);
};