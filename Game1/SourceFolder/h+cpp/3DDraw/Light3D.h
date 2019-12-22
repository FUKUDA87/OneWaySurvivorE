#pragma once
#include<d3dx9.h>
#include"../GameSource/Struct.h"

class C_Light {
public:
	C_Light();
	C_Light(const D3DXMATRIX *WallMat);
	~C_Light();
	//初期化
	void Init(void);
	//アップデート
	bool Update(void);
	//表示
	void Draw3D(void);
	//表示
	void Draw3D(const D3DXMATRIX *Mat);
	//位置行列渡し
	D3DXMATRIX GetMat(void);
protected:

private:
	Object3D2 Light;
};
