#pragma once
#include"PartsMeshDraw_1.h"

class C_GunPartsDraw_1_1 :public C_PartsMeshDraw_1 {
public:
	C_GunPartsDraw_1_1(const int *DrawMeshType, const int *MeshNo, const int *MeshPartsNo);
	//更新処理
	virtual bool Update(const D3DXMATRIX *Mat);
	//表示処理
	virtual void Draw(void);
protected:

private:

};