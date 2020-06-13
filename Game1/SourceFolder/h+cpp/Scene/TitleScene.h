#pragma once
#include<d3dx9.h>
#include"SceneBase.h"
#include"../TitleParts/TitleTex.h"
#include"../TitleParts/StartTex.h"
#include"../TitleParts/TitelCamera.h"
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
#include"../Ground/Ground_Object.h"

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
	void Render2D(void);   // 2D描画
	void Render3D(void);   // 3D描画
	bool Update(void);     // 更新処理
	void SetCamera(void);  // カメラ

	//チェンジシーン用
	void ChangeSceneFade(int ChangeSceneNo);
	bool SetScene(void);

private:

	Judg judg;  // 判定用の関数のクラス

	//<地面
	std::vector<C_Ground_Object*>ground;
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

	//ステージ選択シーンへの移動
	void Next_StageScene_Switch(void);
};
