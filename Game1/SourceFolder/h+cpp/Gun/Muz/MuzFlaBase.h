#pragma once
#include<d3dx9.h>
#include"../../GameSource/Struct.h"
#include"../../MaterialManager/TextureManager.h"

extern TextureManager textureManager;
extern LPDIRECT3DDEVICE9 lpD3DDevice;

class MuzFlaBase {
protected:
	Pol mf;
public:
	virtual void Init() {};
	MuzFlaBase() {};
	~MuzFlaBase() {};
	virtual void Draw3D() {};
	virtual bool Update() { return true; };
};