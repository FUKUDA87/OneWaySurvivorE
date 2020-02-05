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
	LPD3DXMESH lpBall;//���b�V���̌`��̃f�[�^������ϐ�
	D3DMATERIAL9 BallMaterial;//�}�e���A���i�F�E�ގ��j
	D3DXMATRIX BaMat;
};

#endif // !Ball_H
