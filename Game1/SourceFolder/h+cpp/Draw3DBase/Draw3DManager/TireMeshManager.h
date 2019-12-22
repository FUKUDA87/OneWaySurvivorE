#pragma once
#include"MeshManager.h"

class C_TireMeshManager :public C_MeshManager {
public:
	XFILE GetMesh(int MeshNo);
private:
	//検索
	bool GetMeshJudg(int MeshNo);
	//タイヤ１
	bool GetTire1(int MeshNo);
	//タイヤ１01
	bool GetTire101(int MeshNo);
	//タイヤ201
	bool GetTire201(int MeshNo);
};