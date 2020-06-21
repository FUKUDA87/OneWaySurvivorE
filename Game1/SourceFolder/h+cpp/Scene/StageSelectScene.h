#pragma once
#include"SceneBase.h"
#include<vector>
#include<d3dx9.h>

//表示
#include"../TitleParts/TitleSky.h"
#include"../StageParts/StageCar.h"
#include"../StageParts/StageCamera.h"
#include"../2DDraw/modoru.h"
#include"../StageParts/StageTex.h"
#include"../Key/CMouse.h"
#include"../Key/KeyTrue.h"
#include"../StageParts/CarSelect.h"
#include"../Player/PlayerBody.h"
#include"../StageParts/OkButton.h"
#include"../StageParts/CarSet.h"
#include"../StageParts/Stage_Room.h"
#include"../Sound/GameSoundManager.h"
#include"../GameSource/Option/Option.h"


class StageSelectScene :public SceneBase {
public:
	StageSelectScene();
	~StageSelectScene();
	void Render2D(void);
	void Render3D(void);
	bool Update(void);
	void SetCamera(void);

	//車選択の削除
	void DeleteCarSel(void);

	//ステージ選択の削除
	void DeleteStaSel(void);

	//選択-----------------------------------------------------------------
	//選択モード切替
	void ChangeMode();
	//ステージ選択モード
	bool StageSelectMode(void);
	void InitStaSel(void);
	//車切り替えモード
	bool CarSelectMode(void);
	void InitCarSel(void);

	//車のボディ変え
	void ChangeCar(int *No);

protected:
	//チェンジMode
	void ChangeMode_Car(void);

	//通常モードアップデート
	bool Update_Normal(void);
	//カスタムモードアップデート
	bool Update_Car(void);
	//表示３Dの通常モード
	void Draw3D_Normal(void);
	//表示２Dの通常モード
	void Draw2D_Normal(void);

	//タイトルシーンに強制移動
	bool Change_TitleScene(void);

private:

	C_Option *option;

	//地面に立つ様に調べる
	void Car_Ground_Vec(void);

	void Init_New(void);

	StageSky *sky;
	//プレイヤーの情報
	C_PlayerBody *PlayerBody;
	StageCar *car;

	StageCam *cam;
	Modoru *modoru;
	std::vector<StageTex*>stage;

	//マウス
	C_Mouse *mouse;
	//キー
	C_KeyTrue key;

	//終了処理
	bool EndFlg;


	//選択表示
	std::vector<C_CarSelect*>CarSel;

	//選択モードFlg
	bool StageModeFlg;
	bool CarModeFlg;

	//OKボタン
	C_OK *Ok;

	C_CarSet *M_CarSet;

	BODYDATA BodyData_Init;

	//車のスタンド
	C_Stage_Room_Stand *M_C_Garage_Stand;

	//ゲームシーンでデバッグモードにする
	bool GameScene_DebugFlg;
	//デバッグモードに切り替え
	void Set_GameScene_DebugFlg(void);

	//
	c_GameSoundManager* M_C_Sound_Manager;
};