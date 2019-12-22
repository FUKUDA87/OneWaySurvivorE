#pragma once
#include<d3dx9.h>
#include"../GameSource/Struct.h"
#include"Draw3DManager/StandMeshManager.h"

class C_StandBase{
public:
	C_StandBase();
	~C_StandBase();
	//初期化
	virtual void InitStand(void);
	//車に継承した際にオーバーライド
	virtual bool UpdateSta();
	void Draw3DSta();

	//表示用行列渡し
	virtual D3DXMATRIX GetDrawMatSta(void);

	//スタンドのMeshの入れ替え
	void SetMeshSta(int MeshNo);

protected:
	BASE3D Stand;
private:
	XFILE StandMesh;
	C_StandMeshManager standMeshManager;
	float x, y, z;
};

//class Stand1 :public C_Tire {
//private:
//	XFILE standMesh;
//	float x, y, z;
//protected:
//	D3DXMATRIX standMat;
//public:
//	Stand1();
//	~Stand1();
//	virtual bool SUpdate();
//	void SDraw();
//};
