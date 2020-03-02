#pragma once
#include<d3dx9.h>
#include"../GameSource/Judgment.h"
#include"../GameSource/Struct.h"

class C_Ground {
public:
	void Init();
	C_Ground(const int *i);
	C_Ground(const D3DXMATRIX *Mat3, const D3DXMATRIX *Mat4,const S_GROUND_INIT_DATA* Init_Data_Ground);
	~C_Ground();
	
	virtual void SuperUpdate() {
		Update();
	};
	virtual void SuperDraw() {
		Draw();
	};

	D3DXMATRIX GetMat();
	bool GetFlg();
	void SetFlg(bool b);
	//地面判定(レイ)の時に使用
	D3DXVECTOR3 GetVer(int i) { return ground.v[i].Pos; };
	Way GetWay(void) {
		return way;
	};
	float GetPosZ(void) {
		return ground.Base.Pos.z;
	}

	D3DXMATRIX GetMat0();
	D3DXMATRIX GetMat1();
	bool GetIdenFlg(void) {
		return IdenFlg;
	}
protected:
	Pol ground;
	Way way;
	D3DXMATRIX DrawMat;
	bool MoveFlg;
	bool IdenFlg;

	Judg judg;

	void Update();
	void Draw();
private:

};