#pragma once
#include<d3dx9.h>
#include"../../GameSource/TextureManager.h"
#include"../../GameSource/Judgment.h"
#include"../../GameSource/Struct.h"

extern Judg judg;
extern TextureManager textureManager;
extern LPDIRECT3DDEVICE9 lpD3DDevice;

#define	FVF_VERTEX (D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1)

class BulletBase {
public:
	virtual void Init();
	BulletBase();
	~BulletBase() {};
	virtual void Draw3D() {};
	virtual bool Update() { return true; };
	virtual bool UpdateMove(D3DXVECTOR3 bVec) { return true; }
	D3DXMATRIX GetBulMat(void) {
		return bul.Base.Mat;
	}
	//ˆÚ“®‚ÌVce“n‚µ
	virtual D3DXVECTOR3 GetMoveVec() {
		return MoveVec;
	}
	//ˆÚ“®‚ÌVce‚Ì’·‚³“n‚µ
	virtual float GetMoVecDis();
	//ŒÀ®
	virtual bool UpdateTime(void);
	//ƒŒƒCFlg“n‚µ
	virtual bool GetRayFlg(void);
	//ƒŒƒCFlgØ‚è‘Ö‚¦
	virtual void SetRayFlg(const bool *Flg);
protected:
	Pol bul;
	D3DXMATRIX *smokeMat;
	D3DXMATRIX IdenMat;
	int GNUM;
	bool MoBuFlg;
	//ˆÚ“®—Ê‚ÌVec
	D3DXVECTOR3 MoveVec;
	//ŠÔ§ŒÀ
	int NowCount;
	//’e‚ÌƒŒƒC”»’è‰Â”\Flg
	bool BulletRayFlg;
	float MoveSize;
};