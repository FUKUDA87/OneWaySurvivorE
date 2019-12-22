#pragma once
#include"BulletDraw3DBase.h"

class C_BulletPol :public C_BulletDraw3DBase {
public:
	C_BulletPol(const GETGUNDATA * GetGunData);
	~C_BulletPol();
	bool Update(void);
	bool UpdateSet(const D3DXVECTOR3 *Vec);
	virtual void Draw3DAll(const D3DXVECTOR3 *CamPos);

	//çsóÒìnÇµ
	D3DXMATRIX GetMat(void) {
		return Bullet.Mat;
	};
	D3DXMATRIX GetDrawMat(void) {
		return Bullet.Mat;
	};
protected:
	void Draw3DPol(const D3DXVECTOR3 *CamPos);
	D3DXMATRIX *PolMat;
	int BPolNum;
	VERTEX v[4];
	float BPolSize;
	TEXTURE BTex;

	bool MoveFlg;

	void SetTex(const int *TexNo);
private:

};