#pragma once
#include<d3dx9.h>

#ifndef Ball_H
#define Ball_H


class Ball {
public:
	void Init();
	Ball(float radius);
	~Ball() ;
	void Draw();
	bool Update(D3DXMATRIX mat);
protected:

private:
	LPD3DXMESH lpBall;//メッシュの形状のデータを入れる変数
	D3DMATERIAL9 BallMaterial;//マテリアル（色・材質）
	D3DXMATRIX BaMat;
};

#endif // !Ball_H
