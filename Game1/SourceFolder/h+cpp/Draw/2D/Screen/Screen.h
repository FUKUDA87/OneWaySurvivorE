#pragma once
#include<d3dx9.h>
#include"../../../GameSource/Struct.h"

class c_Screen
{
public:
	c_Screen();
	~c_Screen();

	// 更新処理
	bool Update(void);

	// 表示
	void Draw2D(void);

	bool RenderStart(const D3DXMATRIX *Mat);
	void RenderEnd(void);
private:
	
	S_SCREEN_2D M_S_Screen;  // ミニ画面の表示
};