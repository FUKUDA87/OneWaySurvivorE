#pragma once
#include<d3dx9.h>
#include<dsound.h>

//#ifndef Struct_H
//#define Strcut_H

//XFILEの構造体
struct XFILE {
	LPD3DXMESH lpMesh;//メッシュの形状のデータ
	DWORD NumMaterial;//グループの数
	D3DMATERIAL9 *Mat;//マテリアルの内容xグループ数
	LPDIRECT3DTEXTURE9 *Tex;//テクスチャの内容xグループ数
};
//VERTEXの構造体
struct VERTEX
{
	D3DXVECTOR3 Pos;
	D3DCOLOR Color;
	D3DXVECTOR2 Tex;
};
//TEXTUREの構造体
struct TEXTURE {
	LPDIRECT3DTEXTURE9 Tex;
	int Width, Height;
	int r, g, b;
};
//表示物3Dの構造体
struct  BASE3D {
	D3DXMATRIX Mat, Trans,Rot, RotX, RotY, RotZ, Scal,DrawMat;
	D3DXVECTOR3 Pos,ScaPos,TraPos;
	double AngX, AngY, AngZ;
	bool Flg, DrawFlg, UpdateFlg;//存在のオンとオフ
	float AttRad,BodRad;//当たり判定の半径
	bool MoveFlg;//動いているかどうか
	DWORD NumVertex;
};
//表示物2Dの構造体
struct  BASE2D {
	D3DXMATRIX Mat, Trans, RotZ, Scal;
	D3DXVECTOR3 Pos,ScaPos,TraPos;
	D3DXVECTOR3 Pos2D;
	float AngZ;
	bool Flg,DrawFlg,UpdateFlg;//存在のオンとオフ
	bool MFlg;//動いているかどうか
};
//キャラの基本情報
struct CHARABASE {
	int MaxHp, NowHp;//Hp
	int DamageSetFlg;//ダメージを受けるFlg
};
//ステータスの構造体
struct STATUS {
	CHARABASE CharaBase;
	//int NowLevel, MaxLevel;
	//float Attack, Defense, Critical;//攻撃力と守備力と運
};
//ゲームシステムの情報の構造体
struct CONSTITUTION {
	D3DXVECTOR3 Speed;//スピード
	int NowSpeed,MaxSpeed;
	float SpeedMul, SpeedMulJudg;//multiplication
	bool CurFlg;//車線変更時の判定
	bool CurLFlg;//車線変更時の左キー設定
	bool CurRFlg;//車線変更時の右キー設定
	bool DFlg;//敵の攻撃判定フラグ
	bool PEFlg;//敵と自機が衝突フラグ
	unsigned int GroNum;//今の地面
	D3DXMATRIX JudgMat;//車体の方向を得るためのMat
	XFILE ColModMesh;//コリジョンモデル
	XFILE DeadMesh;//死後のメッシュ
	D3DXVECTOR3 PosBig;//メッシュのプラスの遠い座標+方向
	D3DXVECTOR3 PosSmall;//メッシュのプラスの遠い座標-方向
};
struct EneCon {
	float Size;//playerと距離
	bool SiFlg;//playerと距離の判定
};
//立体物3Dの構造体
struct Object3D {
	XFILE Mesh;
	BASE3D Base;
};
//立体物3Dの構造体
struct Object3D2 {
	XFILE Mesh;
	BASE3D Base;
	XFILE ColModMesh;//コリジョンモデル
	D3DXVECTOR3 PosBig;//メッシュのプラスの遠い座標+方向
	D3DXVECTOR3 PosSmall;//メッシュのプラスの遠い座標-方向
};
//キャラクター3Dの構造体
struct CHARA3D {
	XFILE Mesh;
	BASE3D Base;
	STATUS Sta;
	CONSTITUTION Con;
};
struct Enemy3D {
	CHARA3D CH;
	EneCon EC;
};
//画像2Dの構造体
struct CHARA2D {
	TEXTURE TEX;
	BASE2D Base;
};
//画像2Dの構造体2
struct CHARA2D2 {
	TEXTURE TEX;
	TEXTURE TEX2;
	BASE2D Base;
};
//板ポリゴン四角形の構造体
struct Pol {
	VERTEX v[4];
	TEXTURE TEX;
	BASE3D Base;
	//沢山のポリゴン表示用
	D3DXMATRIX *PolMat;
	int PolNum;
};
//道の情報
struct Way
{
	int WayType;//車道の型
	bool Cur;//カーブの車道判定
	float Ang;
	D3DXMATRIX StartMat;//クォータニオン用の始点Mat
	int RailNum;//車線の数
	float *CurTransX;//車線の初期状態の横移動Mat
};
struct judgDeta {
	D3DXMATRIX Mat;
	float Rad;
	int Hp;
	int MaxHp;
};
struct QuaAnim {
	D3DXMATRIX EndMat, StartMat,NowMat,RotX,RotY,RotZ,RotA,Trans;
	float Ang;
	float AnimeFrame,FrameUp,Reverse;//Reverseは1.0fか-1.0f
	D3DXVECTOR3 Pos, Vec,StartPos,EndPos;
	bool MoveFlg,ReverseFlg;
	int Count, CountEnd;
};
struct QuaMove {
	float SpeB;
	//int Qup;//クォータニオン用のMat[変数]
	bool qFlg, qGFlg, cFlg;
	unsigned int GroNo;
	D3DXMATRIX StartMat, EndMat;
};
struct EnemyPop {
	int MaxNum;//最大出現数
	int rePopTime[10];//敵が沸くまでの時間
	int EneNumber[10];//敵の種類
};
struct CHARAData {
	D3DXMATRIX NowMat,StartMat,EndMat;
	float Rad;
	int Speed;
	unsigned int NowGround;
	bool GroundFlg,DrawFlg,CurFlg;
	LPD3DXMESH Mesh;
};

struct CLONEVERTEX {
	D3DXVECTOR3 Pos;//座標
	D3DXVECTOR3 Normal;//法線
	D3DXVECTOR2 Tex;//テクスチャ座標
};
struct QuaForMove{
	D3DXMATRIX NowMat, StartMat, EndMat;
	float AnimeFrame, BodyHeight,SpeedMul,SpeedMul2;
	bool QuaInitFlg,QuaMatInitFlg,CurFlg;
	D3DXVECTOR3 WayVec, CurVec;
};
//プレイヤー以外のスピード管理構造体
struct SpeedMove {
	float NowSpeedMul, SpeedUp,MaxSpeed,StopSpeed;
};
//サウンド用カメラ構造体
struct SoundCamera {
	D3DXVECTOR3 CamPos, CamLook, CamHead;
};
//メッシュのサイズ
struct SizePos {
	D3DXVECTOR3 Big, Small;
};
//サウンド構造体
struct SoundCol {
	LPDIRECTSOUNDBUFFER8 Sound;
	LPDIRECTSOUND3DBUFFER8 Sound3D;
};
//クォータニオンアニメーション
struct QuaAnimeC {
	D3DXMATRIX NowMat, StartMat, EndMat;
	float NowAnime, AnimeFrame;
};
//ポリゴン用クォータニオン
struct PolQuaAni
{
	QuaAnimeC Qac;
	//透明度
	int Alpha,AlphaMax;
	float PolSizeNow, PolSizeMax,PolSizeSmall;
};
//３つのメッシュ
struct XFILE3 {
	XFILE Mesh1;
	XFILE Mesh2;
	XFILE Mesh3;
};
//３つのメッシュ
struct XFILE3B {
	XFILE DrawMesh;//表示用モデル
	XFILE ColModMesh;//判定用モデル
	XFILE DeadMesh;//死後用モデル
};

//パーツ用クラス
struct S_CAR_PARTS_DATA {
	D3DXVECTOR3 TransPos,Ang;//移動、パーツにつなげる用,回転用
	int MeshTypeNo;//メッシュ種類
	int MeshJointNo;//メッシュの種類の中の番号
};
struct ObjectParts {
	BASE3D Base;
	D3DXMATRIX SuperMat;
};
//バレット用
struct BULLETRAYJUDG {
	D3DXVECTOR3 MoveVec;//車の移動量
	D3DXVECTOR3 RayPos;//レイが当たった位置
	bool JudgRayFlg;//レイが当たったか
};

struct QUAMAT {
	D3DXMATRIX RotXMat, RotYMat;
};
//敵の銃回転用
struct GUNAI {
	BASE3D NowBase;
	//回転クォータニオン
	QUAMAT Start, End;
	float NowAnime, AnimeFrame;
	//銃の動きのFlg
	bool GunMoveFlg;

	//レイ判定フラグ
	bool RayJudgFlg;

	//レイが当たった回数
	int RayCountNow,RayCountInit;

	//狙う座標
	D3DXVECTOR3 TragetPos;

	//発射数
	int BulletNum;

	//発射Flg
	bool BulletFlg;

	//発射後の発射タイミング
	int BulletCount;

	//発射後の休憩
	int GunCount;

	//全ての工程終了
	bool EndFlg;

	//引っ付く行列
	D3DXMATRIX ConnectMat;

	//AIFlg
	bool AIFlg;

	//回転終了Flg
	bool GunMoveEndFlg;

	//レイの長さ
	float RayDis;
};

//プレイヤーの車体状態
struct BODYDATA {
	int CarBodyNo;
	int TireNo;
	int StandNo;
	int GunNo;
};
//プレイヤーの車体状態
struct BODYDATAFLG {
	bool CarBodyBulletFlg;
	bool CarBodyAttackFlg;
	bool TireBulletFlg;
};
//車体状態
struct BODYDATACar {
	BODYDATA Body;
	D3DXVECTOR3 ScalPos;
	int MaxHp;
	BODYDATAFLG JudgFlg;//当たり判定のダメージ許可Flg
	int EnemyNo;
};
//銃の表示情報
struct S_GUN_DRAW_NO {
	int GunNo;
	int BulletNo;
	int MuzFlaNo;
	int LaserNo;
};
//銃の情報
struct GUNDATA {
	BASE3D Base;
	XFILE Mesh;
	//レーザー始点と終点
	D3DXVECTOR3 LaserPos_Start,LaserPos_End;
	//レーザー判定とレーザー判定の許可
	bool HitRayFlg, JudgRayFlg;
	//レーザーの長さ
	float LaserSize;
	//表示の情報保管
	S_GUN_DRAW_NO DrawNo;
};
struct Object3DGun {
	float AngX, AngY, AngZ;
	D3DXVECTOR3 TransPos, ScalPos;
	bool DrawFlg;
};
//銃の初期化情報
struct GUNINITDATA {
	S_GUN_DRAW_NO DrawNo;//表示種類
	CHARABASE  CharaBase;//hpのセット
	float LaserSize;//レイの長さ
	Object3DGun InitGun;
	
};
struct GETGUNDATA {
	int TexNo;
	int MeshNo;
	D3DXVECTOR3 MeshScalPos;
	int PolNum;
	float PolSize;
	int InitCountMax;
	D3DXMATRIX Mat;
	float Speed;
};
//弾判定用
struct BULLETJUDGDATA {
	int Type;
	unsigned int JudgNo1;
	unsigned int JudgNo2;
	unsigned int JudgNo3;
	float SamllDis;//レイの最小の長さ保管
};
//レイ判定
struct RAYDATA {
	D3DXMATRIX Mat;
	D3DXVECTOR3 Ray;
};
struct S_ENEMYGUNDATA {
	S_GUN_DRAW_NO DrawNo;
	Object3DGun Gun;
	CHARABASE Hp;
	D3DXVECTOR3 TargetPos;
	int NowPhase;
	QUAMAT NowRot;
	D3DXMATRIX StandMat,TransMat;
	//レイ
	bool RayJudgFlg, RayHitFlg;
	float RayDis;
	//発射フラグ
	bool BulletFlg;
	bool LaserFlg;
	//ターゲットに照準があって完了した時
	bool LockonEndFlg;
};
struct S_ENEMYPARTSDATA
{

};
struct S_ENEMYBODYDATA {
	BODYDATA Body;
	D3DXVECTOR3 ScalPos;
	float GroundHeight;
	CHARABASE CharaBase;
};

struct S_TEXPOS {
	int x;
	int y;
};
struct S_Random {
	int x, y, z;
};
//煙の表示調整用構造体
struct S_Smog
{
	//移動方向ベクトル
	D3DXVECTOR3 MoveVec;
	//移動のフレーム数
	D3DXVECTOR3 Frame;
	//透明度の変数
	int Alpha, AStart, AUp;
	//ポリゴンのサイズ
	float PolSize,PolBit,PolBitUp;
	//表示用
	int Draw_No;
	//移動量の変化
	S_Random Random;
};
//表示の構造体
struct S_DrawBase {
	//
	D3DXMATRIX Mat;
	D3DXVECTOR3 Pos,TransPos,ScalPos;
	float AngX, AngY, AngZ;
};
//回転行列
struct S_DrawRotMat {
	D3DXMATRIX X, Y, Z;
};


//板ポリゴン四角形の構造体
struct S_Pol {
	//沢山のポリゴン表示用
	D3DXMATRIX *PolMat;
	int PolNum;
};

//弾のベース構造体
struct S_BULLET {
	int Damage;
	float Speed;
};

struct S_POL_DATA {
	//表示ポリゴン数
	int PolNum;
	//各頂点
	D3DXVECTOR3 Pos[4];
	//横幅
	float Size;
};



//弾の情報
struct S_BULLET_DATA {
	int DrawType;
	S_BULLET BULLET;
	int TexNo, MeshNo;
};

struct S_GUN_UPDATE_DATA {
	//手動
	D3DXMATRIX CameraMat;
	/*自動*/
	D3DXVECTOR3 TargetPos;
	//キャラ
	int NowPhase;
	//スタンド
	D3DXMATRIX StandMat;
};

struct S_BULLET_DEPAR {
	//銃の発射モード
	int Bullet_Gun_Mode;//1が弾数、２が発射回数、３が秒数。
	int Count_Departure;//123の回数のセット
};

struct S_GUN_DATA {
	//表示処理
	S_DrawBase DrawBase;
	S_DrawRotMat RotMat;
	
	//ターゲットに照準があって完了した時
	bool LockonEndFlg;
	//キャラ
	float ScalSize;

	/*レーザー*/
	//レーザーの表示フラグ
	bool LaserDrawFlg;
	//レーザーの長さ
	float RayDis;
	//レイ判定フラグ
	bool Ray_Hit_Flg;
	bool Ray_Judg_Flg;

	/**/
	//発射フラグ
	bool BulletFlg;

	//発射した弾数
	int Departure_Num;

	//プレイヤーが操作するかFlg
	bool PlayerFlg;

	//今の表示の回転
	QUAMAT NowRot;

	//動きのFlg
	bool MoveFlg;

	//銃の自動撃ちの時の構造体
	S_BULLET_DEPAR Depar;

	//レートの確認
	bool RateFlg;
};

struct S_PARTS_DATA {
	D3DXVECTOR3 JointPos;
};

struct S_GUN_INIT_DATA {

};

struct S_CategoryNo {
	//a=Car.Gun,b=GunNo1.GunNo2
	int a, b;
};

//表示３Dの
struct S_DRAW3D_DATA {
	//表示のタイプ(Pol,Mesh,Pol+Mesh)
	S_CategoryNo Draw3DType;
	//Textureのナンバー
	int TextureNo;
	//メッシュのナンバー
	int MeshNo;
};

//レイ判定の結果の構造体
struct S_RAY_HIT_JUDG_DATA {
	//レイが当たった判定
	bool Flg;
	//レイが当たった位置
	D3DXMATRIX Mat;
};

//弾の初期化の情報渡し
struct S_BULLET3D_INIT_DATA {
	/*銃の表示*/
	S_DRAW3D_DATA Draw3D_Data;

	/*銃の動き*/

	/*プレイヤーの場合*/
	S_RAY_HIT_JUDG_DATA RayHitData;

	/*敵の場合*/

};

//ポリゴン表示の初期化
struct S_PolMat_INIT {
	int PolNum;
	int TexNo;
	D3DXMATRIX Mat;
	float PolSize;
};

//銃のパーツのデータ
struct S_Gun_Parts_Data {
	//弾を撃つことができるFlg
	bool BulletFlg;
	//銃の中心から離れたところの座標
	D3DXVECTOR3 TarnsPos;
	//銃口
	D3DXVECTOR3 MouthPos;
	//レート
	int Rate;
	//弾No
	int BulletNo;
	//カテゴリー数
	int CategoryNo;
	//ブレ度とミリサイズ
	int Bure, BureSura;

};

//色,渡し
struct S_COLOR {
	int r, g, b;
};

struct S_TEX_POS {
	int Width, Height;
};

struct S_TEX_DRAW_DATA
{
	S_TEX_POS Pos;
	S_COLOR Color;
};

struct S_GAGE {
	int Now, Max;
};




//#endif // !Struct_H