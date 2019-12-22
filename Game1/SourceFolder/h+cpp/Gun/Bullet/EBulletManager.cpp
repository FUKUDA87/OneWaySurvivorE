#include "EBulletManager.h"

EBulletManager::EBulletManager()
{
	//SetTimeNum(40);
}

EBulletManager::~EBulletManager()
{
	if (BulletE.size() > 0) {
		for (unsigned int b = 0; b < BulletE.size(); b++) {
			BulDelete(&b);
		}
	}
}

bool EBulletManager::BulletBirth(C_BulletDraw3DBase * bulletBase, bool * b)
{
	if (*b == true) {
		BulletE.push_back(bulletBase);
		*b = false;
	}
	return true;
}

bool EBulletManager::BulletMoveSet(const D3DXVECTOR3 * MoveVec)
{
	if (BulletE.size() > 0) {
		for (unsigned int i = 0; i < BulletE.size(); i++) {
			BulletE[i]->UpdateSet(MoveVec);
		}
	}
	return true;
}

bool EBulletManager::UpdateBMES(const D3DXVECTOR3 *mVec, C_BulletDraw3DBase * bulletBase, bool * b)
{
	if (*b == true) {
		BulletE.push_back(bulletBase);
		*b = false;
	}

	if (BulletE.size() > 0) {
		for (unsigned int i = 0; i < BulletE.size(); i++) {
			BulletE[i]->UpdateSet(mVec);
		}
	}
	/*if (bulFlg == false) {
		if (*b == true) {
			bulFlg = true;
			bulCnt = bul1;
			bullet.push_back(bulletBase);
			*b = false;
		}
	}
	else {
		if (bulFlg == true) {
			bulCnt--;
			if (bulCnt <= 0) {
				bulFlg = false;
			}
		}
	}
	if (bullet.size() > 0) {
		for (unsigned int i = 0; i < bullet.size(); i++) {
			bullet[i]->UpdateMove(mVec);
		}
	}*/
	return true;
}

//bool EBulletManager::UpdateBME(D3DXVECTOR3 mVec, BulletBase * bulletBase, bool * b, int a)
//{
//	/*if (*b == true) {
//		bulFlg = true;
//		bulCnt = bul1;
//		bullet.push_back(bulletBase);
//		*b = false;
//	}
//	
//	if (bullet.size() > 0) {
//		for (unsigned int i = 0; i < bullet.size(); i++) {
//			bullet[i]->UpdateMove(mVec);
//		}
//	}*/
//	return true;
//}

bool EBulletManager::UpdateBME(void)
{
	if (BulletE.size() > 0) {
		for (unsigned int i = 0; i < BulletE.size(); i++) {
			if (BulletE[i]->Update() == false) {
				BulDelete(&i);
			}
		}
	}
	return true;
}

void EBulletManager::DrawBM(const D3DXVECTOR3 *CamPos)
{
	if (BulletE.size() > 0) {
		for (unsigned int b = 0; b < BulletE.size(); b++) {
			BulletE[b]->Draw3DAll(CamPos);
		}
	}
}

void EBulletManager::BulDelete(unsigned int * i)
{
	unsigned int z = *i;
	delete BulletE[z];
	BulletE.erase(BulletE.begin() + z);
	z-=1;
	*i = z;
}
