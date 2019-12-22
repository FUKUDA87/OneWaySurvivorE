#pragma once
#include<d3dx9.h>
#include"../GameSource/Struct.h"
#include"../GameSource/Judgment.h"
#include"../GameSource/CharaBase.h"

class C_PartsBase:public C_CharaBase {
public:
	C_PartsBase(const PARTS *InitGetParts);
	~C_PartsBase();

	//表示
	void Draw3DParts(void);

	//アップデート
	virtual bool UpdateParts(const D3DXMATRIX *Mat);
	//アップデート＋拡大の変化
	virtual bool UpdateParts(const D3DXMATRIX *Mat,const D3DXVECTOR3 *ScalPos);
	virtual bool UpdateParts(const D3DXMATRIX * Mat, const D3DXVECTOR3 * ScalPos, int *Phase) { return true; };

	//情報渡し
	PARTS GetParts(void) {
		return Parts;
	}
	//表示用行列渡し
	D3DXMATRIX GetDrawMatParts(void);

	//スピードセット
	void SetSpeed(const int *GetNowSpeed, const int *GetMaxSpeed);

protected:
	PARTS Parts;

	Judg judg;

	//表示１
	void Draw3DDrawMesh(void);
	//表示２
	void Draw3DDaedMesh(void);
	//スピード(カーの今のスピードと最大スピード)
	int NowSpeed,MaxSpeed;

	//車体の拡大行列いれ
	D3DXVECTOR3 ScalPosBody;

	//初期化
	void InitParts(void);
	//拡大変化
	void ScalParts(const D3DXVECTOR3 *ScalPos);
private:

};