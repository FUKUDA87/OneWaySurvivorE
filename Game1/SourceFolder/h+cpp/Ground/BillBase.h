#pragma once
#include<d3dx9.h>
#include"Wall.h"

class BillBase:public Wall{
private:
protected:
	Object3D bill;
	bool obj;
public:
	void InitBB();
	BillBase(const int *i) :Wall(i) { InitBB(); };
	BillBase(const D3DXMATRIX *Mat3, const D3DXMATRIX *Mat4, const S_GROUND_INIT_DATA * Init_Data_Ground) :Wall(Mat3, Mat4,Init_Data_Ground) { InitBB(); };
	
	virtual bool UpdateBil();
	virtual void DrawBil();
	void SuperUpdate() {
		Update();
		UpdateBil();
	}
	void SuperDraw() {
		Draw();
		WaDraw();
		DrawBil();
	}
	bool GetObjFlg() {
		return obj;
	};
	//ï\é¶ÇÃFlgSet
	//void SetAllDrawFlg(bool Flg) {
	//	//Flgë„ì¸èàóù
	//	ground.Base.DrawFlg = WallDrawFlg = bill.Base.DrawFlg = Flg;
	//}
};
