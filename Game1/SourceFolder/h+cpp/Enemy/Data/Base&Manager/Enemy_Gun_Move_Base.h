#pragma once
#include"../../../Gun/GunDraw/GunMove/GunMoveBase_A.h"
#include"../../../GameSource/Struct.h"

class C_Enemy_Gun_Move_Base :public C_GunMoveBase_A {
public:
	C_Enemy_Gun_Move_Base();

	//銃の更新
	C_GunMoveBase_A* Update(S_GUN_DATA *s_Data, const S_GUN_UPDATE_DATA* s_Update, CHARABASE *Chara);
protected:
	//表示の行列作成
	void Get_Mat(D3DXMATRIX *Mat, const QUAMAT *Rot, const D3DXMATRIX *StandMat);

	//次の動き渡し
	C_GunMoveBase_A* Get_Move(S_GUN_DATA * s_Data, const D3DXMATRIX *StandMat, const int *NowHp, C_GunMoveBase_A * Move);
	C_GunMoveBase_A* Get_Move(S_GUN_DATA * s_Data, const D3DXMATRIX *StandMat,const int *NowHp);

	//終了処理
	virtual void End_Move(S_GUN_DATA *s_Data);

	//銃の停止確認
	bool GunStop_Flg(const S_GUN_UPDATE_DATA* s_Update, const CHARABASE *Chara);

private:
	//前回の更新で銃のHPがゼロかのFlg
	bool M_GunInitFlg;

	//銃の回転の初期化
	void Init_Gun_RotMat(S_GUN_DATA * s_Data, const int *NowHp);
};