#pragma once
#include<d3dx9.h>

class c_ButtonBase
{
public:
	c_ButtonBase();

	// 表示
	virtual void Draw2D(void){}

	// 更新処理
	virtual bool Update(void) { return false; }
	virtual bool Update(const D3DXVECTOR3 *pos);

	// タッチ判定
	virtual bool TouchJudg(void);

	// タッチした時に次の動きの番号渡し
	int GetNextNo(void) { return nextNo; }
protected:
	int nextNo;

	D3DXVECTOR3 Pos,basePos,transPos;  // 位置と基本の位置と移動の位置
	float scalX, scalY;   // 拡縮x,y
	int width, height;  // 画像サイズ
};