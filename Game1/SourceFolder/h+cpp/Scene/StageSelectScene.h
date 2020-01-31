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
#include"../2DDraw/Fade.h"
#include"../StageParts/CarSelect.h"
#include"../Player2/PlayerBody.h"
#include"../StageParts/OkButton.h"
#include"../StageParts/CarSet.h"


class StageSelectScene :public SceneBase {
public:
	StageSelectScene();
	~StageSelectScene();
	void Render2D(void);
	void Render3D(void);
	bool Update(void);
	void SetCamera(void);

	//チェンジシーン用
	void ChangeSceneFade(int ChangeSceneNo);
	void ChangeSceneFade(int ChangeSceneNo,int NextStageNo);
	bool SetScene(void);

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

	void StartFade(void);

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
	//フェード
	Fade *fade;
	//チェンジシーン用
	int SceneNo;
	bool SceneChangeFlg;
	int ChangeStageNo;

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
};