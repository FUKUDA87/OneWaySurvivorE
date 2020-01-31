#pragma once
#include"../Draw3DBase/CarBulletManager.h"
#include"../Enemy/Vector.h"

class C_EnemyBase :public C_CarBulletManager {
public:
	C_EnemyBase();
	~C_EnemyBase();
	//初期化
	void InitEnemy(void);
	//アップデート
	bool UpdateCar(void);
	//表示
	void Draw3DAll(const D3DXVECTOR3 *CamPos);
	void Draw2DAll(void);
	//矢印作成に必要な情報の取得とアップデート
	void GetPos2DSet(const D3DXMATRIX *mProj, const D3DXMATRIX *mView, const D3DVIEWPORT9 *Viewport);

	//エネミーの存在削除渡し
	bool GetDeleFlg(void);

	//パーツの位置調整
	void SetParts(std::vector<BillBase*>ground);

	void UpdateBullet(void);

protected:
	//矢印
	Vector *Vect;

	D3DXVECTOR3 Pos2D;

	int m_EnemyNo;
private:
	
};