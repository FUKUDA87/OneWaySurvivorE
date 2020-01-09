#include"GameScene.h"
#include"TitleScene.h"
#include"StageSelectScene.h"
#include"SceneManager.h"
#include"../GameSource/option.h"
#include"../GameSource/Enum.h"
#include"../GameSource/Judgment.h"
#include"../GameSource/TextureManager.h"
#include"../GameSource/XfileManager.h"
#include"../GameSource/InvBi.h"
#include"../GameSource/Motion.h"
#include"../Sound/Bgm.h"
#include"../Draw3DBase/Draw3DManager/CarSmogManager.h"

extern C_Bgm *bgm;
extern int CountManager;
extern Motion motion;
extern Inv inv;
extern TextureManager textureManager;
extern XfileManager xfileManager;
extern SceneManager sceneManager;
extern Judg judg;
extern Option option;
extern LPDIRECT3DDEVICE9		lpD3DDevice;	// Direct3DDeviceインターフェイス
extern LPD3DXSPRITE lpSprite;	// スプライト
extern LPD3DXFONT lpFont;		// フォント
extern D3DXVECTOR3 CamPosG;
extern float AngD;
#define	SCRW		1280	// ウィンドウ幅（Width
#define	SCRH		720		// ウィンドウ高さ（Height
#define RadJudgF 100
#define StageSelectNo 2
#define GameNo 3
#define TitleNo 1


FILE* fp;
FILE *fp_b;

void GameScene::StageSave(const bool * Flg)
{
	if (*Flg == false)return;
	//ステージセーブ
	NewWaveSave(StageNo);
	//敵のロード
	for (unsigned int i = 0; i < (unsigned int)MaxWaveNum; i++) {
		//ロードできない時
		NewEnemySave(StageNo, i);
	}
}

void GameScene::NewWaveSave(int StagNo)
{
	//wave
	int waveT;
	//txtロード
	sprintf_s(FSName, sizeof(FSName), "../GameFolder/Data/stage/stage%d.txt", StagNo);
	if (fopen_s(&fp, FSName, "r") == 0) {
		fscanf_s(fp, "%d", &waveT);
		fclose(fp);
	}
	else {
		waveT = 3;
	}
	//txtセーブ
	if (fopen_s(&fp, FSName, "w") == 0) {
		fprintf_s(fp, "%d", waveT);
		fclose(fp);
	}
	MaxWaveNum = waveT;
	//datセーブ
	sprintf_s(FSName, sizeof(FSName), "../GameFolder/Data/stage/stage%d.dat", StagNo);
	if (fopen_s(&fp_b, FSName, "wb") == 0) {
		fwrite(&MaxWaveNum, sizeof(int), 1, fp_b);
		fclose(fp_b);
	}

}

void GameScene::NewEnemySave(int StagNo, int WaveNo)
{
	EnemyPop e;
	//ロード
	sprintf_s(FSName, sizeof(FSName), "../GameFolder/Data/stage/stage%dwave%d.txt", StagNo, (int)WaveNo);
	//ロードtxt
	if (fopen_s(&fp, FSName, "r") == 0) {
		fscanf_s(fp, "%d\n", &e.MaxNum);
		for (unsigned int n = 0; n < (unsigned int)e.MaxNum; n++) {
			if (fscanf_s(fp, "%d ", &e.rePopTime[n]) == -1) {
				if (n != 0) {
					e.rePopTime[n] = 60 * 3;
				}
				else {
					e.rePopTime[n] = 60 * 0;
				}
			}
		}
		for (unsigned int n = 0; n < (unsigned int)e.MaxNum; n++) {
			if (n == 0) {
				if (fscanf_s(fp, "\n%d ", &e.EneNumber[n]) == -1) {
					e.EneNumber[n] = 1;
				}
			}
			else {
				if (fscanf_s(fp, "%d ", &e.EneNumber[n]) == -1) {
					e.EneNumber[n] = 1;
				}
			}
		}
		fclose(fp);
	}
	else {
		e.MaxNum = 2;
		if (e.MaxNum > 10)e.MaxNum = 10;
		for (unsigned int n = 0; n < (unsigned int)e.MaxNum; n++) {
			if (n != 0) {
				e.rePopTime[n] = 60 * 3;
			}
			else {
				e.rePopTime[n] = 60 * 0;
			}
		}
		for (unsigned int n = 0; n < (unsigned int)e.MaxNum; n++) {
			e.EneNumber[n] = 1;
		}
	}
	if (e.MaxNum > 10)e.MaxNum = 10;
	//セーブtxt
	if (fopen_s(&fp, FSName, "w") == 0) {
		fprintf_s(fp, "%d\n", e.MaxNum);
		for (unsigned int n = 0; n < (unsigned int)e.MaxNum; n++) {
			fprintf_s(fp, "%d ", e.rePopTime[n]);
		}
		for (unsigned int n = 0; n < (unsigned int)e.MaxNum; n++) {
			if (n == 0) {
				fprintf_s(fp, "\n%d ", e.EneNumber[n]);
			}
			else {
				fprintf_s(fp, "%d ", e.EneNumber[n]);
			}
		}
		fclose(fp);
	}
	//txtからロードした敵の情報をdatにロードする
	sprintf_s(FSName, sizeof(FSName), "../GameFolder/Data/stage/stage%dwave%d.dat", StagNo, (int)WaveNo);
	//セーブdat
	if (fopen_s(&fp_b, FSName, "wb") == 0) {
		fwrite(&e, sizeof(EnemyPop), 1, fp_b);
		fclose(fp_b);
	}
}

bool GameScene::road(void)
{
	//ウェーブのロード
	sprintf_s(FRName, sizeof(FRName), "../GameFolder/Data/stage/stage%d.dat", StageNo);
	//ロード
	if (fopen_s(&fp_b, FRName, "rb") == 0) {
		fread(&MaxWaveNum, sizeof(int), 1, fp_b);
		fclose(fp_b);
	}
	else {
		//ロードできない時
		NewWaveSave(StageNo);
	}

	//敵のロード
	for (unsigned int i = 0; i < (unsigned int)MaxWaveNum; i++) {
		sprintf_s(FRName, sizeof(FRName), "../GameFolder/Data/stage/stage%dwave%d.dat", StageNo,(int)i );
		bool Flg = false;
		//ロード
		do {
			if (fopen_s(&fp_b, FRName, "rb") == 0) {
				EnemyPop e;
				fread(&e, sizeof(EnemyPop), 1, fp_b);
				ePop.push_back(new EnemyPop);
				*ePop[i] = e;
				fclose(fp_b);
				Flg = true;
			}
			else {
				//ロードできない時
				NewEnemySave(StageNo, i);
			}
		} while (Flg == false);
	}
	return true;
}

GameScene::GameScene(const int stageNum){
	debugT = new DebugT();

	//マウスの初期化
	mouse = new C_Mouse();
	mouse->Init();
	mouse->ChaDrawFlg(false);

	//プレイヤーの初期化前に初期化
	PlayerBody = new C_PlayerBody();

	player = new C_PlayerA(&PlayerBody->GetPData());

	//地面初期化--------------------------------------------------------
	//外灯の間隔初期化
	int CountInit = 4;
	LightCount = new C_Count(&CountInit);

	cou = new Cou(0, 5, 1, true, false);
	int i = 0, z;
	ground.push_back(new BillBase(i));
	z = (int)ground[0]->GetPosZ() * 2;
	i = (int)player->GetRadF() / z;
	delete ground[0];
	ground.erase(ground.begin() + 0);
	for (int n = i * (-1); n < i; n++) {
		if (cou->CouJudge() == false) {
			cou->SetNum(0);
		}
		if (cou->GetNum() == 1) {
			ground.push_back(new BillBase(n)); //ground.push_back(new BillBase(n));
		}
		else {
			ground.push_back(new Bill(n));
		}
		//外灯の初期化
		if (LightCount->Update() == true) {
			int wNum = 2;
			ground[ground.size() - 1]->InitLight(&wNum);
		}
		cou->CouUpd();
	}
	for (unsigned int i = 0; i < ground.size(); i++) {
		if (judg.ball(player->GetMatCar(), ground[i]->GetMat(), player->GetRadF()) == false) {
			delete ground[i];
			ground.erase(ground.begin() + i);
			i--;
		}
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
		i = (int)((float)ground.size() *0.9f);
		D3DXMATRIX gMat, Trans;
		gMat = ground[i]->GetWay().StartMat;
		D3DXMatrixTranslation(&Trans, 0.0f, 0.1f, 0.0f);
		Trans = Trans * gMat;
		player->SetMatCar(&Trans);
		player->SetRadF(player->GetRadF() / 2.0f);
	}
	if (NowGroNum(player->GetMatCar(), &num, &Dis) == true) {
		player->SetGroNum(num);//地面の取得
		eneFlg = true;
	}

	//---------------------------------------------------------------------

	//スコアの初期化
	score = new C_Score();
	sky = new Sky();
	camera = new Camera(player->GetMatCar());
	aiming = new Aiming();
	debug = new Debug();
	eneFlg = false;//敵の出現OFF
	GaOv = new GameOver();

	//シーンの切り替え初期化
	SceneChangeFlg = false;
	//フェードの初期化
	fade = new Fade();
	fade->ChaFlg(false);

	EndFlg = false;
	key.Init();
	GroType = 0;

	war = new Warning();

	pause = new Pause();

	//BulletBirthFlgを最初は出ないようにする
	BulletBirthFlg = false;

	//ロード
	StageNo = stageNum;
	if (road() == true) {
		NowWaveNum = 0;
		MaxEnemyNum = ePop[NowWaveNum]->MaxNum;
	}
	else {
		MaxEnemyNum = 1;
	}
	NowEnemyNum = 0;
	NextEnemyNo = 0;

	CountNum = MaxCount = 1;
	spear = new Spear();
	D3DXMatrixTranslation(&SpeMat, 0.0f, 0.0f, 0.0f);


	//bgm初期化
	bgm->ChangeBgm(2);

	Size = 1.0f;
}
GameScene::~GameScene() {
	//ステージ情報セーブの確認
	bool SSFlg = pause->GetStaSavFlg();

	delete debugT;
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
	//敵の削除
	for (unsigned int i = 0; i < enemy.size(); i++) {
		delete enemy[i];
		enemy.erase(enemy.begin() + i); i--;
	}
	for (unsigned int i = 0; i < explo.size(); i++) {
		delete explo[i];
		explo.erase(explo.begin() + i); i--;
	}
	delete player;
	delete sky;
	delete camera;
	delete aiming;
	delete debug;
	delete GaOv;
	delete war;
	delete pause;
	delete spear;
	//スコアの削除
	delete score;
	
	//スモッグの削除
	if (Smog.size() > 0) {
		for (unsigned int s = 0; s < Smog.size(); s++) {
			delete Smog[s];
			Smog.erase(Smog.begin() + s);
			s--;
		}
	}

	//火花の削除
	if (SparkV.size() > 0) {
		for (unsigned int s = 0; s < SparkV.size(); s++) {
			delete SparkV[s];
			SparkV.erase(SparkV.begin() + s);
			s--;
		}
	}

	//敵の情報を削除
	for (unsigned int i = 0; i < ePop.size(); i++) {
		delete ePop[i];
		ePop.erase(ePop.begin() + i);
		i--;
	}

	//マウスの削除
	delete mouse;

	//フェードの削除
	delete fade;

	//弾痕３Dの削除
	if (BHole3D.size() > 0) {
		for (unsigned int b = 0; b < BHole3D.size(); b++) {
			delete BHole3D[b];
			BHole3D.erase(BHole3D.begin() + b);
			b--;
		}
	}

	//プレイヤーの情報削除
	delete PlayerBody;

	//ライトのカウントダウンの削除
	if (LightCount != nullptr) {
		delete LightCount;
	}

	//メニューの削除
	DeleteMenu();

	//セーブ
	StageSave(&SSFlg);
}
void GameScene::Render3D(void) {
	/*if (player->GetBulSiz() > 0) {
		spear->Draw3DV(player->GetBulMat(0));
	}*/
	sky->Draw();
	for (unsigned int i = 0; i < ground.size(); i++) {
		ground[i]->SuperDraw();
	}
	for (unsigned int i = 0; i < explo.size(); i++) {
		explo[i]->ExplDraw();
	}
	if (enemy.size() > 0) {
		for (unsigned int i = 0; i < enemy.size(); i++) {
			enemy[i]->Draw3DAll(&camera->GetPos());
			enemy[i]->Draw3D_Laser(&camera->GetPos());
		}
	}

	player->Draw3DAll();

	//弾痕の表示
	if (BHole3D.size() > 0) {
		for (unsigned int b = 0; b < BHole3D.size(); b++) {
			BHole3D[b]->Draw3DHol3D();
		}
	}

	//火花の表示
	if (SparkV.size() > 0) {
		for (unsigned int s = 0; s < SparkV.size(); s++) {
			SparkV[s]->Draw3DSuper();
		}
	}

	
	
	//スモッグの表示
	if (Smog.size() > 0) {
		for (unsigned int s = 0; s < Smog.size(); s++) {
			Smog[s]->Draw3D(camera->GetPos());
		}
	}
}
void GameScene::Render2D(void) {
	//////////////////////////////////////////////////
	///	スプライトの描画処理
	//////////////////////////////////////////////////
	// 描画開始
	lpSprite->Begin(D3DXSPRITE_ALPHABLEND);
	if (enemy.size() > 0) {
		for (unsigned int i = 0; i < enemy.size(); i++) {
			enemy[i]->Draw2DAll();
		}
	}
	aiming->Draw();
	player->Draw2DAll();
	//スコアの表示
	score->Draw2D();
	//クリアとオーバーの表示
	GaOv->Draw2D();
	//ボス出現表示
	war->Draw2D();

	//ポーズの表示
	pause->Draw2DPau();

	//メニューの表示
	if (Menu.size() > 0) {
		for (auto && m : Menu) {
			m->Draw2DAll();
		}
	}

	//フェードインアウトの表示
	fade->Draw();
	mouse->Draw2D();
	// 描画終了
	lpSprite->End();
	/*debug->Draw();
	debugT->Draw2DT();
	debugT->Draw2DTd();*/
	//debugT->Draw2DF((float)Debug_No, 0, 0);
	//debugT->Draw2DF(Size, 0, 50);*/
	//debugT->Draw2DF(enemy[0]->GetQuaForMove().AnimeFrame, 0, 50);
}
bool GameScene::Update(void) {

	//bgmのアップデート
	bool bFlg = true;
	SoundCamera scB;
	scB.CamPos = camera->GetPos();
	scB.CamLook = camera->GetLook();
	scB.CamHead = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	bgm->Update(&bFlg/*,&scB*/);

	if (GetAsyncKeyState('1') & 0x8000) {
		MaxCount += 1;
		if (MaxCount > 60)MaxCount = 60;
	}
	if (GetAsyncKeyState('2') & 0x8000) {
		MaxCount -= 1;
		if (MaxCount <1)MaxCount = 1;
	}

	mouse->Update();

	//フェードのアップデート
	if (fade->Update() == true) {
		//キーの無力化

	}
	else {
		if (fade->GetMoveEndFlg() == true) {
			if (SceneChangeFlg == true)return SetScene();
		}
	}

	if (pause->GetDFlg() == false) {//ポーズ
		/*if (fade->GetFlg() == true) {
			sceneManager.changeScene(new StageSelectScene());
			return false;
		}
		if (fade->Update() == true) {
			return true;
		}
		else {
			GDebug();
		}*/

		//終わった時
		if (EndFlg == true) {
			mouse->ChaDrawFlg(true);
		}
		else {
			//ポーズ
			if (key.RETURNKeyF() == true) {
				if (pause->GetDFlg() == false) {
					pause->SetDFlg(true);
					mouse->ChaDrawFlg(true);
					bgm->StopSound();
					//ロードの許可
					if ((GetAsyncKeyState('8') & 0x8000) && (GetAsyncKeyState('9') & 0x8000) && (GetAsyncKeyState('0') & 0x8000)) {
						pause->SetStaSavFlg(true);
					}
					SetMenu(true, false, false);
					return true;
				}
			}
		}
		//スロー再生
		if (CountNum >= MaxCount) {
			CountNum = 1;
			//================================================================================
	        //地面
	        //================================================================================
			if (ground.size() > 0) {
				for (unsigned int i = 0; i < ground.size(); i++) {
					ground[i]->SuperUpdate();
					//無限の道の削除と作成
					GroundCreate(&i);
				}
			}

			//========================================
			//プレイヤー
			//========================================
			//カメラ-------------------------------------
			if (EndFlg == false) {
				if (fade->GetMoveFlg() == false) {
					camera->UpdateM(true, mouse);
				}
				else {
					mouse->Init();
				}
			}
			//カメラ上限判定
			camera->RotXJudg(&player->GetMatCar());

			//プレイヤーと地面判定
			float Dis;
			unsigned int num;
			if (NowGroNum(player->GetMatCar(), &num, &Dis) == true) {
				player->SetGroNum(num);//地面の取得
				eneFlg = true;//敵の出現開始
			}
			//敵
			UpdateEnemyAI();

			//横判定
			//===========================================
			//車線変更
			//===========================================
			//左の車線に変更
			//カーブしたかどうかのFlg
			bool LRKeyFlg = false;
			if ((key.AKey() == true)) {
				D3DXMATRIX Trans;
				D3DXMatrixTranslation(&Trans, -1.0f*0.08f, 0.0f, 0.0f);
				Trans = Trans * player->GetTransMatCar();
				player->SetTransMatCar(&Trans);
				Trans = player->GetTransMatCar()*player->GetCon().JudgMat;
				player->SetMatCar(&Trans);
				//横判定
				WallJudg(true, true, false, 0);
				//カーブ
				player->SetRodAngY(-0.3f, true);
				LRKeyFlg = true;


			}
			//右の車線に変更
			if (key.DKey() == true) {
				D3DXMATRIX Trans;
				D3DXMatrixTranslation(&Trans, 1.0f*0.08f, 0.0f, 0.0f);
				Trans = Trans * player->GetTransMatCar();
				player->SetTransMatCar(&Trans);
				Trans = player->GetTransMatCar()*player->GetCon().JudgMat;
				player->SetMatCar(&Trans);
				//横判定
				WallJudg(false, true, false, 0);
				player->SetRodAngY(0.3f, true);
				LRKeyFlg = true;
			}
			if (LRKeyFlg == false)player->SetRodAngY(0.3f, false);

			//前進判定=================================================================
			if (1) {
				//移動後の作成--------------------------------------------------------------

				//移動後の変数
				D3DXMATRIX EndMat;
				D3DXVECTOR3 EndPos;

				//player
				//移動後の行列作成
				EndMat = ForMoveEnd(player->GetCon(), player->GetQuaForMove(), player->GetTransMatCar());
				player->SetForMoveEndMat(EndMat);
				//移動ベクトル計算
				D3DXMATRIX TransMat1, TransMat2,Trans;//両側のレイ発射位置
				D3DXVECTOR3 ScalPosB = player->GetScalPosCar();
				TransMat1 = judg.GetTransMatScal(&D3DXVECTOR3(player->GetCon().PosSmall.x, 0.0f, player->GetCon().PosBig.z), &ScalPosB);
				TransMat2 = judg.GetTransMatScal(&D3DXVECTOR3(player->GetCon().PosBig.x, 0.0f, player->GetCon().PosBig.z), &ScalPosB);
				Trans = judg.GetTransMatScal(&D3DXVECTOR3(0.0f, 0.0f, player->GetCon().PosBig.z), &ScalPosB);
				player->SetForMoveVec(judg.MatMatVec(TransMat1*player->GetMatCar(), TransMat1*player->GetForMoveEndMat()), 0);
				player->SetForMoveVec(judg.MatMatVec(Trans*player->GetMatCar(), Trans*player->GetForMoveEndMat()),1);
				player->SetForMoveVec(judg.MatMatVec(TransMat2*player->GetMatCar(), TransMat2*player->GetForMoveEndMat()), 2);

				//enemy
				if (enemy.size() > 0) {//enemyの存在確認
					//enemyの数
					for (unsigned int e = 0; e < enemy.size(); e++) {
						if (enemy[e]->GetFlgCar() == true) {
							//移動後の行列作成
							EndMat = ForMoveEnd(enemy[e]->GetCon(), enemy[e]->GetQuaForMove(), enemy[e]->GetTransMatCar());
							/*EndPos = D3DXVECTOR3(EndMat._41, EndMat._42, EndMat._43);
							EndMat = enemy[e]->GetMatEn();
							judg.SetMatP(&EndMat, EndPos);*/
							enemy[e]->SetForMoveEndMat(EndMat);
							//移動ベクトル計算
							D3DXMATRIX TransMat1, TransMat2, Trans;//両側のレイ発射位置
							ScalPosB = enemy[e]->GetScalPosCar();

							TransMat1 = judg.GetTransMatScal(&D3DXVECTOR3(enemy[e]->GetCon().PosSmall.x, 0.0f, enemy[e]->GetCon().PosBig.z), &ScalPosB);
							TransMat2 = judg.GetTransMatScal(&D3DXVECTOR3(enemy[e]->GetCon().PosBig.x, 0.0f, enemy[e]->GetCon().PosBig.z), &ScalPosB);
							Trans = judg.GetTransMatScal(&D3DXVECTOR3(0.0f, 0.0f, enemy[e]->GetCon().PosBig.z), &ScalPosB);

							enemy[e]->SetForMoveVec(judg.MatMatVec(TransMat1*enemy[e]->GetMatCar(), TransMat1*enemy[e]->GetForMoveEndMat()), 0);
							enemy[e]->SetForMoveVec(judg.MatMatVec(Trans*enemy[e]->GetMatCar(), Trans*enemy[e]->GetForMoveEndMat()), 1);
							enemy[e]->SetForMoveVec(judg.MatMatVec(TransMat2*enemy[e]->GetMatCar(), TransMat2*enemy[e]->GetForMoveEndMat()), 2);
						}
					}
				}

				//------------------------------------------------------------------------

				//当たり判定--------------------------------------------------------------
				//移動ベクトルのサイズ
				float Mul;
				//当たり判定の回数
				int MaxJudg = 2;
				//当たり判定をMaxJudg回繰り返す
				for (int i = 0; i < MaxJudg; i++) {

					//player
					//playerのVecサイズ
					Mul = player->GetCon().SpeedMulJudg;
					//判定
					ForMoveJudg(player->GetCon(), player->GetDrawMatCar(), player->GetForMoveEndMat(), true, false, 0, player->GetForMoveVec(0), player->GetForMoveVec(1), player->GetForMoveVec(2), &Mul,&player->GetScalPosCar());
					//Mulを本体に入れる
					player->SetQuaVecSize(Mul);
					//最後の繰り返し以外
					if (i != MaxJudg - 1) {
						//新しい移動後を作成
						EndMat=ForMoveEnd(player->GetCon(), player->GetQuaForMove(), player->GetTransMatCar());
						/*EndPos = D3DXVECTOR3(EndMat._41, EndMat._42, EndMat._43);
						EndMat = player->GetMat();
						judg.SetMatP(&EndMat, EndPos);*/
						player->SetForMoveEndMat(EndMat);
						//Mulの初期化
						player->SetQuaVecSize(1.0f);
					}

					//enemy
					if (enemy.size() > 0) {
						for (unsigned int e = 0; e < enemy.size(); e++) {
							if ((enemy[e]->GetFlgCar() == true)&&(enemy[e]->GetSkyType()==false)) {
								//enemyのVecサイズ
								Mul = enemy[e]->GetCon().SpeedMulJudg;
								//判定
								ForMoveJudg(enemy[e]->GetCon(), enemy[e]->GetMatCar(), enemy[e]->GetForMoveEndMat(), false, true, e, enemy[e]->GetForMoveVec(0), enemy[e]->GetForMoveVec(1), enemy[e]->GetForMoveVec(2), &Mul,&enemy[e]->GetScalPosCar());
								//Mulを本体に入れる
								enemy[e]->SetQuaVecSize(Mul);
								//最後の繰り返し以外
								if (i != MaxJudg - 1) {
									//新しい移動後を作成
									EndMat = ForMoveEnd(enemy[e]->GetCon(), enemy[e]->GetQuaForMove(), enemy[e]->GetTransMatCar());
									/*EndPos = D3DXVECTOR3(EndMat._41, EndMat._42, EndMat._43);
									EndMat = enemy[e]->GetMatEn();
									judg.SetMatP(&EndMat, EndPos);*/
									enemy[e]->SetForMoveEndMat(EndMat);
									//Mulの初期化
									enemy[e]->SetQuaVecSize(1.0f);
								}
							}
						}
					}
				}
				//--------------------------------------------------------------
			}
			//=========================================================================


			//player======================================================================
			//playerの移動
			player->UpdateCarFM(ground);
			//移動ベクトルのサイズの初期化
			player->SetQuaVecSize(1.0f);
			//敵の移動
			UpdateEnemyMove();

			//横判定
			WallJudg(true, true, false, 0);
			WallJudg(false, true, false, 0);

			if (enemy.size() > 0) {
				for (unsigned int e = 0; e < enemy.size(); e++) {
					if ((enemy[e]->GetFlgCar() == true)&&(enemy[e]->GetSkyType()==false)) {
						WallJudg(true, false, true, e);
						WallJudg(false, false, true, e);
					}
				}
			}

			//最終Update
			//player->SetParts(camera->GetAngX(),camera->GetAngY());
			if (enemy.size() > 0) {
				for (unsigned int e = 0; e < enemy.size(); e++) {
					if (enemy[e]->GetFlgCar() == true) {
						enemy[e]->SetParts(ground);
					}
				}
			}

			//カメラをplaeyrの前方に振り向かせるクォータニオンの初期化
			if (EndFlg == false) {
				//前方に振り向く計算
				if ((key.RClickF() == true)&&(camera->GetQuaFlg()==false)) {
					D3DXVECTOR3 cVec, ccVec,pVec,ppVec;
					D3DXVec3TransformNormal(&cVec, &D3DXVECTOR3(0.0f, 0.0f, 1.0f), &camera->GetMat());
					D3DXVec3TransformNormal(&pVec, &D3DXVECTOR3(0.0f, 0.0f, 1.0f), &player->GetMatCar());
					ccVec = cVec;
					ppVec = pVec;

					float Dot, Ang,FrameUp;

					//クォータニオンのフレーム数を計算
					Dot = D3DXVec3Dot(&pVec, &cVec);
					if (Dot > 1.0f)Dot = 1.0f;
					if (Dot < -1.0f)Dot = -1.0f;
					Ang = D3DXToDegree(acos(Dot));
					FrameUp = 1.0f / Ang*6.0f;

					//RotYの計算
					D3DXMATRIX CamRotY, CamRotX;
					ppVec.y = 0;
					//内積
					Dot = D3DXVec3Dot(&D3DXVECTOR3(0.0f, 0.0f, 1.0f), &ppVec);
					if (Dot > 1.0f)Dot = 1.0f;
					if (Dot < -1.0f)Dot = -1.0f;
					Ang = D3DXToDegree(acos(Dot));
					if (ppVec.x < 0.0f)Ang *= -1.0f;
					D3DXMatrixRotationY(&CamRotY, D3DXToRadian(Ang));
					//camera->SetRotY(&CamRotY);


					//RotXの計算
					D3DXMATRIX Mat=player->GetMatCar();
					D3DXMatrixRotationY(&CamRotX, D3DXToRadian(-Ang));
					Mat = CamRotX * Mat;
					D3DXVec3TransformNormal(&pVec, &D3DXVECTOR3(0.0f, 0.0f, 1.0f), &Mat);
					//内積
					Dot = D3DXVec3Dot(&D3DXVECTOR3(0.0f, 0.0f, 1.0f), &pVec);
					if (Dot > 1.0f)Dot = 1.0f;
					if (Dot < -1.0f)Dot = -1.0f;
					Ang = D3DXToDegree(acos(Dot));
					if (pVec.y > 0.0f)Ang *= -1.0f;
					D3DXMatrixRotationX(&CamRotX, D3DXToRadian(Ang));
					//camera->SetRotX(&CamRotX);

					//クォータニオンの初期値をセット
					camera->SetQuaMat(&CamRotX, &CamRotY, &FrameUp);
				}
			}
			
			//カメラのクォータニオンのアップデート
			camera->UpdateQua();

			//カーブの車体の角度を反映
			player->SetCurRotMat();

			//playerのパーツ移動
			if (player->UpdateAll(&camera->GetMat()) == false) {
				//playerが死んだときの処理
				if (EndFlg == false) {
					BombInit(&player->GetMatCar());
					EndFlg = true;
					GaOv->Update(false, EndFlg);
					for (unsigned int e = 0; e < enemy.size(); e++) {
						enemy[e]->SetPlaEnd(true/*, player->GetSpeedCar()*/);
					}
					player->SetSpeedCar(player->GetSpeedCar()*0.0f);
					war->SetFlg(false);
					//メニューの表示
					SetMenu(false,false,true);
				}
			}
			//カメラのアップデート
			camera->Update(player->GetMatGun());
			//カメラと壁判定
			CameraWallJudg();

			//プレイヤーと地面判定2
			if (NowGroNum(player->GetMatCar(), &num, &Dis) == true) {
				player->SetGroNum(num);//地面の取得
				eneFlg = true;//敵の出現開始
			}

			//照準のレイ判定
			bool Flg = false;
			BULLETJUDGDATA l_DisD;
			Dis= 2000.0f;
			l_DisD = GetInitBJD(&Dis);
			RAYDATA l_RayR;
			l_RayR.Mat = judg.SetMatP(camera->GetPos());
			l_RayR.Ray= camera->GetVec();
			float Rad = (float)RadJudgF*2.0f;
			//敵のレイ判定
			BulletJudgEnemy(&l_DisD, &l_RayR, &Rad);
			if (l_DisD.Type > 0)Flg = true;
			//照準の変化
			if (Flg == true) {
				aiming->ChaFlg();
			}
			else {
				aiming->ResFlg();
			}
			//地面
			BulletJudgGround(&l_DisD, &l_RayR,NULL, &Rad);
			if (l_DisD.Type > 0)Flg = true;
			//建物のレイ判定
			//バレットの出現処理
			D3DXVECTOR3 pos;
			if (Flg == false) {
				player->SetBPos(pos, Flg);
			}
			else {
				pos = camera->GetPos() + l_RayR.Ray * l_DisD.SamllDis;
				player->SetBPos(pos, Flg);
			}
			
			//================================================================================
			//弾
			//================================================================================

			//弾の誕生決め
			BulletBirthFlg=GetBulletBirthFlg();
			//player弾のUpdate
			//player->GUpdateB(&BulletBirthFlg);
			SoundCamera sc;
			sc.CamPos = camera->GetPos();
			sc.CamLook = camera->GetLook();
			sc.CamHead = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			bool KeyFlg = key.LClickF_N();
			player->UpdateBulPla(&KeyFlg,&BulletBirthFlg,&sc);
			BulletJudg(&co_PlayerCar,NULL);
			player->UpdateBulletMove();
			bool BBFlgB = player->GetBulBirFlgB();
			SoundGun->Update(&BBFlgB);

			//================================================================================
			//空
			//================================================================================
			sky->Update(player->GetMatCar());

			//爆発アップデート================================================================
			for (unsigned int i = 0; i < explo.size(); i++) {
				if (explo[i]->ExplUpdate(&camera->GetMat()) == false) {
					delete explo[i];
					explo.erase(explo.begin() + i);
					i--;
				}
			}

			war->Update();

			//火花のアップデート
			if (SparkV.size() > 0) {
				for (unsigned int s = 0; s < SparkV.size(); s++) {
					if (SparkV[s]->UpdateSuper()== false){
						//削除
						delete SparkV[s];
						SparkV.erase(SparkV.begin() + s);
						s--;
					}
				}
			}

			Update_Smog_Player();


			//弾痕３Dのアップデート
			if (BHole3D.size() > 0) {
				for (unsigned int b = 0; b < BHole3D.size(); b++) {
					if (BHole3D[b]->UpdateHol3D() == false) {
						delete BHole3D[b];
						BHole3D.erase(BHole3D.begin() + b);
						b--;
					}
				}
			}

			//================================================================================
			//敵
			//================================================================================
			if (UpdateE() == false) {
				if (EndFlg == false) {
					EndFlg = true;
					GaOv->Update(true, EndFlg);
					SetMenu(false, true, false);
				}
			}
		}
		else {
			CountNum += 1;
		}
	}

	//メニューの更新
	UpdateMenu();

	return true;
}
bool GameScene::UpdateE(void)
{
	//=======================================================================================================================
	//エネミーUpdate
	//=======================================================================================================================

	if (enemy.size() > 0) {
		//地面判定2
		for (unsigned int e = 0; e < enemy.size(); e++) {
			if (enemy[e]->GetFlgCar() == true) {
				//enemyと地面判定
				unsigned int num;
				float dis;
				if (NowGroNum(enemy[e]->GetMatCar(), &num, &dis) == true) {
					enemy[e]->SetGroNum(num);
				}
				else {
					//if (EndFlg == true) {
						delete enemy[e];
						enemy.erase(enemy.begin() + e);
						e--;
					//}
				}
			}
		}
		for (unsigned int e = 0; e < enemy.size(); e++) {
			EnemyDelete(&e);
		}
		for (unsigned int i = 0; i < enemy.size(); i++) {
			if (enemy[i]->GetGunNum() > 0) {
				for (unsigned int g = 0; g < enemy[i]->GetGunNum(); g++) {
					if (enemy[i]->GetEnemyGunData(&g).RayJudgFlg == true) {
						//レイ判定
						BULLETJUDGDATA b;
						b.SamllDis = enemy[i]->GetEnemyGunData(&g).RayDis;
						RAYDATA r;
						r.Mat = enemy[i]->GetGunMat(&g);
						D3DXVec3TransformNormal(&r.Ray, &D3DXVECTOR3(0.0f, 0.0f, 1.0f), &r.Mat);
						float Rad = (float)RadChara*2.0f;
						BulletJudgPlayer(&b, &r, &Rad);
						bool Flg=false;
						if (b.Type > 0)Flg = true;
						enemy[i]->SetHitRayFlg(&g, &Flg);
						enemy[i]->GetRayHitDis(&g, &b.SamllDis);
					}
				}
			}

			//enemy[i]->UpdateEnd();//Update
			BulletJudg(&co_EnemyCar,&i);
			enemy[i]->UpdateBME();

			if (enemy[i]->GetFlgCar() == true) {
				debugT->Update(true);

				//当たり判定（エネミーと弾）
				judgDeta jd;
				/*jd = enemy[i]->GetJudgDate();
				for (unsigned int b = 0; b < player->GetBulSiz(); b++) {
					if (judg.ball(&jd, player->GetBulMat(b), 0.0f, 1)) {
						player->SetBulDel(&b);
						enemy[i]->SetHp(jd.Hp);
						if (enemy[i]->GetFlgE() == false) {
							BombInit(&enemy[i]->GetMatEn());
							NowEnemyNum -= 1;
							break;
						}
					}
				}*/
			}
			//enemyの弾とplayer判定
			for (unsigned int n = 0; n < enemy[i]->GetBulSize(); n++) {
				//範囲外削除
				if (judg.ball(player->GetMatCar(), enemy[i]->GetBulMat(n), player->GetRadF()) == false) {
					//弾の削除
					enemy[i]->BulDelete(&n);
				}
				//else {
				//	if (judg.ball(player->GetMatCar(), enemy[i]->GetBulMat(n), player->GetRadCar()) == true) {
				//		//playerのHP減少
				//		player->SetHP(1);
				//		//弾の削除
				//		enemy[i]->SetBulDel(&n);
				//	}
				//}
			}
			if ((enemy[i]->GetDeleFlg() == false)&&(judg.ball(enemy[i]->GetMatCar(),player->GetMatCar(),400.0f)==false)) {
				delete enemy[i];
				enemy.erase(enemy.begin() + i);
				i--;
			}

		}
	}
	if (EndFlg == true) {
		return true;
	}
	//敵全滅の確認
	if ((MaxEnemyNum == 0) && (NowEnemyNum == 0)) {
		//全滅したとき
		//ウェーブが一緒の時
		if ((NowWaveNum >= (MaxWaveNum-1))) {
			//ゲームクリア
			return false;
		}
		//ウェーブが違うとき
		NowWaveNum += 1;
		MaxEnemyNum = ePop[NowWaveNum]->MaxNum;
		NextEnemyNo = 0;
		if ((NowWaveNum >= (MaxWaveNum - 1))) {
			//ラストウェーブ
			war->SetFlg(true);
		}
	}
	return true;
}
void GameScene::SetCamera(void){
	D3DXMATRIX mView, mProj;
	D3DXMatrixLookAtLH(&mView,
		&camera->GetPos(),//カメラの位置
		&camera->GetLook(),// カメラの視点
		&D3DXVECTOR3(0.0f, 1.0f, 0.0f)	// カメラの頭の方向
	);


	// 投影行列の設定
	D3DXMatrixPerspectiveFovLH(&mProj, D3DXToRadian(60), (float)SCRW / (float)SCRH, 0.1f, 600.0f);

	//行列設定
	lpD3DDevice->SetTransform(D3DTS_VIEW, &mView);
	lpD3DDevice->SetTransform(D3DTS_PROJECTION, &mProj);

	inv.GetInvRotateMat(camera->GetPos(), camera->GetLook(), D3DXVECTOR3(0.0f, 1.0f, 0.0f));

	CamPosG = camera->GetPos();

	//Pos2Dのした準備
	D3DVIEWPORT9 Viewport;
	lpD3DDevice->GetViewport(&Viewport);
	//Pos2Dを使う
	Pos2DUpdate(&mProj, &mView, &Viewport);
}
void GameScene::GDebug(void)
{
	//--------------------------
	//車道計算
	//--------------------------
	/*debug->KeyUpdate();
	debug->SetDebugMat(ground[debug->GetNum()]->GetVwMat(0));
	ground[debug->GetNum()]->SetVwMat(0, debug->GetDebugMat());
	if (key->RETURNKeyF()) {
		player->SetMat(debug->GetDebugMat());
	}*/
	//矢印
	//debug->SetFlo(enemy[0]->GetAng());
	/*D3DXMATRIX mat,Trans;
	mat = enemy[0]->GetEnemyMat();
	D3DXVECTOR3 Pos;
	//Pos=judg.Pos2D(Pos, D3DXVECTOR3(mat._41, mat._42, mat._43));
	D3DXMatrixTranslation(&Trans, Pos.x, Pos.y, Pos.z);
	debug->SetDebugMat(Trans);*/
	debug->SetDebugMat(player->GetMatCar());
}

bool GameScene::NowGroNum(D3DXMATRIX Mat,unsigned int *Num,float *Dis)
{
	if (ground.size() <= 0) {
		return false;
	}
	float size;
	//地面レイ判定
	for (unsigned int g = 0; g<ground.size(); g++) {
		if (judg.ball(Mat, ground[g]->GetMat(), (float)RadJudgF) == true) {//自分の周囲の地面だけを判定
			D3DXVECTOR3 v[4];
			for (int i = 0; i < 4; i++) {
				v[i] = ground[g]->GetVer(i);
			}
			if (ground[g]->GetIdenFlg() == false) {//地面がIdentityMatで出来ているかの判定
				if (judg.RayPolM(Mat, v[0], v[1], v[2], v[3], ground[g]->GetMat(), D3DXVECTOR3(0.0f, -1.0f, 0.0f), &size) == true)//ポリゴンとレイ判定
				{
					*Num = g;
					*Dis = size;
					return true;
				}
			}
			else {
				if (judg.RayPolM(Mat, v[0], v[1], v[2], v[3], D3DXVECTOR3(0.0f, -1.0f, 0.0f), &size) == true)//ポリゴンとレイ判定
				{
					*Num = g;
					*Dis = size;
					return true;
				}
			}
		}
	}
	return false;
}

void GameScene::BulletJudg(const int * TypeCar, const unsigned int * No)
{
	BULLETJUDGDATA Bullet;

	RAYDATA BulletRay;

	float Dis,Rad=(float)RadJudgF;

	//プレイヤーの弾判定
	if (*TypeCar == co_PlayerCar) {
		if (player->GetBulSize() <= 0)return;

		for (unsigned int b = 0; b < player->GetBulSize(); b++) {
			//初期化
			Dis = player->GetBulletMoveDis(b);
			Bullet = GetInitBJD(&Dis);

			BulletRay.Mat= player->GetBulMat(b);
			D3DXVec3TransformNormal(&BulletRay.Ray, &D3DXVECTOR3(0.0f, 0.0f, 1.0f), &BulletRay.Mat);

			//地面
			if (player->GetBulRayFlgM(&b) == true) {
				bool GroWalJudgFlg;
				BulletJudgGround(&Bullet, &BulletRay,&GroWalJudgFlg,&Rad);
				//次も壁と地面を判定できるかの代入
				player->SetBulRayFlgM(&b, &GroWalJudgFlg);
			}

			//敵
			BulletJudgEnemy(&Bullet, &BulletRay,&Rad);
			//判定結果と弾の削除
			if (SetBulletDamage(&Bullet, &BulletRay, 1) == true)player->BulDelete(&b);
		}
		//判定終了
		return;
	}
	//敵の弾判定
	if (*TypeCar == co_EnemyCar) {
		if (enemy[*No]->GetBulSize() <= 0)return;

		for (unsigned int b = 0; b < enemy[*No]->GetBulSize(); b++) {
			//初期化
			Dis = enemy[*No]->GetBulletMoveDis(b);
			Bullet = GetInitBJD(&Dis);

			BulletRay.Mat = enemy[*No]->GetBulMat(b);
			D3DXVec3TransformNormal(&BulletRay.Ray, &D3DXVECTOR3(0.0f, 0.0f, 1.0f), &BulletRay.Mat);

			//プレイヤー
			BulletJudgPlayer(&Bullet, &BulletRay,&Rad);
			//地面
			BulletJudgGround(&Bullet, &BulletRay,NULL,&Rad);
			//判定結果と弾の削除
			if (SetBulletDamage(&Bullet, &BulletRay, 1) == true)enemy[*No]->BulDelete(&b);
		}
		//判定終了
		return;
	}

}

void GameScene::BulletJudgS(bool PlaBulFlg, unsigned int EnemyNo)
{

	//[0]=当たったら１、[1]=タイプ、[2]=ナンバー
	int JudgB[] = { -2,-2,-2 };

	//レイが当たった距離の最小,レイが当たった距離
	float SmallDis, Dis;

	//レイが当たったFlg
	bool JudgFlg = false;

	D3DXMATRIX BMat;//関数の呼び出し省略Mat

	D3DXVECTOR3 BVec;//弾の向き

	//壁と地面判定用
	bool GroWalJudgFlg = false;

	//レイが当たった座標
	D3DXVECTOR3 RayPos;

	//どっちの壁に当たったかFlg
	bool BulWallFlg;

	//---------------------------------------------------------------------
	//playerBulletレイ判定
	if (PlaBulFlg == true) {
		//================================================================================
		for (unsigned int b = 0; b < player->GetBulSize(); b++) {//弾数

			BMat = player->GetBulMat(b);//関数の呼び出し省略Mat

			//距離の最大を代入
			SmallDis = player->GetBulletMoveDis(b);

			D3DXVec3TransformNormal(&BVec, &D3DXVECTOR3(0.0f, 0.0f, 1.0f), &BMat);//正規化済みの向き
			//-------------------------------------------------------------------------
			//判定できるか
			if (player->GetBulRayFlgM(&b)== true) {
				for (unsigned int g = 0; g < ground.size(); g++) {
					if (judg.ball(BMat, ground[g]->GetMat(), (float)RadJudgF) == true) {//絞り込み
						//レイ判定種類分け
						if (ground[g]->GetIdenFlg() == false) {
							//レイ判定
							if (judg.RayPolM(BMat, ground[g]->GetVer(0), ground[g]->GetVer(1), ground[g]->GetVer(2), ground[g]->GetVer(3), ground[g]->GetMat(), BVec, &Dis) == true) {
								JudgFlg = true;
							}
						}
						else {
							//レイ判定
							if (judg.RayPolM(BMat, ground[g]->GetVer(0), ground[g]->GetVer(1), ground[g]->GetVer(2), ground[g]->GetVer(3), BVec, &Dis) == true) {
								JudgFlg = true;
							}

						}
						if (JudgFlg == true) {//当たった時
							//レイが当たった時に弾の移動のVecの長さより短いか調べる
							if (Dis < SmallDis) {
								SmallDis = Dis;
								JudgB[0] = co_Ground;
								JudgB[1] = g;
							}
							GroWalJudgFlg = true;
							JudgFlg = false;
						}
					}

					//壁判定
					for (int w = 0; w < 2; w++) {
						//二枚の壁判定
						bool LeftFlg = true;
						if (w == 1)LeftFlg = false;
						if (judg.ball(BMat, ground[g]->GetWaMat(&LeftFlg,0), (float)RadJudgF) == true) {
							//レイ判定
							if (judg.Mesh(judg.SetPosM(BMat), BVec, ground[g]->GetWaMat(&LeftFlg), ground[g]->GetColModWall(&LeftFlg), &Dis) == true) {
								//レイが当たった時に弾の移動のVecの長さより短いか調べる
								if (Dis < SmallDis) {
									SmallDis = Dis;
									JudgB[0] = co_Wall;
									JudgB[1] = g;
									JudgB[2] = w;
								}
								BulWallFlg = LeftFlg;
								GroWalJudgFlg = true;
								JudgFlg = false;
							}
						}
					}
				}
				//次も壁と地面を判定できるかの代入
				player->SetBulRayFlgM(&b, &GroWalJudgFlg);
				GroWalJudgFlg = false;
			}
			//-------------------------------------------------------------------------

			//-------------------------------------------------------------------------
			//敵(タイプ２)
			//pos
			D3DXVECTOR3 BPos;
			judg.SetPosM(&BPos, BMat);
			//enemyの数
			for (unsigned int e = 0; e < enemy.size(); e++) {
				if (judg.ball(BMat, enemy[e]->GetMatCar(), (float)RadJudgF) == true) {//絞り込み
					//レイ判定
					//ボディ
					if (judg.Mesh(BPos, BVec, enemy[e]->GetMatCar(), enemy[e]->GetMeshCar(), &Dis) == true) {
						//最大より小さいか
						if (Dis < SmallDis) {
							SmallDis = Dis;
							JudgB[0] = co_EnemyCar;
							JudgB[1] = e;
							JudgB[2] = -2;
						}
					}
					//パーツ
					if (enemy[e]->GetPartsNum() > 0) {
						for (unsigned int p = 0; p < enemy[e]->GetPartsNum(); p++) {
							if (judg.Mesh(BPos, BVec, enemy[e]->GetPartsMat(&p), enemy[e]->GetPartsData(&p).Mesh.DrawMesh.lpMesh, &Dis) == true) {
								//最大より小さいか
								if (Dis < SmallDis) {
									SmallDis = Dis;
									JudgB[0] = co_EnemyParts;
									JudgB[1] = e;
									JudgB[2] = p;
								}
							}
						}
					}
					//銃
					if (enemy[e]->GetGunNum() > 0) {
						for (unsigned int g = 0; g < enemy[e]->GetGunNum(); g++) {
							if (judg.Mesh(BPos, BVec, enemy[e]->GetGunMat(&g), enemy[e]->GetGunData(&g).Mesh.lpMesh, &Dis) == true) {
								//最大より小さいか
								if (Dis < SmallDis) {
									SmallDis = Dis;
									JudgB[0] = co_EnemyGun;
									JudgB[1] = e;
									JudgB[2] = g;
								}
							}
						}
					}

				}
			}
			//--------------------------------------------------------------------------

			//レイ判定でDisより小さい判定確認
			if (JudgB[0] > 0) {
				//地面
				if (JudgB[0] == co_Ground) {
					RayPos = judg.SetPosM(BMat) + BVec * SmallDis;
					int SpeType = 0;
					float Ang = 0.0f;
					SparkV.push_back(new C_BulGro(&ground[JudgB[1]]->GetMat(), &RayPos));
					//弾痕３D
					RayPos = judg.SetPosM(BMat) + BVec * (SmallDis - 0.01f);
					BHole3D.push_back(new C_BulHol3D(&ground[JudgB[1]]->GetMat(), &RayPos, 2));
				}
				else {
					//壁
					if (JudgB[0] == co_Wall) {
						//左
						RayPos = judg.SetPosM(BMat) + BVec * SmallDis;
						int SpeType = 1;
						float Ang = 0.0f;
						//火花
						for (int s = 0; s < 5; s++) {
							SparkV.push_back(new C_SparkDamage(&ground[JudgB[1]]->GetWaMat(&BulWallFlg, 0), &RayPos, &SpeType, &Ang));
						}
						//弾痕３D
						RayPos = judg.SetPosM(BMat) + BVec * (SmallDis - 0.01f);
						BHole3D.push_back(new C_BulHol3D(&ground[JudgB[1]]->GetWaMat(&BulWallFlg, 0), &RayPos, 1));
					}
					else {
						//火花
							//座標
						RayPos = judg.SetPosM(BMat) + BVec * SmallDis;
						//火花の種類
						int SpeType = 2;
						//角度
						for (float Ang = -180.0f; Ang < 175.0f; Ang += 20.0f)
						{
							SparkV.push_back(new C_SparkDamage(&BMat, &RayPos, &SpeType, &Ang));
						}
						DbgSize += 1;
						//敵のhpを削る
						//SetBulletDamage(JudgB[0], JudgB[1], JudgB[2], 1);
					}
				}
				//弾の消去
				player->BulDelete(&b);
				//判定の初期化
				JudgB[0] = -2;
				JudgB[1] = -2;
				JudgB[2] = -2;
			}
		}
		//--------------------------------------------
		return;
		//==============================================================================================
	}
	else{
	    //===============================================================================================
	    //EnemyBulletレイ判定
		//敵数
		//for (unsigned int e = 0; e < enemy.size(); e++) {
			for (unsigned int b = 0; b < enemy[EnemyNo]->GetBulSize(); b++) {//弾数

				BMat = enemy[EnemyNo]->GetBulMat(b);//関数の呼び出し省略Mat

				//距離の最大を代入
				SmallDis = enemy[EnemyNo]->GetBulletMoveDis(b);

				D3DXVec3TransformNormal(&BVec, &D3DXVECTOR3(0.0f, 0.0f, 1.0f), &BMat);//正規化済みの向き
				//-------------------------------------------------------------------------
				//Player(タイプ０)
				D3DXVECTOR3 BPos;//BulletPos
				judg.SetPosM(&BPos, BMat);
				if (judg.ball(BMat, player->GetMatCar(), (float)RadJudgF) == true) {//絞り込み
				//レイ判定
					//ボディ
					if (judg.Mesh(BPos, BVec, player->GetMatCar(), player->GetMeshCar(), &Dis) == true) {
						//レイが当たった時に弾の移動のVecの長さより短いか調べる
						if (Dis < SmallDis) {
							//短い時
							SmallDis = Dis;
							JudgB[0] = 1;
							JudgB[1] = co_PlayerCar;
							JudgB[3] = -2;
						}
					}
					//パーツ
					if (player->GetPartsNum() > 0) {
						for (unsigned int p = 0; p < player->GetPartsNum(); p++) {
							//ボディ
							if (judg.Mesh(BPos, BVec, player->GetPartsMat(&p), player->GetPartsData(&p).Mesh.DrawMesh.lpMesh, &Dis) == true) {
								//最大より小さいか
								if (Dis < SmallDis) {
									SmallDis = Dis;
									JudgB[0] = 1;
									JudgB[1] = co_PlayerParts;
									JudgB[3] = p;
								}
							}
						}
					}
					
				}
				//地面
				for (unsigned int g = 0; g < ground.size(); g++) {
					if (judg.ball(BMat, ground[g]->GetMat(), (float)RadJudgF) == true) {//絞り込み
						//レイ判定種類分け
						if (ground[g]->GetIdenFlg() == false) {
							//レイ判定
							if (judg.RayPolM(BMat, ground[g]->GetVer(0), ground[g]->GetVer(1), ground[g]->GetVer(2), ground[g]->GetVer(3), ground[g]->GetMat(), BVec, &Dis) == true) {
								JudgFlg = true;
							}
						}
						else {
							//レイ判定
							if (judg.RayPolM(BMat, ground[g]->GetVer(0), ground[g]->GetVer(1), ground[g]->GetVer(2), ground[g]->GetVer(3), BVec, &Dis) == true) {
								JudgFlg = true;
							}

						}
						if (JudgFlg == true) {//当たった時
							//レイが当たった時に弾の移動のVecの長さより短いか調べる
							if (Dis < SmallDis) {
								//短いとき
								SmallDis = Dis;
								JudgB[0] = 1;
								JudgB[1] = co_Ground;
								JudgB[2] = g;
							}
							JudgFlg = false;
						}
					}
					//壁判定
					for (int w = 0; w < 2; w++) {
						//二枚の壁判定
						bool LeftFlg = true;
						if (w == 1)LeftFlg = false;
						if (judg.ball(BMat, ground[g]->GetWaMat(&LeftFlg,0), (float)RadJudgF) == true) {
							//レイ判定
							if (judg.Mesh(judg.SetPosM(BMat), BVec, ground[g]->GetWaMat(&LeftFlg), ground[g]->GetColModWall(&LeftFlg), &Dis) == true) {
								JudgFlg = true;
							}
							if (JudgFlg == true) {//当たった時
							//レイが当たった時に弾の移動のVecの長さより短いか調べる
								if (Dis < SmallDis) {
									SmallDis = Dis;
									JudgB[0] = 1;
									JudgB[1] = co_Wall;
									JudgB[2] = g;
								}
								JudgFlg = false;
							}
						}
					}
				}
				//-------------------------------------------------------------------------

				//-------------------------------------------------------------------------
				////敵(タイプ２)
				//int eType = 2;
				////enemyの数
				//for (unsigned int en = 0; en < enemy.size(); en++) {
				//	//今の弾判定しているenemy以外のenemy
				//	if (e != en) {
				//		if (judg.ball(BMat, enemy[en]->GetMatEn(), (float)RadJudgF) == true) {//絞り込み
				//			//レイ判定
				//			if (judg.Mesh(BPos, BVec, enemy[en]->GetMatEn(), enemy[en]->GetMeshE(), &Dis) == true) {
				//				//最大より小さいか
				//				if (Dis < SmallDis) {
				//					//短いとき
				//					SmallDis = Dis;
				//					JudgB[0] = 1;
				//					JudgB[1] = eType;
				//					JudgB[2] = en;
				//				}
				//			}

				//		}
				//	}
				//}
				//--------------------------------------------------------------------------

				//レイ判定でDisより小さい判定確認
				if (JudgB[0] > -1) {
					//Playerであるか
						//SetBulletDamage(JudgB[1], JudgB[2], JudgB[3], 1);
					//else {
					//	//敵であるか
					//	if (JudgB[1] == eType) {
					//		if (enemy[JudgB[2]]->GetFlgE() == true) {
					//			//敵のHPを削る
					//			enemy[JudgB[2]]->SetHp(enemy[JudgB[2]]->GetHp() - 1);
					//			//敵が死んだときの処理
					//			unsigned int eNo = (unsigned int)JudgB[2];
					//			EnemyDelete(&eNo);
					//		}
					//	}
					//}
					//弾の消去
					enemy[EnemyNo]->BulDelete(&b);
					//判定の初期化
					JudgB[0] = -1;
					JudgB[1] = -2;
					JudgB[2] = -2;
					JudgB[3] = -2;
				}
			}
			//--------------------------------------------
		//}
		return;
		//===========================================================================
	}
}

bool GameScene::WallJudg(bool LeftFlg, bool PlayerFlg, bool EnemyFlg, unsigned int No)
{
	//判定の終了Flg
	bool JudgEndFlg = false;
	struct WallJudgChara {
		bool LeftFlg;
		bool PlayerFlg;
		bool EnemyFlg;
		unsigned int No;
		float Rad;
	};
	WallJudgChara Body;
	Body.LeftFlg = LeftFlg;
	Body.PlayerFlg = PlayerFlg;
	Body.EnemyFlg = EnemyFlg;
	Body.No = No;
	int MaxJudgMatNum = 3;
	D3DXMATRIX *JudgMat;
	JudgMat = new D3DXMATRIX[MaxJudgMatNum];

	//当たったレイの番号
	int JudgRayNum;
	//当たったMat
	D3DXMATRIX BaseMat;

	//限界While処理数
	int CountNum=20;

	//火花用壁判定後は出現させない用Flg
	bool WallSparkFlg = false;

	while (JudgEndFlg == false) {
		//次の判定車
		WallJudgChara NextBody;
		int CarFlg = 0;//プレイヤーかエネミーか一般車か判別するFlg
		//判定用Mat
		D3DXMATRIX TransMat;
		//判定用レイ
		D3DXVECTOR3 JudgVec;
		//一番数値の高いZと低いZ
		float BigZ, SmallZ;
		//拡大座標
		D3DXVECTOR3 ScalPosB;
		//判定をしている車の情報
		if (Body.PlayerFlg == true) {
			//プレイヤー
			CarFlg = 1;
			ScalPosB = player->GetScalPosCar();
			//Matの作成
			JudgMat[1] = player->GetCon().JudgMat;
			BigZ = player->GetCon().PosBig.z*ScalPosB.z;
			SmallZ = player->GetCon().PosSmall.z*ScalPosB.z;
			TransMat = player->GetTransMatCar();
			//Radを入れる
			if (Body.LeftFlg == true) {
				//左
				Body.Rad = player->GetCon().PosSmall.x*ScalPosB.x;
			}
			else {
				//右
				Body.Rad = player->GetCon().PosBig.x*ScalPosB.x;
			}
		}
		else {
			if (Body.EnemyFlg == true) {
				if ((enemy.size() <= 0) || (enemy[Body.No]->GetFlgCar() == false)) {
					return false;
				}
				//エネミー
				CarFlg = 2;
				ScalPosB = enemy[Body.No]->GetScalPosCar();
				//Matの作成
				JudgMat[1] = enemy[Body.No]->GetCon().JudgMat;
				BigZ = enemy[Body.No]->GetCon().PosBig.z*ScalPosB.z;
				SmallZ = enemy[Body.No]->GetCon().PosSmall.z*ScalPosB.z;
				TransMat = enemy[Body.No]->GetTransMatCar();
				//Radを入れる
				if (Body.LeftFlg == true) {
					//左
					Body.Rad = enemy[Body.No]->GetCon().PosSmall.x*ScalPosB.x;
				}
				else {
					//右
					Body.Rad = enemy[Body.No]->GetCon().PosBig.x*ScalPosB.x;
				}
			}
			else {
				//一般車
				CarFlg = 3;
			}
		}
		if (Body.Rad < 0.0f)Body.Rad *= -1.0f;
		Body.Rad += 0.01f;
		//Matの作成
		D3DXMATRIX Trans;
		for (int i = 0; i < MaxJudgMatNum; i++) {
			JudgMat[i] = TransMat * JudgMat[1];
		}
		D3DXMatrixTranslation(&Trans, 0.0f, 0.0f, BigZ);
		JudgMat[0] = Trans * JudgMat[1];
		D3DXMatrixTranslation(&Trans, 0.0f, 0.0f, SmallZ);
		JudgMat[2] = Trans * JudgMat[1];
		//レイの方向
		D3DXVECTOR3 Vec;
		if (Body.LeftFlg == true) {
			Vec = D3DXVECTOR3(-1.0f, 0.0f, 0.0f);
		}
		else {
			Vec = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
		}
		D3DXVec3TransformNormal(&JudgVec, &Vec, &JudgMat[1]);
		//判定用レイの距離
		float Dis, SmallDis = Body.Rad;
		if (SmallDis < 0.0f)SmallDis *= -1.0f;
		//レイ判定のtrueCar数
		int CountCar = 0;
		//当たった時の判定
		bool JudgFlg = false;
		//player判定
		if (CarFlg != 1) {
			//
			if (EndFlg == false) {
				//範囲内判定
				if (judg.ball(JudgMat[1], player->GetMatCar(), (float)RadJudgF) == true) {
					for (int i = 0; i < MaxJudgMatNum; i++) {
						D3DXVECTOR3 JudgPos = judg.SetPosM(JudgMat[i]);
						//レイ判定
						if (judg.Mesh(JudgPos, JudgVec, player->GetMatCar(), player->GetColMod(), &Dis) == true) {
							//当たった
							if (Dis < SmallDis) {
								SmallDis = Dis;
								NextBody.PlayerFlg = true;
								NextBody.EnemyFlg = false;
								NextBody.No = 0;
								JudgRayNum = i;
								BaseMat = player->GetMatCar();
							}
							if (Body.Rad > Dis) {
								JudgFlg = true;
							}
						}
					}
					//判定後
					if (JudgFlg == true) {
						CountCar += 1;
						JudgFlg = false;
					}
				}
			}
		}
		//enemy判定
		if (enemy.size() > 0) {
			//enemyの数
			for (unsigned int e = 0; e < enemy.size(); e++) {
				if ((CarFlg == 2) && (Body.No == e)||(enemy[e]->GetSkyType()==true)) {
					//判定しない
				}
				else {
					//判定する
					if (enemy[e]->GetFlgCar() == true) {
						//範囲内判定
						if (judg.ball(JudgMat[1], enemy[e]->GetMatCar(), (float)RadJudgF) == true) {
							for (int i = 0; i < 3; i++) {
								D3DXVECTOR3 JudgPos = judg.SetPosM(JudgMat[i]);
								//レイ判定
								if (judg.Mesh(JudgPos, JudgVec, enemy[e]->GetDrawMatCar(), enemy[e]->GetColMod(), &Dis) == true) {
									//当たった
									if (Dis < SmallDis) {
										SmallDis = Dis;
										NextBody.PlayerFlg = false;
										NextBody.EnemyFlg = true;
										NextBody.No = e;
										JudgRayNum = i;
										BaseMat = enemy[e]->GetMatCar();
									}
									if (Body.Rad > Dis) {
										JudgFlg = true;
									}
								}
							}
							//判定後
							if (JudgFlg == true) {
								CountCar += 1;
								JudgFlg = false;
							}
						}
					}
				}
			}
		}
		//壁判定
		bool WallJudgFlg = false;
		//地面数
		for (unsigned int g = 0; g < ground.size(); g++) {
			//範囲内判定
			
			if (judg.ball(JudgMat[1], ground[g]->GetWaMat(&Body.LeftFlg,0), (float)RadJudgF) == true) {
				for (int i = 0; i < MaxJudgMatNum; i++) {
					//レイ判定
					if (judg.Mesh(judg.SetPosM(JudgMat[i]), JudgVec, ground[g]->GetWaMat(&Body.LeftFlg), ground[g]->GetColModWall(&Body.LeftFlg), &Dis) == true) {
						//当たった
						if (i == 1) {
							if (Dis < SmallDis) {
								SmallDis = Dis;
								WallJudgFlg = true;
								JudgRayNum = i;
								BaseMat = ground[g]->GetWaMat(&Body.LeftFlg);
							}
						}
					}
				}
			}
		}
		//全てのレイ判定終了後
		//足りない長さの計算
		float RadDis = Body.Rad;
		if (RadDis < 0.0f)RadDis *= -1.0f;
		RadDis = RadDis - SmallDis;
		//反対方向にする
		if (Body.LeftFlg == false) RadDis *= -1.0f;
		//今当たり判定している車をずらす
		D3DXMATRIX Trans2;
		D3DXMatrixTranslation(&Trans2, RadDis, 0.0f, 0.0f);
		//反映用行列
		D3DXMATRIX TmpMat;

		//壁に当たった時
		if (WallJudgFlg == true) {
			if (CarFlg == 1) {
				TmpMat = Trans2 * (player->GetTransMatCar());
				player->SetTransMatCar(&TmpMat);
				TmpMat = player->GetTransMatCar()*player->GetCon().JudgMat;
				player->SetMatCar(&TmpMat);
			}
			if (CarFlg == 2) {
				TmpMat = Trans2 * (enemy[Body.No]->GetTransMatCar());
				enemy[Body.No]->SetTransMatCar(&TmpMat);
				TmpMat = enemy[Body.No]->GetTransMatCar()*enemy[Body.No]->GetCon().JudgMat;
				enemy[Body.No]->SetMatCar(&TmpMat);
				//Hpを削る処理
				if (WallSparkFlg == false) {
					enemy[Body.No]->SetHP(1,true);
					unsigned int eNo = Body.No;
					EnemyDelete(&eNo);
				}
			}
			//火花を出す処理
			//複数出す
			bool InitFlg=false;
			for (int i = 0; i < 20; i++) {
				SparkV.push_back(new C_Spark2(&BaseMat, &(judg.SetPosM(JudgMat[JudgRayNum]) + JudgVec * (SmallDis - 0.1f)),&Body.LeftFlg,&InitFlg));
			}
			InitFlg = true;
			for (int i = 0; i < 15; i++) {
				SparkV.push_back(new C_Spark2(&BaseMat, &(judg.SetPosM(JudgMat[JudgRayNum]) + JudgVec * (SmallDis - 0.1f)), &Body.LeftFlg,&InitFlg));
			}
			//リバース
			judg.ReverseFlg(&Body.LeftFlg);
			//壁判定後は火花を出さない
			WallSparkFlg = true;
		}
		else {
			//複数に当たった時
			if (CountCar >= 2) {
				//今当たり判定している車
				if (CarFlg == 1) {
					TmpMat = Trans2 * (player->GetTransMatCar());
					player->SetTransMatCar(&TmpMat);
					TmpMat = player->GetTransMatCar()*player->GetCon().JudgMat;
					player->SetMatCar(&TmpMat);
				}
				if (CarFlg == 2) {
					TmpMat = Trans2 * (enemy[Body.No]->GetTransMatCar());
					enemy[Body.No]->SetTransMatCar(&TmpMat);
					TmpMat = enemy[Body.No]->GetTransMatCar()*enemy[Body.No]->GetCon().JudgMat;
					enemy[Body.No]->SetMatCar(&TmpMat);
				}
				//リバース
				judg.ReverseFlg(&Body.LeftFlg);
			}
			else {
				//1車のみ当たった時
				if (CountCar == 1) {
					//押し出す
					D3DXMatrixTranslation(&Trans2, RadDis*-1.0f, 0.0f, 0.0f);
					//当たった車判定
					Body.PlayerFlg = NextBody.PlayerFlg;
					Body.EnemyFlg = NextBody.EnemyFlg;
					Body.No = NextBody.No;
					if (Body.PlayerFlg == true) {
						CarFlg = 1;
					}
					else {
						if (Body.EnemyFlg == true) {
							CarFlg = 2;
						}
						else {
							CarFlg = 3;
						}
					}
					//当たった車
					if (CarFlg == 1) {
						TmpMat = Trans2 * (player->GetTransMatCar());
						player->SetTransMatCar(&TmpMat);
						TmpMat = player->GetTransMatCar()*player->GetCon().JudgMat;
						player->SetMatCar(&TmpMat);
						//Hpを削る処理
						/*if (WallSparkFlg == false) {
							player->SetHP(1,true);
						}*/

					}
					if (CarFlg == 2) {
						enemy[Body.No]->SetTransMatCar(&judg.GetMatY(&Trans2,&enemy[Body.No]->GetTransMatCar()));
						TmpMat = enemy[Body.No]->GetCon().JudgMat;
						enemy[Body.No]->SetMatCar(&judg.GetMatY(&enemy[Body.No]->GetTransMatCar(),&TmpMat));
						//Hpを削る処理
						if (WallSparkFlg == false) {
							enemy[Body.No]->SetHP(1,true);
							unsigned int eNo = Body.No;
							EnemyDelete(&eNo);
						}
					}
					//火花を出す処理
					if (WallSparkFlg == false) {
						//複数出す
						bool InitFlg = false;
						for (int i = 0; i < 15; i++) {
							SparkV.push_back(new C_Spark2(&BaseMat, &(judg.SetPosM(JudgMat[JudgRayNum]) + JudgVec * (SmallDis - 0.1f)), &InitFlg));
						}
						InitFlg = true;
						for (int i = 0; i < 12; i++) {
							SparkV.push_back(new C_Spark2(&BaseMat, &(judg.SetPosM(JudgMat[JudgRayNum]) + JudgVec * (SmallDis - 0.1f)), &InitFlg));
						}
					}
				}
				else {
					//当たっていない時
					break;
				}
			}
		}
		//処理数処理
		CountNum--;
		if (CountNum <= 0) {
			break;
		}

	}//while文終了
	if (JudgMat != nullptr) {
		delete[] JudgMat;
	}
	return true;
}

bool GameScene::WallJudg(const D3DXMATRIX * JudgMat, D3DXMATRIX * TransMat, const SizePos * sizePos)
{
	return false;
}

bool GameScene::UpdateEnemyAI(void)
{
	//エネミーの出現
	//if (enemy.size() <= 0) {
	//ゲームが終わっていないかの確認
	if (EndFlg == false) {
		if ((MaxEnemyNum != 0) && (war->GetFlg() == false)) {
			//次に出現するまでの時間
			if (ePop[NowWaveNum]->rePopTime[NextEnemyNo] <= 0) {
				if (eneFlg == true) {//playerが地面の判定を得たら
					//地面のナンバー
					unsigned int gNo;
					gNo = player->GetGroNum() -10;
					//地面があるかの判定
					if (gNo < 0)gNo = 0;
					if (gNo > ground.size() - 1)gNo = ground.size() - 1;
					//車線を決める
					int RailNum = rand() % ground[gNo]->GetWay().RailNum;
					//出現可能かどうか
					//if (enemy.size() <= 0) {
						//出現可能
						//enemyのナンバーを探す
					D3DXMATRIX GMat = ground[gNo]->GetWay().StartMat;
						if (EnemyBirth(&ePop[NowWaveNum]->EneNumber[NextEnemyNo],&GMat, &ground[gNo]->GetWay().CurTransX[RailNum])==true) {
							MaxEnemyNum -= 1;
							NowEnemyNum += 1;
							/*enemy[(enemy.size() - 1)]->SetSize
							(judg.ball(player->GetMatCar(), enemy[(enemy.size() - 1)]->GetMatCar()));*/
							unsigned int num;
							float dis;
							if (NowGroNum(enemy[(enemy.size() - 1)]->GetMatCar(), &num, &dis) == true) {
								enemy[(enemy.size() - 1)]->SetGroNum(num);
							}
							NextEnemyNo += 1;
						}
					//}
				}
			}
			else {
				//時間を減らす
				ePop[NowWaveNum]->rePopTime[NextEnemyNo] -= 1;
			}
		}
	}
	//Update
	if (enemy.size() > 0) {
		//地面判定
		for (unsigned int e = 0; e < enemy.size(); e++) {
			if (enemy[e]->GetFlgCar() == true) {
				//enemyと地面判定
				unsigned int num;
				float dis;
				if (NowGroNum(enemy[e]->GetMatCar(), &num, &dis) == true) {
					enemy[e]->SetGroNum(num);
				}
				else {
					if (EndFlg == true) {
						delete enemy[e];
						enemy.erase(enemy.begin() + e);
						e--;
					}
				}
			}
		}
		//AI
		if (EndFlg == false) {
			for (unsigned int i = 0; i < enemy.size(); i++) {
				CHARAData*Data;
				int ChaNum = 0;
				ChaNum += 1;
				Data = new CHARAData[ChaNum];
				Data[0] = player->GetData();
				enemy[i]->UpdateAi(Data, (unsigned int)ChaNum, ground);
				delete Data;
			}
		}
	}
	return false;
}

bool GameScene::UpdateEnemyMove(void)
{
	if (enemy.size() > 0) {
		for (unsigned int i = 0; i < enemy.size(); i++) {
			//
			if (enemy[i]->GetFlgCar() == true) {
				enemy[i]->UpdateAll(ground);//Update
				//移動ベクトルのサイズの初期化
				enemy[i]->SetQuaVecSize(1.0f);
			}
		}
	}
	return false;
}

bool GameScene::ForMoveJudg(CONSTITUTION Con, D3DXMATRIX StartMat, D3DXMATRIX EndMat, bool PlayerFlg, bool EnemyFlg, unsigned int No, D3DXVECTOR3 RayVec1, D3DXVECTOR3 RayVec2, D3DXVECTOR3 RayVec3, float * SpeedMul2,const D3DXVECTOR3 *ScalPos)
{
	int CarFlg = 0;//プレイヤーかエネミーか一般車か判別するFlg
	if (PlayerFlg == true) {
		//プレイヤー
		CarFlg = 1;
	}
	else {
		if (EnemyFlg == true) {
			if ((enemy.size() <= 0) || (enemy[No]->GetFlgCar() == false)) {
				return false;
			}
			//エネミー
			CarFlg = 2;
		}
		else {
			//一般車
			CarFlg = 3;
		}
	}
	D3DXVECTOR3 *MoveVec=new D3DXVECTOR3[3];//移動ベクトル
	float *VecSize=new float[3];//ベクトルの長さ
	MoveVec[0] = RayVec1;
	MoveVec[1] = RayVec2;
	MoveVec[2] = RayVec3;
	for (int i = 0; i < 3; i++) {
		VecSize[i] = D3DXVec3Length(&MoveVec[i]);
		if (VecSize[i] < 0.0f)VecSize[i] *= -1.0f;
		VecSize[i] += 0.1f;
		D3DXVec3Normalize(&MoveVec[i], &MoveVec[i]);//移動ベクトルの正規化
	}
	D3DXMATRIX TransMat1, TransMat2,TransMat3;//両側のレイ発射位置
	TransMat1 = judg.GetTransMatScal(&D3DXVECTOR3(Con.PosSmall.x, 0.0f, Con.PosBig.z), ScalPos);
	TransMat2 = judg.GetTransMatScal(&D3DXVECTOR3(Con.PosBig.x, 0.0f, Con.PosBig.z), ScalPos);
	TransMat3 = judg.GetTransMatScal(&D3DXVECTOR3(0.0f, 0.0f, Con.PosBig.z), ScalPos);
	
	TransMat1 = TransMat1 * StartMat;
	TransMat2 = TransMat2 * StartMat;
	TransMat3 = TransMat3 * StartMat;
	//レイの長さと最小
	float Dis, *SmallDis=new float[3];
	for (int i = 0; i < 3; i++) {
		SmallDis[i] = VecSize[i];
	}
	bool *JudgFlg = new bool[3];
	for (int i = 0; i < 3; i++) {
		JudgFlg[i] = false;
	}

	//player判定
	if (CarFlg != 1) {
		//判定する
		if(EndFlg==false){
		//絞り込み
			if (judg.ball(StartMat, player->GetMatCar(), (float)RadJudgF) == true) {
				D3DXVECTOR3 JudgPos;//レイの始点
				//左から順番に
				for (int i = 0; i < 3; i++) {
					if (i == 0)JudgPos = D3DXVECTOR3(TransMat1._41, TransMat1._42, TransMat1._43);
					if (i == 1)JudgPos = D3DXVECTOR3(TransMat3._41, TransMat3._42, TransMat3._43);
					if (i == 2)JudgPos = D3DXVECTOR3(TransMat2._41, TransMat2._42, TransMat2._43);
					//レイ判定
					if (judg.Mesh(JudgPos, MoveVec[i], player->GetForMoveEndMat(), player->GetColMod(), &Dis, 0) == true) {
						//当たった
						float Dis2;
						D3DXVECTOR3 Pos2, Vec2;
						D3DXMATRIX Mat;
						for (int n = 0; n < 3; n++) {
							if (n == 0) {
								Mat = judg.GetTransMatScal(&D3DXVECTOR3(Con.PosSmall.x, 0.0f, Con.PosBig.z), ScalPos);
								Mat = Mat * EndMat;
								judg.SetPosM(&Pos2, Mat);
								D3DXVec3TransformNormal(&Vec2, &D3DXVECTOR3(0.0f, 0.0f, 1.0f), &Mat);
							}
							if (n == 1) {
								Mat = judg.GetTransMatScal(&D3DXVECTOR3(0.0f, 0.0f, Con.PosBig.z), ScalPos);
								Mat = Mat * EndMat;
								judg.SetPosM(&Pos2, Mat);
								D3DXVec3TransformNormal(&Vec2, &D3DXVECTOR3(0.0f, 0.0f, 1.0f), &Mat);
							}
							if (n == 2) {
								Mat = judg.GetTransMatScal(&D3DXVECTOR3(Con.PosBig.x, 0.0f, Con.PosBig.z), ScalPos);
								Mat = Mat * EndMat;
								judg.SetPosM(&Pos2, Mat);
								D3DXVec3TransformNormal(&Vec2, &D3DXVECTOR3(0.0f, 0.0f, 1.0f), &Mat);
							}
							if (judg.Mesh(Pos2, Vec2, player->GetForMoveEndMat(), player->GetColMod(), &Dis2) == true) {
								if (Dis < SmallDis[i]) {
									SmallDis[i] = Dis;
									JudgFlg[i] = true;
								}
							}
						}
					}
				}
			}
		}
	}
	//敵判定
	if (enemy.size() > 0) {
		for (unsigned int e = 0; e < enemy.size(); e++) {
			if ((CarFlg == 2) && (No == e)||(enemy[e]->GetSkyType()==true)) {
				//判定しない
			}
			else {
				//判定する
				//生きていいるか
				if (enemy[e]->GetFlgCar() == true) {
					//絞り込み距離判定
					if (judg.ball(StartMat, enemy[e]->GetMatCar(), (float)RadJudgF) == true) {
						D3DXVECTOR3 JudgPos;//レイの始点
			            //左から順番に
						for (int i = 0; i < 3; i++) {
							if (i == 0)JudgPos = D3DXVECTOR3(TransMat1._41, TransMat1._42, TransMat1._43);
							if (i == 1)JudgPos = D3DXVECTOR3(TransMat3._41, TransMat3._42, TransMat3._43);
							if (i == 2)JudgPos = D3DXVECTOR3(TransMat2._41, TransMat2._42, TransMat2._43);
							//レイ判定
							if (judg.Mesh(JudgPos, MoveVec[i], enemy[e]->GetForMoveEndMat(), enemy[e]->GetColMod(), &Dis,0) == true) {
								//当たった
								float Dis2;
								D3DXVECTOR3 Pos2, Vec2;
								D3DXMATRIX Mat;
								for (int n = 0; n < 3; n++) {
									if (n == 0) {
										Mat = judg.GetTransMatScal(&D3DXVECTOR3(Con.PosSmall.x, 0.0f, Con.PosBig.z), ScalPos);
										Mat = Mat * EndMat;
										judg.SetPosM(&Pos2,Mat);
										D3DXVec3TransformNormal(&Vec2, &D3DXVECTOR3(0.0f, 0.0f, 1.0f), &Mat);
									}
									if (n == 1) {
										Mat = judg.GetTransMatScal(&D3DXVECTOR3(0.0f, 0.0f, Con.PosBig.z), ScalPos);
										Mat = Mat * EndMat;
										judg.SetPosM(&Pos2, Mat);
										D3DXVec3TransformNormal(&Vec2, &D3DXVECTOR3(0.0f, 0.0f, 1.0f), &Mat);
									}
									if (n == 2) {
										Mat = judg.GetTransMatScal(&D3DXVECTOR3(Con.PosBig.x, 0.0f, Con.PosBig.z), ScalPos);
										Mat = Mat * EndMat;
										judg.SetPosM(&Pos2, Mat);
										D3DXVec3TransformNormal(&Vec2, &D3DXVECTOR3(0.0f, 0.0f, 1.0f), &Mat);
									}
									if (judg.Mesh(Pos2, Vec2, enemy[e]->GetForMoveEndMat(), enemy[e]->GetColMod(), &Dis2) == true) {
										if (Dis < SmallDis[i]) {
											SmallDis[i] = Dis;
											JudgFlg[i] = true;
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
	//レイが当たった
	if ((JudgFlg[0] == true)|| (JudgFlg[1] == true) || (JudgFlg[2] == true)) {
		for (int i = 0; i < 3; i++) {
			SmallDis[i]= (VecSize[i])/(VecSize[1])*((SmallDis[i]) / (VecSize[i]));
		}
		if (JudgFlg[0] == true) {
			Dis = SmallDis[0];
			if (JudgFlg[1] == true) {
				if (Dis > SmallDis[1])Dis = SmallDis[1];
			}
			if (JudgFlg[2] == true) {
				if (Dis > SmallDis[2])Dis = SmallDis[2];
			}
		}
		else {
			if (JudgFlg[1] == true) {
				Dis = SmallDis[1];
				if (JudgFlg[2] == true) {
					if (Dis > SmallDis[2])Dis = SmallDis[2];
				}
			}
			else {
				  Dis = SmallDis[2];
			}
		}
		*SpeedMul2 = *SpeedMul2*Dis;
		if (*SpeedMul2 > 1.0f)*SpeedMul2 = 1.0f;
		/*if ((SmallDis - Con.PosBig.z) < (VecSize - Con.PosBig.z)) {
			float ESize;
			ESize = (SmallDis - Con.PosBig.z - 0.01f) / (VecSize - Con.PosBig.z);
			*SpeedMul2 = *SpeedMul2*ESize;
		}*/
	}
	delete[] MoveVec;
	delete[] VecSize;
	delete[] SmallDis;
	delete[] JudgFlg;

	return true;
}

D3DXMATRIX GameScene::ForMoveEnd(CONSTITUTION Con, QuaForMove q, D3DXMATRIX TransMat)
{
	motion.Formove(Con, &q.NowMat, &q.AnimeFrame, ground, &q.QuaInitFlg, &q.QuaMatInitFlg, &q.SpeedMul, q.SpeedMul2, &q.StartMat, &q.EndMat,
		&q.WayVec, &q.CurFlg, &q.CurVec, q.BodyHeight);
	q.NowMat = TransMat * q.NowMat;
	return q.NowMat;
}

void GameScene::CameraWallJudg(void)
{
	//レイ
	D3DXVECTOR3 Vec = camera->GetPos() - camera->GetLook();
	//レイサイズ
	float Dis, SmallDis = D3DXVec3Length(&Vec);
	//レイの正規化
	D3DXVec3Normalize(&Vec, &Vec);
	//判定フラグ
	bool JudgFlg = false;
	//壁判定
	//地面の存在確認
	if (ground.size() > 0) {
		//存在する
		//地面の数
		for (unsigned int g = 0; g < ground.size(); g++) {
			//範囲絞り込み
			if (judg.ball(camera->GetPos(), ground[g]->GetMat(), (float)RadJudgF) == true) {
				//範囲内
				//左フラグ
				bool LeftFlg = true;
				//壁の数
				for (int w = 0; w < 2; w++) {
					//左右判定
					if (w == 0) {
						//左
						LeftFlg = true;
					}
					else {
						//右
						LeftFlg = false;
					}
					//壁の内側を見せないための拡大行列
					D3DXMATRIX ScalY;
					D3DXMatrixScaling(&ScalY, 1.3f, 1.0f, 1.0f);
					//レイ判定
					if (judg.Mesh(camera->GetLook(), Vec, ScalY*ground[g]->GetWaMat(&LeftFlg), ground[g]->GetColModWall(&LeftFlg), &Dis) == true) {
						//当たった
						if (Dis < SmallDis) {
							SmallDis = Dis;
							JudgFlg = true;
						}
					}
				}
			}
		}
	}
	//判定終了
	//カメラの位置セット
	if (JudgFlg == true) {
		camera->SetCamPos(&(camera->GetLook() + Vec * (SmallDis - 0.01f)));
	}

	//壁のメッシュの弱さを決める判定
	bool Flg;
	for (unsigned int g = 0; g < ground.size(); g++) {
		if (judg.ball(camera->GetPos(), ground[g]->GetMat(),  400.0f) == true) {
			Flg = false;
			ground[g]->SetDoawRadFlg(&Flg);
		}
		else {
			Flg = true;
			ground[g]->SetDoawRadFlg(&Flg);
		}
	}
}

bool GameScene::GetBulletBirthFlg(void)
{
	if (EndFlg == true)return false;
	if ((key.LClickF_N() == true) && (BulletBirthFlg == false))return false;
	return true;
}

void GameScene::BombInit(const D3DXMATRIX * Mat)
{
	SoundCamera scB;
	scB.CamPos = camera->GetPos();
	scB.CamLook = camera->GetLook();
	scB.CamHead = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	explo.push_back(new Explo(*Mat, &scB));
	return;
}

bool GameScene::EnemyDelete(const unsigned int * EnemyNo)
{
	if ((*EnemyNo < 0) || (*EnemyNo > enemy.size() - 1))return false;

	if (enemy[*EnemyNo]->GetFlgCar() == false) {
		if (enemy[*EnemyNo]->GetDeadFlg() == false) {
			enemy[*EnemyNo]->SetDeadFlg(true);
			BombInit(&enemy[*EnemyNo]->GetMatCar());
			NowEnemyNum -= 1;
			int sc = 1000;
			score->ScoreUp(&sc);
			return true;
		}
	}
	return false;
}

bool GameScene::EnemyBirth(const int * EnemyNo, D3DXMATRIX * GroundMat,float * TransX)
{
	//敵の情報を検索
	/*C_EnemySelect EneSel;
	BODYDATACar eData=EneSel.GetEnemy(*EnemyNo);

	Enemyのスピード管理
	C_EnemySpeedManager m_EnemySpeedManager;

	車
	enemy.push_back(new C_EnemyA(*GroundMat, TransX,&eData,m_EnemySpeedManager.GetEnemySpeed(*EnemyNo)));*/
	enemy.push_back(new C_EnemyA(EnemyNo, *GroundMat, TransX));
	return true;

}

void GameScene::ChangeSceneFade(int ChangeSceneNo)
{
	if (fade->GetMoveFlg() == false) {
		if (SceneChangeFlg == false) {
			SceneNo = ChangeSceneNo;
			SceneChangeFlg = true;
			bool BlackFlg = true;
			if (ChangeSceneNo == GameNo)BlackFlg = false;
			fade->SetIn(BlackFlg);

			//キー操作不能
			key.SetFlg(true);
		}
	}
}

void GameScene::ChangeSceneFade(int ChangeSceneNo, int NextStageNo)
{
	ChangeSceneFade(ChangeSceneNo);
	ChangeStageNo = NextStageNo;
}

bool GameScene::SetScene(void)
{
	if (SceneNo == TitleNo) {
		sceneManager.changeScene(new TitleScene());
		return false;
	}
	if (SceneNo == StageSelectNo) {
		sceneManager.changeScene(new StageSelectScene());
		return false;
	}
	if (SceneNo == GameNo) {
		sceneManager.changeScene(new GameScene(ChangeStageNo));
		return false;
	}
	return true;
}

void GameScene::SetMenu(bool PauseFlg, bool ClearFlg, bool OverFlg)
{
	if (Menu.size() > 0)return;

	float yUp;
	int Mode;
	//ポーズ------------------------------------
	if (PauseFlg == true) {
		yUp = 20.0f;
		Mode = 1;

		Menu.push_back(new C_PauseTouch(
			&D3DXVECTOR3(1280.0f / 2.0f, 720.0f / 5.0f*4.0f, 0.0f), &D3DXVECTOR3(0.35f, 0.4f, 1.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), &yUp,&Mode));
		return;
	}
	//ステージクリア---------------------------------------
	if (ClearFlg == true) {
		yUp = 20.0f;
		Mode = 2;

		Menu.push_back(new C_ClearTouch(
			&D3DXVECTOR3(1280.0f / 2.0f, 720.0f / 5.0f*4.0f, 0.0f), &D3DXVECTOR3(0.35f, 0.4f, 1.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), &yUp, &Mode));
		return;
	}
	//ゲームオーバー---------------------------------------
	if (OverFlg == true) {
		yUp = 35.0f;
		Mode = 3;

		Menu.push_back(new C_OverTouch(
			&D3DXVECTOR3(1280.0f / 2.0f, 720.0f / 5.0f*4.0f, 0.0f), &D3DXVECTOR3(0.35f, 0.4f, 1.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), &yUp, &Mode));
		return;
	}

	return;
}

void GameScene::DeleteMenu(void)
{
	if (Menu.size() > 0) {
		for (unsigned int m = 0; m < Menu.size(); m++) {
			delete Menu[m];
			Menu.erase(Menu.begin() + m);
			m--;
		}
	}
}

bool GameScene::UpdateMenu(void)
{
	if (Menu.size() <= 0)return false;

	int Touch = Menu[0]->TouchNow2();

	if (Touch > 0) {
		//mouse->SetTouchFlg();
	}
	else {
		return false;
	}

	if (key.LClickF() != true)return false;

	//ポーズ時--------------------------------
	if (Menu[0]->GetMenuMode() == 1) {
		//プレイを押しす処理
		if (Touch == 1) {
			if (pause->GetDFlg() == true) {
				pause->SetDFlg(false);
				mouse->Init();
				mouse->ChaDrawFlg(false);
				bgm->StartSound();
				pause->SetStaSavFlg(false);

				//メニュー削除
				DeleteMenu();
				return true;
			}
		}

		//セレクトを押しす処理
		if (Touch == 2) {
			if (pause->GetDFlg() == true) {
				ChangeSceneFade(StageSelectNo);
				return true;
			}
		}
	}

	//クリア時----------------------------------------
	if (Menu[0]->GetMenuMode() == 2) {
		//タイトルを押しす処理
		if (Touch == 1) {
			ChangeSceneFade(TitleNo);
			return true;
		}

		//セレクトを押しす処理
		if (Touch == 2) {
			ChangeSceneFade(StageSelectNo);
			return true;
		}
	}

	//ゲームオーバー時----------------------------------------
	if (Menu[0]->GetMenuMode() == 3) {
		//リトライを押しす処理
		if (Touch == 1) {
			ChangeSceneFade(GameNo, StageNo);
			return true;
		}

		//セレクトを押しす処理
		if (Touch == 2) {
			ChangeSceneFade(StageSelectNo);
			return true;
		}

		//タイトルを押しす処理
		if (Touch == 3) {
			ChangeSceneFade(TitleNo);
			return true;
		}
	}

	//ゲームオーバー時

	return true;
}

bool GameScene::GroundCreate(unsigned int *GNo)
{
	if (judg.ball(player->GetMatCar(), ground[*GNo]->GetMat(), player->GetRadF()) == false) {
		if (player->GetGroNum() < *GNo)return false;
		if (ground[*GNo]->GetFlg() == false) return false;
		delete ground[*GNo];
		ground.erase(ground.begin() + *GNo);
		*GNo -= 1;
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
		if (cou->CouJudge() == false) cou->SetNum(0);

		if ((cou->GetNum() == 1) && (GroType == 0)) {
			ground.push_back(new BillBase(Mat[1], Mat[0], GroType, AngGro, 5.0f, GroLenFlg)); //ground.push_back(new BillBase(Mat[1], Mat[0], GroType, AngGro, 5.0f, GroLenFlg));
		}
		else {
			ground.push_back(new Bill(Mat[1], Mat[0], GroType, AngGro, 5.0f, GroLenFlg));
		}
		//外灯の初期化
		if (LightCount->Update() == true) {
			int wNum = 2;
			ground[ground.size() - 1]->InitLight(&wNum);
		}


		if (GroCou.size() > 0) {
			for (unsigned int g = 0; g < GroCou.size(); g++) {
				GroCou[g]->CouUpd();
				if (GroCou[g]->CouJudge() == false) {
					for (unsigned int z = 0; z < GroCou.size(); z++) {
						delete GroCou[z];
						GroCou.erase(GroCou.begin() + z);
						z--;
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
	else {
		//新品の道を判定できるようにする
		if (ground[*GNo]->GetFlg() == false) {
			ground[*GNo]->SetFlg(true);
		}
	}
	return true;
}

void GameScene::Pos2DUpdate(const D3DXMATRIX * mProj, const D3DXMATRIX * mView, const D3DVIEWPORT9 * Viewport)
{
	if (enemy.size() <= 0)return;
	for (unsigned int e = 0; e < enemy.size(); e++) {
		//矢印計算
		enemy[e]->GetPos2DSet(mProj, mView, Viewport);
	}
}

bool GameScene::Update_Smog_Player(void)
{
	//
	float L_Per = (float)player->GetCharaBase().NowHp / (float)player->GetCharaBase().MaxHp;
	if ( L_Per< 0.3f) {
		float L_Num = 30.0f;
		if (rand() % 100 < 20+ (int)(L_Num*0.3f-L_Num*L_Per)) {
			D3DXMATRIX TmpMat;
			C_CarSmogManager L_CarSmogManager;
			D3DXVECTOR3 Vec = L_CarSmogManager.GetPos(player->GetBody().CarBodyNo);
			judg.SetTransMat(&TmpMat, &Vec);
			TmpMat = TmpMat * player->GetMatCar();
			S_Smog s = L_CarSmogManager.GetSmog(player->GetBody().CarBodyNo);
			if (L_Per < 0.3f)s.Draw_No = 53;
			if (L_Per < 0.2f)s.Draw_No = 50;
			if (L_Per < 0.1f)s.Draw_No = 47;
			Smog.push_back(new C_Smog(&TmpMat, &s));
		}
	}

	if (Smog.size() <= 0) return false;

	//スモッグのアップデート
	for (unsigned int s = 0; s < Smog.size(); s++) {
		Smog[s]->PosMoveVec(&player->GetMoveVec());

		if (Smog[s]->Update() == false) {
			delete Smog[s];
			Smog.erase(Smog.begin() + s);
			s--;
		}
	}

	return true;
}


BULLETJUDGDATA GameScene::GetInitBJD(const float * InitDis)
{
	BULLETJUDGDATA BJD;
	BJD.Type = -1;
	BJD.JudgNo1 = -1;
	BJD.JudgNo2 = -1;
	BJD.JudgNo3 = -1;
	BJD.SamllDis = *InitDis;
	return BJD;
}

void GameScene::BulletJudgGround(BULLETJUDGDATA * BJD, const RAYDATA *RD, bool *HitFlg, const float *Rad)
{
	//地面数
	if (ground.size() <= 0)return;

	float Dis;
	bool JudgFlg;

	if (HitFlg != nullptr) {
		*HitFlg = false;
	}

	for (unsigned int g = 0; g < ground.size(); g++) {
		if (judg.ball(RD->Mat, ground[g]->GetMat(), *Rad) == true) {//絞り込み
			JudgFlg = false;
			//レイ判定種類分け
			if (ground[g]->GetIdenFlg() == false) {
				//レイ判定
				if (judg.RayPolM(RD->Mat, ground[g]->GetVer(0), ground[g]->GetVer(1), ground[g]->GetVer(2), ground[g]->GetVer(3), ground[g]->GetMat(), RD->Ray, &Dis) == true) {
					JudgFlg = true;
					if (HitFlg != nullptr) {
						*HitFlg = true;
					}
				}
			}
			else {
				//レイ判定
				if (judg.RayPolM(RD->Mat, ground[g]->GetVer(0), ground[g]->GetVer(1), ground[g]->GetVer(2), ground[g]->GetVer(3), RD->Ray, &Dis) == true) {
					JudgFlg = true;
					if (HitFlg != nullptr) {
						*HitFlg = true;
					}
				}

			}
			if (JudgFlg == true) {//当たった時
				//レイが当たった時に弾の移動のVecの長さより短いか調べる
				if (Dis < BJD->SamllDis) {
					BJD->SamllDis = Dis;
					BJD->Type = co_Ground;
					BJD->JudgNo1 = g;
				}
			}
		}

		//壁判定
		for (int w = 0; w < 2; w++) {
			//二枚の壁判定
			bool LeftFlg = true;
			if (w == 1)LeftFlg = false;
			if (judg.ball(RD->Mat, ground[g]->GetWaMat(&LeftFlg, 0), *Rad) == true) {
				JudgFlg = false;
				//レイ判定
				if (judg.Mesh(judg.SetPosM(RD->Mat), RD->Ray, ground[g]->GetWaMat(&LeftFlg), ground[g]->GetColModWall(&LeftFlg), &Dis) == true) {
					if (HitFlg != nullptr) {
						*HitFlg = true;
					}
					//レイが当たった時に弾の移動のVecの長さより短いか調べる
					if (Dis < BJD->SamllDis) {
						BJD->SamllDis = Dis;
						BJD->Type = co_Wall;
						BJD->JudgNo1 = g;
						BJD->JudgNo2 = (unsigned int)w;
					}
				}
			}
		}
	}
	return;
}

void GameScene::BulletJudgPlayer(BULLETJUDGDATA * BJD, const RAYDATA * RD, const float *Rad)
{
	D3DXVECTOR3 BPos;//BulletPos
	judg.SetPosM(&BPos, RD->Mat);

	float Dis;

	if (judg.ball(RD->Mat, player->GetMatCar(), *Rad) == true) {//絞り込み
	//レイ判定
		//ボディ
		if (judg.Mesh(BPos, RD->Ray, player->GetDrawMatCar(), player->GetMeshCar(), &Dis) == true) {
			//レイが当たった時に弾の移動のVecの長さより短いか調べる
			if (Dis < BJD->SamllDis) {
				//短い時
				BJD->SamllDis = Dis;
				BJD->Type = co_PlayerCar;
			}
		}
		//パーツ
		if (player->GetPartsNum() > 0) {
			for (unsigned int p = 0; p < player->GetPartsNum(); p++) {
				//ボディ
				if (judg.Mesh(BPos, RD->Ray, player->GetPartsMat(&p), player->GetPartsData(&p).Mesh.DrawMesh.lpMesh, &Dis) == true) {
					//最大より小さいか
					if (Dis < BJD->SamllDis) {
						//短い時
						BJD->SamllDis = Dis;
						BJD->Type = co_PlayerParts;
						BJD->JudgNo1 = p;
					}
				}
			}
		}

	}
	return;
}

void GameScene::BulletJudgEnemy(BULLETJUDGDATA * BJD, const RAYDATA * RD, const float *Rad)
{
	if (enemy.size() <= 0)return;

	D3DXVECTOR3 BPos;
	judg.SetPosM(&BPos, RD->Mat);

	float Dis;

	//enemyの数
	for (unsigned int e = 0; e < enemy.size(); e++) {
		if (judg.ball(RD->Mat, enemy[e]->GetMatCar(), *Rad) == true) {//絞り込み
			//レイ判定
			//ボディ
			if (judg.Mesh(BPos, RD->Ray, enemy[e]->GetDrawMatCar(), enemy[e]->GetMeshCar(), &Dis) == true) {
				//最大より小さいか
				if (Dis < BJD->SamllDis) {
					BJD->SamllDis = Dis;
					BJD->Type = co_EnemyCar;
					BJD->JudgNo1 = e;
				}
			}
			//パーツ
			if (enemy[e]->GetPartsNum() > 0) {
				for (unsigned int p = 0; p < enemy[e]->GetPartsNum(); p++) {
					if (enemy[e]->GetPartsData(&p).MeshDrawFlg <= 0)continue;
					if (judg.Mesh(BPos, RD->Ray, enemy[e]->GetPartsMat(&p), enemy[e]->GetPartsData(&p).Mesh.DrawMesh.lpMesh, &Dis) != true) continue;
					//最大より小さいか
					if (Dis > BJD->SamllDis) continue;
					BJD->SamllDis = Dis;
					BJD->Type = co_EnemyParts;
					BJD->JudgNo1 = e;
					BJD->JudgNo2 = p;
				}
			}
			//銃
			if (enemy[e]->GetGunNum() > 0) {
				for (unsigned int g = 0; g < enemy[e]->GetGunNum(); g++) {
					if (enemy[e]->GetGunData(&g).Base.DrawFlg != true)continue;
					if (judg.Mesh(BPos, RD->Ray, enemy[e]->GetGunMat(&g), enemy[e]->GetGunData(&g).Mesh.lpMesh, &Dis) != true) continue;
					//最大より小さいか
					if (Dis > BJD->SamllDis) continue;
					BJD->SamllDis = Dis;
					BJD->Type = co_EnemyGun;
					BJD->JudgNo1 = e;
					BJD->JudgNo2 = g;
				}
			}

		}
	}
	return;
}

bool GameScene::SetBulletDamage(const BULLETJUDGDATA* BJD, const RAYDATA *RD, const int Damage)
{
	if (BJD->Type < 0)return false;

	//地面///////////////////////////////////////////////////////////////////////////////////
	//地面
	if (SetBulletDamageGround(BJD,RD) == true)return true;
	//壁
	if (SetBulletDamageWall(BJD, RD) == true)return true;

	//プレイヤー/////////////////////////////////////////////////////////////////////////////
	//車体
	if (SetBulletDamagePlaCar(&BJD->Type,&Damage) == true)return true;
	//標準パーツ
	if (SetBulletDamagePlaParts(&BJD->Type, &BJD->JudgNo1, &Damage) == true)return true;
	//銃
	if (SetBulletDamagePlaGun(&BJD->Type, &BJD->JudgNo1, &Damage) == true)return true;

	//エネミー//////////////////////////////////////////////////////////////////////////////
	//車体
	if (SetBulletDamageEneCar(&BJD->Type, &BJD->JudgNo1,&Damage) == true)return true;
	//標準パーツ
	if (SetBulletDamageEneParts(&BJD->Type, &BJD->JudgNo1, &BJD->JudgNo2, &Damage) == true)return true;
	//銃
	if (SetBulletDamageEneGun(&BJD->Type, &BJD->JudgNo1, &BJD->JudgNo2, &Damage) == true)return true;
	
	//当たっていない
	return false;
}

bool GameScene::SetBulletDamageGround(const BULLETJUDGDATA* BJD, const RAYDATA *RD)
{
	if (BJD->Type != co_Ground)return false;
	//火花
	D3DXVECTOR3 RayPos;
	RayPos = judg.SetPosM(RD->Mat) + RD->Ray * BJD->SamllDis;
	int SpeType = 0;
	float Ang = 0.0f;
	SparkV.push_back(new C_BulGro(&ground[BJD->JudgNo1]->GetMat(), &RayPos));
	//弾痕３D
	RayPos = judg.SetPosM(RD->Mat) + RD->Ray * (BJD->SamllDis - 0.01f);
	BHole3D.push_back(new C_BulHol3D(&ground[BJD->JudgNo1]->GetMat(), &RayPos, 2));
	
	return true;
}

bool GameScene::SetBulletDamageWall(const BULLETJUDGDATA* BJD, const RAYDATA *RD)
{
	if (BJD->Type != co_Wall)return false;
	//火花
	D3DXVECTOR3 RayPos;
	RayPos = judg.SetPosM(RD->Mat) + RD->Ray * BJD->SamllDis;
	int SpeType = 1;
	float Ang = 0.0f;
	bool BulWallFlg = true;
	if (BJD->JudgNo2 == 1)BulWallFlg = false;
	//火花
	for (int s = 0; s < 5; s++) {
		SparkV.push_back(new C_SparkDamage(&ground[BJD->JudgNo1]->GetWaMat(&BulWallFlg, 0), &RayPos, &SpeType, &Ang));
	}
	//弾痕３D
	RayPos = judg.SetPosM(RD->Mat) + RD->Ray * (BJD->SamllDis - 0.01f);
	BHole3D.push_back(new C_BulHol3D(&ground[BJD->JudgNo1]->GetWaMat(&BulWallFlg, 0), &RayPos, 1));
	return true;
}

bool GameScene::SetBulletDamagePlaCar(const int * BulletJudgFlg, const int * Damage)
{
	if (*BulletJudgFlg != co_PlayerCar)return false;

	if (player->SetHP(*Damage, false) == true) {
		//ダメージを受けた時
		int sc = -10;
		score->ScoreUp(&sc);
	}
	return true;
}

bool GameScene::SetBulletDamagePlaParts(const int * BulletJudgFlg, const unsigned int * HitMesh, const int * Damage)
{
	if (*BulletJudgFlg != co_PlayerParts)return false;

	if (player->SetDamageParts(HitMesh, Damage) == true) {

	}

	return true;
}

bool GameScene::SetBulletDamagePlaGun(const int * BulletJudgFlg, const unsigned int * HitMesh, const int * Damage)
{
	return false;
}

bool GameScene::SetBulletDamageEneCar(const int * BulletJudgFlg, const unsigned int * HitBodyNo, const int * Damage)
{
	if (*BulletJudgFlg != co_EnemyCar)return false;

	if (enemy[*HitBodyNo]->GetFlgCar() == false)return true;

	if (enemy[*HitBodyNo]->SetHP(*Damage, false) == true) {
		EnemyDelete(HitBodyNo);
	}

	return true;
}

bool GameScene::SetBulletDamageEneParts(const int * BulletJudgFlg, const unsigned int * HitBodyNo, const unsigned int * HitMesh, const int * Damage)
{
	if (*BulletJudgFlg != co_EnemyParts)return false;

	if (enemy[*HitBodyNo]->SetDamageParts(HitMesh, Damage) == true) {

	}

	return true;
}

bool GameScene::SetBulletDamageEneGun(const int * BulletJudgFlg, const unsigned int * HitBodyNo, const unsigned int * HitMesh, const int * Damage)
{
	if (*BulletJudgFlg != co_EnemyGun)return false;

	if (enemy[*HitBodyNo]->SetDamageGun(HitMesh, Damage) == true) {

	}

	return true;
}


