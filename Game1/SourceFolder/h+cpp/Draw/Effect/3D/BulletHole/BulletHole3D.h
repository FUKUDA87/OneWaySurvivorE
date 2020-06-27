#pragma once
#include<d3dx9.h>
#include"../../EffectBase.h"

class C_BulletHole3D:public c_EffectBase
{
public:
	C_BulletHole3D(const D3DXMATRIX *Mat, const D3DXVECTOR3 *Pos, int TypeNo);
	
	// �X�V����
	bool Update(void);
	
	// �\��
	void Draw3D(const D3DXVECTOR3 *CameraPos);
	
private:
	Pol Hole;
	//����
	//�ǔ���
	void InitWall(int TypeNo);
	//�n�ʔ���
	void InitGround(int TypeNo);
	//����
	int NowCount;

	//������
	void Init(void);

	//������
	bool CountUpdate(void);
};