#pragma once
#include<d3dx9.h>
#include<vector>
#include"SceneBase.h"
#include"../Ground/Sky.h"
#include"../Player/Aiming.h"
#include"../3DDraw/Effect_3D/Explosion.h"
#include"../Player/Camera.h"
#include"../GameSource/Countdown.h"
#include"../GameSource/Debug.h"
#include"../GameSource/Text_Num.h"
#include"../2DDraw/Game_End/Game_End_Now.h"
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
#include"../3DDraw/Effect_3D/Spark2.h"
#include"../Key/CMouse.h"
#include"../Key/KeyTrue.h"
#include"../2DDraw/Fade.h"
#include"../3DDraw/Effect_3D/BulletHole3D.h"
#include"../Player/PlayerA.h"
#include"../Enemy/EnemyA.h"
#include"../Player/PlayerBody.h"
#include"../2DDraw/PauseTouch.h"
#include"../2DDraw/OverTouch.h"
#include"../GameSource/Count.h"
#include"../Enemy/EnemySelect.h"
#include"../EnemyData/Base&Manager/EnemySpeedManager.h"
#include"../3DDraw/Effect_3D/CarSmog.h"
#include"../Const/Const_Draw_Judg.h"
#include"../Stage_Data/Car_Pop/Car_Pop_New.h"
#include"../Ground/Stage_Ground/Ground_Pop_New.h"
#include"../Sound/Sound_Manager_Base.h"
#include"../Draw/Damage_Num/Damage_Move_A.h"
#include"../Draw/Damage_Num/Damage_Move_B.h"
#include"../Ground/Ground_Object.h"

extern Motion motion;

//#ifndef GameScene_H
//#define GameScene_H

#define RadChara 200//キャラクターの範囲

class GameScene :public SceneBase
{
public:
	GameScene(const int stageNum);
	GameScene(const int stageNum,const bool *DebugFlg);
	~GameScene();
	void Render3D(void);
	void Render3D_Screen(void);
	void Render2D(void);
	void SetCamera(void);
	bool Update(void);
	bool UpdateE(void);
	
	//弾のレイ判定
	void BulletJudg(const int *TypeCar,const unsigned int *CarNo);

	//壁と車体横の判定
	void Side_Judg(const int *Car_Type, const unsigned int *Car_No);
	bool Side_Judg(const bool *Left_Flg,const int *Car_Type,const unsigned int *Car_No);

	//敵の誕生と思考
	bool UpdateEnemyAI(void);
	//敵の移動
	bool UpdateEnemyMove(void);

	//前進レイ判定
	bool ForMoveJudg(const CONSTITUTION *Con,const D3DXMATRIX *StartMat,const D3DXMATRIX *EndMat,
		const int *Car_Type,const unsigned int *Car_No,const D3DXVECTOR3 *RayVec1,const D3DXVECTOR3 *RayVec2,
		const D3DXVECTOR3 *RayVec3,float *SpeedMul2,const D3DXVECTOR3 *ScalPos,const bool *CollisionJudg_TrueFlg);


	//移動後の行列作成
	void ForMoveEnd(D3DXMATRIX *Mat,const CONSTITUTION *Con,const QuaForMove *q,const D3DXMATRIX *TransMat);
	//カメラと壁判定
	void CameraWallJudg(void);
	//BulletBirthFlg
	bool GetBulletBirthFlg(void);
	//爆発インスタンス化関数
	void BombInit(const D3DXMATRIX *Mat);
	//デリートエネミー
	bool EnemyDelete(const unsigned int *EnemyNo);

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
	//タイトルに戻るキー
	bool Change_TitleScene(void);

	//コンストラクタ関数
	void AllNew(void);
	//デストラクタ関数
	void AllDelete(void);

	/*アップデート*/

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

	//車の今の位置の更新
	bool Update_Car_SetMat(void);

	//カメラ行列の取得
	bool Update_CameraMat(void);

	//地面の出現
	int Init_Ground_Push(const D3DXMATRIX *Mat1, const D3DXMATRIX *Mat0,const int *Type);

	//ゲーム本編の最後の更新
	bool Update_Pop_End(void);

	//車の出現確認
	bool Get_Car_Pop(const int *Car_Type);

	//車の出現の更新の停止命令渡し
	bool Get_Car_Pop_Update_MoveFlg(void);

	//地面の情報入れ
	void Set_Ground_Data(void);

	//ゲームオーバー時
	void Set_Game_Over(void);

	//ゲームクリア時
	void Set_Game_Clear(void);

	//全ての弾の更新
	bool Update_Bullet(void);

	//弾のMoveVecの加算の更新
	bool Update_Bullet_MoveVec(void);

	//弾の出現準備の更新
	bool Update_Bullet_Enemy_Init(void);

	//弾の出現の更新
	bool Update_Bullet_Init(void);

	//弾の判定の更新
	bool Update_Bullet_Judg(void);

	//弾の更新
	bool Update_Bullet_Move(void);

	//レールの操作
	int Get_Rail_Num(const int *Way_Rail_Num, const int *Pop_Rail_Num);

	//音の管理
	bool Update_Sound(void);

	void New_Sound(const int *Type, const int *Category, const int No, const int *Change);
	void New_Sound(const int *Category, const int No,const D3DXVECTOR3* Pos, const int *Change);

	bool Update_Damage_Num_Draw(void);

	//ゲーム終了Flg
	bool Get_End_Flg(void);

	//ゲームのモードチェンジ
	void Geme_End_Change(const int *Mode);

	//敵の出現
	void Pop_Enemy(void);

	//車の出現可能調査(出現可能ならtrue)
	bool Car_Pop_Judg(const D3DXMATRIX *GroundMat, const float *TransX);

	//出現する車とプレイヤーの出現判定
	bool Car_Pop_Judg_Player(const D3DXVECTOR3 *Pop_Pos, const float *Pop_Radius);

	//出現する車とエネミーの出現判定
	bool Car_Pop_Judg_Enemy(const D3DXVECTOR3 *Pop_Pos, const float *Pop_Radius);

	//デバック用の文字表示
	void Debug_Text(void);

	//車の生存確認

	/*削除*/
	void Delete_Damage_Num_Draw(unsigned int *vector_No);
	void New_Damage_Num_Draw(const int *Character_Type, const D3DXMATRIX* Ray_Mat, const D3DXVECTOR3* Ray_Vec
		,const float *Ray_Dis, const int *Damage, const bool *DamageFlg);

	/*弾*/

	//弾判定の情報初期化
	BULLETJUDGDATA GetInitBJD(const float *InitDis);
	//弾判定集
	void BulletJudgGround(BULLETJUDGDATA* BJD,const RAYDATA *RD,bool *HitFlg,const float *Rad);
	void BulletJudgPlayer(BULLETJUDGDATA* BJD, const RAYDATA *RD, const float *Rad);
	void BulletJudgEnemy(BULLETJUDGDATA* BJD,const RAYDATA *RD, const float *Rad,const unsigned int *EnemyNo);
	void BulletJudgEnemy_Ball(BULLETJUDGDATA* BJD, const RAYDATA *RD, const float *Rad);
	//弾判定によるダメージ計算
	bool SetBulletDamage(const BULLETJUDGDATA* BJD, const RAYDATA *RD,const int Damage);
	bool SetBulletDamageGround(const BULLETJUDGDATA* BJD, const RAYDATA *RD);
	bool SetBulletDamageWall(const BULLETJUDGDATA* BJD, const RAYDATA *RD);
	bool SetBulletDamagePlaCar(const BULLETJUDGDATA* BJD, const RAYDATA *RD, const int *Damage);
	bool SetBulletDamagePlaParts(const BULLETJUDGDATA* BJD, const RAYDATA *RD, const int *Damage);
	bool SetBulletDamagePlaGun(const BULLETJUDGDATA* BJD, const RAYDATA *RD, const int *Damage);
	bool SetBulletDamageEneCar(const BULLETJUDGDATA* BJD, const RAYDATA *RD, const int *Damage);
	bool SetBulletDamageEneParts(const BULLETJUDGDATA* BJD, const RAYDATA *RD, const int *Damage);
	bool SetBulletDamageEneGun(const BULLETJUDGDATA* BJD, const RAYDATA *RD, const int *Damage);

	/*横の衝突判定*/

	//横の衝突判定の準備
	bool SideJudg_Preparation(S_SideJudgChara *Judg_Car, D3DXMATRIX *JudgMat,
		D3DXVECTOR3 *JudgVec, float *SmallDis, float *Over_Dis, const int *JudgMat_Num);

	//横の衝突判定でプレイヤーと判定
	int Side_Judg_Player(S_SideJudgChara *Next_Data, float *Small_Dis,int *RayHit_No,
		D3DXMATRIX *RayHit_Mat, float *Over_Dis, bool *Over_Flg,const S_SideJudgChara *Data,
		const int *JudgMat_Num,const D3DXMATRIX *JudgMat,const D3DXVECTOR3 *Ray_Vec);

	//横の衝突判定で敵と判定
	int Side_Judg_Enemy(S_SideJudgChara *Next_Data, float *Small_Dis, int *RayHit_No,
		D3DXMATRIX *RayHit_Mat, float *Over_Dis, bool *Over_Flg, const S_SideJudgChara *Data,
		const int *JudgMat_Num, const D3DXMATRIX *JudgMat, const D3DXVECTOR3 *Ray_Vec);

	//横の衝突判定で地面と判定
	bool Side_Judg_Ground(const S_SideJudgChara *Data,
		const D3DXMATRIX *JudgMat_Base,const D3DXVECTOR3 *Ray_Vec, float *Small_Dis,
		int *RayHit_No, D3DXMATRIX *RayHit_Mat);

	//横の衝突判定
	int Side_Judg_Ray(S_SideJudgChara *Next_Data, float *Small_Dis, int *RayHit_No,
		D3DXMATRIX *RayHit_Mat, float *Over_Dis, bool *Over_Flg, const int *Judg_Car_Type,
		const unsigned int *Car_No, const S_SideJudgChara *Data, const int *JudgMat_Num,
		const D3DXMATRIX *JudgMat, const D3DXVECTOR3 *Ray_Vec);

	int Side_Judg_Ray(const int *Judg_Car_Type, const unsigned int *Car_No, const float *Car_Rad, S_SideJudgChara *Next_Data
		, float *Small_Dis,int *RayHit_No, D3DXMATRIX *RayHit_Mat,const float *Ray_Hit_Dis,const D3DXMATRIX *Judg_Car_Mat,const int *RayPos_No);

	//横の衝突判定の壁の火花の出現処理
	void Wall_Spark_Init(bool *Spark_Init_Flg, const D3DXMATRIX *RayHit_Mat, const D3DXVECTOR3 *RayHit_Pos, bool *LeftFlg);
	void Car_Spark_Init(const bool *Spark_Init_Flg, const D3DXMATRIX *RayHit_Mat, const D3DXVECTOR3 *RayHit_Pos);

	/*レイ判定*/
	//プレイヤーのコリジョンモデル
	bool Ray_Judg_Player_ColModel(const D3DXVECTOR3* Ray_Pos, const D3DXVECTOR3* Ray_Vec, float *Dis);
	//敵のコリジョンモデル
	bool Ray_Judg_Enemy_ColModel(const unsigned int *Enemy_No,const D3DXVECTOR3* Ray_Pos, const D3DXVECTOR3* Ray_Vec, float *Dis);

	//衝突による敵のAiと攻撃をStopさせる
	void Enemy_Stop(const unsigned int *e,const int *Side_Judg_Car_Type);

private:
	//判定用の関数のクラス
	Judg judg;

	//デバッグ用----------------
	int CountNum, MaxCount;//スロー再生用
	Spear *spear;
	D3DXMATRIX SpeMat;
	//--------------------------
	//プレイヤーの情報
	C_PlayerBody *PlayerBody;
	//プレイヤー
	C_PlayerBase *player;//

	//地面のメンバ
	std::vector<C_Ground_Object*>ground;
	Cou *cou;//bill
	std::vector<Cou*>GroCou;
	//外灯表示用カウントダウン
	C_Count *LightCount;

	std::vector<C_EnemyAi*>enemy;
	bool eneFlg;//出現の切り替え
	Sky *sky;
	Aiming *aiming;
	std::vector<Explo*>explo;
	Camera *camera;
	Debug *debug;
	//文字表示
	C_Text_Num *M_Text_Num;
	
	C_Game_End_Base* M_C_Game_End;

	Warning *war;

	int StageNo;
	

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

	/*車の沸き情報*/
	C_Car_Pop_New *M_C_Car_Pop;

	/*地面の情報*/
	C_Ground_Pop_New* M_C_Ground_Pop;

	//音の管理
	C_Sound_Manager_Base* M_C_Sound_Manager;

	std::vector<C_Damage_Num_Base*>M_Damage_Num_Draw;

	//ミニ画面の表示
	S_SCREEN_2D M_S_Screen;

	//ミニ画面の初期化
	void Debug_Screen_Init(void);
	//ミニ画面の終了処理
	void Debug_Screen_End(void);
	//ミニ画面の表示
	void Debug_Screen_Draw(void);

	//視錐台カリング
	void FrustumCulling(const D3DXMATRIX *mProj, const D3DXMATRIX *mView, const D3DVIEWPORT9 *Viewport);

	//地面の視錐台カリング
	void FrustumCulling_Ground(const S_Frustum_Vec *FV_Data);

	//地面の壁の視錐台カリング
	void FrustumCulling_Ground_Wall(const unsigned int *gNo, const S_Frustum_Vec *FV_Data);

	//地面の表示物の視錐台カリング
	void FrustumCulling_Ground_Object(const unsigned int *gNo, const S_Frustum_Vec *FV_Data);

	//被弾音を流す処理
	void Set_BulletHit_Sound(const int *BulletHit_Type, const D3DXVECTOR3 *Sound_Pos);
	void Set_BulletHit_Sound(const int *BulletHit_Type, const D3DXVECTOR3 *Sound_Pos,const bool *DamageFlg);
	void Set_BulletHit_Sound(const int *BulletHit_Type, const BULLETJUDGDATA* BJD, const RAYDATA * RD,const bool *DamageFlg);

	/*正面衝突判定*/

	//プレイヤーと正面衝突判定
	void M_ForMoveJudg_Player(bool *JudgFlg, float *SmallDis,int *Hit_CarType,
		unsigned int *Hit_CarNumber, const int *Car_Type,
		const D3DXMATRIX *StartMat, const D3DXMATRIX *EndMat, const D3DXMATRIX *TransMat,
		const int *TransNum, const D3DXVECTOR3 *MoveVec, const D3DXVECTOR3 *PosBig,
		const D3DXVECTOR3 *PosSmall, const D3DXVECTOR3 *ScalPos,
		const bool *CollisionJudg_TrueFlg);

	//敵と正面衝突判定
	void M_ForMoveJudg_Enemy(bool *JudgFlg, float *SmallDis, int *Hit_CarType,
		unsigned int *Hit_CarNumber,const int *Car_Type,const unsigned int *Car_No,
		const D3DXMATRIX *StartMat, const D3DXMATRIX *EndMat, const D3DXMATRIX *TransMat, const int *TransNum,
		const D3DXVECTOR3 *MoveVec, const D3DXVECTOR3 *PosBig, const D3DXVECTOR3 *PosSmall,
		const D3DXVECTOR3 *ScalPos, const bool *CollisionJudg_TrueFlg);

	//正面衝突判定の移動後の車のレイの発射位置とベクトルの作成
	bool M_ForMoveJudg_AfterMovingRay(D3DXVECTOR3 *Ray_Pos, D3DXVECTOR3 *Ray_Vec,const int *Vec_No,
		const D3DXVECTOR3 *PosBig,const D3DXVECTOR3 *PosSmall,const D3DXVECTOR3 *ScalPos,const D3DXMATRIX *EndMat);

	//死亡確認
	bool Get_Dead_Flg(const int *Car_Type,const unsigned int *Car_Number);

	//特定のターゲットを死亡させる
	void M_Dead_Car(const int *Car_Type, const unsigned int *Car_Number);

	//出現している車の情報の作成と車の出現の更新
	void M_Car_Pop_Data_Update(void);

};

//#endif // !GameScene_H
