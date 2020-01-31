#pragma once
#include"../../../Draw/DrawBase/Mesh_Draw/MeshDraw1_1/MeshSet2_1/MeshSet2_1.h"
#include"../../../GameSource/CharaBase.h"

class C_PartsBase_1:public C_CharaBase {
public:
	C_PartsBase_1();
	~C_PartsBase_1();

	//Šg‘åk¬‚Ì‘€ì
	void Set_ScalPos(const D3DXVECTOR3 *s_ScalPos);

	//•\¦s—ñì¬
	D3DXMATRIX Get_DrawMat(void);

protected:
	BASE3D M_Base;
	D3DXVECTOR3 M_ScalPos;

private:

};