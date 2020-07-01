#pragma once
#include<d3dx9.h>
#include"../GameSource/Judgment.h"
#include"../GameSource/Struct.h"
#include<vector>
#include"Wall.h"

class C_Ground {
public:
	C_Ground(const int *i);
	C_Ground(const D3DXMATRIX *Mat3, const D3DXMATRIX *Mat4,const S_GROUND_INIT_DATA* Init_Data_Ground);
	~C_Ground();
	
	// �X�V����
	virtual bool Update();

	// �\��
	virtual void Draw3D() { Draw3DGround(); }

	D3DXMATRIX GetMat(void) { return ground.Base.Mat; }

	bool GetFlg(void) { return ground.Base.Flg; }

	void SetFlg(bool b) { ground.Base.Flg = b; }

	//�n�ʔ���(���C)�̎��Ɏg�p
	D3DXVECTOR3 GetVer(int i) { return ground.v[i].Pos; };

	Way GetWay(void) { return way; }

	float GetPosZ(void) { return ground.Base.Pos.z; }

	D3DXMATRIX GetMat0();

	D3DXMATRIX GetMat1();

	bool GetIdenFlg(void) { return IdenFlg; }

	// ��
	unsigned int GetWallNum(void) { return wall.size(); }
	D3DXMATRIX GetWallMat(const unsigned int *wc) { return wall[*wc]->GetMat(); }
	D3DXMATRIX GetWallDrawMat(const unsigned int *wc) { return wall[*wc]->GetDrawMat(); }
	LPD3DXMESH GetWallColMod(const unsigned int *wc) { return wall[*wc]->GetColMod(); }
	S_Base3D_2 GetWallData(const unsigned int *wc) { return wall[*wc]->GetData(); }
	void SetWallDrawFlg(const unsigned int *wc, const bool *DrawFlg) { return wall[*wc]->SetDrawFlg(DrawFlg); }
	void GetBallJudgWall(float *Radius, D3DXVECTOR3 *Pos, const unsigned int *wc) { return wall[*wc]->GetBallJudgWall(Radius, Pos); }

protected:
	Pol ground;

	Way way;

	D3DXMATRIX DrawMat;

	bool MoveFlg;

	bool IdenFlg;

	std::vector<c_Wall*>wall;

	Judg judg;

	void UpdateGround();

	void Draw3DGround();
private:
	void Init();
	void InitWall(void);
};