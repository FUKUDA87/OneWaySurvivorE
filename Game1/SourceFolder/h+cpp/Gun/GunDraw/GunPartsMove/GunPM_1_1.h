#pragma once
#include"PartsMeshDraw_1.h"

class C_GunPartsDraw_1_1 :public C_PartsMeshDraw_1 {
public:
	C_GunPartsDraw_1_1(const int *DrawMeshType, const int *MeshNo, const int *MeshPartsNo);
	//XVˆ—
	virtual bool Update(const D3DXMATRIX *Mat);
	//•\¦ˆ—
	virtual void Draw(void);
protected:

private:

};