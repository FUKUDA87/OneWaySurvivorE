#pragma once
#include"PartsBase_1.h"

class C_PartsMeshDraw_1 :public C_PartsBase_1 {
public:
	C_PartsMeshDraw_1(const int *DrawMeshType,const int *MeshNo, const int *MeshPartsNo);
	~C_PartsMeshDraw_1();
protected:
	//表示のクラス
	C_MeshDraw_1 *M_C_Draw;
private:
	//初期化
	void Init_C_Draw(const int *DrawMeshType, const int *MeshNo, const int *MeshPartsNo);

	//削除
	void Delete_C_Draw(void);
};