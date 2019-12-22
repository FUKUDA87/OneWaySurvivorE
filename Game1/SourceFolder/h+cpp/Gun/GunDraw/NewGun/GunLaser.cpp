#include "GunLaser.h"
#include"../../Laser/LaserDraw1.h"

C_GunLaser::C_GunLaser()
{
	int No = 0;
	mc_Laser = new C_LaserDraw1(&No);
}

C_GunLaser::~C_GunLaser()
{
	if (mc_Laser != nullptr) {
		delete mc_Laser;
	}
}

void C_GunLaser::Draw3D_Laser(const D3DXVECTOR3 * CamPos)
{
	if (mc_Laser == nullptr)return;

	float PolSize = 0.01f;
	bool Flg = false;
	if ((s_Data.RayJudgFlg == true) && (s_Data.DrawNo.LaserNo > 0))Flg = true;
	mc_Laser->Draw3DAll(&Gun.Base.Mat, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &PolSize, CamPos, &m_Dis, &Flg);
}

void C_GunLaser::GetDis(const float * Dis)
{
	if (s_Data.RayHitFlg == true) {
		m_Dis = *Dis;
	}
	else {
		m_Dis = s_Data.RayDis;
	}
}
