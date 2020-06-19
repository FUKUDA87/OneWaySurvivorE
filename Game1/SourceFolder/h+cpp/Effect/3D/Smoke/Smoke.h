#pragma once
#include<d3dx9.h>
#include"../../../GameSource/Struct.h"
#include"../../EffectBase.h"

class c_Smoke:public c_EffectBase {
public:
	c_Smoke(const D3DXMATRIX *Mat, const S_Smog *H_Smog,const float *HpPer, const int *NowHp);
	
	// 更新処理
	bool Update(const s_CarEffectUpdateData *updateData);
	
	//表示
	void Draw3D(const D3DXVECTOR3 *CameraPos);

private:
	Pol smog;
	//時限削除用
	int NowCount;
	//拡大用
	float ScalSize;
	// 煙の種類
	int Draw_No;

	//表示方法の構造体
	S_Smog M_S_Smog;

	//透明度のアップデート
	void Update_Alpha(void);
	//乱数の数値作成
	float RandPlus(const int *Num);
	//ポリゴンサイズの変化
	float GetPolSize(void);

	//時限式
	bool CountUpdate(void);

	// 煙の濃さ
	int InitDrawNo(const float *HpPer, const int *NowHp);
};