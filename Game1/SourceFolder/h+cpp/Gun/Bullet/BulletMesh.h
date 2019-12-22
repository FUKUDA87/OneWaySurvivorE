#pragma once
#include"BulletPol.h"

class C_BulletMesh :public C_BulletPol {
public:
	C_BulletMesh(const GETGUNDATA * GetGunData);
	virtual void Draw3DAll(const D3DXVECTOR3 *CamPos);
protected:
	void Draw3DMesh(void);
	void Init(const int *MeshNo, const D3DXVECTOR3* ScalPos);
	XFILE BulletMesh;
	D3DXMATRIX ScalMat;
private:

};