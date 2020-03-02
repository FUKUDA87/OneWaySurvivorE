#pragma once
#include<d3dx9.h>
#include"ground.h"
#include"../GameSource/Struct.h"
#include<vector>

const int WNum = 2;
class Wall :public C_Ground {
public:
	Wall(const int *i);
	Wall(const D3DXMATRIX *Mat3, const D3DXMATRIX *Mat4, const S_GROUND_INIT_DATA * Init_Data_Ground);

	//壁の数
	int Get_Wall_Num(void) {
		return 2;
	}

	void SuperDraw();

	//壁のコリジョンモデル渡し
	LPD3DXMESH GetColModWall(void) {
		return M_Wall.ColModMesh.lpMesh;
	}
	//壁3Dの表示行列渡し
	D3DXMATRIX Get_DrawMat_Wall(const int *Wall_Num);
	//壁3Dの行列渡し
	D3DXMATRIX Get_Mat_Wall(const int *Wall_Num);

	//壁の情報渡し
	S_Base3D_2 Get_Data_Wall(const int *Wall_Num);

	//表示の変更
	void Set_Draw_Flg_Wall(const int *Wall_Num, const bool *DrawFlg);

protected:

	void WaDraw();

private:
	//壁3D用
	S_Object3D_Data M_Wall;

	S_Base3D_2 Wall3D[2];

	//壁のサイズの初期化後の初期化
	void Init_Wall3D_All(void);

	//壁の初期化
	void Init_Wall();

	//地面の行列が単位行列じゃない場合の初期化
	void Init_Wall_Mat(void);

	//地面の表示行列に単位行列が使用されている場合の初期化
	void Init_Wall_Iden(void);

	//壁のサイズの初期化
	void Init_Wall_SizeZ(const D3DXVECTOR3 * Ground_Vec, const int *Wall_No);
};