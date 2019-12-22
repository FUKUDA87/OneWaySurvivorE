#pragma once
#include<d3dx9.h>
#include"../GameSource/Struct.h"

#ifndef Sky_H
#define Sky_H

class Sky{
protected:
	Object3D sky;
public:
	void Init();
	Sky();
	~Sky();
	bool Update(D3DXMATRIX PM);
	void Draw();
};

#endif // !Sky_H
