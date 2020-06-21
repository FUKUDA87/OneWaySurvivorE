#include"TitleScene.h"
#include"SceneManager.h"
#include"GameScene.h"
#include"../MaterialManager/TextureManager.h"
#include"../MaterialManager/XfileManager.h"
#include"StageSelectScene.h"
#include"../GameSource/GameSystem.h"
#include"../Fade/Fade.h"

extern TextureManager textureManager;
extern XFileManager xfileManager;
extern LPD3DXSPRITE lpSprite;	// スプライト
extern SceneManager sceneManager;
extern LPDIRECT3DDEVICE9		lpD3DDevice;	// Direct3DDeviceインターフェイス
extern C_Fade fade;

#define	SCRW		1280	// ウィンドウ幅（Width
#define	SCRH		720		// ウィンドウ高さ（Height
#define StageSelectNo 1

void LoadTexture(LPDIRECT3DTEXTURE9 *lpTex, const char fname[], int W, int H, D3DCOLOR Color);


TitleScene::TitleScene()
{
	// オプションのインスタンス化
	option = new C_Option();
	option->Read();

	// フェードインの開始
	fade.StartFadein();

	//プレイヤーの初期化の前に初期化
	PlaBodData = new C_PlayerBody();

	player = new C_PlayerA(&PlaBodData->GetPData());
	//地面初期化--------------------------------------------------------
	//外灯の間隔初期化
	int CountInit = 4;
	LightCount = new C_Count(&CountInit);

	cou = new Cou(0, 5, 1, true, false);
	int i = 0, z;
	ground.push_back(new C_Ground_Object(&i));
	z = (int)ground[0]->GetPosZ() * 2;
	i = (int)player->GetRadF() / z;
	delete ground[0];
	ground.erase(ground.begin() + 0);
	for (int n = i * (-1); n < i; n++) {
		if (cou->CouJudge() == false) {
			cou->SetNum(0);
		}
		if (cou->GetNum() == 1) {
			ground.push_back(new C_Ground_Object(&n)); //ground.push_back(new BillBase(n));
		}
		else {
			ground.push_back(new C_Ground_Object(&n));
		}
		//外灯の初期化
		if (LightCount->Update() == true)ground[ground.size() - 1]->Init_Light();

		cou->CouUpd();
	}
	for (unsigned int i = 0; i < ground.size(); i++) {

		float L_Radius = player->GetRadF();

		if (judg.BallJudg(&judg.SetPosM(&player->GetMatCar()), &judg.SetPosM(&ground[i]->GetMat()), &L_Radius) != false) continue;

		delete ground[i];
		ground.erase(ground.begin() + i);
		i--;

	}
	int c = 2;
	/*for (int i = (ground.size() - 1); i >= 0; i--) {
		if (ground[i]->GetObjFlg() == true) {
			if (c == 4) c = 1;
			break;
		}
		else {
			c++;
		}
	}*/
	cou->SetNum(c);
	//カーブの形成初期化
	GroKNum = 4;
	GroType = 1;
	CurType = new int[GroKNum];
	CurType[0] = CurType[3] = 1;
	CurType[1] = CurType[2] = 2;
	NowCur = 0;
	//playerの位置調整
	unsigned int num;
	float Dis;
	if (ground.size() > 100) {
		i = (int)(ground.size() - ground.size() / 10);
		D3DXMATRIX gMat, Trans;
		gMat = ground[i]->GetWay().StartMat;
		D3DXMatrixTranslation(&Trans, 0.0f, 0.1f, 0.0f);

		D3DXMATRIX TmpMat= Trans * gMat;
		player->SetMatCar(&TmpMat);
		player->SetRadF(player->GetRadF() / 2.0f);
	}

	// 地面と当たり判定
	C_GameSystem gameSystem;
	if (gameSystem.JudgNowGround(&num, &Dis, player->GetMatCar(), ground) == true) {
		player->SetGroNum(&num);//地面の取得
	}

	//---------------------------------------------------------------------
	//マウスの初期化
	mouse = new C_Mouse();
	mouse->ChaDrawFlg(true);

	titleTex = new TitleTex();
	startTex = new StartTex();

	camera = new TitleCamera();
	sky = new Sky();

	key.Init();

	//サウンドの初期化
	if (M_C_Sound_Manager == nullptr)M_C_Sound_Manager = new c_GameSoundManager();

	//弾痕の初期化
	if (false) {
		float AngZ = -90.0f;
		BulHol.push_back(new C_BulletHole(&D3DXVECTOR3(250.0f, 720.0f / 4.0f*3.0f, 0.0f), &AngZ, &D3DXVECTOR3(2.1f, 2.1f, 1.0f), 1));
		BulHol.push_back(new C_BulletHole(&D3DXVECTOR3(250.0f, 720.0f / 4.0f*3.0f, 0.0f), &AngZ, &D3DXVECTOR3(2.1f, 2.1f, 1.0f), 2));
		AngZ = (70.0f)*-1.0f;
		BulHol.push_back(new C_BulletHole(&D3DXVECTOR3(1050.0f, 500.0f, 0.0f), &AngZ, &D3DXVECTOR3(2.1f, 2.1f, 1.0f), 1));
		AngZ += 50.0f;
		BulHol.push_back(new C_BulletHole(&D3DXVECTOR3(990.0f, 380.0f, 0.0f), &AngZ, &D3DXVECTOR3(2.1f, 2.1f, 1.0f), 1));
		AngZ -= 50.0f;
		BulHol.push_back(new C_BulletHole(&D3DXVECTOR3(1050.0f, 500.0f, 0.0f), &AngZ, &D3DXVECTOR3(2.1f, 2.1f, 1.0f), 2));
		AngZ += 50.0f;
		BulHol.push_back(new C_BulletHole(&D3DXVECTOR3(990.0f, 380.0f, 0.0f), &AngZ, &D3DXVECTOR3(2.1f, 2.1f, 1.0f), 2));
		AngZ = -0.0f;
		//BulHol.push_back(new C_BulletHole(&D3DXVECTOR3(455.0f, 85.0f, 0.0f), &AngZ, &D3DXVECTOR3(1.2f, 1.2f, 1.0f)));
		BulHol.push_back(new C_BulletHole(&D3DXVECTOR3(300.0f, 200.0f, 0.0f), &AngZ, &D3DXVECTOR3(2.1f, 2.1f, 1.0f), 1));
		BulHol.push_back(new C_BulletHole(&D3DXVECTOR3(300.0f, 200.0f, 0.0f), &AngZ, &D3DXVECTOR3(2.1f, 2.1f, 1.0f), 2));

		BulHol.push_back(new C_BulletHole(&D3DXVECTOR3(1100.0f, 100.0f, 0.0f), &AngZ, &D3DXVECTOR3(2.1f, 2.1f, 1.0f), 1));
		BulHol.push_back(new C_BulletHole(&D3DXVECTOR3(1100.0f, 100.0f, 0.0f), &AngZ, &D3DXVECTOR3(2.1f, 2.1f, 1.0f), 2));
	}

	int No = 2;
	C_Struct_Init C_S_Init;
	M_C_Sound_Manager->New_Sound_Data(&C_S_Init.Get_S_SOUND_DATA(
		&Co_Sound_Type_2D, &Co_Sound_Category_BGM, &No, &Co_Sound_Change));

}
TitleScene::~TitleScene()
{

	delete player;
	delete titleTex;
	delete startTex;
	delete camera;
	delete sky;
	//地面の削除
	for (unsigned int i = 0; i < ground.size(); i++) {
		delete ground[i];
		ground.erase(ground.begin() + i); i--;
	}
	delete[] CurType;
	if (GroCou.size() > 0) {
		for (unsigned int g = 0; g < GroCou.size(); g++) {
			delete GroCou[g];
			GroCou.erase(GroCou.begin() + g);
			g--;
		}
	}
	delete cou;
	//弾痕削除
	if (BulHol.size() > 0) {
		for (unsigned int b = 0; b < BulHol.size(); b++) {
			delete BulHol[b];
			BulHol.erase(BulHol.begin() + b);
			b--;
		}
	}
	//マウスの削除
	delete mouse;

	delete PlaBodData;

	//ライトのカウントダウンの削除
	if (LightCount != nullptr) {
		delete LightCount;
	}

	if (M_C_Sound_Manager != nullptr) {
		M_C_Sound_Manager->Stop_Sound_All();
		delete M_C_Sound_Manager;
	}

	// オプションの削除
	option->Write();
	if (option != nullptr) delete option;

}
bool TitleScene::Update(void)
{

	if (M_C_Sound_Manager != nullptr) {

		S_OptionData l_OptionData = option->GetOptionData();

		M_C_Sound_Manager->Set_Sound(&l_OptionData.BGMVolume);

		M_C_Sound_Manager->Update_Sound(&l_OptionData.BGMVolume);
	}

	Game_End();

	//bgmのアップデート
	bool bFlg = true;
	SoundCamera scB;
	scB.CamPos = camera->GetPos();
	scB.CamLook = camera->GetLook();
	scB.CamHead = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	mouse->Update();

	//フェードのアップデート
	if (fade.Update() == true) {
		//キーの無力化

	}
	else {
		// フェードアウトが完了した時
		if (fade.GetMoveEndFlg() == true) {
			sceneManager.changeScene(new StageSelectScene());
			return false;
		}
	}

	//ステージ選択シーンへ移動
	Next_StageScene_Switch();

	//================================================================================
	//地面
	//================================================================================
	if (ground.size() > 0) {
		for (unsigned int i = 0; i < ground.size(); i++) {
			ground[i]->SuperUpdate();
			//無限の道の削除と作成
			if (player->GetCon().GroNum > i) {

				float L_Radius = player->GetRadF();

				if (judg.BallJudg(&judg.SetPosM(&player->GetMatCar()), &judg.SetPosM(&ground[i]->GetMat()), &L_Radius) == false) {
					if (ground[i]->GetFlg() == true) {
						delete ground[i];
						ground.erase(ground.begin() + i);
						i--;

						bool Flg = true;
						if (Flg == true) {
							D3DXMATRIX Mat[2];
							Mat[0] = ground[ground.size() - 1]->GetMat0();
							Mat[1] = ground[ground.size() - 1]->GetMat1();
							int StopNum;
							if (GroCou.size() == 0) {//地面の形成
								if (GroType == 0) {
									GroType = CurType[NowCur];
									NowCur++;
									if (NowCur == GroKNum)NowCur = 0;
								}
								else {
									GroType = 0;
									cou->SetNum(2);
								}
								if (GroType == 0)StopNum = rand() % 20 + 40;
								if (GroType == 1)StopNum = 5;
								if (GroType == 2)StopNum = 5;
								if (GroType != 0) {
									AngGro = 90.0f / 5.0f;
									GroLenFlg = false;
								}
								else {
									GroLenFlg = true;
								}
								GroCou.push_back(new Cou(0, StopNum, 1, true, false));
							}
							if (cou->CouJudge() == false) {
								cou->SetNum(0);
							}
							S_GROUND_INIT_DATA Init_Data;
							Init_Data.gType = GroType;
							Init_Data.Ang = AngGro;
							Init_Data.Length = 5.0f;
							Init_Data.LengthAuto = GroLenFlg;
							if ((cou->GetNum() == 1) && (GroType == 0)) {
								ground.push_back(new C_Ground_Object(&Mat[1], &Mat[0],&Init_Data)); 
							}
							else {
								ground.push_back(new C_Ground_Object(&Mat[1], &Mat[0], &Init_Data));
							}

							//外灯の初期化
							if (LightCount->Update() == true)ground[ground.size() - 1]->Init_Light();

							if (GroCou.size() > 0) {
								for (unsigned int g = 0; g < GroCou.size(); g++) {
									GroCou[g]->CouUpd();
									if (GroCou[g]->CouJudge() == false) {
										for (unsigned int g = 0; g < GroCou.size(); g++) {
											delete GroCou[g];
											GroCou.erase(GroCou.begin() + g);
											g--;
										}
										if (GroCou.size() <= 0) {
											break;
										}
									}
								}
							}
							if (GroType == 0) {
								cou->CouUpd();
							}
						}
					}
				}
				else {
					//新品の道を判定できるようにする
					if (ground[i]->GetFlg() == false) {
						ground[i]->SetFlg(true);
					}
				}
			}
		}
	}
	// プレイヤーと地面判定
	float Dis;
	unsigned int num;
	C_GameSystem gameSystem;
	if (gameSystem.JudgNowGround(&num, &Dis, player->GetMatCar(), ground) == true) {
		player->SetGroNum(&num);//地面の取得
	}
	player->UpdateCarFM(ground);
	D3DXMATRIX Mat = player->GetMatCar();
	judg.SetMatP(&Mat, &D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	player->UpdateAll(&Mat);
	camera->Update(player->GetMatCar());
	sky->Update(&player->GetMatCar());

	
	return true;
}

void TitleScene::Render2D(void)
{
	//////////////////////////////////////////////////
	///	スプライトの描画処理
	//////////////////////////////////////////////////
	// 描画開始
	lpSprite->Begin(D3DXSPRITE_ALPHABLEND);

	//titleTexの表示
	titleTex->Draw();

	startTex->DrawSu();

	fade.Draw();

	//弾痕表示
	if (BulHol.size() > 0) {
		for (unsigned int b = 0; b < BulHol.size(); b++) {
			BulHol[b]->Draw2DBH();
		}
	}
	

	mouse->Draw2D();
	// 描画終了
	lpSprite->End();
}

void TitleScene::Render3D(void)
{
	for (unsigned int i = 0; i < ground.size(); i++) {
		ground[i]->SuperDraw();
	}
	player->Draw3DAll(&camera->GetPos());
	sky->Draw();
}

void TitleScene::SetCamera(void)
{
	D3DXMATRIX mView, mProj;
	D3DXMatrixLookAtLH(&mView,
		&camera->GetPos(),//カメラの位置
		&camera->GetLook(),// カメラの視点
		&D3DXVECTOR3(0.0f, 1.0f, 0.0f)	// カメラの頭の方向
	);

	// 投影行列の設定
	D3DXMatrixPerspectiveFovLH(&mProj, D3DXToRadian(60), (float)SCRW / (float)SCRH, 0.1f, 1200.0f);

	//行列設定
	lpD3DDevice->SetTransform(D3DTS_VIEW, &mView);
	lpD3DDevice->SetTransform(D3DTS_PROJECTION, &mProj);

}

bool TitleScene::Game_End(void)
{
	if (key.EscapeKey_F() == true) {
		PostQuitMessage(0);
		return false;
	}
	return true;
}

void TitleScene::Next_StageScene_Switch(void)
{
	//スイッチの更新と動作の確認
	if (startTex->UpdateSu() != false) return;

	//マウスカーソルを手にする処理
	mouse->SetTouchFlg();

	//スイッチが動作中かの確認
	if (startTex->GetMoveFlg() != false)return;

	//シーン切り替え状態であるかの確認
	if (fade.GetMoveFlg() != false) return;

	//クリックしたかの確認
	if (key.LClickF() != true) return;

	//スイッチの動作開始
	startTex->SetMoveFlg(true);

	//フェードアウトの開始
	fade.StartFadeout();

	//BGMの削除
	M_C_Sound_Manager->New_Sound_Data(&Co_Sound_Type_2D, &Co_Sound_Category_BGM, 1, &Co_Sound_Delete);

	//クリック音
	M_C_Sound_Manager->New_Sound_Data(&Co_Sound_Type_2D, &Co_Sound_Category_Click, 1, &Co_Sound_New);
}
