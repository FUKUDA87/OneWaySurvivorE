#pragma once
#include"../Draw_3D_Base.h"
#include"../../../GameSource/Struct.h"
#include"../../../GameSource/XfileManager.h"

class C_Draw_3D_Mesh_1 :public C_Draw_3D_Base {
public:
	C_Draw_3D_Mesh_1(std::string FileName);

	//•\Ž¦
	void Draw(const D3DXVECTOR3 *CameraPos, const D3DXMATRIX *Mat);
protected:
	XFILE_B M_Mesh;
};