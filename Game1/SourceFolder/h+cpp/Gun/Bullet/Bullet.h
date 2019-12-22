#pragma once
#include<d3dx9.h>
#include"../../GameSource/Struct.h"
#include"../../GameSource/Const.h"

#ifndef Bullet_H
#define Bullet_H


class Bullet{
private:
	Pol bul;
	D3DXMATRIX smokeMat[GNUM];
	D3DXMATRIX IdenMat;
	//çUåÇóÕ
public:
	void Init();
	Bullet(D3DXMATRIX mat);
	Bullet(D3DXMATRIX mat, D3DXVECTOR3 pos);
	Bullet();
	~Bullet();
	void Draw();
	bool Update();
	bool UpdateM(D3DXVECTOR3 bVec);

	D3DXMATRIX GetBulMat(void) {
		return bul.Base.Mat;
	}
};

#endif // !Bullet_H