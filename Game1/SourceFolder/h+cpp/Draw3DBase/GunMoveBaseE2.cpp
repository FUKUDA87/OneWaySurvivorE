#include "GunMoveBaseE2.h"

C_GunMoveBaseE2::~C_GunMoveBaseE2()
{
	DeleteGun();
}

void C_GunMoveBaseE2::InitSetGun(const GUNINITDATA * GunInitDataS)
{
	//m_Gun.push_back(new C_GunLaser(GunInitDataS));
}

void C_GunMoveBaseE2::DeleteGun(void)
{
	if (m_Gun.size() <= 0)return;
	//íœ
	for (unsigned int g = 0; g < m_Gun.size(); g++) {
		delete m_Gun[g];
		m_Gun.erase(m_Gun.begin() + g);
		g--;
	}
}

//GUNDATA C_GunMoveBaseE2::GetGunData(unsigned int * No)
//{
//	if (m_Gun.size() <= 0)return GUNDATA();
//
//	unsigned int pNo = *No;
//	if (pNo <= 0)pNo = 0;
//	if (pNo >= m_Gun.size())pNo = m_Gun.size() - 1;
//
//	return m_Gun[pNo]->GetGunData();
//}
//
//D3DXMATRIX C_GunMoveBaseE2::GetGunMat(unsigned int * No)
//{
//	if (m_Gun.size() <= 0)return D3DXMATRIX();
//
//	unsigned int pNo = *No;
//	if (pNo <= 0)pNo = 0;
//	if (pNo >= m_Gun.size())pNo = m_Gun.size() - 1;
//	return m_Gun[pNo]->GetDrawMatGun();
//}

bool C_GunMoveBaseE2::SetDamageGun(const unsigned int * gNo, const int * Damage)
{
	if (*gNo < 0)return false;
	if (*gNo > m_Gun.size() - 1)return false;

	if (m_Gun[*gNo]->HpDamage(Damage) != true)return false;

	return true;
}

int C_GunMoveBaseE2::GunDeadFlg(unsigned int * gNo)
{
	if (*gNo < 0)return 2;
	if (*gNo > m_Gun.size() - 1)return 2;

	if (m_Gun[*gNo]->Dead() == true)return 0;

	return 1;
}

void C_GunMoveBaseE2::GetTargetPos(const D3DXVECTOR3 * Pos)
{
	if (m_Gun.size() <= 0)return;

	for (unsigned int g = 0; g < m_Gun.size(); g++) {
		//m_Gun[g]->GetTargetPos(Pos);
	}
}

//S_ENEMYGUNDATA C_GunMoveBaseE2::GetEnemyGunData(const unsigned int * gNo)
//{
//	return m_Gun[*gNo]->GetEnemyGunData();
//}

void C_GunMoveBaseE2::SetHitRayFlg(const unsigned int * gNo, const bool * Flg)
{
	//m_Gun[*gNo]->SetHitRayFlg(Flg);
}

bool C_GunMoveBaseE2::UpdateBullet2(const D3DXVECTOR3 *mVec)
{
	/*if (m_Gun.size() > 0) {
		for (unsigned int g = 0; g < m_Gun.size(); g++) {
			if (m_Gun[g]->GetEnemyGunData().BulletFlg == true) {
				bool Flg = m_Gun[g]->GetEnemyGunData().BulletFlg;
				BulletBirth(m_Gun[g]->GetBullet(), &Flg);
				m_Gun[g]->SetBulletFlg(&Flg);
			}
		}
	}
	BulletMoveSet(mVec);*/
	return false;
}

void C_GunMoveBaseE2::Draw3D_Laser(const D3DXVECTOR3 * CamPos)
{
	if (m_Gun.size() <= 0)return;

	for (auto && g: m_Gun) {
		g->Draw3D_Laser(CamPos);
	}
}

void C_GunMoveBaseE2::GetRayHitDis(const unsigned int * gNo, const float * Dis)
{
	if (m_Gun.size() <= 0)return;

	m_Gun[*gNo]->GetDis(Dis);
}
