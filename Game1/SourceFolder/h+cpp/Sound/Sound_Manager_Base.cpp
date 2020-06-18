#include "Sound_Manager_Base.h"
#include"SE/Sound_2D_Gun_1.h"
#include"BGM/Sound_BGM_Manager.h"
#include"SE/Warning/Sound_Warning_Manager.h"
#include"SE/Click/Sound_Click_Manager.h"
#include"SE/SE_Manager/Sound_Explosion_Manager.h"
#include"SE/Bullet_Hit/Sound_Bullet_Hit_Manager.h"

C_Sound_Manager_Base::~C_Sound_Manager_Base()
{
	//Stop_Sound_All();

	Delete_All();
}

bool C_Sound_Manager_Base::Update_Sound(const int *Volume)
{
	if (M_Sound_2D_Manager.size() < 1)return false;

	bool Flg = false;

	for (unsigned int s = 0; s < M_Sound_2D_Manager.size(); s++) {
		if (M_Sound_2D_Manager[s]->Update(&M_CamPos,&Flg,Volume) == false) {
			delete M_Sound_2D_Manager[s];
			M_Sound_2D_Manager.erase(M_Sound_2D_Manager.begin() + s);
			s--;
		}
	}

	return false;
}

bool C_Sound_Manager_Base::Set_Sound(const S_SOUND_DATA * Data, const int *Volume)
{
	//サウンドの種類
	switch (Data->Sound_CategoryNo)
	{
	case Co_Sound_Category_Bullet:
		return Judg_Bullet(Data,Volume);
		break;
	case Co_Sound_Category_BGM:
		return Judg_BGM(Data, Volume);
		break;
	case Co_Sound_Category_Warning:
		return Judg_Warning(Data, Volume);
		break;
	case Co_Sound_Category_Click:
		return Judg_Click(Data, Volume);
		break;
	case Co_Sound_Category_Explosion:
		return Judg_Explosion_3D(Data, Volume);
		break;
	case Co_Sound_Category_Bullet_Hit:
		return true;
		break;
	}

	return false;
}

bool C_Sound_Manager_Base::Judg_Warning(const S_SOUND_DATA * Data, const int *Volume)
{
	bool Flg = true;

	C_Sound_Warning_Manager Manager;

	New_Sound_2D(Manager.Get_Warning(&Data->Sound_No));
		
	M_Sound_2D_Manager[M_Sound_2D_Manager.size() - 1]->Update(&M_CamPos, &Flg,Volume);

	return true;
}

bool C_Sound_Manager_Base::Judg_Click(const S_SOUND_DATA * Data, const int *Volume)
{
	bool Flg = true;

	C_Sound_Click_Manager Manager;

	New_Sound_2D(Manager.Get_Click(&Data->Sound_No));

	M_Sound_2D_Manager[M_Sound_2D_Manager.size() - 1]->Update(&M_CamPos, &Flg,Volume);

	return true;
}

bool C_Sound_Manager_Base::Judg_Explosion_3D(const S_SOUND_DATA * Data, const int *Volume)
{
	bool Flg = true;

	C_Sound_Explosion_Manager Manager;

	New_Sound_2D(Manager.Get_Sound(Data));

	M_Sound_2D_Manager[M_Sound_2D_Manager.size() - 1]->Update(&M_CamPos, &Flg,Volume);

	return true;
}

void C_Sound_Manager_Base::New_Sound_Play(const int *Volume)
{
	//音声を流すFlg
	bool PlayFlg = true;

	//音声を流す処理
	M_Sound_2D_Manager[M_Sound_2D_Manager.size() - 1]->Update(&M_CamPos, &PlayFlg,Volume);
}

void C_Sound_Manager_Base::Set_Sound(const int *Volume)
{
	if (Get_Sound_Data_Num() < 1)return;

	for (unsigned int d = 0; d < Get_Sound_Data_Num(); d++) {

		if (Judg_Sound(&Get_Sound_Data(&d), Volume) == true) {

			Delete_Sound(&d);
		}
	}
}

void C_Sound_Manager_Base::Stop_Sound_All(void)
{
	if (M_Sound_2D_Manager.size() < 1)return;

	for (auto&& s : M_Sound_2D_Manager) {
		s->StopSound_All();
	}
}

void C_Sound_Manager_Base::Stop_Sound_2_All(void)
{
	if (M_Sound_2D_Manager.size() < 1)return;

	for (auto&& s : M_Sound_2D_Manager) {
		s->Stop_Sound2();
	}
}

void C_Sound_Manager_Base::Stop_Sound_2_All(const int CategoryNo)
{
	if (M_Sound_2D_Manager.size() < 1)return;

	for (auto&& s : M_Sound_2D_Manager) {
		if (s->Get_Data().Sound_CategoryNo == CategoryNo) {
			s->Stop_Sound2();
		}
	}
}

void C_Sound_Manager_Base::Strat_Sound_All(const int *Volume)
{
	if (M_Sound_2D_Manager.size() < 1)return;

	for (auto&& s : M_Sound_2D_Manager) {
		s->Start_Sound(Volume);
	}
}

void C_Sound_Manager_Base::Set_Bullet_Hit_Sound(const int * BulletHit_Type, const D3DXVECTOR3 * Sound_Pos, const int *Volume)
{
	S_SOUND_DATA Data;

	//位置の初期化
	Data.Pos = *Sound_Pos;

	//音の種類の初期化
	Data.Sound_CategoryNo = Co_Sound_Category_Bullet_Hit;

	//被弾した種類の検索
	switch (*BulletHit_Type)
	{
	case Hit_Type_Player://プレイヤーに被弾
		Data.Sound_Type = Co_Sound_Type_2D;
		Data.Sound_No = 1;
		break;
	case Hit_Type_Enemy://敵に被弾
		Data.Sound_Type = Co_Sound_Type_3D;
		Data.Sound_No = 1;
		break;
	case Hit_Type_Player*-1://ダメージ無効の時に被弾
		Data.Sound_Type = Co_Sound_Type_2D;
		Data.Sound_No = 1;
		break;
	case Hit_Type_Enemy*-1://ダメージ無効の時に被弾
		Data.Sound_Type = Co_Sound_Type_3D;
		Data.Sound_No = 1;
		break;
	case Hit_Type_Wall://壁に被弾
		Data.Sound_Type = Co_Sound_Type_3D;
		Data.Sound_No = 1;
		break;
	case Hit_Type_Ground://地面に被弾
		Data.Sound_Type = Co_Sound_Type_3D;
		Data.Sound_No = 1;
		break;
	default://検索にひっかからない場合
		Data.Sound_Type = Co_Sound_Type_2D;
		Data.Sound_No = 1;
		break;
	}

	//被弾音の管理クラス
	C_Sound_Bullet_Hit_Manager Sound_Hit_Manager;

	//インスタンス化
	M_Sound_2D_Manager.push_back(Sound_Hit_Manager.Get_Sound(&Data));

	//インスタンス化した音声を流す処理
	New_Sound_Play(Volume);

	return;
}

void C_Sound_Manager_Base::Set_Bullet_Hit_Sound(const int * BulletHit_Type, const D3DXVECTOR3 * Sound_Pos, const bool * DamageFlg,const int *Volume)
{
	//被弾音の種類
	int Type = *BulletHit_Type;

	//ダメージを受けた確認
	if (*DamageFlg != true) Type *= -1;

	//被弾音を流す処理
	Set_Bullet_Hit_Sound(&Type, Sound_Pos,Volume);
}

bool C_Sound_Manager_Base::Set_Sound_2D(const S_SOUND_DATA * Data, const int *Volume)
{
	if (M_Sound_2D_Manager.size() < 1)return false;

	if (Data->Sound_Type != Co_Sound_Type_2D)return false;

	bool Flg = true;

	for (auto && s : M_Sound_2D_Manager) {
		if (Judg_Data(&s->Get_Data(), Data) == true) {
			s->Update(&M_CamPos, &Flg,Volume);
			return true;
		}
	}

	return false;
}

void C_Sound_Manager_Base::New_Sound_2D(C_Sound_Base_2D * Sound)
{
	M_Sound_2D_Manager.push_back(Sound);
}

bool C_Sound_Manager_Base::Judg_Data2(const S_SOUND_DATA * M_Data, const S_SOUND_DATA * Set_Data)
{
	if (M_Data->Sound_Type != Set_Data->Sound_Type)return false;

	if (M_Data->Sound_CategoryNo != Set_Data->Sound_CategoryNo)return false;

	return true;
}

bool C_Sound_Manager_Base::Judg_Data(const S_SOUND_DATA * M_Data, const S_SOUND_DATA * Set_Data)
{
	if (M_Data->Sound_CategoryNo != Set_Data->Sound_CategoryNo)return false;

	if (M_Data->Sound_No != Set_Data->Sound_No)return false;

	return true;
}

bool C_Sound_Manager_Base::Judg_Bullet(const S_SOUND_DATA * Data, const int *Volume)
{
	bool Flg = true;

	if (Data->Sound_No == 1) {
		New_Sound_2D(new C_Sound_2D_Gun_1());
		M_Sound_2D_Manager[M_Sound_2D_Manager.size() - 1]->Update(&M_CamPos, &Flg,Volume);
	}

	return true;
}

bool C_Sound_Manager_Base::Judg_BGM(const S_SOUND_DATA * Data, const int *Volume)
{
	bool Flg = true;

	if (M_Sound_2D_Manager.size() > 0) {
		for (unsigned int s = 0; s < M_Sound_2D_Manager.size();s++) {
			if (M_Sound_2D_Manager[s]->Get_Data().Sound_CategoryNo == Co_Sound_Category_BGM) {
				if (M_Sound_2D_Manager[s]->Get_Data().Sound_No == Data->Sound_No) {
					Flg = false;
				}
				else {
					delete M_Sound_2D_Manager[s];
					M_Sound_2D_Manager.erase(M_Sound_2D_Manager.begin() + s);
					s--;
				}
			}
		}
	}
	if (Flg == true) {
		C_Sound_BGM_Manager Manager;
		New_Sound_2D(Manager.Get_BGM(&Data->Sound_No));
		M_Sound_2D_Manager[M_Sound_2D_Manager.size() - 1]->Update(&M_CamPos, &Flg,Volume);
	}
	return true;
}

bool C_Sound_Manager_Base::Update_Sound(const D3DXVECTOR3 * CamPos, const D3DXVECTOR3 * CamLook, const D3DXVECTOR3 * CamHead, const int *Volume)
{
	M_CamPos.Pos=*CamPos;
	M_CamPos.Look = *CamLook;
	M_CamPos.Head = *CamHead;

	Update_Sound(Volume);

	return true;
}

bool C_Sound_Manager_Base::Judg_Sound(const S_SOUND_DATA * M_Data, const int *Volume)
{
	if (M_Data->Change_Type < 0)return false;

	switch (M_Data->Change_Type)
	{
	case Co_Sound_New:
		Set_Sound(M_Data,Volume);
		break;
	case Co_Sound_Delete:
		Delete_All(M_Data,true);
		break;
	case Co_Sound_Start:
		if (M_Sound_2D_Manager.size() > 0) {
			for (unsigned int s = 0; s < M_Sound_2D_Manager.size(); s++) {
				if (Judg_Data2(M_Data, &M_Sound_2D_Manager[s]->Get_Data()) == true) M_Sound_2D_Manager[s]->Start_Sound(Volume);
			}
		}
		break;
	case Co_Sound_Stop:
		if (M_Sound_2D_Manager.size() > 0) {
			for (unsigned int s = 0; s < M_Sound_2D_Manager.size(); s++) {
				if (Judg_Data2(M_Data, &M_Sound_2D_Manager[s]->Get_Data()) == true) M_Sound_2D_Manager[s]->Stop_Sound2();
			}
		}
		break;
	case Co_Sound_All_Delete:
		Stop_Sound_All();
		Delete_All();
		break;
	case Co_Sound_All_Start:
		Strat_Sound_All(Volume);
		break;
	case Co_Sound_All_Stop:
		Stop_Sound_2_All();
		break;
	case Co_Sound_Change:
		if (Delete_All(M_Data,false) == true) {
			Set_Sound(M_Data,Volume);
		}
		break;
	default:
		break;
	}
	
	return true;
}

void C_Sound_Manager_Base::Delete_All(void)
{
	if (M_Sound_2D_Manager.size() < 1)return;

	for (unsigned int s = 0; s < M_Sound_2D_Manager.size(); s++) {
		delete M_Sound_2D_Manager[s];
		M_Sound_2D_Manager.erase(M_Sound_2D_Manager.begin() + s);
		s--;
	}
}

void C_Sound_Manager_Base::Sound_Delete(unsigned int * No)
{
	M_Sound_2D_Manager[*No]->StopSound_All();

	delete M_Sound_2D_Manager[*No];
	M_Sound_2D_Manager.erase(M_Sound_2D_Manager.begin() + *No);
	*No -= 1;
}

bool C_Sound_Manager_Base::Delete_All(const S_SOUND_DATA * M_Data, const bool Flg)
{
	if (M_Sound_2D_Manager.size() < 1) return true;

	bool L_Flg = true;

	for (unsigned int s = 0; s < M_Sound_2D_Manager.size(); s++) {
		if (Judg_Data2(M_Data, &M_Sound_2D_Manager[s]->Get_Data()) == true) {
			if (Flg != true) {
				if (M_Data->Sound_No == M_Sound_2D_Manager[s]->Get_Data().Sound_No) {
					L_Flg = false;
				}
				else {
					Sound_Delete(&s);
				}
			}
			else {
				Sound_Delete(&s);
			}
		}
	}

	return L_Flg;
}

