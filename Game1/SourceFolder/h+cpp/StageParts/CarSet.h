#pragma once
#include<d3dx9.h>
#include"../GameSource/Struct.h"
#include"../GameSource/Judgment.h"

class C_CarSet {
public:
	C_CarSet();
	~C_CarSet();
	void ChangeMode(const bool Flg);

	void DrawTxt(void);

	void Draw3D(void);

	bool GetModeFlg(void) {
		return ModeFlg;
	}
	//呼び出したら車メッシュ変更
	void ChangeCar(void);

	D3DXVECTOR3 GetPartsPos(void) {
		return PartsPos;
	}

	void SetPartsPos(const D3DXVECTOR3* Pos) {
		PartsPos = *Pos;
	}

	float GetUp(void) {
		return 0.01f;
	}

	void ChangePartsMeshFlg(const bool Flg);

	void GroundSize(const float *H_Y);

	LPD3DXMESH GetTire(void) {
		return Tire.lpMesh;
	}

protected:
	
private:
	bool ModeFlg;

	int PartsMeshFlg;

	XFILE Car,Tire, Vector;
	D3DXVECTOR3 PartsPos;

	Judg judg;

	int CarMeshNo,ChangeMeshNo;

	float GroundY;//車からタイヤの下までの距離
};