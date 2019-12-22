#pragma once
#include"MeshManager.h"

class C_CarMeshManager :public C_Mesh3Manager{
public:
	XFILE3 GetMesh(int MeshNo);
private:
	//モデル情報探し
	bool GetMeshJudg(int MeshNo);

	//カー１
	bool GetCar1(int MeshNo);
	//カー2
	bool GetCar2(int MeshNo);
	//車101
	bool GetCar101(int MeshNo);
	//車201
	bool GetCar201(int MeshNo);
};