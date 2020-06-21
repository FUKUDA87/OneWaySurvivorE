#pragma once
#include<d3dx9.h>
#include"../GameSource/Struct.h"
#include"../Const/Const_Sound_Type.h"
#include"Base/Sound_Base_2D.h"
#include"vector/Sound_Data_Vector.h"
#include"../Const/Const_Damage.h"
#include<vector>

//サウンドの流すクラス
class c_GameSoundManager:public C_Sound_Data_Vector {
public:
	
	~c_GameSoundManager();

	//音の更新
	bool Update_Sound(const int *Volume);
	bool Update_Sound(const D3DXVECTOR3 *CamPos, const D3DXVECTOR3 *CamLook, const D3DXVECTOR3 *CamHead, const int *Volume);

	//モードの検索
	bool Judg_Sound(const S_SOUND_DATA* M_Data, const int *Volume);

	//音の変更
	void Set_Sound(const int *Volume);

	void Reset(void);

	void Stop(void);

	void Stop(const int CategoryNo);

	void Restart(const int *Volume);

	//被弾音を流す処理
	void Set_Bullet_Hit_Sound(const int * BulletHit_Type, const D3DXVECTOR3 * Sound_Pos, const int *Volume);

	//被弾した物体が無敵状態の判定と音を流す処理
	void Set_Bullet_Hit_Sound(const int * BulletHit_Type, const D3DXVECTOR3 * Sound_Pos,const bool *DamageFlg, const int *Volume);

	/*BGM*/

	// 再生開始
	void BGMStart(void);
	// 削除
	void BGMDelete(void);
	// 再生再開
	void BGMRestart(const int *Volume);
	// 停止
	void BGMStop(void);

private:
	std::vector<C_Sound_Base_2D*>m_SoundManager;
	C_Sound_Base_2D *m_BGMSound;

	S_CAMERA_POS M_CamPos;

	//情報の検索
	bool Judg_Data2(const S_SOUND_DATA* M_Data, const S_SOUND_DATA* Set_Data);
	bool Judg_Data(const S_SOUND_DATA* M_Data, const S_SOUND_DATA* Set_Data);

	//弾の検索
	bool Judg_Bullet(const S_SOUND_DATA* Data, const int *Volume);

	//BGMの検索
	bool Judg_BGM(const S_SOUND_DATA* Data, const int *Volume);

	//音の全削除
	void Delete_All(void);

	//音の削除
	void Sound_Delete(unsigned int *No);

	//音の削除
	bool Delete_All(const S_SOUND_DATA* M_Data,const bool Flg);

	//音を外部からNew
	bool Set_Sound(const S_SOUND_DATA* Data, const int *Volume);

	//警告音を流す処理
	bool Judg_Warning(const S_SOUND_DATA* Data, const int *Volume);

	//クリック音を流す処理
	bool Judg_Click(const S_SOUND_DATA* Data, const int *Volume);

	//爆発の判定
	bool Judg_Explosion_3D(const S_SOUND_DATA* Data, const int *Volume);

	//最新の音声を流す処理
	void New_Sound_Play(const int *Volume);

	//2Dの検索
	bool Set_Sound_2D(const S_SOUND_DATA* Data, const int *Volume);

	void New_Sound_2D(C_Sound_Base_2D* Sound);


};