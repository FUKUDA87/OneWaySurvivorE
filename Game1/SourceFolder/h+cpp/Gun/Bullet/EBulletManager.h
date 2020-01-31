#pragma once
//#include"BulletManager.h"
#include"Bullet.h"
#include<vector>
#include"BulletDraw3DBase.h"
#include"../../Draw3DBase/GunMoveBaseE2.h"

class EBulletManager{
public:
	//EBulletManager(int cnt) { bul1 = cnt; };
	EBulletManager();
	~EBulletManager();
	bool BulletBirth(C_BulletDraw3DBase* bulletBase, bool *b);
	bool BulletMoveSet(const D3DXVECTOR3 *MoveVec);
	bool UpdateBMES(const D3DXVECTOR3 *mVec, C_BulletDraw3DBase* bulletBase, bool *b);
	//bool UpdateBME(D3DXVECTOR3 mVec, BulletBase* bulletBase, bool *b,int a);
	bool UpdateBME(void);
	void DrawBM(const D3DXVECTOR3 *CamPos);
	//バレットMat
	D3DXMATRIX GetBulMat(unsigned int i) {
		return BulletE[i]->GetMat();
	}
	unsigned int GetBulSize(void) {
		return (unsigned int)BulletE.size();
	}
	void BulDelete(unsigned int *i);
	//移動の長さ渡し
	float GetBulletMoveDis(unsigned int i) {
		return BulletE[i]->GetBulletSpeed();
	}
	//バレットの待ち時間セット
	/*void SetTimeNum(int Num) {
		bul1 = Num;
	}*/

protected:
	std::vector<C_BulletDraw3DBase*>BulletE;
private:
};