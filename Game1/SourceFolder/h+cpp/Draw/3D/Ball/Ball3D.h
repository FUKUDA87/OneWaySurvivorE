#pragma once
#include<d3dx9.h>

class c_Ball3D {
public:
	c_Ball3D(float Radius);
	c_Ball3D(float Radius,float alpha);
	~c_Ball3D();

	void Draw();
	void DrawB();

	void SetPos(const D3DXVECTOR3 *Pos) { pos = *Pos; }

	void SetRadius(void);

	float GetRadius(void) { return radius; }

	D3DXVECTOR3 GetPos(void) { return pos; }

protected:
	void Init(void);
	void Release(void);
private:
	LPD3DXMESH lpBall;//���b�V���̌`��̃f�[�^������ϐ�
	D3DMATERIAL9 BallMaterial;//�}�e���A���i�F�E�ގ��j
	D3DXVECTOR3 pos;
	float radius;
};
