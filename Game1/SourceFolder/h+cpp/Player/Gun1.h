#pragma once
#include<d3dx9.h>
#include"Stand1.h"
#include"../Gun/Bullet/BulletManager.h"
#include"../Gun/GunDraw/GunBase.h"

#ifndef Gun1_H
#define Gun1_H

class Gun1 :public Stand1,public BulletManager{
public:
	void Init();
	Gun1();
	~Gun1();
	virtual bool GUpdate(float AngX, float AngY);
	virtual bool GUpdate(const D3DXMATRIX *CamMat);
	virtual bool GUpdate(void);
	//弾を打つ
	virtual bool GUpdateB(void);
	//弾を打つ止める
	virtual bool GUpdateB(const bool *BirthFlg);
	//弾を撃つと音
	virtual bool GUpdateB(const bool *BirthFlg,const SoundCamera *sc);
	//弾を撃つと音とKey
	virtual bool GUpdateB(const bool *KeyFlg, const bool *BirthFlg, const SoundCamera *sc);
	//弾の移動
	virtual bool GUpdateBEnd(void);
	bool MoveUpdate(std::vector<BillBase*>ground);
	bool SuperUpdate(float AngX, float AngY) ;
	bool SetParts(float AngX, float AngY);
	bool SuperUpdate(const D3DXMATRIX *CamMat);
	bool SetParts(const D3DXMATRIX *CamMat);
	void GDraw();
	void SuperDraw();
	D3DXMATRIX GetGMat();

	//弾用メンバー関数---------------------------------------------
	//弾
	void SetBPos(D3DXVECTOR3 pos, bool b);
	//D3DXMATRIX GetBulMat(int i) { return bulletM->GetBulMat(i); };
	//void SetBulDel(unsigned int *i) { return bulletM->BulDelete(i); };
	//unsigned int GetBulSiz(void) { return bulletM->GetBulSize(); };
	////Bulletの移動長さ
	//float GetBulletMMoveDis(unsigned int i) { return bulletM->GetBulletMoveDis(i); }
	////弾のレイ判定許可Flg渡し
	//bool GetBulRayFlgG(const unsigned int *BNo) {
	//	return bulletM->GetBulRayFlgM(BNo);
	//}
	////弾のレイ判定許可Flg切り替え
	//void SetBulRayFlgG(const unsigned int *BNo,const bool *Flg) {
	//	bulletM->SetBulRayFlgM(BNo, Flg);
	//}

	//-------------------------------------------------------------

	//前進判定用関数-----------------------------------------------
	//移動の情報を渡す
	QuaForMove GetQuaForMove(void);
	//移動ベクトルの長さ入れ
	void SetQuaVecSize(float size) {
		player.Con.SpeedMulJudg = size;
	}
	//前進判定用の移動ベクトル渡し
	D3DXVECTOR3 GetForMoveVec(int i) {
		return ForMoveVec[i];
	}
	//前進判定用の移動ベクトル入れ
	void SetForMoveVec(D3DXVECTOR3 Vec,int i) {
		ForMoveVec[i] = Vec;
	}
	//前進判定用の移動後Mat渡し
	D3DXMATRIX GetForMoveEndMat(void) {
		return ForMoveEndMat;
	}
	//前進判定用の移動後Mat入れ
	void SetForMoveEndMat(D3DXMATRIX Mat) {
		ForMoveEndMat = Mat;
	}
protected:
	Object3D gun;
	GunBase *gunBase;
	//BulletManager *bulletM;
	bool B;
	D3DXVECTOR3 Pos;
	
	int Count;
	D3DXVECTOR3 qVec;
private:
	float x, y, z;
	D3DXVECTOR3 bVec, cVec;//バレット移動用
	D3DXMATRIX PlaMovMat;//playerの移動前のMat
	QuaForMove Q;//前進判定用クォータニオン
	D3DXMATRIX ForMoveEndMat;//前進完了時のMat
	D3DXVECTOR3 ForMoveVec[3];//移動前から移動後のVec
};

#endif // !Gun1_H
