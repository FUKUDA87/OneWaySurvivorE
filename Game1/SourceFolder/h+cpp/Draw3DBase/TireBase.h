#pragma once
#include"../GameSource/Struct.h"
#include"Draw3DManager/TireMeshManager.h"
#include"../GameSource/Judgment.h"

extern Judg judg;

class C_TireBase {
public:
	C_TireBase();
	//vector型
	C_TireBase(const BASE3D *TireBase);
	~C_TireBase();
	//初期化
	void InitTire(void);
	//アップデート
	virtual bool UpdateTire(void);
	virtual bool UpdateTire(const D3DXMATRIX *CarMat);
	//表示
	virtual void Draw3DTire(void);

	//表示用行列渡し
	virtual D3DXMATRIX GetDrawMatTire(void) {
		return judg.GetDrawMat(&Tire.Mat, &Tire.Scal, &Tire.ScaPos);
	}
	//メッシュの切り替え
	void SetMeshTire(int MeshNo);

	//回転Flg入れ
	void SetMoveTireFlg(const bool *Flg) {
		MoveTireFlg = *Flg;
	}

protected:
	BASE3D Tire;
private:
	XFILE TireMesh;

	C_TireMeshManager tireMeshManager;

	//回転の有無Flg
	bool MoveTireFlg;
};