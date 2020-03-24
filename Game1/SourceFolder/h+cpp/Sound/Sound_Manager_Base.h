#pragma once
#include<d3dx9.h>
#include"../GameSource/Struct.h"
#include"../Const/Const_Sound_Type.h"
#include"Base/Sound_Base_2D.h"
#include"vector/Sound_Data_Vector.h"
#include"../Const/Const_Damage.h"
#include<vector>

//サウンドの流すクラス
class C_Sound_Manager_Base:public C_Sound_Data_Vector {
public:
	
	~C_Sound_Manager_Base();


	//音の更新
	bool Update_Sound(void);
	bool Update_Sound(const D3DXVECTOR3 *CamPos, const D3DXVECTOR3 *CamLook, const D3DXVECTOR3 *CamHead);

	//モードの検索
	bool Judg_Sound(const S_SOUND_DATA* M_Data);

	//音の変更
	void Set_Sound(void);

	void Stop_Sound_All(void);

	void Stop_Sound_2_All(void);

	void Stop_Sound_2_All(const int CategoryNo);

	void Strat_Sound_All(void);

	//被弾音を流す処理
	void Set_Bullet_Hit_Sound(const int * BulletHit_Type, const D3DXVECTOR3 * Sound_Pos);

	//被弾した物体が無敵状態の判定と音を流す処理
	void Set_Bullet_Hit_Sound(const int * BulletHit_Type, const D3DXVECTOR3 * Sound_Pos,const bool *DamageFlg);
protected:
	//2Dの検索
	bool Set_Sound_2D(const S_SOUND_DATA* Data);

	void New_Sound_2D(C_Sound_Base_2D* Sound);

	std::vector<C_Sound_Base_2D*>M_Sound_2D_Manager;

private:
	S_CAMERA_POS M_CamPos;

	//情報の検索
	bool Judg_Data2(const S_SOUND_DATA* M_Data, const S_SOUND_DATA* Set_Data);
	bool Judg_Data(const S_SOUND_DATA* M_Data, const S_SOUND_DATA* Set_Data);

	//弾の検索
	bool Judg_Bullet(const S_SOUND_DATA* Data);

	//BGMの検索
	bool Judg_BGM(const S_SOUND_DATA* Data);

	//音の全削除
	void Delete_All(void);

	//音の削除
	void Sound_Delete(unsigned int *No);

	//音の削除
	bool Delete_All(const S_SOUND_DATA* M_Data,const bool Flg);

	//音を外部からNew
	bool Set_Sound(const S_SOUND_DATA* Data);

	//警告音を流す処理
	bool Judg_Warning(const S_SOUND_DATA* Data);

	//クリック音を流す処理
	bool Judg_Click(const S_SOUND_DATA* Data);

	//爆発の判定
	bool Judg_Explosion_3D(const S_SOUND_DATA* Data);

	//最新の音声を流す処理
	void New_Sound_Play(void);


};