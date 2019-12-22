#pragma once
#include<d3dx9.h>
#include"Tire2.h"

class StandE:public Tire2{
private:
	D3DXVECTOR3 Pos;
protected:
	Object3D stand;
public:
	void InitSta();
	StandE() { InitSta(); };
	StandE(D3DXMATRIX GroundMat, float *TransX):Tire2(GroundMat, TransX) { InitSta(); };
	~StandE() {};
	virtual bool StaUpdate();
	void StaDraw();

	bool UpdateAll();
	void DrawAll();

	/*D3DXMATRIX GetMat(void) { return; };
	void SetMat(D3DXMATRIX mat) { = mat; };
	bool GetFlg(void) { return; };
	void SetFlg(bool b) { = b; };*/
};