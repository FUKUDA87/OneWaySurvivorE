#pragma once
#include"../../../GameSource/Struct.h"
#include<stdio.h>
#include"../../../GameSource/Const.h"

//１つのメッシュ
class C_MeshManager {
public:
	//モデル情報渡し
	virtual XFILE GetMesh(int MeshNo) = 0;
protected:
	//モデル情報探し
	virtual bool GetMeshJudg(int MeshNo) = 0;

	char MeshName[100];
};
//３つのメッシュ
class C_Mesh3Manager {
public:
	//スタンドのモデル情報渡し
	virtual XFILE3 GetMesh(int MeshNo) = 0;
protected:
	//スタンドのモデル情報探し
	virtual bool GetMeshJudg(int MeshNo) = 0;

	char MeshName[3][100];
};