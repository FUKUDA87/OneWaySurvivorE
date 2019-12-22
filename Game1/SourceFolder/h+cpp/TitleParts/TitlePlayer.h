#pragma once
#include<d3dx9.h>
#include"../Player/Gun1.h"
#include"../GameSource/Motion.h"


extern Motion motion;

#ifndef TitlePlayer_H
#define TitlePlayer_H

void DrawMesh(XFILE *XFile);
class TitlePlayer:public Gun1{
private:
protected:
	D3DXVECTOR3 qVec, cVec;
public:
	void Init();
	TitlePlayer() {};
	~TitlePlayer() {};
	void Draw();
	bool SuperUpdate(float AngX, float AngY, std::vector<BillBase*>ground);
	void SuperDraw();
};

#endif //!TitlePlayer_H