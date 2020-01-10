#pragma once
#include<d3dx9.h>
#include<vector>
#include"SceneBase.h"
#include"../Ground/Sky.h"
#include"../Player/Gun1.h"
#include"../Ground/BillBase.h"
#include"../Player/Aiming.h"
#include"../Enemy/MoveE.h"
#include"../3DDraw/Effect_3D/Explosion.h"
#include"../Gun/Bullet/BulletManager.h"
#include"../Player/Camera.h"
#include"../GameSource/Countdown.h"
#include"../Ground/Bill1.h"
#include"../GameSource/Debug.h"
#include"../GameSource/Debug2.h"
#include"../2DDraw/GameOver.h"
#include"../GameSource/Struct.h"
#include"../2DDraw/Warning.h"
#include"../2DDraw/Pause.h"
#include"../GameSource/Judgment.h"
#include"../3DDraw/Spear.h"
#include"../GameSource/Motion.h"
#include"../3DDraw/Effect_3D/Smoke2.h"
#include"../2DDraw/Score.h"
#include"../3DDraw/Effect_3D/SpaekDamage.h"
#include"../3DDraw/Effect_3D/Smog.h"
#include"../3DDraw/Effect_3D/BulletGround.h"
#include"../Sound/SoundGun1.h"
#include"GameSceneSoundManager.h"
#include"../3DDraw/Effect_3D/Spark2.h"
#include"../Enemy/EnemySky.h"
#include"../Key/CMouse.h"
#include"../Key/KeyTrue.h"
#include"../2DDraw/Fade.h"
#include"../3DDraw/Effect_3D/BulletHole3D.h"
#include"../Player2/PlayerA.h"
#include"../Enemy2/EnemyA.h"
#include"../Player2/PlayerBody.h"
#include"../2DDraw/PauseTouch.h"
#include"../2DDraw/OverTouch.h"
#include"../GameSource/Count.h"
#include"../Enemy2/EnemySelect.h"
#include"../EnemyData/Base&Manager/EnemySpeedManager.h"
#include"../3DDraw/Effect_3D/CarSmog.h"

extern Judg judg;
extern Motion motion;

//#ifndef GameScene_H
//#define GameScene_H

#define RadChara 200//キャラクターの範囲

class GameScene :public SceneBase, public C_GameSSM
{
public:
	void StageSave(const bool *Flg);
	void NewWaveSave(int StagNo);
	void NewEnemySave(int StagNo,int WaveNo);
	bool road(void);
	GameScene(const int stageNum);
	~GameScene();
	void Render3D(void);
	void Render2D(void);
	void SetCamera(void);
	bool Update(void);
	bool UpdateE(void);
	void GDebug(void);
	//地面取得
	bool NowGroNum(D3DXMATRIX Mat,unsigned int *Num,float *Dis);
	//弾のレイ判定
	void BulletJudg(const int *TypeCar,const unsigned int *CarNo);
	//壁と車体横の判定
	bool WallJudg(bool LeftFlg, bool PlayerFlg, bool EnemyFlg, unsigned int No);
	//壁と車横の判定(車が地面から離れた時用)
	bool WallJudg(const D3DXMATRIX *JudgMat, D3DXMATRIX *TransMat, const SizePos *sizePos);
	//敵の誕生と思考
	bool UpdateEnemyAI(void);
	//敵の移動
	bool UpdateEnemyMove(void);
	//前進レイ判定
	bool ForMoveJudg(CONSTITUTION Con, D3DXMATRIX StartMat, D3DXMATRIX EndMat, bool PlayerFlg, bool EnemyFlg, unsigned int No, D3DXVECTOR3 RayVec1, D3DXVECTOR3 RayVec2, D3DXVECTOR3 RayVec3, float *SpeedMul2,const D3DXVECTOR3 *ScalPosB);
	//移動後のMat作成
	D3DXMATRIX ForMoveEnd(CONSTITUTION Con, QuaForMove q, D3DXMATRIX TransMat);
	//カメラと壁判定
	void CameraWallJudg(void);
	//BulletBirthFlg
	bool GetBulletBirthFlg(void);
	//爆発インスタンス化関数
	void BombInit(const D3DXMATRIX *Mat);
	//デリートエネミー
	bool EnemyDelete(const unsigned int *EnemyNo);
	//敵の出現種類
	bool EnemyBirth(const int *EnemyNo,D3DXMATRIX *GroundMat,float *TransX);

	//チェンジシーン用
	void ChangeSceneFade(int ChangeSceneNo);
	void ChangeSceneFade(int ChangeSceneNo, int NextStageNo);
	bool SetScene(void);

	//メニューの入れ
	void SetMenu(bool PauseFlg, bool ClearFlg, bool OverFlg);
	//メニューの削除
	void DeleteMenu(void);
	//メニューの処理
	bool UpdateMenu(void);
	//地面の自動生成
	bool GroundCreate(unsigned int *GNo);
	//Pos2D計算
	void Pos2DUpdate(const D3DXMATRIX *mProj, const D3DXMATRIX *mView, const D3DVIEWPORT9 *Viewport);

protected:
	//コンストラクタ関数
	void AllNew(void);
	//デストラクタ関数
	void AllDelete(void);

	/*アップデート*/

	//BGMの更新
	bool Update_Bgm(void);

	//デバックの更新
	bool Update_Debug(void);

	//フェードの更新
	bool Update_Fade(void);

	//ゲーム本編の更新
	bool Update_Game(void);

	//ゲーム本編時のポーズ画面移動関数
	bool Update_Game_Pause(void);

	//ゲームのフレーム数の判定
	bool Judg_Game_Frame(void);

	//地面の更新
	bool Update_Ground(void);

	//爆発の更新
	bool Update_Explo(void);

	//火花の更新
	bool Update_Spark(void);

	//車の煙の更新
	bool Update_CarSmoke(void);

	//弾痕の更新
	bool Update_Bullet_Hole(void);

	//車の前方にカメラを向ける処理
	bool Update_Camera_Car(void);

	//プレイヤーの照準によるレイ判定と弾の撃つと更新
	bool Update_Player_Bullet(void);

	//今いる車で前進判定
	bool Update_Car_ForMove(void);

	//今いる車で横判定
	bool Update_Car_SideJudg(void);

	//プレイヤーの横移動処理
	bool Update_Player_XTrans(void);

	//プレイヤーの更新
	bool Update_Player(void);
	/*弾*/

	//弾判定の情報初期化
	BULLETJUDGDATA GetInitBJD(const float *InitDis);
	//弾判定集
	void BulletJudgGround(BULLETJUDGDATA* BJD,const RAYDATA *RD,bool *HitFlg,const float *Rad);
	void BulletJudgPlayer(BULLETJUDGDATA* BJD, const RAYDATA *RD, const float *Rad);
	void BulletJudgEnemy(BULLETJUDGDATA* BJD,const RAYDATA *RD, const float *Rad);
	//弾判定によるダメージ計算
	bool SetBulletDamage(const BULLETJUDGDATA* BJD, const RAYDATA *RD,const int Damage);
	bool SetBulletDamageGround(const BULLETJUDGDATA* BJD, const RAYDATA *RD);
	bool SetBulletDamageWall(const BULLETJUDGDATA* BJD, const RAYDATA *RD);
	bool SetBulletDamagePlaCar(const int *BulletJudgFlg, const int *Damage);
	bool SetBulletDamagePlaParts(const int *BulletJudgFlg, const unsigned int *HitMesh, const int *Damage);
	bool SetBulletDamagePlaGun(const int *BulletJudgFlg, const unsigned int *HitMesh, const int *Damage);
	bool SetBulletDamageEneCar(const int *BulletJudgFlg, const unsigned int *HitBodyNo, const int *Damage);
	bool SetBulletDamageEneParts(const int *BulletJudgFlg, const unsigned int *HitBodyNo, const unsigned int *HitMesh, const int *Damage);
	bool SetBulletDamageEneGun(const int *BulletJudgFlg, const unsigned int *HitBodyNo, const unsigned int *HitMesh, const int *Damage);
	void BulletJudgS(bool PlaBulFlg, unsigned int EnemyNo);
private:
	//デバッグ用----------------
	float Size, RaySize;
	int CountNum, MaxCount;//スロー再生用
	Spear *spear;
	D3DXMATRIX SpeMat;
	float DbgSize;
	//--------------------------
	//プレイヤーの情報
	C_PlayerBody *PlayerBody;
	//プレイヤー
	C_PlayerBase *player;//

	//地面のメンバ
	std::vector<BillBase*>ground;
	Cou *cou;//bill
	std::vector<Cou*>GroCou;
	int GroType, GroKNum, *CurType, NowCur;
	float AngGro;//カーブ時の角度
	bool GroLenFlg;//長さの変更
	//外灯表示用カウントダウン
	C_Count *LightCount;

	std::vector<C_EnemyAi*>enemy;
	bool eneFlg;//出現の切り替え
	Sky *sky;
	Aiming *aiming;
	std::vector<Explo*>explo;
	Camera *camera;
	Debug *debug;
	DebugT *debugT;
	GameOver *GaOv;
	bool EndFlg;//クリアとエンドのFlg

	Warning *war;

	//敵の情報を持ってくる変数
	char FRName[100];//ロード用
	char FSName[100];//セーブ用
	int StageNo;
	std::vector<EnemyPop*>ePop;
	int MaxWaveNum;//最大ウェーブ数
	int NowWaveNum;//今のウェーブ数
	int MaxEnemyNum;//今のウェーブの最大敵の数
	int NowEnemyNum;//今のウェーブの敵の数
	int NextEnemyNo;//今のウェーブの敵のナンバー

	Pause *pause;

	//火花変数
	std::vector<C_Spark*>SparkV;

	//スコア
	C_Score *score;

	//バレットバースFlg
	bool BulletBirthFlg;

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

	//弾痕３D
	std::vector<C_BulHol3D*>BHole3D;

	//タッチ
	std::vector<C_NextTouch*>Menu;

	//車用の煙エフェクト
	C_SmokeCar* M_C_SmokeCar;
};

//#endif // !GameScene_H
