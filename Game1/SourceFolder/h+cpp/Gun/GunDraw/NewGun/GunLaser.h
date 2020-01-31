#pragma once
#include"GunMuzFla.h"
#include"../../Laser/LaserBase2.h"

class C_GunLaser :public C_GunMuzFla {
public:
	~C_GunLaser();
	void Draw3D_Laser(const D3DXVECTOR3*CamPos);
	void GetDis(const float* Dis);
protected:
	C_LaserBase2 *mc_Laser;
	float m_Dis;
private:

};