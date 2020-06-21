#include"GameScene.h"
#include"TitleScene.h"
#include"StageSelectScene.h"
#include"SceneManager.h"
#include"../GameSource/Enum.h"
#include"../MaterialManager/TextureManager.h"
#include"../MaterialManager/XfileManager.h"
#include"../GameSource/Motion.h"
#include"../Draw3DBase/Draw3DManager/CarSmogManager.h"
#include"../EnemyData/Base&Manager/Enemy_Manager.h"
#include"../Const/Const_Wave_Type.h"
#include"../Const/Const_Rail_Type.h"
#include"../Const/Const_Stage_Type.h"
#include"../GameSource/StructClass/Struct_Init.h"
#include"../Gun/Bullet/Const_Bullet_No.h"
#include"../GameSource/GameSystem.h"
#include"../Fade/Fade.h"

extern int CountManager;
extern Motion motion;
extern TextureManager textureManager;
extern XFileManager xfileManager;
extern SceneManager sceneManager;
extern LPDIRECT3DDEVICE9		lpD3DDevice;	// Direct3DDeviceインターフェイス
extern LPD3DXSPRITE lpSprite;	// スプライト
extern LPD3DXFONT lpFont;		// フォント
extern C_Fade fade;

#define	SCRW		1280	// ウィンドウ幅（Width
#define	SCRH		720		// ウィンドウ高さ（Height
#define RadJudgF 100
#define StageSelectNo 2
#define GameNo 3
#define TitleNo 1

GameScene::GameScene(const int stageNum)
{

	StageNo = stageNum;
	AllNew();

}
GameScene::GameScene(const int stageNum, const bool * DebugFlg)
{
	StageNo = stageNum;

	if (*DebugFlg == true)StageNo = Co_Stage_Type_Debug;

	AllNew();

	if (*DebugFlg != true)return;

	if (player != nullptr) {
		unsigned int i = 0;
		player->Set_Gun_Bullet_No(&i, &Co_Bullet_No99);
	}
}
GameScene::~GameScene() {

	AllDelete();

	//メニューの削除
	if (Menu != nullptr)delete Menu;
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
			SparkV[s]->Draw3DSuper(&camera->GetPos());
		}
	}

}
void GameScene::Render3D_Screen(void)
{
	if (M_S_Screen.DrawFlg != true)return;

	lpD3DDevice->SetRenderTarget(0, M_S_Screen.lpTmpBackBuffer);
	lpD3DDevice->SetDepthStencilSurface(M_S_Screen.lpTmpZBuffer);
	D3DVIEWPORT9 Viewport;
	Viewport.X = 0;
	Viewport.Y = 0;
	Viewport.Width = 1280 / 2;
	Viewport.Height = 720 / 2;
	Viewport.MinZ = 0;
	Viewport.MaxZ = 1;
	lpD3DDevice->SetViewport(&Viewport);
	// バックバッファと Z バッファをクリア
	lpD3DDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 255), 1.0f, 0);
	//    バックバッファ　　　Zバックバッファ

	D3DXMATRIX mView, mProj;

	//カメラの位置の行列作成
	D3DXMATRIX CamMat;
	D3DXMatrixTranslation(&CamMat, 45.0f, 50.0f, -1.0f);
	CamMat = CamMat * player->GetCon().JudgMat;

	D3DXMATRIX L_CameraLook_Mat = player->GetCon().JudgMat;

	// 視点行列の設定
	D3DXMatrixLookAtLH(&mView,
		&judg.SetPosM(&CamMat),	// カメラの位置
		&judg.SetPosM(&L_CameraLook_Mat) ,	// カメラの視点
		&D3DXVECTOR3(0.0f, 1.0f, 0.0f)	// カメラの頭の方向
	);

	// 投影行列の設定
	D3DXMatrixPerspectiveFovLH(&mProj, D3DXToRadian(60), (float)SCRW / (float)SCRH, 0.1f, 600.0f);

	//行列設定
	lpD3DDevice->SetTransform(D3DTS_VIEW, &mView);
	lpD3DDevice->SetTransform(D3DTS_PROJECTION, &mProj);

	Render3D();
	lpD3DDevice->SetRenderTarget(0, M_S_Screen.lpBackBuffer);
	lpD3DDevice->SetDepthStencilSurface(M_S_Screen.lpZBuffer);
}
void GameScene::Render2D(void) {
	//////////////////////////////////////////////////
	///	スプライトの描画処理
	//////////////////////////////////////////////////
	// 描画開始
	lpSprite->Begin(D3DXSPRITE_ALPHABLEND);

	if (M_Damage_Num_Draw.size() > 0) {
		for (auto && v : M_Damage_Num_Draw) {
			v->Draw_2D();
		}
	}

	if (enemy.size() > 0) {
		for (unsigned int i = 0; i < enemy.size(); i++) {
			enemy[i]->Draw2DAll();
		}
	}

	aiming->Draw();
	player->Draw2DAll();

	Debug_Screen_Draw();

	//スコアの表示
	score->Draw2D();
	//クリアとオーバーの表示
	if (M_C_Game_End != nullptr) {
		M_C_Game_End->Draw_2D();
	}
	//ボス出現表示
	war->Draw2D();

	//ポーズの表示
	pause->Draw();

	//メニューの表示
	if (Menu != nullptr)Menu->Draw2DAll();

	//フェードインアウトの表示
	fade.Draw();
	mouse->Draw2D();
	// 描画終了
	lpSprite->End();

	//デバック用の文字表示
	Debug_Text();
}
bool GameScene::Update(void) {

	if (Change_TitleScene() != true)return false;

	Update_Sound();

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

			if (enemy[e]->GetFlgCar() != true) continue;

			//enemyと地面判定
			unsigned int num;
			float dis;
			C_GameSystem gameSystem;
			if (gameSystem.JudgNowGround(&num, &dis, enemy[e]->GetMatCar(), ground) == true) {
				enemy[e]->SetGroNum(&num);
			}
			else {
				delete enemy[e];
				enemy.erase(enemy.begin() + e);
				e--;
			}
			
		}
		for (unsigned int e = 0; e < enemy.size(); e++) {
			EnemyDelete(&e);
		}
		for (unsigned int i = 0; i < enemy.size(); i++) {

			if (enemy[i]->GetDeleFlg() != false)continue;

			float L_Radius = 400.0f;

			if (judg.BallJudg(&judg.SetPosM(&enemy[i]->GetMatCar()), &judg.SetPosM(&player->GetMatCar()), &L_Radius) != false) continue;

			delete enemy[i];
			enemy.erase(enemy.begin() + i);
			i--;
			
		}
	}
	if (Get_End_Flg() == true) {
		return true;
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

	//Pos2Dのした準備
	D3DVIEWPORT9 Viewport;
	lpD3DDevice->GetViewport(&Viewport);
	//Pos2Dを使う
	Pos2DUpdate(&mProj, &mView, &Viewport);

	FrustumCulling(&mProj, &mView, &Viewport);

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
			Bullet.Character_Type = co_PlayerCar;

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
			BulletJudgEnemy(&Bullet, &BulletRay,&Rad,nullptr);
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
			Bullet.Character_Type = co_EnemyCar;

			BulletRay.Mat = enemy[*No]->Get_Bullet_Mat(&b);
			D3DXVec3TransformNormal(&BulletRay.Ray, &D3DXVECTOR3(0.0f, 0.0f, 1.0f), &BulletRay.Mat);

			//プレイヤー
			BulletJudgPlayer(&Bullet, &BulletRay,&Rad);
			//地面
			if (enemy[*No]->Get_Bullet_GroWal_Judg_Flg(&b) == true) {
				bool GroWalJudgFlg;
				BulletJudgGround(&Bullet, &BulletRay, &GroWalJudgFlg, &Rad);
				//次も壁と地面を判定できるかの代入
				enemy[*No]->Set_Bullet_GroWal_Judg_Flg(&b, &GroWalJudgFlg);
			}
			//敵
			BulletJudgEnemy(&Bullet, &BulletRay, &Rad,No);
			//判定結果と弾の削除
			if (SetBulletDamage(&Bullet, &BulletRay, enemy[*No]->Get_Bullet_Damage(&b)) == true)enemy[*No]->Delete_Bullet(&b);
		}
		//判定終了
		return;
	}

}

void GameScene::Side_Judg(const int * Car_Type, const unsigned int * Car_No)
{
	//左
	bool Left_Flg = true;
	Side_Judg(&Left_Flg, Car_Type, Car_No);

	//右
	Left_Flg = false;
	Side_Judg(&Left_Flg, Car_Type, Car_No);
}

bool GameScene::Side_Judg(const bool * Left_Flg, const int * Car_Type, const unsigned int * Car_No)
{
	//判定する車の情報
	S_SideJudgChara Judg_Car;
	Judg_Car.LeftFlg = *Left_Flg;
	Judg_Car.Car_Type = *Car_Type;
	if (Car_No !=nullptr) Judg_Car.No = *Car_No;

	//車の判定のレイの数(前、中間、後)
	int L_JudgNum = 3;

	//
	D3DXMATRIX *L_JudgMat = new D3DXMATRIX[L_JudgNum];

	//当たったレイの番号
	int Ray_Hit_No;

	//当たった行列
	D3DXMATRIX Ray_Hit_Mat;

	//壁に当たってから火花を出さないFlg
	bool Spark_Init_Flg = true;

	//20回まで横判定する
	for (int f_c = 0; f_c < 20;f_c++) {

		/*判定の準備*/

		//次に判定する車の情報
		S_SideJudgChara Next_Car;

		Next_Car.JudgeType = Co_Judge_YES;

		//判定用レイ
		D3DXVECTOR3 JudgVec;

		//レイ判定のtrueCar数
		int CountCar = 0;

		//判定用レイの距離、追い出し用のレイの長さ
		float SmallDis,L_Over_Dis;

		//車の追い出し判定の確認
		bool L_OverFlg = false;

		//レイ判定の準備ができなかった場合、横の衝突判定を終了させる
		if (SideJudg_Preparation(&Judg_Car, L_JudgMat, &JudgVec, &SmallDis,&L_Over_Dis, &L_JudgNum) != true)break;


		/*レイ判定*/

		//player判定
		CountCar += Side_Judg_Player(&Next_Car, &SmallDis, &Ray_Hit_No, &Ray_Hit_Mat,
			&L_Over_Dis, &L_OverFlg, &Judg_Car, &L_JudgNum, L_JudgMat, &JudgVec);

		//enemy判定
		CountCar += Side_Judg_Enemy(&Next_Car, &SmallDis, &Ray_Hit_No, &Ray_Hit_Mat,
			&L_Over_Dis, &L_OverFlg, &Judg_Car, &L_JudgNum, L_JudgMat, &JudgVec);

		//壁判定
		bool WallJudgFlg = Side_Judg_Ground(&Judg_Car, &L_JudgMat[Const_Middle], &JudgVec,
			&SmallDis, &Ray_Hit_No, &Ray_Hit_Mat);


		/*レイ判定後の処理*/

		//全てのレイ判定終了後
		//足りない長さの計算
		float RadDis = Judg_Car.Rad;
		if (RadDis < 0.0f)RadDis *= -1.0f;
		if ((L_OverFlg == true) && (WallJudgFlg != true) && (CountCar < 2))SmallDis = L_Over_Dis;
		RadDis = RadDis - SmallDis;
		//反対方向にする
		if (Judg_Car.LeftFlg == false) RadDis *= -1.0f;
		//今当たり判定している車をずらす
		D3DXMATRIX Trans2;
		D3DXMatrixTranslation(&Trans2, RadDis, 0.0f, 0.0f);
		//反映用行列
		D3DXMATRIX TmpMat;

		//壁に当たった時
		if (WallJudgFlg == true) {
			switch (Judg_Car.Car_Type)
			{
			case Hit_Type_Player:
				TmpMat = Trans2 * (player->GetTransMatCar());
				player->SetTransMatCar(&TmpMat);
				TmpMat = player->GetTransMatCar()*player->GetCon().JudgMat;
				player->SetMatCar(&TmpMat);
				break;
			case Hit_Type_Enemy:
				TmpMat = Trans2 * (enemy[Judg_Car.No]->GetTransMatCar());
				enemy[Judg_Car.No]->SetTransMatCar(&TmpMat);
				TmpMat = enemy[Judg_Car.No]->GetTransMatCar()*enemy[Judg_Car.No]->GetCon().JudgMat;
				enemy[Judg_Car.No]->SetMatCar(&TmpMat);
				//Hpを削る処理
				if (Spark_Init_Flg == true) {
					enemy[Judg_Car.No]->SetHP(1, true);
					unsigned int eNo = Judg_Car.No;
					EnemyDelete(&eNo);
				}
				break;
			}


			//レイの座標
			D3DXVECTOR3 Ray_Pos = judg.SetPosM(&L_JudgMat[Ray_Hit_No]) + JudgVec * (SmallDis - 0.1f);

			//火花を出す処理
			Wall_Spark_Init(&Spark_Init_Flg, &Ray_Hit_Mat, &Ray_Pos, &Judg_Car.LeftFlg);

			continue;
		}
		
		//複数に当たった時、もしくは当たった車がボスだった場合
		if ((CountCar >= 2)||(Next_Car.JudgeType==Co_Judge_BOSS)) {
			//今当たり判定している車
			switch (Judg_Car.Car_Type)
			{
			case Hit_Type_Player:
				TmpMat = Trans2 * (player->GetTransMatCar());
				player->SetTransMatCar(&TmpMat);
				TmpMat = player->GetTransMatCar()*player->GetCon().JudgMat;
				player->SetMatCar(&TmpMat);
				break;
			case Hit_Type_Enemy:
				TmpMat = Trans2 * (enemy[Judg_Car.No]->GetTransMatCar());
				enemy[Judg_Car.No]->SetTransMatCar(&TmpMat);
				TmpMat = enemy[Judg_Car.No]->GetTransMatCar()*enemy[Judg_Car.No]->GetCon().JudgMat;
				enemy[Judg_Car.No]->SetMatCar(&TmpMat);
				break;
			}
			//リバース
			judg.ReverseFlg(&Judg_Car.LeftFlg);

			continue;
		}

		//ボディ内でレイ判定した場合の処理
		if (L_OverFlg == true) {

			//押し出す
			D3DXMatrixTranslation(&Trans2, RadDis*-1.0f, 0.0f, 0.0f);

			//今当たり判定している車
			switch (Judg_Car.Car_Type)
			{
			case Hit_Type_Player:
				TmpMat = Trans2 * (player->GetTransMatCar());
				player->SetTransMatCar(&TmpMat);
				TmpMat = player->GetTransMatCar()*player->GetCon().JudgMat;
				player->SetMatCar(&TmpMat);
				break;
			case Hit_Type_Enemy:
				TmpMat = Trans2 * (enemy[Judg_Car.No]->GetTransMatCar());
				enemy[Judg_Car.No]->SetTransMatCar(&TmpMat);
				TmpMat = enemy[Judg_Car.No]->GetTransMatCar()*enemy[Judg_Car.No]->GetCon().JudgMat;
				enemy[Judg_Car.No]->SetMatCar(&TmpMat);
				break;
			}
			continue;
		}
			
		//1車のみ当たった時
		if (CountCar == 1) {
			//押し出す
			D3DXMatrixTranslation(&Trans2, RadDis*-1.0f, 0.0f, 0.0f);
			//当たった車判定
			Judg_Car.Car_Type = Next_Car.Car_Type;
			Judg_Car.No = Next_Car.No;

			//当たった車
			switch (Judg_Car.Car_Type)
			{
			case Hit_Type_Player://プレイヤー
				TmpMat = Trans2 * (player->GetTransMatCar());
				player->SetTransMatCar(&TmpMat);
				TmpMat = player->GetTransMatCar()*player->GetCon().JudgMat;
				player->SetMatCar(&TmpMat);
				//Hpを削る処理
				/*if (Spark_Init_Flg==true) {
					player->SetHP(1,true);
				}*/
				break;
			case Hit_Type_Enemy://敵
				enemy[Judg_Car.No]->SetTransMatCar(&judg.GetMatY(&Trans2, &enemy[Judg_Car.No]->GetTransMatCar()));
				TmpMat = enemy[Judg_Car.No]->GetCon().JudgMat;
				enemy[Judg_Car.No]->SetMatCar(&judg.GetMatY(&enemy[Judg_Car.No]->GetTransMatCar(), &TmpMat));

				//衝突による敵のAiと銃をStopさせる
				Enemy_Stop(&Judg_Car.No, Car_Type);

				//Hpを削る処理
				if (Spark_Init_Flg == true) {
					enemy[Judg_Car.No]->SetHP(1, true);
					unsigned int eNo = Judg_Car.No;
					EnemyDelete(&eNo);
				}

				break;

			}

			//レイの座標
			D3DXVECTOR3 Ray_Pos = judg.SetPosM(&L_JudgMat[Ray_Hit_No]) + JudgVec * (SmallDis - 0.1f);

			//火花を出せる判定
			Car_Spark_Init(&Spark_Init_Flg, &Ray_Hit_Mat, &Ray_Pos);

			continue;
		}
				
		//当たっていない時
		break;
		
	}

	//解放
	if (L_JudgMat != nullptr)delete[] L_JudgMat;

	return true;
	
}

bool GameScene::UpdateEnemyAI(void)
{
	//エネミーの出現
	Pop_Enemy();

	//出現している敵の数がゼロの場合に地面判定をしない
	if (enemy.size() <= 0) return false;

	//地面判定
	for (unsigned int e = 0; e < enemy.size(); e++) {
		//enemyと地面判定
		unsigned int num;
		float dis;
		C_GameSystem gameSystem;
		if (gameSystem.JudgNowGround(&num, &dis, enemy[e]->GetMatCar(), ground) == true) {
			enemy[e]->SetGroNum(&num);
		}
		else {
			if (Get_End_Flg() == true) {
				delete enemy[e];
				enemy.erase(enemy.begin() + e);
				e--;
			}
		}
	}

	//出現している敵の数がゼロの場合にAIの処理をしない
	if (enemy.size() <= 0) return false;

	/*Aiの動作準備*/

	//プレイヤー側の情報の作成
	CHARAData*Data;
	int ChaNum = 0;
	ChaNum += 1;
	Data = new CHARAData[ChaNum];
	Data[0] = player->GetData();

	/*Aiの動作処理*/

	for (unsigned int i = 0; i < enemy.size(); i++) {

		//全ての戦闘終了Flg
		bool L_EndFlg = Get_End_Flg();

		//Aiの動作処理
		enemy[i]->UpdateAi(Data, &ChaNum, ground, &L_EndFlg);

	}

	//情報の削除
	if (Data != nullptr)delete Data;

	return true;
}

bool GameScene::UpdateEnemyMove(void)
{
	if (enemy.size() <= 0) return false;

	float L_ResetSize = 1.0f;

	for (unsigned int i = 0; i < enemy.size(); i++) {
		enemy[i]->UpdateAll(ground);//Update
		//移動ベクトルのサイズの初期化
		enemy[i]->SetQuaVecSize(&L_ResetSize);
	}

	return false;
}

bool GameScene::ForMoveJudg(const CONSTITUTION * Con, const D3DXMATRIX * StartMat, const D3DXMATRIX * EndMat,
	const int * Car_Type, const unsigned int * Car_No, const D3DXVECTOR3 * RayVec1, const D3DXVECTOR3 * RayVec2,
	const D3DXVECTOR3 * RayVec3, float * SpeedMul2, const D3DXVECTOR3 * ScalPos, const bool *CollisionJudg_TrueFlg)
{
	//車のvectorナンバー
	unsigned int L_Car_No = 0;

	if (Car_No != nullptr)L_Car_No = *Car_No;

	int VecNum = 3;

	D3DXVECTOR3 *MoveVec = new D3DXVECTOR3[VecNum];//移動ベクトル
	float *VecSize = new float[VecNum];//ベクトルの長さ

	MoveVec[0] = *RayVec1;
	MoveVec[1] = *RayVec2;
	MoveVec[2] = *RayVec3;

	for (int i = 0; i < VecNum; i++) {
		VecSize[i] = D3DXVec3Length(&MoveVec[i]);
		if (VecSize[i] < 0.0f)VecSize[i] *= -1.0f;
		VecSize[i] += 0.1f;
		D3DXVec3Normalize(&MoveVec[i], &MoveVec[i]);//移動ベクトルの正規化
	}

	//真ん中とサイドのレイ発射位置
	D3DXMATRIX *TransMat=new D3DXMATRIX[VecNum];

	TransMat[0] = judg.GetTransMatScal(&D3DXVECTOR3(Con->PosSmall.x, 0.0f, Con->PosBig.z), ScalPos);
	TransMat[1] = judg.GetTransMatScal(&D3DXVECTOR3(Con->PosBig.x, 0.0f, Con->PosBig.z), ScalPos);
	TransMat[2] = judg.GetTransMatScal(&D3DXVECTOR3(0.0f, 0.0f, Con->PosBig.z), ScalPos);

	TransMat[0] = TransMat[0] * (*StartMat);
	TransMat[1] = TransMat[1] * (*StartMat);
	TransMat[2] = TransMat[2] * (*StartMat);

	//レイの長さと最小
	float Dis, *SmallDis = new float[VecNum];

	for (int i = 0; i < VecNum; i++) SmallDis[i] = VecSize[i];

	bool *JudgFlg = new bool[VecNum];

	for (int i = 0; i < VecNum; i++) JudgFlg[i] = false;

	int L_Hit_CarType;
	unsigned int L_Hit_CarNumber;

	//player判定
	M_ForMoveJudg_Player(JudgFlg, SmallDis, &L_Hit_CarType, &L_Hit_CarNumber, Car_Type, StartMat,
		EndMat, TransMat, &VecNum, MoveVec,&Con->PosBig, &Con->PosSmall, ScalPos, CollisionJudg_TrueFlg);

	//敵判定
	M_ForMoveJudg_Enemy(JudgFlg, SmallDis, &L_Hit_CarType, &L_Hit_CarNumber, Car_Type, &L_Car_No, StartMat,
		EndMat, TransMat, &VecNum, MoveVec, &Con->PosBig, &Con->PosSmall, ScalPos, CollisionJudg_TrueFlg);
	
	//レイが当たった
	if ((JudgFlg[0] == true) || (JudgFlg[1] == true) || (JudgFlg[2] == true)) {
		for (int i = 0; i < VecNum; i++) {
			SmallDis[i] = (VecSize[i]) / (VecSize[1])*((SmallDis[i]) / (VecSize[i]));
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


		//衝突した車の死亡確認
		if (Get_Dead_Flg(&L_Hit_CarType, &L_Hit_CarNumber) == true) {

			//判定してる車を死亡させる
			M_Dead_Car(Car_Type, &L_Car_No);

		}


	}

	/*メモリの解放*/

	if (TransMat != nullptr)delete[] TransMat;

	if (MoveVec != nullptr)delete[] MoveVec;

	if (VecSize != nullptr)delete[] VecSize;

	if (SmallDis != nullptr)delete[] SmallDis;

	if (JudgFlg != nullptr)delete[] JudgFlg;

	return true;
}

void GameScene::ForMoveEnd(D3DXMATRIX * Mat, const CONSTITUTION * Con, const QuaForMove * q, const D3DXMATRIX * TransMat)
{
	QuaForMove  L_q = *q;

	motion.Formove(&L_q, Con, ground);

	*Mat = *TransMat * L_q.NowMat;
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

			float L_Radius = (float)RadJudgF;

			//範囲絞り込み
			if (judg.BallJudg(&camera->GetPos(), &judg.SetPosM(&ground[g]->GetMat()), &L_Radius) != true) continue;
			
			//範囲内
			//左フラグ
			bool LeftFlg = true;
			//壁の数
			for (int w = 0; w < ground[g]->Get_Wall_Num(); w++) {
				//壁の内側を見せないための拡大行列
				D3DXMATRIX ScalY;
				D3DXMatrixScaling(&ScalY, 1.3f, 1.0f, 1.0f);
				//レイ判定
				if (judg.RayJudg_Mesh(&camera->GetLook(), &Vec, &(ScalY*ground[g]->Get_DrawMat_Wall(&w)), ground[g]->GetColModWall(), &Dis) == true) {
					//当たった
					if (Dis < SmallDis) {
						SmallDis = Dis;
						JudgFlg = true;
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
}

bool GameScene::GetBulletBirthFlg(void)
{
	if (Get_End_Flg() == true)return false;
	if ((key.LClickF_N() == true) && (BulletBirthFlg == false))return false;
	return true;
}

void GameScene::BombInit(const D3DXMATRIX * Mat)
{
	explo.push_back(new Explo(Mat));
	New_Sound(&Co_Sound_Category_Explosion, 1, &judg.SetPosM(Mat), &Co_Sound_New);
	return;
}

bool GameScene::EnemyDelete(const unsigned int * EnemyNo)
{
	if ((*EnemyNo < 0) || (*EnemyNo > enemy.size() - 1))return false;

	if (enemy[*EnemyNo]->GetFlgCar() == false) {
		if (enemy[*EnemyNo]->GetDeadFlg() == false) {
			enemy[*EnemyNo]->SetDeadFlg(true);

			//死亡した敵がボスなら他の敵のHPをゼロにする
			if ((enemy[*EnemyNo]->Get_BossFlg() == true) && (enemy.size() > 0)) {
				int L_Hp = 0;
				for (auto && e : enemy)e->SetNowHp(&L_Hp);
			}

			BombInit(&enemy[*EnemyNo]->GetMatCar());
			int sc = 1000;
			score->ScoreUp(&sc);
			return true;
		}
	}
	return false;
}

void GameScene::SetMenu(bool PauseFlg, bool ClearFlg, bool OverFlg)
{
	//ポーズ------------------------------------
	if (PauseFlg == true) {
		
		if (Menu != nullptr)delete Menu;

		Menu=new C_PauseTouch();
		return;
	}
	//ステージクリア---------------------------------------
	if (ClearFlg == true) {
		
		if (Menu != nullptr)delete Menu;

		Menu = new C_ClearTouch();
		return;
	}
	//ゲームオーバー---------------------------------------
	if (OverFlg == true) {
		
		if (Menu != nullptr)delete Menu;

		Menu = new C_OverTouch();
		return;
	}

	return;
}

bool GameScene::UpdateMenu(void)
{
	if (Menu==nullptr)return false;

	int Touch = Menu->Touch();

	if (Touch > 0) {
		//mouse->SetTouchFlg();
	}
	else {
		return false;
	}

	if (fade.GetMoveFlg() != false)return false;

	if (key.LClickF() != true)return false;

	// タイトルを押しす処理
	if (Touch == co_TitleScene) {
		fade.SetNextScene(co_TitleScene, true);
		return true;
	}

	// セレクトを押す処理
	if (Touch == co_StageSelectScene) {
		fade.SetNextScene(co_StageSelectScene, true);
		return true;
	}

	// リトライを押しす処理
	if (Touch == co_GameScene) {
		bool DebugFlg = false;
		if (StageNo == Co_Stage_Type_Debug)DebugFlg = true;
		fade.SetNextStageNo(StageNo);
		fade.SetNextStageNo(&DebugFlg);
		fade.SetNextScene(co_GameScene, true);
		return true;
	}

	// プレイを押す処理
	if (Touch == co_PlayGame) {
		pause->SetDFlg(false);
		mouse->Init();
		mouse->ChaDrawFlg(false);
		pause->SetStaSavFlg(false);
		if (M_C_Sound_Manager != nullptr) {

			S_OptionData l_OptionData = option->GetOptionData();

			M_C_Sound_Manager->Restart(&l_OptionData.BGMVolume);
		}

		//メニュー削除
		if (Menu != nullptr)delete Menu;
		Menu = new C_NextTouch();

		return true;
	}

	return true;
}

bool GameScene::GroundCreate(unsigned int *GNo)
{
	float L_Radius = player->GetRadF();

	if (judg.BallJudg(&judg.SetPosM(&player->GetMatCar()), &judg.SetPosM(&ground[*GNo]->GetMat()), &L_Radius) == false) {

		if (player->GetCon().GroNum < *GNo)return false;
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
		if (LightCount->Update() == true) ground[ground.size() - 1]->Init_Light();
	


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

	if (M_Damage_Num_Draw.size() > 0) {
		D3DXVECTOR3 Pos3D,Pos2D;
		Judg L_judg;
		for (auto && v : M_Damage_Num_Draw) {

			D3DXMATRIX L_JudgMat = player->GetCon().JudgMat;

			Pos3D = v->Get_Pos_3D(&L_JudgMat);
			L_judg.Pos2D(&Pos2D, &Pos3D, mProj, mView, Viewport);
			v->Set_Pos_2D(&Pos2D);
		}
	}

	if (enemy.size() <= 0)return;
	for (unsigned int e = 0; e < enemy.size(); e++) {
		//矢印計算
		enemy[e]->GetPos2DSet(mProj, mView, Viewport,&camera->GetPos());
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
	// フェードインの開始
	fade.StartFadein();

	Debug_Screen_Init();

	if(M_Text_Num==nullptr)M_Text_Num = new C_Text_Num();

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
	ground.push_back(new C_Ground_Object(&i));
	z = (int)ground[0]->GetPosZ() * 2;
	i = (int)player->GetRadF() / z;
	delete ground[0];
	ground.erase(ground.begin() + 0);
	for (int n = i * (-1); n < i; n++) {
		if (cou->CouJudge() == false) {
			cou->SetNum(0);
		}
		ground.push_back(new C_Ground_Object(&n));

		if (cou->GetNum() == 1) ground[ground.size() - 1]->Init_Bill();
		
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
	// 地面の当たり判定
	C_GameSystem gameSystem;
	if (gameSystem.JudgNowGround(&num, &Dis,player->GetMatCar(),ground) == true) {
		player->SetGroNum(&num);//地面の取得
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
	M_C_Game_End = new C_Game_End_Now();

	key.Init();

	war = new Warning();

	pause = new Pause();

	//BulletBirthFlgを最初は出ないようにする
	BulletBirthFlg = false;

	//車の出現の初期化
	M_C_Car_Pop = new C_Car_Pop_New(&StageNo);

	CountNum = MaxCount = 1;
	spear = new Spear();
	D3DXMatrixTranslation(&SpeMat, 0.0f, 0.0f, 0.0f);

	M_C_Ground_Pop = new C_Ground_Pop_New(1);

	//サウンドの初期化
	if (M_C_Sound_Manager == nullptr)M_C_Sound_Manager = new c_GameSoundManager();

	New_Sound(&Co_Sound_Type_2D, &Co_Sound_Category_BGM, 1, &Co_Sound_Change);

	// オプションのインスタンス化
	option = new C_Option();
	option->Read();
}

void GameScene::AllDelete(void)
{
	Debug_Screen_End();

	if(M_Text_Num!=nullptr)delete M_Text_Num;

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
	
	if (M_C_Game_End != nullptr) {
		delete M_C_Game_End;
	}

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

	//地面の情報削除
	if (M_C_Ground_Pop != nullptr) {
		delete M_C_Ground_Pop;
	}

	//音の管理の削除
	if (M_C_Sound_Manager != nullptr) {
		M_C_Sound_Manager->Reset();
		delete M_C_Sound_Manager;
	}

	if (M_Damage_Num_Draw.size() > 0) {
		for (unsigned int v = 0; v < M_Damage_Num_Draw.size(); v++) {
			Delete_Damage_Num_Draw(&v);
		}
	}

	// オプションの削除
	option->Write();
	if (option != nullptr) delete option;
}

bool GameScene::Update_Debug(void)
{
	/*if (StageNo != Co_Stage_Type_Debug)return true;*/

	//フレーム数の操作

	/*if (GetAsyncKeyState('1') & 0x8000) {
		MaxCount += 1;
		if (MaxCount > 60)MaxCount = 60;
	}
	if (GetAsyncKeyState('2') & 0x8000) {
		MaxCount -= 1;
		if (MaxCount < 1)MaxCount = 1;
	}*/

	if (key.Num1_Key_F())judg.ReverseFlg(&M_S_Screen.DrawFlg);

	if (key.XKeyF() == true)player->SetHP(1);

	return true;
}

bool GameScene::Update_Fade(void)
{
	//フェードのアップデート
	if (fade.Update() == true) {
		//キーの無力化
		key.SetFlg(true);
	}
	else {
		if (fade.GetMoveEndFlg() == true) {
			sceneManager.changeScene(fade.GetNextScene());
			return false;
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
	if (Get_End_Flg() == false) {
		if (fade.GetMoveFlg() == false) {
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
	C_GameSystem gameSystem;
	if (gameSystem.JudgNowGround(&num, &Dis, player->GetMatCar(), ground) == true) {
		player->SetGroNum(&num);//地面の取得
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

	float L_ResetSize = 1.0f;

	//移動ベクトルのサイズの初期化
	player->SetQuaVecSize(&L_ResetSize);
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
	if (gameSystem.JudgNowGround(&num, &Dis, player->GetMatCar(), ground) == true) {
		player->SetGroNum(&num);//地面の取得
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
		if (Get_End_Flg() == false) {
			Geme_End_Change(&Co_Stage_End_Clear);
			SetMenu(false, true, false);
		}
	}

	//空
	sky->Update(&player->GetMatCar());

	Update_Explo();

	Update_Damage_Num_Draw();

	war->Update();

	Update_Spark();

	Update_Bullet_Hole();

	Update_Pop_End();

	return true;
}

bool GameScene::Update_Game_Pause(void)
{
	//終わった時
	if (Get_End_Flg() == true) {
		mouse->ChaDrawFlg(true);
	}
	else {
		//ポーズ
		if (key.RETURNKeyF() == true) {
			if (pause->GetDFlg() == false) {
				pause->SetDFlg(true);
				mouse->ChaDrawFlg(true);
				//ロードの許可
				if ((GetAsyncKeyState('8') & 0x8000) && (GetAsyncKeyState('9') & 0x8000) && (GetAsyncKeyState('0') & 0x8000)) {
					pause->SetStaSavFlg(true);
				}
				SetMenu(true, false, false);

				if (M_C_Sound_Manager != nullptr) {
					M_C_Sound_Manager->Stop();
				}

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

		if (explo[i]->ExplUpdate(&camera->GetMat()) != false) continue;

		delete explo[i];
		explo.erase(explo.begin() + i);
		i--;
		
	}

	return true;
}

bool GameScene::Update_Spark(void)
{
	//火花のアップデート
	if (SparkV.size() < 1) return false;

	for (unsigned int s = 0; s < SparkV.size(); s++) {

		if (SparkV[s]->UpdateSuper() != false) continue;
		
		//削除
		delete SparkV[s];
		SparkV.erase(SparkV.begin() + s);
		s--;

	}

	return true;
}

bool GameScene::Update_Bullet_Hole(void)
{
	//弾痕３Dのアップデート
	if (BHole3D.size() < 1) return false;

	for (unsigned int b = 0; b < BHole3D.size(); b++) {

		if (BHole3D[b]->UpdateHol3D() != false) continue;
		
		delete BHole3D[b];
		BHole3D.erase(BHole3D.begin() + b);
		b--;

	}

	return true;
}

bool GameScene::Update_Camera_Car(void)
{
	//カメラをplaeyrの前方に振り向かせるクォータニオンの初期化
	if (Get_End_Flg() != false) return false;
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
	l_RayR.Mat = judg.SetMatP(&camera->GetPos());
	l_RayR.Ray = camera->GetVec();
	float Rad = 400.0f;
	//敵のレイ判定
	unsigned int EnemyNo = -1;
	BulletJudgEnemy(&l_DisD, &l_RayR, &Rad,&EnemyNo);
	if (l_DisD.Type > 0)Hit_Data.Flg = true;
	//照準の変化
	if (Hit_Data.Flg == true) {
		aiming->ChaFlg();
	}
	else {
		aiming->ResFlg();
	}
	//地面
	BulletJudgGround(&l_DisD, &l_RayR, nullptr, &Rad);
	if (l_DisD.Type > 0)Hit_Data.Flg = true;
	//建物のレイ判定
	//バレットの出現処理
	if (Hit_Data.Flg == false) {
		player->Set_Gun_Ray_Data(&Hit_Data);
	}
	else {

		//レイが当たった座標
		D3DXVECTOR3 Ray_Hit_Pos;

		//レイが当たった座標を求める
		judg.Get_Ray_Pos3D(&Ray_Hit_Pos, &camera->GetPos(), &l_RayR.Ray, &l_DisD.SamllDis);

		//レイが当たった座標を行列に変換
		Hit_Data.Mat = judg.SetMatP(&Ray_Hit_Pos);

		player->Set_Gun_Ray_Data(&Hit_Data);
	}

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
	ForMoveEnd(&EndMat, &player->GetCon(), &player->GetQuaForMove(), &player->GetTransMatCar());
	player->SetForMoveEndMat(&EndMat);
	//移動ベクトル計算
	D3DXMATRIX TransMat1, TransMat2, Trans;//両側のレイ発射位置
	D3DXVECTOR3 ScalPosB = player->GetScalPosCar();
	TransMat1 = judg.GetTransMatScal(&D3DXVECTOR3(player->GetCon().PosSmall.x, 0.0f, player->GetCon().PosBig.z), &ScalPosB);
	TransMat2 = judg.GetTransMatScal(&D3DXVECTOR3(player->GetCon().PosBig.x, 0.0f, player->GetCon().PosBig.z), &ScalPosB);
	Trans = judg.GetTransMatScal(&D3DXVECTOR3(0.0f, 0.0f, player->GetCon().PosBig.z), &ScalPosB);
	player->SetForMoveVec(&judg.MatMatVec(TransMat1*player->GetMatCar(), TransMat1*player->GetForMoveEndMat()), &Const_Left);
	player->SetForMoveVec(&judg.MatMatVec(Trans*player->GetMatCar(), Trans*player->GetForMoveEndMat()), &Const_Middle);
	player->SetForMoveVec(&judg.MatMatVec(TransMat2*player->GetMatCar(), TransMat2*player->GetForMoveEndMat()), &Const_Right);

	//enemy
	if (enemy.size() > 0) {//enemyの存在確認
		//enemyの数
		for (unsigned int e = 0; e < enemy.size(); e++) {
			//移動後の行列作成
			ForMoveEnd(&EndMat, &enemy[e]->GetCon(), &enemy[e]->GetQuaForMove(), &enemy[e]->GetTransMatCar());
			enemy[e]->SetForMoveEndMat(&EndMat);
			//移動ベクトル計算
			D3DXMATRIX TransMat1, TransMat2, Trans;//両側のレイ発射位置
			ScalPosB = enemy[e]->GetScalPosCar();

			TransMat1 = judg.GetTransMatScal(&D3DXVECTOR3(enemy[e]->GetCon().PosSmall.x, 0.0f, enemy[e]->GetCon().PosBig.z), &ScalPosB);
			TransMat2 = judg.GetTransMatScal(&D3DXVECTOR3(enemy[e]->GetCon().PosBig.x, 0.0f, enemy[e]->GetCon().PosBig.z), &ScalPosB);
			Trans = judg.GetTransMatScal(&D3DXVECTOR3(0.0f, 0.0f, enemy[e]->GetCon().PosBig.z), &ScalPosB);

			enemy[e]->SetForMoveVec(&judg.MatMatVec(TransMat1*enemy[e]->GetMatCar(), TransMat1*enemy[e]->GetForMoveEndMat()), &Const_Left);
			enemy[e]->SetForMoveVec(&judg.MatMatVec(Trans*enemy[e]->GetMatCar(), Trans*enemy[e]->GetForMoveEndMat()), &Const_Middle);
			enemy[e]->SetForMoveVec(&judg.MatMatVec(TransMat2*enemy[e]->GetMatCar(), TransMat2*enemy[e]->GetForMoveEndMat()), &Const_Right);

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
		Mul = player->GetQuaForMove().SpeedMulJudg;

		bool L_CollisionJudg_TrueFlg = player->Get_CollisionJudg_TrueFlg();

		//判定
		ForMoveJudg(&player->GetCon(), &player->GetDrawMatCar(), &player->GetForMoveEndMat(),&Hit_Type_Player,nullptr,
			&player->GetForMoveVec(&Const_Left), &player->GetForMoveVec(&Const_Middle), &player->GetForMoveVec(&Const_Right), &Mul,
			&player->GetScalPosCar(),&L_CollisionJudg_TrueFlg);
		//Mulを本体に入れる
		player->SetQuaVecSize(&Mul);
		//最後の繰り返し以外
		if (i != MaxJudg - 1) {
			//新しい移動後を作成
			ForMoveEnd(&EndMat, &player->GetCon(), &player->GetQuaForMove(), &player->GetTransMatCar());
			player->SetForMoveEndMat(&EndMat);

			float L_ResetSize = 1.0f;

			//Mulの初期化
			player->SetQuaVecSize(&L_ResetSize);
		}

		//enemy
		if (enemy.size() > 0) {
			for (unsigned int e = 0; e < enemy.size(); e++) {

				if (enemy[e]->Get_JudgeType() == Co_Judge_NO)continue;

				//enemyのVecサイズ
				Mul = enemy[e]->GetQuaForMove().SpeedMulJudg;

				L_CollisionJudg_TrueFlg = enemy[e]->Get_CollisionJudg_TrueFlg();

				//判定
				ForMoveJudg(&enemy[e]->GetCon(), &enemy[e]->GetMatCar(), &enemy[e]->GetForMoveEndMat(), &Hit_Type_Enemy, &e,
					&enemy[e]->GetForMoveVec(&Const_Left), &enemy[e]->GetForMoveVec(&Const_Middle), &enemy[e]->GetForMoveVec(&Const_Right), &Mul,
					&enemy[e]->GetScalPosCar(),&L_CollisionJudg_TrueFlg);
				//Mulを本体に入れる
				enemy[e]->SetQuaVecSize(&Mul);
				//最後の繰り返し以外
				if (i != MaxJudg - 1) {
					//新しい移動後を作成
					ForMoveEnd(&EndMat, &enemy[e]->GetCon(), &enemy[e]->GetQuaForMove(), &enemy[e]->GetTransMatCar());
					enemy[e]->SetForMoveEndMat(&EndMat);

					float L_ResetSize = 1.0f;

					//Mulの初期化
					enemy[e]->SetQuaVecSize(&L_ResetSize);
				}
			}
		}
	}

	/*当たり判定完了*/

	return true;
}

bool GameScene::Update_Car_SideJudg(void)
{
	//プレイヤーの横判定
	if (player != nullptr) {
		Side_Judg(&Hit_Type_Player,nullptr);
	}

	//敵の横判定
	if (enemy.size() <1) return true;
	
	for (unsigned int e = 0; e < enemy.size(); e++) {
		if (enemy[e]->Get_JudgeType() != Co_Judge_NO) Side_Judg(&Hit_Type_Enemy, &e);
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

	if (Get_End_Flg() != true) {

		if ((key.AKey() == true)) {
			D3DXMATRIX Trans;
			D3DXMatrixTranslation(&Trans, -1.0f*0.08f, 0.0f, 0.0f);
			Trans = Trans * player->GetTransMatCar();
			player->SetTransMatCar(&Trans);
			Trans = player->GetTransMatCar()*player->GetCon().JudgMat;
			player->SetMatCar(&Trans);
			//横判定
			bool LeftFlg = true;
			Side_Judg(&LeftFlg, &Hit_Type_Player, nullptr);
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
			bool LeftFlg = false;
			Side_Judg(&LeftFlg, &Hit_Type_Player, nullptr);
			//カーブ
			player->SetRodAngY(0.3f, true);
			LRKeyFlg = true;
		}

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

	ground.push_back(new C_Ground_Object(Mat1, Mat0, &L_Data));

	if ((cou->GetNum() == 1) && (L_Data.gType == Co_Ground_Type_Straight)) ground[ground.size() - 1]->Init_Bill();

	return L_Data.gType;
}

bool GameScene::Update_Pop_End(void)
{
	if (M_C_Car_Pop == nullptr) return false;

	if (Get_End_Flg() == true) return false;

	//現在の生存している敵数の調査
	int Num = 0;

	if (enemy.size() > 0) {

		for (auto && e : enemy) if (e->GetFlgCar() == true)Num++;

	}

	M_C_Car_Pop->Set_Now_Enemy_Num_N(&Num);

	//出現している車から車の出現の変更
	M_Car_Pop_Data_Update();

	Set_Ground_Data();

	if (M_C_Car_Pop->Get_Change_Class_EndFlg() == true) {
		if (M_C_Car_Pop->Get_Now_Wave_Data_N().WaveType_Now == Co_Wave_Type_Boss) {
			war->SetFlg(true);
			New_Sound(&Co_Sound_Type_2D, &Co_Sound_Category_BGM, 1, &Co_Sound_Delete);
			New_Sound(&Co_Sound_Type_2D, &Co_Sound_Category_Warning, 1, &Co_Sound_New);
			war->New_Sound_Data_Change_No(&Co_Sound_Type_2D, &Co_Sound_Category_BGM, 4, &Co_Sound_Change);
			return true;
		}
		if (M_C_Car_Pop->Get_Now_Wave_Data_N().WaveType_Now == Co_Wave_Type_Normal) {
			New_Sound(&Co_Sound_Type_2D, &Co_Sound_Category_BGM, 1, &Co_Sound_Change);
			return true;
		}
	}
	
	//Popの終了確認処理
	if (M_C_Car_Pop->Get_Now_Wave_Data_N().WaveType_Now == Co_Wave_Type_End) {

		//ゲームクリア状態にする
		Set_Game_Clear();

		return false;
	}

	return true;
}

bool GameScene::Get_Car_Pop(const int * Car_Type)
{
	//ゲーム終了Flg
	if (Get_End_Flg() == true)return false;

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
	if (Get_End_Flg() == true)return false;

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
	if (Get_End_Flg() == true)return;

	//playerが死んだときの処理
	BombInit(&player->GetMatCar());
	
	Geme_End_Change(&Co_Stage_End_Over);

	for (unsigned int e = 0; e < enemy.size(); e++) {
		enemy[e]->SetPlaEnd(true/*, player->GetSpeedCar()*/);
	}
	player->SetSpeedCar(&(player->GetCon().Speed *0.0f));
	war->SetFlg(false);
	//メニューの表示
	SetMenu(false, false, true);
}

void GameScene::Set_Game_Clear(void)
{
	if (Get_End_Flg() == true)return;

	Geme_End_Change(&Co_Stage_End_Clear);
	SetMenu(false, true, false);
	New_Sound(&Co_Sound_Type_2D, &Co_Sound_Category_BGM, 5, &Co_Sound_Change);
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

		if (enemy[i]->Get_Gun_Num() <= 0) continue;

		for (unsigned int g = 0; g < enemy[i]->Get_Gun_Num(); g++) {

			if (enemy[i]->Get_Gun_Data(&g).Ray_Judg_Flg != true) continue;

			//レイ判定
			BULLETJUDGDATA b;
			b.SamllDis = enemy[i]->Get_Gun_Data(&g).RayDis;
			RAYDATA r;
			r.Mat = enemy[i]->Get_Gun_Data(&g).DrawBase.Mat;
			D3DXVec3TransformNormal(&r.Ray, &D3DXVECTOR3(0.0f, 0.0f, 1.0f), &r.Mat);
			float Rad = (float)RadChara*2.0f;

			//レイ判定
			BulletJudgPlayer(&b, &r, &Rad);
			BulletJudgEnemy(&b, &r, &Rad,&i);

			//レイが当たった時のFlg
			bool Ray_HitFlg = false;
			if (b.Type > 0)Ray_HitFlg = true;

			enemy[i]->Set_Ray_Hit_Flg(&g, &Ray_HitFlg);
			enemy[i]->Set_Ray_Dis(&g, &b.SamllDis);
		}
	}

	return true;
}

bool GameScene::Update_Bullet_Init(void)
{
	if (player != nullptr) {
		if (Get_End_Flg() != true) {
			player->Init_Bullet();
		}
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

bool GameScene::Update_Sound(void)
{
	if (M_C_Sound_Manager == nullptr)return false;

	S_OptionData l_OptionData = option->GetOptionData();

	M_C_Sound_Manager->Update_Sound(&camera->GetPos(), &camera->GetLook(),&D3DXVECTOR3(0.0f, 1.0f, 0.0f), &l_OptionData.BGMVolume);

	M_C_Sound_Manager->Set_Sound(&l_OptionData.BGMVolume);

	if (player != nullptr) {
		for (unsigned int s = 0; s < player->Get_Sound_Data_Num(); s++) {
			if (M_C_Sound_Manager->Judg_Sound(&player->Get_Sound_Data(&s), &l_OptionData.BGMVolume) == true) {
				player->Delete_Sound(&s);
			}
		}
	}

	if (war != nullptr) {
		for (unsigned int d = 0; d < war->Get_Sound_Data_Num(); d++) {
			if (M_C_Sound_Manager->Judg_Sound(&war->Get_Sound_Data(&d), &l_OptionData.BGMVolume) == true) {
				war->Delete_Sound(&d);
			}
		}
	}

	return true;
}


void GameScene::New_Sound(const int * Type, const int * Category, const int No, const int * Change)
{
	if (M_C_Sound_Manager == nullptr)return;

	C_Struct_Init C_S_Init;
	M_C_Sound_Manager->New_Sound_Data(&C_S_Init.Get_S_SOUND_DATA(Type, Category, &No, Change));
}

void GameScene::New_Sound(const int * Category, const int No, const D3DXVECTOR3 * Pos, const int * Change)
{
	if (M_C_Sound_Manager == nullptr)return;

	M_C_Sound_Manager->New_Sound_Data(Category, No, Pos, Change);
}

bool GameScene::Update_Damage_Num_Draw(void)
{
	if (M_Damage_Num_Draw.size() <1) return false;

	for (unsigned int v = 0; v < M_Damage_Num_Draw.size(); v++) {
		if (M_Damage_Num_Draw[v]->Update() != true) {
			Delete_Damage_Num_Draw(&v);
		}
	}

	return true;
}

bool GameScene::Get_End_Flg(void)
{
	if (M_C_Game_End == nullptr)return true;

	return M_C_Game_End->Get_EndFlg();
}

void GameScene::Geme_End_Change(const int * Mode)
{
	if (M_C_Game_End == nullptr)return;

	C_Game_End_Base* Game_End;

	Game_End=M_C_Game_End->Change(Mode);

	if (Game_End != nullptr) {
		delete M_C_Game_End;
		M_C_Game_End = Game_End;
	}
}

void GameScene::Pop_Enemy(void)
{
	//エネミーの出現
	if (Get_Car_Pop(&co_EnemyCar) != true) return;

	//車の情報取得
	S_CAR_INIT_DATA L_Data = M_C_Car_Pop->Get_Next_Car_Data_N();

	//地面のナンバー
	unsigned int gNo;
	gNo = player->GetCon().GroNum + L_Data.GroundNo;
	//地面があるかの判定
	if (gNo < 0)gNo = 0;
	if (gNo > ground.size() - 1)gNo = ground.size() - 1;
	//車線を決める
	int Ground_Rail_Num = ground[gNo]->GetWay().RailNum;
	int RailNum = Get_Rail_Num(&Ground_Rail_Num, &L_Data.WayNo);
	
	//地面の位置
	D3DXMATRIX GroundMat = ground[gNo]->GetWay().StartMat;

	//地面の初期位置の横幅
	float TransX = ground[gNo]->GetWay().CurTransX[RailNum];

	//出現できるかの判定
	if (Car_Pop_Judg(&GroundMat, &TransX) != true)return;

	//ボスが出現する時の判定
	if (L_Data.CarNo > 100) {
		if (enemy.size() > 0) {
			for (auto && e : enemy) {
				if (e->GetCon().GroNum > gNo)return;
			}
		}
	}

	//敵の種類
	C_Enemy_Manager Manager;

	//出現
	enemy.push_back(Manager.Get_Enemy(&L_Data.CarNo, &GroundMat, &TransX));

	// 地面の当たり判定
	unsigned int num;
	float dis;
	C_GameSystem gameSystem;
	if (gameSystem.JudgNowGround(&num, &dis, enemy[(enemy.size() - 1)]->GetMatCar(), ground) == true) {
		enemy[(enemy.size() - 1)]->SetGroNum(&num);
	}

	//出現後の処理
	M_C_Car_Pop->Car_Init_Rear_N();
}

bool GameScene::Car_Pop_Judg(const D3DXMATRIX * GroundMat, const float * TransX)
{
	D3DXMATRIX TmpMat;

	//地面の横幅の行列作成
	D3DXMatrixTranslation(&TmpMat, *TransX, 0.0f, 0.0f);

	//出現する初期位置の行列の合成
	TmpMat = TmpMat * (*GroundMat);

	//出現位置、走行中の車の位置
	D3DXVECTOR3 Pop_Pos, Car_Pos;

	//出現位置の初期化
	judg.SetPosM(&Pop_Pos, &TmpMat);

	//出現可能半径
	float Radius = 4.0f*2.0f;

	//プレイヤーとの判定
	if (Car_Pop_Judg_Player(&Pop_Pos, &Radius) == true)return false;

	//エネミーとの判定
	if (Car_Pop_Judg_Enemy(&Pop_Pos, &Radius) == true)return false;

	//出現可能
	return true;
}

bool GameScene::Car_Pop_Judg_Player(const D3DXVECTOR3 * Pop_Pos, const float * Pop_Radius)
{
	if (player == nullptr)return false;

	D3DXVECTOR3 Pos;

	judg.SetPosM(&Pos, &player->GetMatCar());

	return judg.Pop_BallJudg(Pop_Pos, &Pos, Pop_Radius);
}

bool GameScene::Car_Pop_Judg_Enemy(const D3DXVECTOR3 * Pop_Pos, const float * Pop_Radius)
{
	if (enemy.size() <= 0) return false;

	for (auto && e : enemy) {
		
		D3DXVECTOR3 Pos;

		judg.SetPosM(&Pos, &e->GetMatCar());

		if (judg.Pop_BallJudg(Pop_Pos, &Pos, Pop_Radius) == true)return true;

	}

	return false;
}

void GameScene::Debug_Text(void)
{
	if (M_Text_Num == nullptr)return;

	/*if (enemy.size() > 0) {
		if (enemy[enemy.size() - 1]->Get_Gun_Num() > 0) {
			char Text[200];
			unsigned int L_GunNo = 0;
			D3DXMATRIX Mat = enemy[enemy.size() - 1]->Get_Gun_Data(&L_GunNo).DrawBase.Mat;
			D3DXVECTOR3 Pos = judg.SetPosM(&Mat);
			sprintf_s(Text, sizeof(Text), "%f,%f,%f", Pos.x, Pos.y, Pos.z);
			M_Text_Num->Draw_Text_char(&Text[0], &D3DXVECTOR2(0, 0));
		}
	}*/
}

void GameScene::Delete_Damage_Num_Draw(unsigned int * vector_No)
{
	delete M_Damage_Num_Draw[*vector_No];
	M_Damage_Num_Draw.erase(M_Damage_Num_Draw.begin() + *vector_No);
	*vector_No -= 1;
}

void GameScene::New_Damage_Num_Draw(const int * Character_Type, const D3DXMATRIX * Ray_Mat,
	const D3DXVECTOR3 * Ray_Vec,const float * Ray_Dis, const int * Damage, const bool * DamageFlg)
{
	return;//非表示中

	if (*Character_Type != co_PlayerCar) return;

	if (*DamageFlg != true)return;

	Judg L_judg;

	D3DXVECTOR3 Ray_Hit_Pos;

	L_judg.Get_Ray_Pos3D(&Ray_Hit_Pos,&judg.SetPosM(Ray_Mat), Ray_Vec, Ray_Dis);

	int L_Damage = *Damage;
	if (*DamageFlg != true)L_Damage = 0;

	D3DXMATRIX L_JudgMat = player->GetCon().JudgMat;

	M_Damage_Num_Draw.push_back(new C_Damage_Move_B(&Ray_Hit_Pos, &L_JudgMat, &L_Damage));
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
		if (judg.BallJudg(&judg.SetPosM(&RD->Mat), &judg.SetPosM(&ground[g]->GetMat()), Rad) == true) {//絞り込み
			JudgFlg = false;
			
			bool L_IdenFlg = ground[g]->GetIdenFlg();

			//レイ判定
			if (judg.RayJudg_Polygon(&judg.SetPosM(&RD->Mat), &RD->Ray, &ground[g]->GetMat(),
				&ground[g]->GetVer(0), &ground[g]->GetVer(1), &ground[g]->GetVer(2), &ground[g]->GetVer(3), &Dis, &L_IdenFlg) == true) {

				//レイが当たった時の処理

				JudgFlg = true;
				if (HitFlg != nullptr) {
					*HitFlg = true;
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
		for (int w = 0; w < ground[g]->Get_Wall_Num(); w++) {
			//二枚の壁判定
			if (judg.BallJudg(&judg.SetPosM(&RD->Mat), &judg.SetPosM(&ground[g]->Get_Mat_Wall(&w)), Rad) == true) {
				JudgFlg = false;
				//レイ判定
				if (judg.RayJudg_Mesh(&judg.SetPosM(&RD->Mat), &RD->Ray, &ground[g]->Get_DrawMat_Wall(&w), ground[g]->GetColModWall(), &Dis) == true) {
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
	judg.SetPosM(&BPos, &RD->Mat);

	float Dis;

	if (judg.BallJudg(&judg.SetPosM(&RD->Mat), &judg.SetPosM(&player->GetMatCar()), Rad) == true) {//絞り込み
	//レイ判定
		//ボディ
		if (judg.RayJudg_Mesh(&BPos, &RD->Ray, &player->GetDrawMatCar(), player->GetMeshCar(), &Dis) == true) {
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

void GameScene::BulletJudgEnemy(BULLETJUDGDATA * BJD, const RAYDATA * RD, const float * Rad, const unsigned int * EnemyNo)
{
	if (enemy.size() <= 0)return;

	D3DXVECTOR3 BPos;
	judg.SetPosM(&BPos, &RD->Mat);

	//判定しない敵
	unsigned int No_Judg_EnemyNo = -1;
	if (EnemyNo != nullptr)No_Judg_EnemyNo = *EnemyNo;

	//enemyの数
	for (unsigned int e = 0; e < enemy.size(); e++) {

		if (e == No_Judg_EnemyNo)continue;

		if (judg.BallJudg(&judg.SetPosM(&RD->Mat), &judg.SetPosM(&enemy[e]->GetMatCar()), Rad) != true)continue;

		//レイ判定
		//ボディ
		if (judg.RayJudg_Mesh_SmallDis(&BPos, &RD->Ray, &enemy[e]->GetDrawMatCar(), enemy[e]->GetMeshCar(), &BJD->SamllDis) == true) {

			BJD->Type = co_EnemyCar;
			BJD->JudgNo1 = e;

		}
		//パーツ
		if (enemy[e]->Get_Car_Parts_Num() > 0) {
			for (unsigned int p = 0; p < enemy[e]->Get_Car_Parts_Num(); p++) {
				//if (enemy[e]->GetPartsData(&p).MeshDrawFlg <= 0)continue;

				//メッシュ判定
				if (enemy[e]->Get_Parts_Draw_Draw_JudgFlg(&p) == Co_Draw_Mesh) {

					//表示行列
					D3DXMATRIX DrawMat = enemy[e]->Get_Parts_Draw_DrawMat(&p);

					//レイ判定
					if (judg.RayJudg_Mesh_SmallDis(&BPos, &RD->Ray, &DrawMat
						, enemy[e]->Get_Parts_Draw_Mesh(&p), &BJD->SamllDis) != true) continue;

					BJD->Type = co_EnemyParts;
					BJD->JudgNo1 = e;
					BJD->JudgNo2 = p;

				}
				else {
					//板ポリゴン判定
					if (enemy[e]->Get_Parts_Draw_Draw_JudgFlg(&p) == Co_Draw_Pol) {

						int a = 0, b = 1, c = 2, d = 3;

						//レイ判定
						if (judg.RayJudg_Polygon_SmallDis(&BPos, &RD->Ray, &enemy[e]->Get_Parts_Draw_DrawMat(&p),
							&enemy[e]->Get_Parts_Draw_Pol_Pos(&p, &a), &enemy[e]->Get_Parts_Draw_Pol_Pos(&p, &b)
							, &enemy[e]->Get_Parts_Draw_Pol_Pos(&p, &c), &enemy[e]->Get_Parts_Draw_Pol_Pos(&p, &d)
							, &BJD->SamllDis) != true) continue;

						BJD->Type = co_EnemyParts;
						BJD->JudgNo1 = e;
						BJD->JudgNo2 = p;

					}
				}
			}
		}
		//銃
		if (enemy[e]->Get_Gun_Num() > 0) {
			for (unsigned int g = 0; g < enemy[e]->Get_Gun_Num(); g++) {
				//if (enemy[e]->GetGunData(&g).Base.DrawFlg != true)continue;

				if (enemy[e]->Ray_Judg_Gun_Flg(&g) != true) continue;

				if (enemy[e]->Get_Gun_Draw_Parts_Num(&g) <= 0) continue;

				for (unsigned int g_p = 0; g_p < enemy[e]->Get_Gun_Draw_Parts_Num(&g); g_p++) {

					if (enemy[e]->Get_Gun_Draw_Parts_Draw_JudgFlg(&g, &g_p) != Co_Draw_Mesh) continue;

					//レイ判定
					if (judg.RayJudg_Mesh_SmallDis(&BPos, &RD->Ray, &enemy[e]->Get_Gun_Draw_Parts_Draw_Mat(&g, &g_p)
						, enemy[e]->Get_Gun_Draw_Parts_Mesh(&g, &g_p), &BJD->SamllDis) != true) continue;

					BJD->Type = co_EnemyGun;
					BJD->JudgNo1 = e;
					BJD->JudgNo2 = g;
					BJD->JudgNo3 = g_p;

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
	judg.SetPosM(&BPos, &RD->Mat);

	//enemyの数
	for (unsigned int e = 0; e < enemy.size(); e++) {

		//
		if (judg.BallJudg(&judg.SetPosM(&RD->Mat), &judg.SetPosM(&enemy[e]->GetMatCar()), Rad) != true) continue;

		/*パーツ*/
		if (enemy[e]->Get_Car_Parts_Num() <= 0) continue;

		for (unsigned int p = 0; p < enemy[e]->Get_Car_Parts_Num(); p++) {

			if (enemy[e]->Get_Parts_Draw_Draw_JudgFlg(&p) != Co_Draw_Ball) continue;

			float L_Radius = enemy[e]->Get_Parts_Draw_Dis(&p);

			if (judg.BallJudg(&BPos, &judg.SetPosM(&enemy[e]->Get_Parts_Draw_DrawMat(&p)),
				&L_Radius) != true) continue;

			//最大より小さいか
			BJD->Type = co_EnemyParts;
			BJD->JudgNo1 = e;
			BJD->JudgNo2 = p;

		}
	}
}

bool GameScene::SetBulletDamage(const BULLETJUDGDATA * BJD, const RAYDATA * RD, const int Damage)
{
	if (BJD->Type < 0)return false;

	//地面///////////////////////////////////////////////////////////////////////////////////
	//地面
	if (SetBulletDamageGround(BJD, RD) == true)return true;
	//壁
	if (SetBulletDamageWall(BJD, RD) == true)return true;

	//プレイヤー/////////////////////////////////////////////////////////////////////////////
	//車体
	if (SetBulletDamagePlaCar(BJD,RD, &Damage) == true)return true;
	//標準パーツ
	if (SetBulletDamagePlaParts(BJD, RD, &Damage) == true)return true;
	//銃
	if (SetBulletDamagePlaGun(BJD, RD, &Damage) == true)return true;

	//エネミー//////////////////////////////////////////////////////////////////////////////
	//車体
	if (SetBulletDamageEneCar(BJD, RD, &Damage) == true)return true;
	//標準パーツ
	if (SetBulletDamageEneParts(BJD, RD, &Damage) == true)return true;
	//銃
	if (SetBulletDamageEneGun(BJD, RD, &Damage) == true)return true;

	//当たっていない
	return false;
}

bool GameScene::SetBulletDamageGround(const BULLETJUDGDATA* BJD, const RAYDATA *RD)
{
	if (BJD->Type != co_Ground)return false;
	//火花
	D3DXVECTOR3 Ray_Hit_Pos;
	judg.Get_Ray_Pos3D(&Ray_Hit_Pos, &judg.SetPosM(&RD->Mat), &RD->Ray, &BJD->SamllDis);

	int SpeType = 0;
	float Ang = 0.0f;
	SparkV.push_back(new C_BulGro(&ground[BJD->JudgNo1]->GetMat(), &Ray_Hit_Pos));

	//弾痕３D
	float Ray_Dis = BJD->SamllDis - 0.01f;

	judg.Get_Ray_Pos3D(&Ray_Hit_Pos, &judg.SetPosM(&RD->Mat), &RD->Ray, &Ray_Dis);

	BHole3D.push_back(new C_BulHol3D(&ground[BJD->JudgNo1]->GetMat(), &Ray_Hit_Pos, 2));

	//被弾音の初期化
	Set_BulletHit_Sound(&Hit_Type_Ground, &Ray_Hit_Pos);
	
	return true;
}

bool GameScene::SetBulletDamageWall(const BULLETJUDGDATA* BJD, const RAYDATA *RD)
{
	if (BJD->Type != co_Wall)return false;
	//火花
	D3DXVECTOR3 Ray_Hit_Pos;
	judg.Get_Ray_Pos3D(&Ray_Hit_Pos, &judg.SetPosM(&RD->Mat), &RD->Ray, &BJD->SamllDis);

	int SpeType = 1;
	float Ang = 0.0f;
	//火花
	int i = (int)BJD->JudgNo2;
	for (int s = 0; s < 5; s++) {
		SparkV.push_back(new C_SparkDamage(&ground[BJD->JudgNo1]->Get_Mat_Wall(&i), &Ray_Hit_Pos, &SpeType, &Ang));
	}
	//弾痕３D
	float Ray_Dis = BJD->SamllDis - 0.01f;

	judg.Get_Ray_Pos3D(&Ray_Hit_Pos, &judg.SetPosM(&RD->Mat), &RD->Ray, &Ray_Dis);

	BHole3D.push_back(new C_BulHol3D(&ground[BJD->JudgNo1]->Get_Mat_Wall(&i), &Ray_Hit_Pos, 1));

	//被弾音の初期化
	Set_BulletHit_Sound(&Hit_Type_Wall, &Ray_Hit_Pos);

	return true;
}

bool GameScene::SetBulletDamagePlaCar(const BULLETJUDGDATA* BJD, const RAYDATA * RD, const int * Damage)
{
	if (BJD->Type != co_PlayerCar)return false;

	if (player->SetHP(*Damage, false) == true) {
		//ダメージを受けた時
		int sc = -10;
		score->ScoreUp(&sc);

		//被弾座標
		D3DXVECTOR3 RayPos;

		//被弾音の初期化
		Set_BulletHit_Sound(&Hit_Type_Player, &RayPos);
	}
	return true;
}

bool GameScene::SetBulletDamagePlaParts(const BULLETJUDGDATA* BJD, const RAYDATA * RD, const int * Damage)
{
	if (BJD->Type != co_PlayerParts)return false;

	/*if (player->SetDamageParts(HitMesh, Damage) == true) {

	}*/

	return true;
}

bool GameScene::SetBulletDamagePlaGun(const BULLETJUDGDATA* BJD, const RAYDATA * RD, const int * Damage)
{
	return false;
}

bool GameScene::SetBulletDamageEneCar(const BULLETJUDGDATA* BJD, const RAYDATA * RD, const int * Damage)
{
	if (BJD->Type != co_EnemyCar)return false;

	if (enemy[BJD->JudgNo1]->GetFlgCar() == false)return true;

	bool DamageFlg = enemy[BJD->JudgNo1]->SetHP(*Damage, false);

	New_Damage_Num_Draw(&BJD->Character_Type, &RD->Mat, &RD->Ray, &BJD->SamllDis, Damage, &DamageFlg);

	//被弾音の初期化
	Set_BulletHit_Sound(&Hit_Type_Enemy, BJD, RD,&DamageFlg);

	return true;
}

bool GameScene::SetBulletDamageEneParts(const BULLETJUDGDATA* BJD, const RAYDATA * RD, const int * Damage)
{
	if (BJD->Type != co_EnemyParts)return false;

	bool DamageFlg=enemy[BJD->JudgNo1]->Damage_CarParts(&BJD->JudgNo2, Damage);

	New_Damage_Num_Draw(&BJD->Character_Type, &RD->Mat, &RD->Ray, &BJD->SamllDis, Damage, &DamageFlg);

	//被弾音の初期化
	Set_BulletHit_Sound(&Hit_Type_Enemy, BJD, RD, &DamageFlg);

	return true;
}

bool GameScene::SetBulletDamageEneGun(const BULLETJUDGDATA* BJD, const RAYDATA * RD, const int * Damage)
{
	if (BJD->Type != co_EnemyGun)return false;

	bool DamageFlg = enemy[BJD->JudgNo1]->Damage_Gun(&BJD->JudgNo2, Damage);

	New_Damage_Num_Draw(&BJD->Character_Type, &RD->Mat, &RD->Ray, &BJD->SamllDis, Damage, &DamageFlg);

	//被弾音の初期化
	Set_BulletHit_Sound(&Hit_Type_Enemy, BJD, RD, &DamageFlg);

	return true;
}

bool GameScene::SideJudg_Preparation(S_SideJudgChara * Judg_Car, D3DXMATRIX * JudgMat,
	D3DXVECTOR3 * JudgVec, float * SmallDis,float *Over_Dis, const int * JudgMat_Num)
{
	//判定用Mat
	D3DXMATRIX TransMat;
	//一番数値の高いZと低いZ
	float BigZ, SmallZ;
	//拡大座標
	D3DXVECTOR3 ScalPosB;
	//判定をしている車の情報
	switch (Judg_Car->Car_Type)
	{
	case Hit_Type_Player://プレイヤー
		ScalPosB = player->GetScalPosCar();
		//Matの作成
		JudgMat[1] = player->GetCon().JudgMat;
		BigZ = player->GetCon().PosBig.z*ScalPosB.z;
		SmallZ = player->GetCon().PosSmall.z*ScalPosB.z;
		TransMat = player->GetTransMatCar();
		//Radを入れる
		if (Judg_Car->LeftFlg == true) {
			//左
			Judg_Car->Rad = player->GetCon().PosSmall.x*ScalPosB.x;
		}
		else {
			//右
			Judg_Car->Rad = player->GetCon().PosBig.x*ScalPosB.x;
		}
		break;
	case Hit_Type_Enemy://敵

		if (enemy.size() <= 0) return false;

		//エネミー
		ScalPosB = enemy[Judg_Car->No]->GetScalPosCar();
		//Matの作成
		JudgMat[1] = enemy[Judg_Car->No]->GetCon().JudgMat;
		BigZ = enemy[Judg_Car->No]->GetCon().PosBig.z*ScalPosB.z;
		SmallZ = enemy[Judg_Car->No]->GetCon().PosSmall.z*ScalPosB.z;
		TransMat = enemy[Judg_Car->No]->GetTransMatCar();
		//Radを入れる
		if (Judg_Car->LeftFlg == true) {
			//左
			Judg_Car->Rad = enemy[Judg_Car->No]->GetCon().PosSmall.x*ScalPosB.x;
		}
		else {
			//右
			Judg_Car->Rad = enemy[Judg_Car->No]->GetCon().PosBig.x*ScalPosB.x;
		}
		break;
	default:
		return false;
		break;
	}
	if (Judg_Car->Rad < 0.0f)Judg_Car->Rad *= -1.0f;
	Judg_Car->Rad += 0.01f;
	//Matの作成
	D3DXMATRIX Trans;
	for (int i = 0; i < *JudgMat_Num; i++) {
		JudgMat[i] = TransMat * JudgMat[1];
	}
	D3DXMatrixTranslation(&Trans, 0.0f, 0.0f, BigZ);
	JudgMat[0] = Trans * JudgMat[1];
	D3DXMatrixTranslation(&Trans, 0.0f, 0.0f, SmallZ);
	JudgMat[2] = Trans * JudgMat[1];
	//レイの方向
	if (Judg_Car->LeftFlg == true) {
		D3DXVec3TransformNormal(JudgVec, &D3DXVECTOR3(-1.0f, 0.0f, 0.0f), &JudgMat[1]);
	}
	else {
		D3DXVec3TransformNormal(JudgVec, &D3DXVECTOR3(1.0f, 0.0f, 0.0f), &JudgMat[1]);
	}

	//判定用レイの距離
	*SmallDis = Judg_Car->Rad;
	if (*SmallDis < 0.0f)*SmallDis *= -1.0f;

	*Over_Dis = Judg_Car->Rad;
	if (*Over_Dis < 0.0f)*Over_Dis *= -1.0f;

	return true;
}

int GameScene::Side_Judg_Player(S_SideJudgChara * Next_Data, float * Small_Dis,
	int * RayHit_No, D3DXMATRIX * RayHit_Mat, float * Over_Dis, bool * Over_Flg,
	const S_SideJudgChara * Data, const int * JudgMat_Num, const D3DXMATRIX * JudgMat,
	const D3DXVECTOR3 * Ray_Vec)
{
	if (Data->Car_Type == Hit_Type_Player)return 0;

	if (Get_End_Flg() != false) return 0;

	float L_Radius = (float)RadJudgF;

	//範囲内判定
	if (judg.BallJudg(&judg.SetPosM(&JudgMat[Const_Middle]), &judg.SetPosM(&player->GetMatCar()),
		&L_Radius) != true) return 0;

	if (Side_Judg_Ray(Next_Data, Small_Dis, RayHit_No, RayHit_Mat, Over_Dis, Over_Flg,
		&Hit_Type_Player, nullptr, Data, JudgMat_Num, JudgMat, Ray_Vec) > 0) {
		Next_Data->JudgeType = player->Get_JudgeType();
		return 1;
	}

	return 0;
}

int GameScene::Side_Judg_Enemy(S_SideJudgChara * Next_Data, float * Small_Dis, int * RayHit_No,
	D3DXMATRIX * RayHit_Mat, float * Over_Dis, bool * Over_Flg, const S_SideJudgChara * Data,
	const int * JudgMat_Num, const D3DXMATRIX * JudgMat, const D3DXVECTOR3 * Ray_Vec)
{
	if (enemy.size() <= 0) return 0;

	int Hit_Car_Count = 0;

	//enemyの数
	for (unsigned int e = 0; e < enemy.size(); e++) {
		//判定しない条件
		if (((Data->Car_Type == Hit_Type_Enemy) && (Data->No == e)) || (enemy[e]->Get_JudgeType()==Co_Judge_NO))continue;

		float L_Radius = (float)RadJudgF;

		//範囲内判定
		if (judg.BallJudg(&judg.SetPosM(&JudgMat[Const_Middle]),
			&judg.SetPosM(&enemy[e]->GetMatCar()), &L_Radius) != true)continue;

		//レイ判定
		if (Side_Judg_Ray(Next_Data, Small_Dis, RayHit_No, RayHit_Mat, Over_Dis, Over_Flg,
			&Hit_Type_Enemy, &e, Data, JudgMat_Num, JudgMat, Ray_Vec) > 0) {
			Hit_Car_Count++;

			//当たった車の状態のセット
			Next_Data->JudgeType = enemy[e]->Get_JudgeType();
		}
	}

	return Hit_Car_Count;
}

bool GameScene::Side_Judg_Ground(const S_SideJudgChara * Data,
	const D3DXMATRIX * JudgMat_Base,const D3DXVECTOR3 * Ray_Vec, float * Small_Dis,
	int * RayHit_No, D3DXMATRIX * RayHit_Mat)
{
	if (ground.size() <= 0)return false;

	//壁の
	int w = 1;
	if (Data->LeftFlg == true)w = 0;

	D3DXVECTOR3 Ray_Pos = judg.SetPosM(JudgMat_Base);

	bool Wall_Hit_Flg = false;

	//地面数
	for (unsigned int g = 0; g < ground.size(); g++) {

		float L_Radius = (float)RadJudgF;

		if (judg.BallJudg(&judg.SetPosM(JudgMat_Base), &judg.SetPosM(&ground[g]->Get_Mat_Wall(&w)), &L_Radius) != true) continue;

		float Dis;

		//レイ判定
		if (judg.RayJudg_Mesh(&Ray_Pos, Ray_Vec, &ground[g]->Get_DrawMat_Wall(&w), ground[g]->GetColModWall(), &Dis) != true) continue;

		if (Dis > *Small_Dis) continue;

		*Small_Dis = Dis;
		*RayHit_No = 1;
		*RayHit_Mat = ground[g]->Get_DrawMat_Wall(&w);

		Wall_Hit_Flg = true;

	}

	return Wall_Hit_Flg;
}

int GameScene::Side_Judg_Ray(S_SideJudgChara * Next_Data, float * Small_Dis, int * RayHit_No,
	D3DXMATRIX * RayHit_Mat, float * Over_Dis, bool * Over_Flg, const int * Judg_Car_Type,
	const unsigned int * Car_No, const S_SideJudgChara * Data, const int * JudgMat_Num,
	const D3DXMATRIX * JudgMat, const D3DXVECTOR3 * Ray_Vec)
{
	int Hit_Count = 0;

	float Dis;

	for (int RayPos_No = 0; RayPos_No < *JudgMat_Num; RayPos_No++) {

		D3DXVECTOR3 Ray_Pos = judg.SetPosM(&JudgMat[RayPos_No]);

		//
		D3DXMATRIX Car_Mat;

		//当たったポリゴン数
		int L_PolNum;

		//レイ判定
		switch (*Judg_Car_Type)
		{
		case Hit_Type_Player:

			//レイ判定
			L_PolNum = judg.RayJudg_Mesh_PolNum(&Ray_Pos, Ray_Vec,
				&player->GetMatCar(), player->GetColMod(), &Dis);

			if (L_PolNum >= 2) Car_Mat = player->GetMatCar();

			break;
		case Hit_Type_Enemy:

			//レイ判定
			L_PolNum = judg.RayJudg_Mesh_PolNum(&Ray_Pos, Ray_Vec,
				&enemy[*Car_No]->GetDrawMatCar(), enemy[*Car_No]->GetColMod(), &Dis);

			if (L_PolNum >= 2) Car_Mat = enemy[*Car_No]->GetMatCar();

			break;
		}

		if (L_PolNum == 1) {
			if (Data->Car_Type != Hit_Type_Player) {

				float L_Over_Dis = *Over_Dis;

				if (L_Over_Dis < 0.0f)L_Over_Dis *= -1.0f;

				if ((L_Over_Dis > Dis) || (*Over_Flg != true)) {
					*Over_Flg = true;
					*Over_Dis = Dis * -1.0f;
				}
			}
			continue;
		}

		//レイ判定でレイが当たった時の処理
		if (L_PolNum >= 2) {
			Hit_Count += Side_Judg_Ray(Judg_Car_Type, Car_No, &Data->Rad, Next_Data, Small_Dis, RayHit_No, RayHit_Mat,
				&Dis, &Car_Mat, &RayPos_No);
		}
	}

	return Hit_Count;
}

int GameScene::Side_Judg_Ray(const int * Judg_Car_Type, const unsigned int * Car_No, const float * Car_Rad,
	S_SideJudgChara * Next_Data, float * Small_Dis,int * RayHit_No, D3DXMATRIX * RayHit_Mat,
	const float * Ray_Hit_Dis, const D3DXMATRIX * Judg_Car_Mat, const int * RayPos_No)
{
	//当たった
	if (*Ray_Hit_Dis < *Small_Dis) {
		*Small_Dis = *Ray_Hit_Dis;
		Next_Data->Car_Type = *Judg_Car_Type;
		if (Car_No != nullptr)Next_Data->No = *Car_No;
		*RayHit_No = *RayPos_No;
		*RayHit_Mat = *Judg_Car_Mat;
	}
	if (*Car_Rad > *Ray_Hit_Dis) return 1;

	//当たっていない
	return 0;
}

void GameScene::Wall_Spark_Init(bool * Spark_Init_Flg, const D3DXMATRIX * RayHit_Mat, const D3DXVECTOR3 * RayHit_Pos, bool * LeftFlg)
{
	if (*Spark_Init_Flg != true)return;

	//火花を出す処理
	//複数出す
	bool InitFlg = false;
	for (int i = 0; i < 20; i++) {
		SparkV.push_back(new C_Spark2(RayHit_Mat, RayHit_Pos, LeftFlg, &InitFlg));
	}
	InitFlg = true;
	for (int i = 0; i < 15; i++) {
		SparkV.push_back(new C_Spark2(RayHit_Mat, RayHit_Pos, LeftFlg, &InitFlg));
	}

	//リバース
	judg.ReverseFlg(LeftFlg);

	//壁判定後は火花を出さない
	*Spark_Init_Flg = false;
}

void GameScene::Car_Spark_Init(const bool * Spark_Init_Flg, const D3DXMATRIX * RayHit_Mat, const D3DXVECTOR3 * RayHit_Pos)
{
	//火花を出せる判定
	if (*Spark_Init_Flg != true) return;

	//複数出す
	bool InitFlg = false;
	for (int i = 0; i < 15; i++) {
		SparkV.push_back(new C_Spark2(RayHit_Mat, RayHit_Pos, &InitFlg));
	}
	InitFlg = true;
	for (int i = 0; i < 12; i++) {
		SparkV.push_back(new C_Spark2(RayHit_Mat, RayHit_Pos, &InitFlg));
	}
}

bool GameScene::Ray_Judg_Player_ColModel(const D3DXVECTOR3 * Ray_Pos, const D3DXVECTOR3 * Ray_Vec, float * Dis)
{
	return judg.RayJudg_Mesh(Ray_Pos, Ray_Vec, &player->GetMatCar(), player->GetColMod(), Dis);
}

bool GameScene::Ray_Judg_Enemy_ColModel(const unsigned int * Enemy_No, const D3DXVECTOR3 * Ray_Pos, const D3DXVECTOR3 * Ray_Vec, float * Dis)
{
	return judg.RayJudg_Mesh(Ray_Pos, Ray_Vec, &enemy[*Enemy_No]->GetDrawMatCar(), enemy[*Enemy_No]->GetColMod(), Dis);
}

void GameScene::Enemy_Stop(const unsigned int * e, const int * Side_Judg_Car_Type)
{
	if (*Side_Judg_Car_Type != Hit_Type_Player)return;

	if (enemy[*e]->GetFlgCar() != true)return;

	if (enemy[*e]->Get_Move_Stop_Time() > 0)return;

	int Time = 60 * 8, L_Speed = player->GetCon().NowSpeed;

	enemy[*e]->Set_Move_Stop_Time(&Time,&L_Speed);
}

void GameScene::Debug_Screen_Init(void)
{
	M_S_Screen.DrawFlg = false;

	lpD3DDevice->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &M_S_Screen.lpBackBuffer);
	lpD3DDevice->GetDepthStencilSurface(&M_S_Screen.lpZBuffer);//DepthStencilSurface=Zバッファ
	D3DXCreateTexture(lpD3DDevice, 2048, 1024, 1, D3DUSAGE_RENDERTARGET, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &M_S_Screen.lpTmpTex);//X=2048,Y=1024,裏バックバッファを２のべき乗サイズ
	M_S_Screen.lpTmpTex->GetSurfaceLevel(0, &M_S_Screen.lpTmpBackBuffer);
	lpD3DDevice->CreateDepthStencilSurface(2048, 1024, D3DFMT_D16, D3DMULTISAMPLE_NONE, 0, FALSE, &M_S_Screen.lpTmpZBuffer, NULL);
}

void GameScene::Debug_Screen_End(void)
{
	M_S_Screen.lpBackBuffer->Release();
	M_S_Screen.lpZBuffer->Release();
	M_S_Screen.lpTmpBackBuffer->Release();
	M_S_Screen.lpTmpZBuffer->Release();
	M_S_Screen.lpTmpTex->Release();
}

void GameScene::Debug_Screen_Draw(void)
{
	if (M_S_Screen.DrawFlg != true)return;

	RECT rcTmp = { 0,0,1280,720 };
	D3DXMATRIX tmp;
	D3DXMatrixTranslation(&tmp, 0.0f, 0.0f, NULL);
	lpSprite->SetTransform(&tmp);
	lpSprite->Draw(M_S_Screen.lpTmpTex, &rcTmp, &D3DXVECTOR3(0, 0, 0), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));//２５５～１０残像ができる
}

void GameScene::FrustumCulling(const D3DXMATRIX * mProj, const D3DXMATRIX * mView, const D3DVIEWPORT9 * Viewport)
{
	S_Frustum_Vec FV_Data;

	judg.Get_Frustum_NormalVec(&FV_Data, mProj, mView, Viewport);

	FrustumCulling_Ground(&FV_Data);
}

void GameScene::FrustumCulling_Ground(const S_Frustum_Vec * FV_Data)
{
	if (ground.size() <= 0) return;

	for (unsigned int g = 0; g < ground.size(); g++) {

		FrustumCulling_Ground_Wall(&g, FV_Data);

		FrustumCulling_Ground_Object(&g, FV_Data);
	}
}

void GameScene::FrustumCulling_Ground_Wall(const unsigned int * gNo, const S_Frustum_Vec * FV_Data)
{
	unsigned int g = *gNo;

	if (ground[g]->Get_Wall_Num() <= 0)return;

	for (int w = 0; w < ground[g]->Get_Wall_Num(); w++) {
		D3DXVECTOR3 pos = judg.SetPosM(&ground[g]->Get_Mat_Wall(&w)) - camera->GetPos();
		float Radius = ground[g]->Get_Data_Wall(&w).CullingRad;

		bool DrawFlg;

		// 上下左右との比較(Near,Farは省略) normal ・ center > radius
		judg.Judg_Frustum(&DrawFlg, FV_Data, &pos, &Radius);

		ground[g]->Set_Draw_Flg_Wall(&w, &DrawFlg);
	}
}

void GameScene::FrustumCulling_Ground_Object(const unsigned int * gNo, const S_Frustum_Vec * FV_Data)
{
	if (ground[*gNo]->Get_Object_Draw_Num() <= 0)return;

	for (unsigned int o = 0; o < ground[*gNo]->Get_Object_Draw_Num(); o++) {
		S_Base3D_2 Data = ground[*gNo]->Get_Object_Data(&o);
		D3DXVECTOR3 pos = judg.SetPosM(&Data.Base.Mat) - camera->GetPos();

		bool DrawFlg;

		// 上下左右との比較(Near,Farは省略) normal ・ center > radius
		judg.Judg_Frustum(&DrawFlg, FV_Data, &pos, &Data.CullingRad);

		ground[*gNo]->Set_DrawFlg_Object(&o, &DrawFlg);
	}

}

void GameScene::Set_BulletHit_Sound(const int * BulletHit_Type, const D3DXVECTOR3 * Sound_Pos)
{
	if (M_C_Sound_Manager == nullptr)return;

	//M_C_Sound_Manager->Set_Bullet_Hit_Sound(BulletHit_Type, Sound_Pos);
}

void GameScene::Set_BulletHit_Sound(const int * BulletHit_Type, const D3DXVECTOR3 * Sound_Pos, const bool * DamageFlg)
{
	if (M_C_Sound_Manager == nullptr)return;

	//M_C_Sound_Manager->Set_Bullet_Hit_Sound(BulletHit_Type, Sound_Pos,DamageFlg);
}

void GameScene::Set_BulletHit_Sound(const int * BulletHit_Type, const BULLETJUDGDATA * BJD, const RAYDATA * RD, const bool * DamageFlg)
{
	//被弾座標
	D3DXVECTOR3 RayPos = judg.SetPosM(&RD->Mat) + RD->Ray * BJD->SamllDis;

	Set_BulletHit_Sound(BulletHit_Type, &RayPos, DamageFlg);
}

void GameScene::M_ForMoveJudg_Player(bool * JudgFlg, float * SmallDis, int * Hit_CarType,
	unsigned int * Hit_CarNumber, const int * Car_Type, const D3DXMATRIX * StartMat,
	const D3DXMATRIX * EndMat, const D3DXMATRIX * TransMat, const int * TransNum,
	const D3DXVECTOR3 * MoveVec, const D3DXVECTOR3 * PosBig, const D3DXVECTOR3 * PosSmall,
	const D3DXVECTOR3 * ScalPos, const bool * CollisionJudg_TrueFlg)
{
	//プレイヤーとプレイヤーで判定しないようにする
	if (*Car_Type == Hit_Type_Player)return;

	//全ての戦闘が終了しているときプレイヤーと判定しない
	if (Get_End_Flg() != false) return;

	//判定できない状態の場合判定をしない
	if (*CollisionJudg_TrueFlg != true)return;

	float L_Radius = (float)RadJudgF;

	//判定する車が近くにいるか判定する
	if (judg.BallJudg(&judg.SetPosM(StartMat), &judg.SetPosM(&player->GetMatCar()), &L_Radius) != true) return;

	D3DXVECTOR3 JudgPos;//レイの始点
	//左から順番に
	for (int i = 0; i < *TransNum; i++) {

		JudgPos = judg.SetPosM(&TransMat[i]);

		float Dis;

		//レイ判定
		if (judg.RayJudg_Mesh(&JudgPos, &MoveVec[i], &player->GetForMoveEndMat(), player->GetColMod(), &Dis) != true) continue;

		float Dis2;
		D3DXVECTOR3 Pos2, Vec2;
		for (int n = 0; n < *TransNum; n++) {

			//レイの発射位置とベクトルの作成
			if (M_ForMoveJudg_AfterMovingRay(&Pos2, &Vec2, &n, PosBig, PosSmall, ScalPos, EndMat) != true)continue;

			//レイ判定
			if (judg.RayJudg_Mesh(&Pos2, &Vec2, &player->GetForMoveEndMat(), player->GetColMod(), &Dis2) != true) continue;

			if (Dis < SmallDis[i]) {
				SmallDis[i] = Dis;
				JudgFlg[i] = true;
				*Hit_CarType = Hit_Type_Player;
			}

		}
	}
}

void GameScene::M_ForMoveJudg_Enemy(bool * JudgFlg, float * SmallDis, int * Hit_CarType,
	unsigned int * Hit_CarNumber, const int * Car_Type, const unsigned int * Car_No,
	const D3DXMATRIX * StartMat, const D3DXMATRIX * EndMat, const D3DXMATRIX * TransMat,
	const int * TransNum, const D3DXVECTOR3 * MoveVec, const D3DXVECTOR3 * PosBig,
	const D3DXVECTOR3 * PosSmall, const D3DXVECTOR3 * ScalPos, const bool * CollisionJudg_TrueFlg)
{
	//出現している敵がいない場合レイ判定しない
	if (enemy.size() <= 0)return;

	//全ての戦闘が終了した場合プレイヤーの車と判定しない
	if ((Get_End_Flg() == true) && (*Car_Type == Hit_Type_Player))return;

	for (unsigned int e = 0; e < enemy.size(); e++) {

		//同じ敵で判定しない
		if ((*Car_Type == Hit_Type_Enemy) && (*Car_No == e))continue;

		//敵が空を飛んでいる場合判定しない
		if (enemy[e]->Get_JudgeType() == Co_Judge_NO)continue;

		//判定する敵が判定できない状態でプレイヤーと判定する場合判定しない
		if ((*Car_Type == Hit_Type_Player) && (enemy[e]->Get_CollisionJudg_TrueFlg() != true))continue;

		float L_Radius = (float)RadJudgF;

		//絞り込み距離判定
		if (judg.BallJudg(&judg.SetPosM(StartMat), &judg.SetPosM(&enemy[e]->GetMatCar()), &L_Radius) != true) continue;

		D3DXVECTOR3 JudgPos;//レイの始点

		//左から順番に
		for (int i = 0; i < *TransNum; i++) {

			JudgPos = judg.SetPosM(&TransMat[i]);

			float Dis;

			//レイ判定
			if (judg.RayJudg_Mesh(&JudgPos, &MoveVec[i], &enemy[e]->GetForMoveEndMat(), enemy[e]->GetColMod(), &Dis) != true) continue;

			float Dis2;
			D3DXVECTOR3 Pos2, Vec2;
			for (int n = 0; n < *TransNum; n++) {

				//レイの発射位置とベクトルの作成
				if (M_ForMoveJudg_AfterMovingRay(&Pos2, &Vec2, &n, PosBig, PosSmall, ScalPos, EndMat) != true)continue;

				//レイ判定
				if (judg.RayJudg_Mesh(&Pos2, &Vec2, &enemy[e]->GetForMoveEndMat(), enemy[e]->GetColMod(), &Dis2) != true) continue;

				if (Dis < SmallDis[i]) {
					SmallDis[i] = Dis;
					JudgFlg[i] = true;
					*Hit_CarType = Hit_Type_Enemy;
					*Hit_CarNumber = e;

					/*if (*Car_Type == Hit_Type_Player) {
						bool Flg = false;
						enemy[e]->Set_CollisionJudg_TrueFlg(&Flg);
					}*/
				}

			}
		}
	}
}

bool GameScene::M_ForMoveJudg_AfterMovingRay(D3DXVECTOR3 *Ray_Pos, D3DXVECTOR3 *Ray_Vec, const int * Vec_No,
	const D3DXVECTOR3 * PosBig, const D3DXVECTOR3 * PosSmall,const D3DXVECTOR3 *ScalPos, const D3DXMATRIX * EndMat)
{
	D3DXVECTOR3 TmpPos;

	switch (*Vec_No)
	{
	case 0:
		TmpPos = D3DXVECTOR3(PosSmall->x, 0.0f, PosBig->z);
		break;
	case 1:
		TmpPos = D3DXVECTOR3(0.0f, 0.0f, PosBig->z);
		break;
	case 2:
		TmpPos = D3DXVECTOR3(PosBig->x, 0.0f, PosBig->z);
		break;
	default://検索にひっかからない場合、準備をしない
		return false;
		break;
	}

	D3DXMATRIX Mat;

	judg.Get_TransMatScal(&Mat, &TmpPos, ScalPos);

	Mat = Mat * (*EndMat);

	//レイの発射位置の作成
	judg.SetPosM(Ray_Pos, &Mat);

	//レイのベクトルの作成
	D3DXVec3TransformNormal(Ray_Vec, &D3DXVECTOR3(0.0f, 0.0f, 1.0f), &Mat);

	//準備完了
	return true;
}

bool GameScene::Get_Dead_Flg(const int * Car_Type, const unsigned int * Car_Number)
{
	//プレイヤーの死亡確認
	if ((player != nullptr) && (*Car_Type == Hit_Type_Player)) {
		if (player->Dead() == true)return true;
	}

	//敵の死亡確認
	if (*Car_Type == Hit_Type_Enemy) {
		if ((enemy.size() > 0) && (*Car_Number < enemy.size())) {
			if (enemy[*Car_Number]->Dead() == true)return true;
		}
	}

	return false;
}

void GameScene::M_Dead_Car(const int * Car_Type, const unsigned int * Car_Number)
{
	//プレイヤーの死亡確認
	if ((player != nullptr) && (*Car_Type == Hit_Type_Player)) return;

	//敵の死亡確認
	if (*Car_Type == Hit_Type_Enemy) {
		if ((enemy.size() > 0) && (*Car_Number < enemy.size())) {
			if (enemy[*Car_Number]->Dead() == true)return;

			int L_Hp = 0;
			
			//HPをゼロにする
			enemy[*Car_Number]->SetNowHp(&L_Hp);

			return;
		}
	}

	return;
}

void GameScene::M_Car_Pop_Data_Update(void)
{
	/*出現している敵の情報作成*/

	////出現している敵の数
	//int L_Enemy_Num = (int)enemy.size();

	////動的配列の初期化用配列数
	//int L_Init_Num = L_Enemy_Num;

	//if (L_Init_Num <= 0)L_Init_Num = 1;

	////敵の情報
	//S_ENEMY_DATA *L_Enemy_Data = new S_ENEMY_DATA[L_Init_Num];

	////出現している敵の作成
	//if ((L_Enemy_Num > 0) && (L_Enemy_Data != nullptr)) {

	//	if (enemy.size() > 0) {

	//		for (unsigned int e = enemy.size() - 1; e >= 0; e--)
	//		{
	//			//情報の作成
	//			L_Enemy_Data[(int)e].CarFlg = enemy[e]->GetFlgCar();
	//			L_Enemy_Data[(int)e].BossFlg = enemy[e]->Get_BossFlg();
	//			L_Enemy_Data[(int)e].Phase_Now = enemy[e]->Get_Gun_Update_Data().NowPhase;
	//		}

	//	}
	//}

	//出現している車の情報で車の情報の更新
	if (M_C_Car_Pop != nullptr)M_C_Car_Pop->M_Car_Pop_Update_N(enemy);

	////メモリの解放
	//if (L_Enemy_Data != nullptr)delete[] L_Enemy_Data;
}
