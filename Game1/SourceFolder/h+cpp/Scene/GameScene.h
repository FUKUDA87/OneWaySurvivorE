#pragma once
#include<d3dx9.h>
#include<vector>
#include"SceneBase.h"
#include"../Ground/Sky.h"
#include"../Player/Aiming.h"
#include"../Player/Camera.h"
#include"../GameSource/Countdown.h"
#include"../GameSource/Debug.h"
#include"../GameSource/Text_Num.h"
#include"../Draw/2D/GameEnd/Game_End_Now.h"
#include"../GameSource/Struct.h"
#include"../Draw/2D/Warning.h"
#include"../Draw/2D/Pause.h"
#include"../GameSource/Judgment.h"
#include"../Draw/3D/Spear.h"
#include"../GameSource/Motion.h"
#include"../Draw/2D/Score.h"
#include"../Draw/Effect/3D/Spark/Spark2.h"
#include"../Key/CMouse.h"
#include"../Key/KeyTrue.h"
#include"../Player/PlayerA.h"
#include"../Enemy/EnemyA.h"
#include"../Player/PlayerBody.h"
#include"../Draw/Menu/PauseTouch.h"
#include"../Draw/Menu/OverTouch.h"
#include"../GameSource/Count.h"
#include"../Enemy/EnemySelect.h"
#include"../Enemy/Data/Base&Manager/EnemySpeedManager.h"
#include"../Const/Const_Draw_Judg.h"
#include"../Stage_Data/Car_Pop/Car_Pop_New.h"
#include"../Ground/Stage_Ground/Ground_Pop_New.h"
#include"../Sound/GameSoundManager.h"
#include"../Draw/Damage_Num/Damage_Move_A.h"
#include"../Draw/Damage_Num/Damage_Move_B.h"
#include"../Ground/Ground_Object.h"
#include"../GameSource/Option/Option.h"
#include"../Draw/Menu/ClearTouch.h"
#include"../Ground/GroundManager.h"
#include"../Draw/Effect/EffectBase.h"

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

	// 3D描画
	void Render3D(void);

	// 3D描画の上からの視点
	void Render3D_Screen(void);

	// 2D描画
	void Render2D(void);

	// カメラ
	void SetCamera(void);

	// 更新処理
	bool Update(void);

private:

	C_Option *option;

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

	std::vector<C_EnemyAi*>enemy;
	bool eneFlg;//出現の切り替え
	Sky *sky;
	Aiming *aiming;
	Camera *camera;
	Debug *debug;
	//文字表示
	C_Text_Num *M_Text_Num;

	c_GroundManager *groundManager;

	C_Game_End_Base* M_C_Game_End;

	Warning *war;

	int StageNo;


	Pause *pause;

	//スコア
	C_Score *score;

	//バレットバースFlg
	bool BulletBirthFlg;

	//マウス
	C_Mouse *mouse;
	//キー
	C_KeyTrue key;

	//弾痕３D
	std::vector<c_EffectBase*>effect;

	//タッチ
	C_NextTouch* Menu;

	/*車の沸き情報*/
	C_Car_Pop_New *M_C_Car_Pop;

	//音の管理
	c_GameSoundManager* M_C_Sound_Manager;

	std::vector<C_Damage_Num_Base*>M_Damage_Num_Draw;

	//ミニ画面の表示
	S_SCREEN_2D M_S_Screen;

	// 初期化
	void Init(void);

	bool UpdateEnemy(void);
	
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
	
	//BulletBirthFlg
	bool GetBulletBirthFlg(void);
	//爆発インスタンス化関数
	void BombInit(const D3DXMATRIX *Mat);
	//デリートエネミー
	bool EnemyDelete(const unsigned int *EnemyNo);

	//メニューの入れ
	void SetMenu(bool PauseFlg, bool ClearFlg, bool OverFlg);

	//メニューの処理
	bool UpdateMenu(void);
	
	//Pos2D計算
	void Pos2DUpdate(const D3DXMATRIX *mProj, const D3DXMATRIX *mView, const D3DVIEWPORT9 *Viewport);

	//タイトルに戻るキー
	bool Change_TitleScene(void);

	//ゲーム本編の更新
	bool Update_Game(void);

	//ゲーム本編時のポーズ画面移動関数
	bool Update_Game_Pause(void);

	//ゲームのフレーム数の判定
	bool Judg_Game_Frame(void);

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

	//ゲーム本編の最後の更新
	bool Update_Pop_End(void);

	//車の出現確認
	bool Get_Car_Pop(const int *Car_Type);

	//車の出現の更新の停止命令渡し
	bool Get_Car_Pop_Update_MoveFlg(void);

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

	//ミニ画面の初期化
	void Debug_Screen_Init(void);
	//ミニ画面の終了処理
	void Debug_Screen_End(void);
	//ミニ画面の表示
	void Debug_Screen_Draw(void);

	//視錐台カリング
	void FrustumCulling(const D3DXMATRIX *mProj, const D3DXMATRIX *mView, const D3DVIEWPORT9 *Viewport);

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
