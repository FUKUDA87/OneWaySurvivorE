#pragma once
#include<d3dx9.h>
#include"BillBase.h"


class Bill :public BillBase {
private:
protected:
public:
	void InitB1() { 
	bill.Base.DrawFlg= false; };
	Bill() {};
	Bill(int i) :BillBase(i) { InitB1(); };
	Bill(D3DXMATRIX Mat3, D3DXMATRIX Mat4, int gType, float Ang, float Length, bool LengthAuto) :BillBase(Mat3, Mat4,gType,Ang,Length,LengthAuto) { InitB1(); };
	~Bill() {};
	bool UpdateBil() { return true; };
	void SuperUpdate();
	void SuperDraw();
};

