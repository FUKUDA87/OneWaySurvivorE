#pragma once
#include<d3dx9.h>
#include"../GameSource/Struct.h"
#include"../Draw/3D/Ball/Ball3D.h"

class c_Wall {
public:
	c_Wall(const bool *PolygonIdenFlg,const bool *LeftFlg,const D3DXMATRIX *Mat
		,const D3DXVECTOR3 *StartPos,const D3DXVECTOR3 *EndPos);
	~c_Wall() { if (ball3D != nullptr)delete ball3D; }

	// 表示
	void Draw3D();

	//壁のコリジョンモデル渡し
	LPD3DXMESH GetColMod(void) { return collisionMesh.lpMesh; }

	//壁3Dの表示行列渡し
	D3DXMATRIX GetDrawMat();

	//壁3Dの行列渡し
	D3DXMATRIX GetMat();

	//壁の情報渡し
	S_Base3D_2 GetData();

	//表示の変更
	void SetDrawFlg(const bool *DrawFlg);

	// 球判定の準備情報
	void GetBallJudgWall(float *Radius, D3DXVECTOR3 *Pos);

private:
	//壁3D用
	XFILE_B wallMesh;
	XFILE collisionMesh;

	S_Base3D_2 Wall3D;

	c_Ball3D *ball3D;

	//壁のサイズの初期化
	void InitWallSizeZ(const D3DXVECTOR3 * Ground_Vec);
};