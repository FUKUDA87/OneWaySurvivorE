#pragma once
#include"Gun_No1_Shot_Effect.h"
#include"../../../../Draw/DrawBase2/Draw_Mesh_Base_A.h"
#include"../../../../GameSource/Count.h"

class C_Gun_No1_Bullet_Enpty :public C_Draw_Mesh_Base {
public:
	C_Gun_No1_Bullet_Enpty(const D3DXMATRIX *GunMat);
	~C_Gun_No1_Bullet_Enpty();

	//�\���֐�
	virtual void Draw3D(const D3DXVECTOR3 *CameraPos);

	//�ړ��ʂ̃Z�b�g
	virtual void Set_MoveVec(const D3DXVECTOR3 *MoveVec);

	bool Update(void);
protected:
	//�ړ��x�N�g��
	D3DXVECTOR3 M_MoveVec;
	//y�̌��炷��
	float yDown;

	C_Count *M_Count;

	//������
	void Init_Bullet(void);

private:

};