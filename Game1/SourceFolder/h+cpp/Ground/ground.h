#pragma once
#include<d3dx9.h>
#include"../GameSource/Judgment.h"
#include"../GameSource/Struct.h"

class C_Ground {
public:
	void Init();
	C_Ground();
	C_Ground(int i);
	C_Ground(D3DXMATRIX Mat3, D3DXMATRIX Mat4,int gType,float Ang,float Length,bool LengthAuto);
	~C_Ground();
	void Update();
	void Draw();
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
private:
protected:
	Pol ground;
	Way way;
	D3DXMATRIX DrawMat;
	bool MoveFlg;
	bool IdenFlg;

	Judg judg;
};