#pragma once
#include<d3dx9.h>
#include"../../GameSource/Struct.h"
#include"../../GameSource/Countdown.h"


class Explo {
public:
	void Init();
	Explo();
	Explo(D3DXMATRIX mat);
	Explo(D3DXMATRIX mat,const SoundCamera *sc);
	~Explo();
	bool ExplUpdate(float AngX, float AngY);
	bool ExplUpdate(const D3DXMATRIX *CamMat);
	void ExplDraw();
protected:
	Pol expl;
	//ƒJƒEƒ“ƒg
	int num;
private:
	Cou *cou;
};

