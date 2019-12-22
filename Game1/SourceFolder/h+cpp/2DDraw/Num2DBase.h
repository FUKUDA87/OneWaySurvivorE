#pragma once
#include<d3dx9.h>
#include<string>
#include"../GameSource/Judgment.h"

class C_Num2DBase {
public:

	//位置と拡大のセット
	void SetNum(const D3DXVECTOR3 *Pos, const D3DXVECTOR3 *Scal);
	//画像のセット
	void SetTex(std::string FileName,const int *Width, const int *Height);
	//表示(継承させる)
	virtual void Draw2DNB(const int *TmpNum)=0;
	//表示用行列の作成
	virtual D3DXMATRIX GetDrawMatNDB(const D3DXMATRIX *Mat);
	//画像の情報渡し
	CHARA2D GetTexNDB(void) {
		return Num;
	}
protected:
	Judg judg;
	CHARA2D Num;
private:
};