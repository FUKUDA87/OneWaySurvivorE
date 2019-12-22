#pragma once
#include<d3dx9.h>
#include"../GameSource/option.h"
#include"../GameSource/Enum.h"
#include"../GameSource/Struct.h"
#include"../3DDraw/Ball.h"
#include"../2DDraw/HpD.h"
#include"../3DDraw/Spear.h"
#include"../Ground/BillBase.h"
#include<vector>
#include"../Enemy/Vector.h"

class C_Player{
public:
	void Init();
	C_Player();
	~C_Player();
	 virtual bool Update();
	 virtual bool SuperUpdate(float AngX,float AngY,std::vector<BillBase*>ground);
	 void Draw();
	 void Draw2();
	 virtual void SuperDraw();
	D3DXMATRIX GetMat();
	void SetMat(D3DXMATRIX mat);
	float GetRad();

	//-------------------------------
	//ゲット
	//-------------------------------
	D3DXVECTOR3 GetSpeed(void) {
		return player.Con.Speed;
	}
	void SetSpeed(D3DXVECTOR3 spe) {
		player.Con.Speed = spe;
	}
	float GetRadF(void) {
		return radF;
	}
	void SetRadF(float rad) {
		radF=rad;
	}
	void SetGroNum(unsigned int i) { player.Con.GroNum=i; };
	unsigned int GetGroNum(void) { return player.Con.GroNum; };
	//HP
	//int GetHP(void) { return player.Sta.NowHp; };
	void SetHP(int Damage);
	void SetHP(int *Hp);


	//カーブのリバース
	void CurReverse(bool b);

	//playerMesh
	LPD3DXMESH GetMesh() {
		return player.Mesh.lpMesh;
	}

	//player情報
	CHARAData GetData(void);

	bool GetFlgP(void) {
		return player.Base.Flg;
	}
	float GetBodRad(void) {
		return player.Base.BodRad;
	}
	//当たり判定用のMat渡し
	D3DXMATRIX GetJudgMat() {
		return player.Con.JudgMat;
	}
	//playerのTransMat渡し
	D3DXMATRIX GetTransMatPla(void) {
		return player.Base.Trans;
	}
	//playerのTransMat入れ
	void SetTransMatPla(D3DXMATRIX TransMat) {
		player.Base.Trans = TransMat;
	}
	//コリジョンモデル渡し
	LPD3DXMESH GetColMod(void) {
		return player.Con.ColModMesh.lpMesh;
	}
	//移動の情報渡し
	CONSTITUTION GetCon(void) {
		return player.Con;
	}
	//カーブのAngいれ
	void SetRodAngY(float Inc, bool KeyFlg);
	//CurEnd
	void SetCurRotMat(void);
	/*virtual QuaForMove GetQuaForMove(void) {
		QuaForMove q;
		q.AnimeFrame = Move.AnimeFrame;
		q.BodyHeight = 5.0f;
		return q;
	}*/
protected:
	QuaAnim cur;//車線変更用
	QuaAnim Move;//前進用
	QuaMove FMove;//前進用２
	CHARA3D player;
	Vector* vector;
	Ball *ball;
	HpD *hp;
	Spear *spear;
private:
	float radF;
	//ダメージフラグ
	bool DFlg;

	FILE* fp;
	//カーブ角度
	float CurAng;
	D3DXMATRIX CurRotMatY;
};
