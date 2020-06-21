#include "GameSoundManager.h"
#include"SE/Sound_2D_Gun_1.h"
#include"BGM/Sound_BGM_Manager.h"
#include"SE/Warning/Sound_Warning_Manager.h"
#include"SE/Click/Sound_Click_Manager.h"
#include"SE/SE_Manager/Sound_Explosion_Manager.h"
#include"SE/Bullet_Hit/Sound_Bullet_Hit_Manager.h"

c_GameSoundManager::~c_GameSoundManager()
{
	//Stop_Sound_All();

	Delete_All();

	BGMDelete();
}

bool c_GameSoundManager::Update_Sound(const int *Volume)
{
	if (m_SoundManager.size() < 1)return false;

	bool Flg = false;

	for (unsigned int s = 0; s < m_SoundManager.size(); s++) {
		if (m_SoundManager[s]->Update(&M_CamPos,&Flg,Volume) == false) {
			delete m_SoundManager[s];
			m_SoundManager.erase(m_SoundManager.begin() + s);
			s--;
		}
	}

	return false;
}

bool c_GameSoundManager::Set_Sound(const S_SOUND_DATA * Data, const int *Volume)
{
	//�T�E���h�̎��
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

bool c_GameSoundManager::Judg_Warning(const S_SOUND_DATA * Data, const int *Volume)
{
	bool Flg = true;

	C_Sound_Warning_Manager Manager;

	New_Sound_2D(Manager.Get_Warning(&Data->Sound_No));
		
	m_SoundManager[m_SoundManager.size() - 1]->Update(&M_CamPos, &Flg,Volume);

	return true;
}

bool c_GameSoundManager::Judg_Click(const S_SOUND_DATA * Data, const int *Volume)
{
	bool Flg = true;

	C_Sound_Click_Manager Manager;

	New_Sound_2D(Manager.Get_Click(&Data->Sound_No));

	m_SoundManager[m_SoundManager.size() - 1]->Update(&M_CamPos, &Flg,Volume);

	return true;
}

bool c_GameSoundManager::Judg_Explosion_3D(const S_SOUND_DATA * Data, const int *Volume)
{
	bool Flg = true;

	C_Sound_Explosion_Manager Manager;

	New_Sound_2D(Manager.Get_Sound(Data));

	m_SoundManager[m_SoundManager.size() - 1]->Update(&M_CamPos, &Flg,Volume);

	return true;
}

void c_GameSoundManager::New_Sound_Play(const int *Volume)
{
	//�����𗬂�Flg
	bool PlayFlg = true;

	//�����𗬂�����
	m_SoundManager[m_SoundManager.size() - 1]->Update(&M_CamPos, &PlayFlg,Volume);
}

void c_GameSoundManager::Set_Sound(const int *Volume)
{
	if (Get_Sound_Data_Num() < 1)return;

	for (unsigned int d = 0; d < Get_Sound_Data_Num(); d++) {

		if (Judg_Sound(&Get_Sound_Data(&d), Volume) == true) {

			Delete_Sound(&d);
		}
	}
}

void c_GameSoundManager::Reset(void)
{
	if (m_SoundManager.size() < 1)return;

	for (auto&& s : m_SoundManager) {
		s->Reset();
	}
}

void c_GameSoundManager::Stop(void)
{
	if (m_SoundManager.size() < 1)return;

	for (auto&& s : m_SoundManager) {
		s->Stop();
	}
}

void c_GameSoundManager::Stop(const int CategoryNo)
{
	if (m_SoundManager.size() < 1)return;

	for (auto&& s : m_SoundManager) {
		if (s->Get_Data().Sound_CategoryNo == CategoryNo) {
			s->Stop();
		}
	}
}

void c_GameSoundManager::Restart(const int *Volume)
{
	if (m_SoundManager.size() < 1)return;

	for (auto&& s : m_SoundManager) {
		s->Restart(Volume);
	}
}

void c_GameSoundManager::Set_Bullet_Hit_Sound(const int * BulletHit_Type, const D3DXVECTOR3 * Sound_Pos, const int *Volume)
{
	S_SOUND_DATA Data;

	//�ʒu�̏�����
	Data.Pos = *Sound_Pos;

	//���̎�ނ̏�����
	Data.Sound_CategoryNo = Co_Sound_Category_Bullet_Hit;

	//��e������ނ̌���
	switch (*BulletHit_Type)
	{
	case Hit_Type_Player://�v���C���[�ɔ�e
		Data.Sound_Type = Co_Sound_Type_2D;
		Data.Sound_No = 1;
		break;
	case Hit_Type_Enemy://�G�ɔ�e
		Data.Sound_Type = Co_Sound_Type_3D;
		Data.Sound_No = 1;
		break;
	case Hit_Type_Player*-1://�_���[�W�����̎��ɔ�e
		Data.Sound_Type = Co_Sound_Type_2D;
		Data.Sound_No = 1;
		break;
	case Hit_Type_Enemy*-1://�_���[�W�����̎��ɔ�e
		Data.Sound_Type = Co_Sound_Type_3D;
		Data.Sound_No = 1;
		break;
	case Hit_Type_Wall://�ǂɔ�e
		Data.Sound_Type = Co_Sound_Type_3D;
		Data.Sound_No = 1;
		break;
	case Hit_Type_Ground://�n�ʂɔ�e
		Data.Sound_Type = Co_Sound_Type_3D;
		Data.Sound_No = 1;
		break;
	default://�����ɂЂ�������Ȃ��ꍇ
		Data.Sound_Type = Co_Sound_Type_2D;
		Data.Sound_No = 1;
		break;
	}

	//��e���̊Ǘ��N���X
	C_Sound_Bullet_Hit_Manager Sound_Hit_Manager;

	//�C���X�^���X��
	m_SoundManager.push_back(Sound_Hit_Manager.Get_Sound(&Data));

	//�C���X�^���X�����������𗬂�����
	New_Sound_Play(Volume);

	return;
}

void c_GameSoundManager::Set_Bullet_Hit_Sound(const int * BulletHit_Type, const D3DXVECTOR3 * Sound_Pos, const bool * DamageFlg,const int *Volume)
{
	//��e���̎��
	int Type = *BulletHit_Type;

	//�_���[�W���󂯂��m�F
	if (*DamageFlg != true) Type *= -1;

	//��e���𗬂�����
	Set_Bullet_Hit_Sound(&Type, Sound_Pos,Volume);
}

void c_GameSoundManager::BGMStart(void)
{
}

void c_GameSoundManager::BGMDelete(void)
{
	if (m_BGMSound == nullptr)return;

	delete m_BGMSound;

	m_BGMSound = nullptr;
}

void c_GameSoundManager::BGMRestart(const int *Volume)
{
	if (m_BGMSound == nullptr)return;

	m_BGMSound->Restart(Volume);
}

void c_GameSoundManager::BGMStop(void)
{
	if (m_BGMSound == nullptr)return;

	m_BGMSound->Stop();
}

bool c_GameSoundManager::Set_Sound_2D(const S_SOUND_DATA * Data, const int *Volume)
{
	if (m_SoundManager.size() < 1)return false;

	if (Data->Sound_Type != Co_Sound_Type_2D)return false;

	bool Flg = true;

	for (auto && s : m_SoundManager) {
		if (Judg_Data(&s->Get_Data(), Data) == true) {
			s->Update(&M_CamPos, &Flg,Volume);
			return true;
		}
	}

	return false;
}

void c_GameSoundManager::New_Sound_2D(C_Sound_Base_2D * Sound)
{
	m_SoundManager.push_back(Sound);
}

bool c_GameSoundManager::Judg_Data2(const S_SOUND_DATA * M_Data, const S_SOUND_DATA * Set_Data)
{
	if (M_Data->Sound_Type != Set_Data->Sound_Type)return false;

	if (M_Data->Sound_CategoryNo != Set_Data->Sound_CategoryNo)return false;

	return true;
}

bool c_GameSoundManager::Judg_Data(const S_SOUND_DATA * M_Data, const S_SOUND_DATA * Set_Data)
{
	if (M_Data->Sound_CategoryNo != Set_Data->Sound_CategoryNo)return false;

	if (M_Data->Sound_No != Set_Data->Sound_No)return false;

	return true;
}

bool c_GameSoundManager::Judg_Bullet(const S_SOUND_DATA * Data, const int *Volume)
{
	bool Flg = true;

	if (Data->Sound_No == 1) {
		New_Sound_2D(new C_Sound_2D_Gun_1());
		m_SoundManager[m_SoundManager.size() - 1]->Update(&M_CamPos, &Flg,Volume);
	}

	return true;
}

bool c_GameSoundManager::Judg_BGM(const S_SOUND_DATA * Data, const int *Volume)
{
	bool Flg = true;

	if (m_SoundManager.size() > 0) {
		for (unsigned int s = 0; s < m_SoundManager.size();s++) {
			if (m_SoundManager[s]->Get_Data().Sound_CategoryNo == Co_Sound_Category_BGM) {
				if (m_SoundManager[s]->Get_Data().Sound_No == Data->Sound_No) {
					Flg = false;
				}
				else {
					delete m_SoundManager[s];
					m_SoundManager.erase(m_SoundManager.begin() + s);
					s--;
				}
			}
		}
	}
	if (Flg == true) {
		C_Sound_BGM_Manager Manager;
		New_Sound_2D(Manager.Get_BGM(&Data->Sound_No));
		m_SoundManager[m_SoundManager.size() - 1]->Update(&M_CamPos, &Flg,Volume);
	}
	return true;
}

bool c_GameSoundManager::Update_Sound(const D3DXVECTOR3 * CamPos, const D3DXVECTOR3 * CamLook, const D3DXVECTOR3 * CamHead, const int *Volume)
{
	M_CamPos.Pos=*CamPos;
	M_CamPos.Look = *CamLook;
	M_CamPos.Head = *CamHead;

	Update_Sound(Volume);

	return true;
}

bool c_GameSoundManager::Judg_Sound(const S_SOUND_DATA * M_Data, const int *Volume)
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
		if (m_SoundManager.size() > 0) {
			for (unsigned int s = 0; s < m_SoundManager.size(); s++) {
				if (Judg_Data2(M_Data, &m_SoundManager[s]->Get_Data()) == true) m_SoundManager[s]->Restart(Volume);
			}
		}
		break;
	case Co_Sound_Stop:
		if (m_SoundManager.size() > 0) {
			for (unsigned int s = 0; s < m_SoundManager.size(); s++) {
				if (Judg_Data2(M_Data, &m_SoundManager[s]->Get_Data()) == true) m_SoundManager[s]->Stop();
			}
		}
		break;
	case Co_Sound_All_Delete:
		Reset();
		Delete_All();
		break;
	case Co_Sound_All_Start:
		Restart(Volume);
		break;
	case Co_Sound_All_Stop:
		Stop();
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

void c_GameSoundManager::Delete_All(void)
{
	if (m_SoundManager.size() < 1)return;

	for (unsigned int s = 0; s < m_SoundManager.size(); s++) {
		delete m_SoundManager[s];
		m_SoundManager.erase(m_SoundManager.begin() + s);
		s--;
	}
}

void c_GameSoundManager::Sound_Delete(unsigned int * No)
{
	m_SoundManager[*No]->Reset();

	delete m_SoundManager[*No];
	m_SoundManager.erase(m_SoundManager.begin() + *No);
	*No -= 1;
}

bool c_GameSoundManager::Delete_All(const S_SOUND_DATA * M_Data, const bool Flg)
{
	if (m_SoundManager.size() < 1) return true;

	bool L_Flg = true;

	for (unsigned int s = 0; s < m_SoundManager.size(); s++) {
		if (Judg_Data2(M_Data, &m_SoundManager[s]->Get_Data()) == true) {
			if (Flg != true) {
				if (M_Data->Sound_No == m_SoundManager[s]->Get_Data().Sound_No) {
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

