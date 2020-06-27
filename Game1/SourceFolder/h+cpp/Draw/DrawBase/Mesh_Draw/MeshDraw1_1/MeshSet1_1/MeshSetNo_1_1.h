#pragma once
#include"../MeshDraw1_1.h"
#include"../../../../../Car/Data/Draw3DManager/MeshManager.h"

class C_MeshSetNo_1_1 :public C_MeshDraw_1_1 {
public:
	C_MeshSetNo_1_1(const int *MeshNo, C_MeshManager *s_MeshManager);
	~C_MeshSetNo_1_1();

	void MeshChange(const int *MeshNo);

private:
	C_MeshManager *M_MeshManager;

	void ManagerSet(C_MeshManager *s_MeshManager);

	void DeleteManager(void);
};