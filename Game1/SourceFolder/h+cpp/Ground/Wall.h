#pragma once
#include<d3dx9.h>
#include"../GameSource/Struct.h"
#include"../Draw/3D/Ball/Ball3D.h"

class c_Wall {
public:
	c_Wall(const bool *PolygonIdenFlg,const bool *LeftFlg,const D3DXMATRIX *Mat
		,const D3DXVECTOR3 *StartPos,const D3DXVECTOR3 *EndPos);
	~c_Wall() { if (ball3D != nullptr)delete ball3D; }

	// �\��
	void Draw3D();

	//�ǂ̃R���W�������f���n��
	LPD3DXMESH GetColMod(void) { return collisionMesh.lpMesh; }

	//��3D�̕\���s��n��
	D3DXMATRIX GetDrawMat();

	//��3D�̍s��n��
	D3DXMATRIX GetMat();

	//�ǂ̏��n��
	S_Base3D_2 GetData();

	//�\���̕ύX
	void SetDrawFlg(const bool *DrawFlg);

	// ������̏������
	void GetBallJudgWall(float *Radius, D3DXVECTOR3 *Pos);

private:
	//��3D�p
	XFILE_B wallMesh;
	XFILE collisionMesh;

	S_Base3D_2 Wall3D;

	c_Ball3D *ball3D;

	//�ǂ̃T�C�Y�̏�����
	void InitWallSizeZ(const D3DXVECTOR3 * Ground_Vec);
};