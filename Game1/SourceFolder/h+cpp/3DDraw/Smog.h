#pragma once
#include<d3dx9.h>
#include"../GameSource/Struct.h"

class C_Smog {
public:
	C_Smog(const D3DXVECTOR3 *Pos);
	~C_Smog();
	//初期化
	void Init();
	//アップデート
	virtual bool Update(void);
	//時限式
	bool CountUpdate(void);
	//表示
	void Draw3D(void);
	virtual void Draw3D(D3DXVECTOR3 CamPos);
protected:
	Pol smog;
	//時限削除用
	int NowCount;
	//移動用
	float yUp;
	//拡大用
	float ScalSize;
private:

};