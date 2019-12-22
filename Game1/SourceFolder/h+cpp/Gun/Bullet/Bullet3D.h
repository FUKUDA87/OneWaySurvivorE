#pragma once
#include<d3dx9.h>
#include"../../GameSource/Struct.h"

class C_Bullet3D {
public:
	C_Bullet3D();
	C_Bullet3D(const D3DXMATRIX *GunMat);
	~C_Bullet3D();
	//初期化
	void Init();
	//アップデート
	bool Update(void);
	bool Update(const D3DXVECTOR3 *MoveVec);
	//表示
	void Draw3D(void);

	//行列渡し
	D3DXMATRIX GetMat(void) {
		return BulletMesh.Base.Scal*BulletMesh.Base.Mat;
	}
protected:
private:
	//弾のメッシュ
	Object3D BulletMesh;
	//時間で削除
	int NowCount, MaxCount;
	//最初だけMoveVecを足さないFlg
	bool IncFlg;
	//yUp
	float yUp;
};