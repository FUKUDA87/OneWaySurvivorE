#pragma once
#include"PartsBase_1.h"

class C_PartsMeshDraw_1 :public C_PartsBase_1 {
public:
	C_PartsMeshDraw_1(const int *DrawMeshType,const int *MeshNo, const int *MeshPartsNo);
	~C_PartsMeshDraw_1();
protected:
	//�\���̃N���X
	C_MeshDraw_1 *M_C_Draw;
private:
	//������
	void Init_C_Draw(const int *DrawMeshType, const int *MeshNo, const int *MeshPartsNo);

	//�폜
	void Delete_C_Draw(void);
};