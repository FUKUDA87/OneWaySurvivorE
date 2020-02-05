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
#include"../EnemyData/Base&Manager/Enemy_Manager.h"
#include"../Const/Const_Phase_Type.h"
#include"../Const/Const_Rail_Type.h"

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

GameScene::GameScene(const int stageNum){
	AllNew();

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

	war = new Warning();

	pause = new Pause();

	//BulletBirthFlgを最初は出ないようにする
	BulletBirthFlg = false;

	//車の出現の初期化
	StageNo = stageNum;
	M_C_Car_Pop = new C_Car_Pop_New(&StageNo);

	CountNum = MaxCount = 1;
	spear = new Spear();
	D3DXMatrixTranslation(&SpeMat, 0.0f, 0.0f, 0.0f);


	//bgm初期化
	bgm->ChangeBgm(2);

	Size = 1.0f;

}
GameScene::~GameScene() {

	AllDelete();

	//メニューの削除
	DeleteMenu();
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
		}
	}

	player->Draw3DAll(&camera->GetPos());

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

	if (M_C_SmokeCar != nullptr) {
		M_C_SmokeCar->Draw3D_CS(&camera->GetPos());
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
	/*float f=0.0f;
	debugT->Draw2DF(f, 0, 0);*/
}
bool GameScene::Update(void) {

	if (Change_TitleScene() != true)return false;

	Update_Bgm();

	Update_Debug();

	mouse->Update();

	if (Update_Fade() != true)return false;

	Update_Game();

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
					delete enemy[e];
					enemy.erase(enemy.begin() + e);
					e--;
				}
			}
		}
		for (unsigned int e = 0; e < enemy.size(); e++) {
			EnemyDelete(&e);
		}
		for (unsigned int i = 0; i < enemy.size(); i++) {
			//if (enemy[i]->Get_Gun_Num() > 0) {
			//	for (unsigned int g = 0; g < enemy[i]->Get_Gun_Num(); g++) {
			//		if (enemy[i]->Get_Gun_Data(&g).Ray_Judg_Flg == true) {
			//			//レイ判定
			//			BULLETJUDGDATA b;
			//			b.SamllDis = enemy[i]->Get_Gun_Data(&g).RayDis;
			//			RAYDATA r;
			//			r.Mat = enemy[i]->Get_Gun_Data(&g).DrawBase.Mat;
			//			D3DXVec3TransformNormal(&r.Ray, &D3DXVECTOR3(0.0f, 0.0f, 1.0f), &r.Mat);
			//			float Rad = (float)RadChara*2.0f;
			//			BulletJudgPlayer(&b, &r, &Rad);
			//			bool Flg=false;
			//			if (b.Type > 0)Flg = true;

			//			enemy[i]->Set_Ray_Hit_Flg(&g, &Flg);
			//			enemy[i]->Set_Ray_Dis(&g, &b.SamllDis);
			//		}
			//	}
			//}

			

			if (enemy[i]->GetFlgCar() == true) {
				debugT->Update(true);

				//当たり判定（エネミーと弾）
				judgDeta jd;
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
		if (player->Get_BulletNum() <= 0)return;

		for (unsigned int b = 0; b < player->Get_BulletNum(); b++) {
			//初期化
			Dis = player->Get_Bullet_MoveDis(&b);
			Bullet = GetInitBJD(&Dis);

			BulletRay.Mat = player->Get_Bullet_Mat(&b);
			D3DXVec3TransformNormal(&BulletRay.Ray, &D3DXVECTOR3(0.0f, 0.0f, 1.0f), &BulletRay.Mat);

			//地面
			if (player->Get_Bullet_GroWal_Judg_Flg(&b) == true) {
				bool GroWalJudgFlg;
				BulletJudgGround(&Bullet, &BulletRay,&GroWalJudgFlg,&Rad);
				//次も壁と地面を判定できるかの代入
				player->Set_Bullet_GroWal_Judg_Flg(&b, &GroWalJudgFlg);
			}

			//敵
			BulletJudgEnemy(&Bullet, &BulletRay,&Rad);
			//敵の球パーツ判定
			BulletJudgEnemy_Ball(&Bullet, &BulletRay, &Rad);
			//判定結果と弾の削除
			if (SetBulletDamage(&Bullet, &BulletRay, player->Get_Bullet_Damage(&b)) == true)player->Delete_Bullet(&b);
		}
		//判定終了
		return;
	}
	//敵の弾判定
	if (*TypeCar == co_EnemyCar) {
		if (enemy[*No]->Get_BulletNum() <= 0)return;

		for (unsigned int b = 0; b < enemy[*No]->Get_BulletNum(); b++) {
			//初期化
			Dis = enemy[*No]->Get_Bullet_MoveDis(&b);
			Bullet = GetInitBJD(&Dis);

			BulletRay.Mat = enemy[*No]->Get_Bullet_Mat(&b);
			D3DXVec3TransformNormal(&BulletRay.Ray, &D3DXVECTOR3(0.0f, 0.0f, 1.0f), &BulletRay.Mat);

			//プレイヤー
			BulletJudgPlayer(&Bullet, &BulletRay,&Rad);
			//地面
			BulletJudgGround(&Bullet, &BulletRay,NULL,&Rad);
			//判定結果と弾の削除
			if (SetBulletDamage(&Bullet, &BulletRay, enemy[*No]->Get_Bullet_Damage(&b)) == true)enemy[*No]->Delete_Bullet(&b);
		}
		//判定終了
		return;
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
	if (Get_Car_Pop(&co_EnemyCar) == true) {
		//車の情報取得
		S_CAR_INIT_DATA L_Data = M_C_Car_Pop->Get_Next_Car_Data_N();

		//地面のナンバー
		unsigned int gNo;
		gNo = player->GetGroNum() + L_Data.GroundNo;
		//地面があるかの判定
		if (gNo < 0)gNo = 0;
		if (gNo > ground.size() - 1)gNo = ground.size() - 1;
		//車線を決める
		int Ground_Rail_Num = ground[gNo]->GetWay().RailNum;
		int RailNum = Get_Rail_Num(&Ground_Rail_Num, &L_Data.WayNo);
		//出現可能かどうか
		//if (enemy.size() <= 0) {
			//出現可能
			//enemyのナンバーを探す
		D3DXMATRIX GMat = ground[gNo]->GetWay().StartMat;
		if (EnemyBirth(&L_Data.CarNo, &GMat, &ground[gNo]->GetWay().CurTransX[RailNum]) == true) {
			unsigned int num;
			float dis;
			if (NowGroNum(enemy[(enemy.size() - 1)]->GetMatCar(), &num, &dis) == true) {
				enemy[(enemy.size() - 1)]->SetGroNum(num);
			}
			M_C_Car_Pop->Car_Init_Rear_N();
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
			int sc = 1000;
			score->ScoreUp(&sc);
			return true;
		}
	}
	return false;
}

bool GameScene::EnemyBirth(const int * EnemyNo, D3DXMATRIX * GroundMat,float * TransX)
{
	C_Enemy_Manager Manager;
	enemy.push_back(Manager.Get_Enemy(EnemyNo,*GroundMat,TransX));
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

		int StopNum=2;
		if (GroCou.size() == 0) {//地面の形成
			GroCou.push_back(new Cou(0, StopNum, 1, true, false));
		}
		if (cou->CouJudge() == false) cou->SetNum(0);

		const int L_Type=0;
		int L_Type2 = Init_Ground_Push(&Mat[1], &Mat[0], &L_Type);
		if(L_Type2>= 0) {
			if (M_C_Ground_Pop != nullptr) {
				M_C_Ground_Pop->Ground_Pop_Rear_N();
			}
			if (L_Type2 == 0) {
				cou->CouUpd();
			}
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

bool GameScene::Change_TitleScene(void)
{
	if (key.EscapeKey_F() == true) {
		sceneManager.changeScene(new TitleScene());
		return false;
	}
	return true;
}

void GameScene::AllNew(void)
{
	//煙
	M_C_SmokeCar = new C_SmokeCar();

	M_C_Ground_Pop = new C_Ground_Pop_New(1);
}

void GameScene::AllDelete(void)
{
	delete debugT;
	//地面の削除
	for (unsigned int i = 0; i < ground.size(); i++) {
		delete ground[i];
		ground.erase(ground.begin() + i); i--;
	}

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

	//火花の削除
	if (SparkV.size() > 0) {
		for (unsigned int s = 0; s < SparkV.size(); s++) {
			delete SparkV[s];
			SparkV.erase(SparkV.begin() + s);
			s--;
		}
	}

	//車の情報を削除
	if (M_C_Car_Pop != nullptr) {
		delete M_C_Car_Pop;
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
	if (M_C_SmokeCar != nullptr) {
		delete M_C_SmokeCar;
	}

	//地面の情報削除
	if (M_C_Ground_Pop != nullptr) {
		delete M_C_Ground_Pop;
	}
}

bool GameScene::Update_Bgm(void)
{
	//bgmのアップデート
	bool bFlg = true;
	bgm->Update(&bFlg);

	return true;
}

bool GameScene::Update_Debug(void)
{
	//フレーム数の操作

	if (GetAsyncKeyState('1') & 0x8000) {
		MaxCount += 1;
		if (MaxCount > 60)MaxCount = 60;
	}
	if (GetAsyncKeyState('2') & 0x8000) {
		MaxCount -= 1;
		if (MaxCount < 1)MaxCount = 1;
	}

	if (key.XKeyF() == true)player->SetHP(1);

	return true;
}

bool GameScene::Update_Fade(void)
{
	//フェードのアップデート
	if (fade->Update() == true) {
		//キーの無力化

	}
	else {
		if (fade->GetMoveEndFlg() == true) {
			if (SceneChangeFlg == true)return SetScene();
		}
	}

	return true;
}

bool GameScene::Update_Game(void)
{
	//ポーズ
	if (pause->GetDFlg() != false)return true;

	//ポーズ画面に移動の処理
	if (Update_Game_Pause() != true)return true;

	if (Judg_Game_Frame() != true)return true;
	
	Update_Ground();

	//車の情報の更新
	if (M_C_Car_Pop != nullptr) {
		bool MoveFlg = Get_Car_Pop_Update_MoveFlg();
		M_C_Car_Pop->Update(&MoveFlg);
	}

	//========================================
	//プレイヤー
	//========================================

	Update_Car_SetMat();

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

	//プレイヤーの横移動処理
	Update_Player_XTrans();

	//前進判定
	Update_Car_ForMove();


	//player======================================================================
	//playerの移動
	player->UpdateCarFM(ground);
	//移動ベクトルのサイズの初期化
	player->SetQuaVecSize(1.0f);
	//敵の移動
	UpdateEnemyMove();

	//横判定
	Update_Car_SideJudg();

	//最終Update
	//player->SetParts(camera->GetAngX(),camera->GetAngY());
	if (enemy.size() > 0) {
		for (unsigned int e = 0; e < enemy.size(); e++) {
			//if (enemy[e]->GetFlgCar() == true) {
				enemy[e]->SetParts(ground);
			//}
		}
	}

	//カメラの前方に向く処理
	Update_Camera_Car();
	//カメラのクォータニオンのアップデート
	camera->UpdateQua();

	//カーブの車体の角度を反映
	player->SetCurRotMat();

	//カメラ行列の取得
	Update_CameraMat();

	//playerのパーツ移動
	Update_Player();

	//カメラのアップデート
	unsigned int i = 0;
	D3DXMATRIX Mat = player->Get_Camera_Mat();
	camera->Update(Mat);
	//カメラと壁判定
	CameraWallJudg();

	//プレイヤーと地面判定2
	if (NowGroNum(player->GetMatCar(), &num, &Dis) == true) {
		player->SetGroNum(num);//地面の取得
		eneFlg = true;//敵の出現開始
	}

	//--------------------------------------------
	//車の動き完了後の処理
	//--------------------------------------------

	Update_Bullet();

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

	//空
	sky->Update(player->GetMatCar());

	Update_Explo();

	war->Update();

	Update_Spark();

	Update_CarSmoke();

	Update_Bullet_Hole();

	Update_Pop_End();

	return true;
}

bool GameScene::Update_Game_Pause(void)
{
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
				return false;
			}
		}
	}

	return true;
}

bool GameScene::Judg_Game_Frame(void)
{
	//スロー再生
	if (CountNum >= MaxCount) {
		CountNum = 1;
		return true;
	}
	else {
		CountNum += 1;
	}
	return false;
}

bool GameScene::Update_Ground(void)
{
	if (ground.size() < 1) return false;

	for (unsigned int i = 0; i < ground.size(); i++) {
		ground[i]->SuperUpdate();
		//無限の道の削除と作成
		GroundCreate(&i);
	}

	return true;
}

bool GameScene::Update_Explo(void)
{
	if (explo.size() < 1)return false;

	//爆発
	for (unsigned int i = 0; i < explo.size(); i++) {
		if (explo[i]->ExplUpdate(&camera->GetMat()) == false) {
			delete explo[i];
			explo.erase(explo.begin() + i);
			i--;
		}
	}

	return true;
}

bool GameScene::Update_Spark(void)
{
	//火花のアップデート
	if (SparkV.size() < 1) return false;

	for (unsigned int s = 0; s < SparkV.size(); s++) {
		if (SparkV[s]->UpdateSuper() == false) {
			//削除
			delete SparkV[s];
			SparkV.erase(SparkV.begin() + s);
			s--;
		}
	}

	return true;
}

bool GameScene::Update_CarSmoke(void)
{
	if (M_C_SmokeCar == nullptr) return false;

	//int CarNo = player->GetBody().CarBodyNo;
	//M_C_SmokeCar->Update_CS(&player->GetCharaBase(), &CarNo, &player->GetMatCar(), &player->GetMoveVec());

	return true;
}

bool GameScene::Update_Bullet_Hole(void)
{
	//弾痕３Dのアップデート
	if (BHole3D.size() < 1) return false;

	for (unsigned int b = 0; b < BHole3D.size(); b++) {
		if (BHole3D[b]->UpdateHol3D() == false) {
			delete BHole3D[b];
			BHole3D.erase(BHole3D.begin() + b);
			b--;
		}
	}

	return true;
}

bool GameScene::Update_Camera_Car(void)
{
	//カメラをplaeyrの前方に振り向かせるクォータニオンの初期化
	if (EndFlg != false) return false;
	//前方に振り向く計算
	if ((key.RClickF() != true) || (camera->GetQuaFlg() != false))return false;

	D3DXVECTOR3 cVec, ccVec, pVec, ppVec;
	D3DXVec3TransformNormal(&cVec, &D3DXVECTOR3(0.0f, 0.0f, 1.0f), &camera->GetMat());
	D3DXVec3TransformNormal(&pVec, &D3DXVECTOR3(0.0f, 0.0f, 1.0f), &player->GetMatCar());
	ccVec = cVec;
	ppVec = pVec;

	float Dot, Ang, FrameUp;

	//クォータニオンのフレーム数を計算
	Dot = D3DXVec3Dot(&pVec, &cVec);
	if (Dot > 1.0f)Dot = 1.0f;
	if (Dot < -1.0f)Dot = -1.0f;
	Ang = D3DXToDegree(acos(Dot));
	FrameUp = 1.0f / Ang * 6.0f;

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
	D3DXMATRIX Mat = player->GetMatCar();
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

	return true;
}

bool GameScene::Update_Player_Bullet(void)
{
	//照準のレイ判定
	S_RAY_HIT_JUDG_DATA Hit_Data;
	Hit_Data.Flg = false;

	BULLETJUDGDATA l_DisD;
	float Dis = 2000.0f;
	l_DisD = GetInitBJD(&Dis);
	RAYDATA l_RayR;
	l_RayR.Mat = judg.SetMatP(camera->GetPos());
	l_RayR.Ray = camera->GetVec();
	float Rad = (float)RadJudgF*2.0f;
	//敵のレイ判定
	BulletJudgEnemy(&l_DisD, &l_RayR, &Rad);
	if (l_DisD.Type > 0)Hit_Data.Flg = true;
	//照準の変化
	if (Hit_Data.Flg == true) {
		aiming->ChaFlg();
	}
	else {
		aiming->ResFlg();
	}
	//地面
	BulletJudgGround(&l_DisD, &l_RayR, NULL, &Rad);
	if (l_DisD.Type > 0)Hit_Data.Flg = true;
	//建物のレイ判定
	//バレットの出現処理
	if (Hit_Data.Flg == false) {
		player->Set_Gun_Ray_Data(&Hit_Data);
	}
	else {
		Hit_Data.Mat = judg.SetMatP(camera->GetPos() + l_RayR.Ray * l_DisD.SamllDis);
		player->Set_Gun_Ray_Data(&Hit_Data);
	}

	//================================================================================
	//弾
	//================================================================================

	//弾の誕生決め
	//BulletBirthFlg = GetBulletBirthFlg();
	////player弾のUpdate
	////player->GUpdateB(&BulletBirthFlg);
	//SoundCamera sc;
	//sc.CamPos = camera->GetPos();
	//sc.CamLook = camera->GetLook();
	//sc.CamHead = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	//bool KeyFlg = key.LClickF_N();
	//player->UpdateBulPla(&KeyFlg, &BulletBirthFlg, &sc);
	//BulletJudg(&co_PlayerCar, NULL);
	//player->UpdateBulletMove();
	//bool BBFlgB = player->GetBulBirFlgB();
	//SoundGun->Update(&BBFlgB);

	bool T_Flg = false;
	if (key.LClickF_N() == true) {
		T_Flg = true;
	}
	unsigned int GunNo = 0;

	player->Set_Gun_Trigger(&GunNo, &T_Flg);

	return true;
}

bool GameScene::Update_Car_ForMove(void)
{
	/*移動後の作成*/

	//移動後の変数
	D3DXMATRIX EndMat;
	D3DXVECTOR3 EndPos;

	//player
	//移動後の行列作成
	EndMat = ForMoveEnd(player->GetCon(), player->GetQuaForMove(), player->GetTransMatCar());
	player->SetForMoveEndMat(EndMat);
	//移動ベクトル計算
	D3DXMATRIX TransMat1, TransMat2, Trans;//両側のレイ発射位置
	D3DXVECTOR3 ScalPosB = player->GetScalPosCar();
	TransMat1 = judg.GetTransMatScal(&D3DXVECTOR3(player->GetCon().PosSmall.x, 0.0f, player->GetCon().PosBig.z), &ScalPosB);
	TransMat2 = judg.GetTransMatScal(&D3DXVECTOR3(player->GetCon().PosBig.x, 0.0f, player->GetCon().PosBig.z), &ScalPosB);
	Trans = judg.GetTransMatScal(&D3DXVECTOR3(0.0f, 0.0f, player->GetCon().PosBig.z), &ScalPosB);
	player->SetForMoveVec(judg.MatMatVec(TransMat1*player->GetMatCar(), TransMat1*player->GetForMoveEndMat()), 0);
	player->SetForMoveVec(judg.MatMatVec(Trans*player->GetMatCar(), Trans*player->GetForMoveEndMat()), 1);
	player->SetForMoveVec(judg.MatMatVec(TransMat2*player->GetMatCar(), TransMat2*player->GetForMoveEndMat()), 2);

	//enemy
	if (enemy.size() > 0) {//enemyの存在確認
		//enemyの数
		for (unsigned int e = 0; e < enemy.size(); e++) {
			if (enemy[e]->GetFlgCar() == true) {
				//移動後の行列作成
				EndMat = ForMoveEnd(enemy[e]->GetCon(), enemy[e]->GetQuaForMove(), enemy[e]->GetTransMatCar());
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
	/*移動後の作成完了*/


	/*当たり判定*/

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
		ForMoveJudg(player->GetCon(), player->GetDrawMatCar(), player->GetForMoveEndMat(), true, false, 0, player->GetForMoveVec(0), player->GetForMoveVec(1), player->GetForMoveVec(2), &Mul, &player->GetScalPosCar());
		//Mulを本体に入れる
		player->SetQuaVecSize(Mul);
		//最後の繰り返し以外
		if (i != MaxJudg - 1) {
			//新しい移動後を作成
			EndMat = ForMoveEnd(player->GetCon(), player->GetQuaForMove(), player->GetTransMatCar());
			player->SetForMoveEndMat(EndMat);
			//Mulの初期化
			player->SetQuaVecSize(1.0f);
		}

		//enemy
		if (enemy.size() > 0) {
			for (unsigned int e = 0; e < enemy.size(); e++) {
				if ((enemy[e]->GetFlgCar() == true) && (enemy[e]->GetSkyType() == false)) {
					//enemyのVecサイズ
					Mul = enemy[e]->GetCon().SpeedMulJudg;
					//判定
					ForMoveJudg(enemy[e]->GetCon(), enemy[e]->GetMatCar(), enemy[e]->GetForMoveEndMat(), false, true, e, enemy[e]->GetForMoveVec(0), enemy[e]->GetForMoveVec(1), enemy[e]->GetForMoveVec(2), &Mul, &enemy[e]->GetScalPosCar());
					//Mulを本体に入れる
					enemy[e]->SetQuaVecSize(Mul);
					//最後の繰り返し以外
					if (i != MaxJudg - 1) {
						//新しい移動後を作成
						EndMat = ForMoveEnd(enemy[e]->GetCon(), enemy[e]->GetQuaForMove(), enemy[e]->GetTransMatCar());
						enemy[e]->SetForMoveEndMat(EndMat);
						//Mulの初期化
						enemy[e]->SetQuaVecSize(1.0f);
					}
				}
			}
		}
	}
	/*当たり判定完了*/

	return true;
}

bool GameScene::Update_Car_SideJudg(void)
{
	//横判定
	WallJudg(true, true, false, 0);
	WallJudg(false, true, false, 0);

	if (enemy.size() <1) return true;

	for (unsigned int e = 0; e < enemy.size(); e++) {
		if ((enemy[e]->GetFlgCar() == true) && (enemy[e]->GetSkyType() == false)) {
			WallJudg(true, false, true, e);
			WallJudg(false, false, true, e);
		}
	}

	return true;
}

bool GameScene::Update_Player_XTrans(void)
{
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

	return true;
}

bool GameScene::Update_Player(void)
{

	if (player->UpdateAll(&camera->GetMat()) != false)return true;
	
	Set_Game_Over();

	return false;
}

bool GameScene::Update_Car_SetMat(void)
{
	if (player != nullptr) {
		player->SetCarMoveMat();
	}

	if (enemy.size() > 0) {
		for (auto && e : enemy) {
			e->SetCarMoveMat();
		}
	}


	return true;
}

bool GameScene::Update_CameraMat(void)
{
	player->Set_CameraMat(&camera->GetMat());

	return true;
}

int GameScene::Init_Ground_Push(const D3DXMATRIX * Mat1, const D3DXMATRIX * Mat0, const int * Type)
{
	S_GROUND_INIT_DATA L_Data = M_C_Ground_Pop->Get_Pop_Data_N();

	if ((cou->GetNum() == 1) && (L_Data.gType == Co_Ground_Type_Straight)) {
		ground.push_back(new BillBase(*Mat1, *Mat0, L_Data.gType, L_Data.Ang, L_Data.Length, L_Data.LengthAuto));
		return L_Data.gType;
	}
	else {
		ground.push_back(new Bill(*Mat1, *Mat0, L_Data.gType, L_Data.Ang, L_Data.Length, L_Data.LengthAuto));
		return L_Data.gType;
	}
	return 0;
}

bool GameScene::Update_Pop_End(void)
{
	if (M_C_Car_Pop == nullptr) return false;

	if (EndFlg == true) return false;

	//現在の生存している敵数の調査
	int Num = 0;

	if (enemy.size() > 0) {
		for (auto && e : enemy) {
			if (e->GetFlgCar() == true)Num++;
		}
	}

	M_C_Car_Pop->Set_Now_Enemy_Num_N(&Num);

	Set_Ground_Data();

	if (M_C_Car_Pop->Get_Change_Class_EndFlg() == true) {
		if (M_C_Car_Pop->Get_Stage_Phase_Data_N().Phase_Type == Co_Phase_Type_Boss) {
			war->SetFlg(true);
			return true;
		}
	}
	
	//Popの終了確認処理
	if (M_C_Car_Pop->Get_Stage_Phase_Data_N().Phase_Type == Co_Phase_Type_End) {
		Set_Game_Clear();
		return false;
	}

	return true;
}

bool GameScene::Get_Car_Pop(const int * Car_Type)
{
	//ゲーム終了Flg
	if (EndFlg == true)return false;

	//プレイヤーが地面Noの取得Flg
	if (eneFlg != true)return false;

	//出現させる車の情報
	if (M_C_Car_Pop == nullptr)return false;

	if (M_C_Car_Pop->Get_Car_Pop_Flg_N() != true)return false;

	if (M_C_Car_Pop->Get_Next_Car_Data_N().CarType != *Car_Type)return false;

	//出現可能
	return true;
}

bool GameScene::Get_Car_Pop_Update_MoveFlg(void)
{
	if (EndFlg == true)return false;

	if (war->GetFlg() == true)return false;

	return true;
}

void GameScene::Set_Ground_Data(void)
{
	if (M_C_Ground_Pop == nullptr)return;

	if (M_C_Car_Pop == nullptr)return;

	int No = M_C_Car_Pop->Get_GroundNo();

	if (No == M_C_Ground_Pop->Get_GroundNo()) return;
	
	M_C_Ground_Pop->New_Pop(&No);
}

void GameScene::Set_Game_Over(void)
{
	if (EndFlg == true)return;

	//playerが死んだときの処理
	BombInit(&player->GetMatCar());
	EndFlg = true;
	GaOv->Update(false, EndFlg);
	for (unsigned int e = 0; e < enemy.size(); e++) {
		enemy[e]->SetPlaEnd(true/*, player->GetSpeedCar()*/);
	}
	player->SetSpeedCar(player->GetSpeedCar()*0.0f);
	war->SetFlg(false);
	//メニューの表示
	SetMenu(false, false, true);
}

void GameScene::Set_Game_Clear(void)
{
	if (EndFlg == true)return;

	EndFlg = true;
	GaOv->Update(true, EndFlg);
	SetMenu(false, true, false);
}

bool GameScene::Update_Bullet(void)
{
	//弾のMoveVecの加算
	Update_Bullet_MoveVec();

	//弾の出現準備
	Update_Player_Bullet();
	Update_Bullet_Enemy_Init();

	//弾の出現
	Update_Bullet_Init();

	//弾の判定
	Update_Bullet_Judg();

	//弾の更新
	Update_Bullet_Move();

	return true;
}

bool GameScene::Update_Bullet_MoveVec(void)
{
	if (player != nullptr) {
		player->MoveVec_Bullet();
	}

	if (enemy.size() < 1)return true;

	for (auto && e : enemy) {
		e->MoveVec_Bullet();
	}

	return true;
}

bool GameScene::Update_Bullet_Enemy_Init(void)
{
	if (enemy.size() < 1)return true;

	for (unsigned int i = 0; i < enemy.size(); i++) {
		if (enemy[i]->Get_Gun_Num() > 0) {
			for (unsigned int g = 0; g < enemy[i]->Get_Gun_Num(); g++) {
				if (enemy[i]->Get_Gun_Data(&g).Ray_Judg_Flg == true) {
					//レイ判定
					BULLETJUDGDATA b;
					b.SamllDis = enemy[i]->Get_Gun_Data(&g).RayDis;
					RAYDATA r;
					r.Mat = enemy[i]->Get_Gun_Data(&g).DrawBase.Mat;
					D3DXVec3TransformNormal(&r.Ray, &D3DXVECTOR3(0.0f, 0.0f, 1.0f), &r.Mat);
					float Rad = (float)RadChara*2.0f;
					BulletJudgPlayer(&b, &r, &Rad);
					bool Flg = false;
					if (b.Type > 0)Flg = true;

					enemy[i]->Set_Ray_Hit_Flg(&g, &Flg);
					enemy[i]->Set_Ray_Dis(&g, &b.SamllDis);
				}
			}
		}
	}

	return true;
}

bool GameScene::Update_Bullet_Init(void)
{
	if (player != nullptr) {
		player->Init_Bullet();
	}

	if (enemy.size() < 1)return true;

	for (auto && e : enemy) {
		e->Init_Bullet();
	}

	return true;
}

bool GameScene::Update_Bullet_Judg(void)
{
	if (player != nullptr) {
		BulletJudg(&co_PlayerCar, NULL);
	}

	if (enemy.size() < 1)return true;

	for (unsigned int e = 0; e < enemy.size(); e++) {
		BulletJudg(&co_EnemyCar, &e);
	}

	return true;
}

bool GameScene::Update_Bullet_Move(void)
{
	if (player != nullptr) {
		player->Update_Bullet();
	}

	if (enemy.size() < 1)return true;

	for (auto && e : enemy) {
		e->Update_Bullet();
	}

	return true;
}

int GameScene::Get_Rail_Num(const int * Way_Rail_Num, const int * Pop_Rail_Num)
{
	int No = *Pop_Rail_Num;

	if (No == Co_Rail_Type_Random) {
		No = rand() % (*Way_Rail_Num);
		return No;
	}

	if (No < 0)No = 0;
	if (No >= *Way_Rail_Num)No = (*Way_Rail_Num) - 1;

	return No;
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
		//if (player->GetPartsNum() > 0) {
		//	for (unsigned int p = 0; p < player->GetPartsNum(); p++) {
		//		//ボディ
		//		if (judg.Mesh(BPos, RD->Ray, player->GetPartsMat(&p), player->GetPartsData(&p).Mesh.DrawMesh.lpMesh, &Dis) == true) {
		//			//最大より小さいか
		//			if (Dis < BJD->SamllDis) {
		//				//短い時
		//				BJD->SamllDis = Dis;
		//				BJD->Type = co_PlayerParts;
		//				BJD->JudgNo1 = p;
		//			}
		//		}
		//	}
		//}

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
			if (enemy[e]->Get_Car_Parts_Num() > 0) {
				for (unsigned int p = 0; p < enemy[e]->Get_Car_Parts_Num(); p++) {
					//if (enemy[e]->GetPartsData(&p).MeshDrawFlg <= 0)continue;
					if (enemy[e]->Get_Parts_Draw_Draw_JudgFlg(&p) == Co_Draw_Mesh) {
						if (judg.Mesh(BPos, RD->Ray, enemy[e]->Get_Parts_Draw_DrawMat(&p)
							, enemy[e]->Get_Parts_Draw_Mesh(&p), &Dis) == true) {
							//最大より小さいか
							if (Dis < BJD->SamllDis) {
								BJD->SamllDis = Dis;
								BJD->Type = co_EnemyParts;
								BJD->JudgNo1 = e;
								BJD->JudgNo2 = p;
							}
						}
					}
					if (enemy[e]->Get_Parts_Draw_Draw_JudgFlg(&p) == Co_Draw_Pol) {
						int a = 0, b = 1, c = 2, d = 3;
						if (judg.RayPolM(RD->Mat, enemy[e]->Get_Parts_Draw_Pol_Pos(&p, &a), enemy[e]->Get_Parts_Draw_Pol_Pos(&p, &b)
							, enemy[e]->Get_Parts_Draw_Pol_Pos(&p, &c), enemy[e]->Get_Parts_Draw_Pol_Pos(&p, &d)
							, enemy[e]->Get_Parts_Draw_DrawMat(&p), RD->Ray, &Dis) == true) {
							//最大より小さいか
							if (Dis < BJD->SamllDis) {
								BJD->SamllDis = Dis;
								BJD->Type = co_EnemyParts;
								BJD->JudgNo1 = e;
								BJD->JudgNo2 = p;
							}
						}
					}
				}
			}
			//銃
			if (enemy[e]->Get_Gun_Num() > 0) {
				for (unsigned int g = 0; g < enemy[e]->Get_Gun_Num(); g++) {
					//if (enemy[e]->GetGunData(&g).Base.DrawFlg != true)continue;
					if (enemy[e]->Ray_Judg_Gun_Flg(&g) == true) {
						if (enemy[e]->Get_Gun_Draw_Parts_Num(&g) > 0) {
							for (unsigned int g_p = 0; g_p < enemy[e]->Get_Gun_Draw_Parts_Num(&g); g_p++) {
								if (enemy[e]->Get_Gun_Draw_Parts_Draw_JudgFlg(&g, &g_p) == Co_Draw_Mesh) {
									if (judg.Mesh(BPos, RD->Ray, enemy[e]->Get_Gun_Draw_Parts_Draw_Mat(&g, &g_p)
										, enemy[e]->Get_Gun_Draw_Parts_Mesh(&g, &g_p), &Dis) == true) {
										//最大より小さいか
										if (Dis < BJD->SamllDis) {
											BJD->SamllDis = Dis;
											BJD->Type = co_EnemyGun;
											BJD->JudgNo1 = e;
											BJD->JudgNo2 = g;
											BJD->JudgNo3 = g_p;
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
	return;
}

void GameScene::BulletJudgEnemy_Ball(BULLETJUDGDATA * BJD, const RAYDATA * RD, const float * Rad)
{
	if (enemy.size() <= 0)return;

	D3DXVECTOR3 BPos;
	judg.SetPosM(&BPos, RD->Mat);

	//enemyの数
	for (unsigned int e = 0; e < enemy.size(); e++) {
		if (judg.ball(RD->Mat, enemy[e]->GetMatCar(), *Rad) == true) {//絞り込み

			//パーツ
			if (enemy[e]->Get_Car_Parts_Num() > 0) {
				for (unsigned int p = 0; p < enemy[e]->Get_Car_Parts_Num(); p++) {

					if (enemy[e]->Get_Parts_Draw_Draw_JudgFlg(&p) == Co_Draw_Ball) {
						if (judg.ball(BPos, enemy[e]->Get_Parts_Draw_DrawMat(&p), enemy[e]->Get_Parts_Draw_Dis(&p)) == true) {
							//最大より小さいか
							BJD->Type = co_EnemyParts;
							BJD->JudgNo1 = e;
							BJD->JudgNo2 = p;
						}
					}

				}
			}

		}
	}
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
	if (SetBulletDamagePlaCar(BJD,&Damage) == true)return true;
	//標準パーツ
	if (SetBulletDamagePlaParts(BJD, &Damage) == true)return true;
	//銃
	if (SetBulletDamagePlaGun(BJD, &Damage) == true)return true;

	//エネミー//////////////////////////////////////////////////////////////////////////////
	//車体
	if (SetBulletDamageEneCar(BJD,&Damage) == true)return true;
	//標準パーツ
	if (SetBulletDamageEneParts(BJD, &Damage) == true)return true;
	//銃
	if (SetBulletDamageEneGun(BJD, &Damage) == true)return true;
	
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

bool GameScene::SetBulletDamagePlaCar(const BULLETJUDGDATA* BJD, const int * Damage)
{
	if (BJD->Type != co_PlayerCar)return false;

	if (player->SetHP(*Damage, false) == true) {
		//ダメージを受けた時
		int sc = -10;
		score->ScoreUp(&sc);
	}
	return true;
}

bool GameScene::SetBulletDamagePlaParts(const BULLETJUDGDATA* BJD, const int * Damage)
{
	if (BJD->Type != co_PlayerParts)return false;

	/*if (player->SetDamageParts(HitMesh, Damage) == true) {

	}*/

	return true;
}

bool GameScene::SetBulletDamagePlaGun(const BULLETJUDGDATA* BJD, const int * Damage)
{
	return false;
}

bool GameScene::SetBulletDamageEneCar(const BULLETJUDGDATA* BJD, const int * Damage)
{
	if (BJD->Type != co_EnemyCar)return false;

	if (enemy[BJD->JudgNo1]->GetFlgCar() == false)return true;

	if (enemy[BJD->JudgNo1]->SetHP(*Damage, false) == true) {
		EnemyDelete(&BJD->JudgNo1);
	}

	return true;
}

bool GameScene::SetBulletDamageEneParts(const BULLETJUDGDATA* BJD, const int * Damage)
{
	if (BJD->Type != co_EnemyParts)return false;

	enemy[BJD->JudgNo1]->Damage_CarParts(&BJD->JudgNo2, Damage);

	return true;
}

bool GameScene::SetBulletDamageEneGun(const BULLETJUDGDATA* BJD, const int * Damage)
{
	if (BJD->Type != co_EnemyGun)return false;

	enemy[BJD->JudgNo1]->Damage_Gun(&BJD->JudgNo2, Damage);

	return true;
}


