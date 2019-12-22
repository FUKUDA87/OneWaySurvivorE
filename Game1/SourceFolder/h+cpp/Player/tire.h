#pragma once
#include<d3dx9.h>
#include"player.h"
#include"../GameSource/Const.h"

class C_Tire:public C_Player {
private:
protected:
	XFILE tireMesh;
	BASE3D tire[TNUM];
public:
	C_Tire();
	~C_Tire();
	virtual bool TUpdate(void);
	void TDraw();
};
