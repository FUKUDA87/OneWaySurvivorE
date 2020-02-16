#pragma once
#include<d3dx9.h>
#include"SceneBase.h"
#include"../TitleParts/TitleTex.h"
#include"../TitleParts/StartTex.h"
#include"../TitleParts/TitelCamera.h"
#include"../Ground/Bill1.h"
#include"../Ground/BillBase.h"
#include"../Ground/Sky.h"
#include"../GameSource/Countdown.h"
#include"../Ground/Wall.h"
#include"../2DDraw/BulletHole.h"
#include"../Key/CMouse.h"
#include"../Key/Key.h"
#include"../2DDraw/Fade.h"
#include"../Player/PlayerBody.h"
#include"../Player/PlayerA.h"
#include"../GameSource/Count.h"
#include"../Sound/Sound_Manager_Base.h"

template<class T>
inline void SafeRelease(T& lpAdd)
{
	if (lpAdd != nullptr) {
		lpAdd->Release();
		lpAdd = nullptr;
	}
}
class TitleScene :public SceneBase
{

public:
	TitleScene();
	~TitleScene();
	void Render2D(void);
	void Render3D(void);
	bool Update(void);
	void SetCamera(void);
	bool NowGroNum(D3DXMATRIX Mat, unsigned int *Num, float *Dis);

	//チェンジシーン用
	void ChangeSceneFade(int ChangeSceneNo);
	bool SetScene(void);

private:
	//<地面
	std::vector<BillBase*>ground;
	Cou *cou;//bill
	std::vector<Cou*>GroCou;
	int GroType, GroKNum, *CurType, NowCur;
	float AngGro;//カーブ時の角度
	bool GroLenFlg;//長さの変更
	//外灯表示用カウントダウン
	C_Count *LightCount;

	LPDIRECT3DTEXTURE9 Tex;
	TitleTex *titleTex;
	StartTex *startTex;
	
	//プレイヤー
	C_PlayerBase *player;
	//プレイヤーの情報
	C_PlayerBody *PlaBodData;

	TitleCamera *camera;
	Sky *sky;
	//弾痕
	std::vector<C_BulletHole*>BulHol;

	//マウス
	C_Mouse *mouse;
	//キー
	Key key;
	//フェード
	Fade *fade;
	//チェンジシーン用
	int SceneNo;
	bool SceneChangeFlg;

	//ゲームの終了
	bool Game_End(void);

	C_Sound_Manager_Base* M_C_Sound_Manager;
};
