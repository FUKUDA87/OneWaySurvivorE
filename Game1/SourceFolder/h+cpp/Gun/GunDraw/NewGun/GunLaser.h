#pragma once
#include"GunBullet.h"
#include"../../Laser/LaserBase2.h"

class C_GunLaser :public C_GunBullet {
public:
	~C_GunLaser();
	//�\���̏���
	void Draw(const D3DXVECTOR3* CameraPos);
	void GetDis(const float* Dis);
protected:
	C_LaserBase2 *mc_Laser;
	float m_Dis;
	//�\��
	void Draw3D_Laser(const D3DXVECTOR3*CamPos);

	//���[�U�[�̍쐬
	void New_Laser(void);
private:

};