#pragma once
#include"MeshManager.h"

class C_StandMeshManager :public C_MeshManager{
public:
	XFILE GetMesh(int MeshNo);
protected:
	//スタンドのモデル情報探し
	bool GetMeshJudg(int MeshNo);
private:
	//スタンド１
	bool GetStand1(int MeshNo);
	//スタンド１01
	bool GetStand101(int MeshNo);
};