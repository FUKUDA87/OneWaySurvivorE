#pragma once
#include<d3dx9.h>
#include"../../GameSource/Struct.h"

class C_Spark {
public:
	//Mat=初期角度,Pos＝座標
	C_Spark(const D3DXMATRIX *Mat,const D3DXVECTOR3 *Pos);
	~C_Spark();
	//初期化
	void Init();
	//アップデート
	virtual bool Update(void);
	//Vec=車体の移動量
	bool Update(const D3DXVECTOR3 *CarMoveVec);
	//継承を含めたアップデート
	virtual bool UpdateSuper(void);
	//時限式
	bool CountUpdate(void);
	//表示
	virtual void Draw3D(const D3DXVECTOR3 *CameraPos);
	//継承を含めたDraw3D
	virtual void Draw3DSuper(const D3DXVECTOR3 *CameraPos);
protected:
	//最初にVecを足さないFlg
	bool CarMoveFlg;
	//ポリゴン表示用構造体
	Pol spark;
	//ポリゴン数
	int PNum;
	//ジャンプ移動の変数
	float yUp, yDown;
	//後ろ方向に移動させる
	float zDown;
	//表示用行列
	D3DXMATRIX IdenMat;
	//時間で削除
	int NowCount;
	//ポリゴンサイズ
	float PolSize;
private:
};