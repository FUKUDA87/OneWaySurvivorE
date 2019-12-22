#pragma once
#include<d3dx9.h>

#ifndef Ball_H
#define Ball_H


class Ball {
private:
	LPD3DXMESH lpBall;//メッシュの形状のデータを入れる変数
	D3DMATERIAL9 BallMaterial;//マテリアル（色・材質）
	D3DXMATRIX BaMat;
protected:
public:
	void Init();
	Ball() {};
	Ball(float radius);
	~Ball() ;
	void Draw();
	bool Update(D3DXMATRIX mat);
};

#endif // !Ball_H
