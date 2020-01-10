#pragma once
#include<d3dx9.h>
#include"../../GameSource/Struct.h"

class C_Smog {
public:
	C_Smog(const D3DXMATRIX *Mat);
	C_Smog(const D3DXMATRIX *Mat,const S_Smog *H_Smog);
	~C_Smog();
	//初期化
	void Init();
	//アップデート
	virtual bool Update(void);
	//時限式
	bool CountUpdate(void);
	//表示
	virtual void Draw3D(D3DXVECTOR3 CamPos);

	void Init_Num(void);

	int GetNum(void) {
		return M_S_Smog.Draw_No;
	}

	void NumJudg(void);

	void SetNum(const int s_Num);

	//位置の補正
	void PosMoveVec(const D3DXVECTOR3*MoveVec);
protected:
	Pol smog;
	//時限削除用
	int NowCount;
	//拡大用
	float ScalSize;

	//位置の補正判定
	bool MoveVecJudg(void);
	//移動行列の初期化
	void Init_Mat(void);
private:
	//表示方法の構造体
	S_Smog M_S_Smog;

	//移動の
	bool MoveVecFlg;

	//透明度のアップデート
	void Update_Alpha(void);
	//乱数の数値作成
	float RandPlus(const int *Num);
	//ポリゴンサイズの変化
	float GetPolSize(void);

};