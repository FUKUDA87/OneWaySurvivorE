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

	Delete();

	BGMDelete();
}

bool c_GameSoundManager::Update(const int * Volume)
{
	bool Flg = false;

	if (m_BGMSound != nullptr)m_BGMSound->Update(&M_CamPos, &Flg, Volume);

	if (m_SoundManager.size() < 1)return false;

	for (unsigned int s = 0; s < m_SoundManager.size(); s++) {
		if (m_SoundManager[s]->Update(&M_CamPos, &Flg, Volume) == false) {
			delete m_SoundManager[s];
			m_SoundManager.erase(m_SoundManager.begin() + s);
			s--;
		}
	}

	return false;
}

bool c_GameSoundManager::Update(const D3DXVECTOR3 * CamPos, const D3DXVECTOR3 * CamLook, const D3DXVECTOR3 * CamHead, const int * Volume)
{
	M_CamPos.Pos = *CamPos;
	M_CamPos.Look = *CamLook;
	M_CamPos.Head = *CamHead;

	Update(Volume);

	return true;
}

bool c_GameSoundManager::Order(const S_SOUND_DATA * M_Data, const int * Volume)
{
	if (M_Data->Change_Type < 0)return false;

	switch (M_Data->Change_Type)
	{
	case Co_SoundNew:
		SearchNew(M_Data, Volume);
		break;
	case Co_SoundDelete:
		Delete(M_Data, true);
		break;
	case Co_SoundStart:
		Restart(M_Data, Volume);
		break;
	case Co_SoundStop:
		Stop(M_Data);
		break;
	case Co_SoundDeleteAll:
		Reset();
		Delete();
		break;
	case Co_SoundStartAll:
		Restart(Volume);
		break;
	case Co_SoundStopAll:
		Stop();
		break;
	default:
		break;
	}

	return true;
}

void c_GameSoundManager::Reset(void)
{
	BGMReset();

	if (m_SoundManager.size() < 1)return;

	for (auto&& s : m_SoundManager) {
		s->Reset();
	}
}

void c_GameSoundManager::Stop(void)
{
	BGMStop();

	if (m_SoundManager.size() < 1)return;

	for (auto&& s : m_SoundManager) {
		s->Stop();
	}
}

void c_GameSoundManager::Stop(const S_SOUND_DATA * M_Data)
{
	// BGM�̌���
	if (M_Data->Sound_Type == Co_Sound_Type_2D) {
		if (M_Data->Sound_CategoryNo == Co_Sound_Category_BGM) {
			BGMStop();
			return;
		}
	}

	if (m_SoundManager.size() < 1) return;

	// ����
	for (unsigned int s = 0; s < m_SoundManager.size(); s++) {
		if (JudgData(M_Data, &m_SoundManager[s]->Get_Data()) == true) m_SoundManager[s]->Stop();
	}
}

void c_GameSoundManager::Restart(const int *Volume)
{
	BGMRestart(Volume);

	if (m_SoundManager.size() < 1)return;

	for (auto&& s : m_SoundManager) {
		s->Restart(Volume);
	}
}

void c_GameSoundManager::Restart(const S_SOUND_DATA * M_Data, const int * Volume)
{
	// BGM�̌���
	if (M_Data->Sound_Type == Co_Sound_Type_2D) {
		if (M_Data->Sound_CategoryNo == Co_Sound_Category_BGM) {
			BGMRestart(Volume);
			return;
		}
	}

	if (m_SoundManager.size() < 1) return;

	// ����
	for (unsigned int s = 0; s < m_SoundManager.size(); s++) {
		if (JudgData(M_Data, &m_SoundManager[s]->Get_Data()) == true) m_SoundManager[s]->Restart(Volume);
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
	bool PlayFlg = true;
	m_SoundManager[m_SoundManager.size() - 1]->Update(&M_CamPos, &PlayFlg, Volume);

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

void c_GameSoundManager::BGMStart(const int *No, const int *Volume)
{
	BGMDelete();

	C_Sound_BGM_Manager Manager;
	m_BGMSound = Manager.Get_BGM(No);

	bool Flg = true;

	m_BGMSound->Update(&M_CamPos, &Flg, Volume);
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

void c_GameSoundManager::BGMReset(void)
{
	if (m_BGMSound == nullptr)return;

	m_BGMSound->Reset();
}

bool c_GameSoundManager::JudgData(const S_SOUND_DATA * M_Data, const S_SOUND_DATA * Set_Data)
{
	if (M_Data->Sound_Type != Set_Data->Sound_Type)return false;

	if (M_Data->Sound_CategoryNo != Set_Data->Sound_CategoryNo)return false;

	return true;
}

void c_GameSoundManager::Delete(void)
{
	if (m_SoundManager.size() < 1)return;

	for (unsigned int s = 0; s < m_SoundManager.size(); s++) {
		delete m_SoundManager[s];
		m_SoundManager.erase(m_SoundManager.begin() + s);
		s--;
	}
}

void c_GameSoundManager::Delete(unsigned int * count)
{
	m_SoundManager[*count]->Reset();

	delete m_SoundManager[*count];
	m_SoundManager.erase(m_SoundManager.begin() + *count);
	*count--;
}

bool c_GameSoundManager::Delete(const S_SOUND_DATA * M_Data, const bool Flg)
{
	if (m_SoundManager.size() < 1) return true;

	bool L_Flg = true;

	for (unsigned int s = 0; s < m_SoundManager.size(); s++) {
		if (JudgData(M_Data, &m_SoundManager[s]->Get_Data()) == true) {
			if (Flg != true) {
				if (M_Data->Sound_No == m_SoundManager[s]->Get_Data().Sound_No) {
					L_Flg = false;
				}
				else {
					Delete(&s);
				}
			}
			else {
				Delete(&s);
			}
		}
	}

	return L_Flg;
}

bool c_GameSoundManager::SearchNew(const S_SOUND_DATA * Data, const int * Volume)
{
	bool PlayFlg = false;

	//�T�E���h�̎��
	switch (Data->Sound_CategoryNo)
	{
	case Co_Sound_Category_Bullet:
		if (Data->Sound_No == 1) {
			m_SoundManager.push_back(new C_Sound_2D_Gun_1());
			PlayFlg = true;
		}
		break;
	case Co_Sound_Category_BGM:
		BGMStart(&Data->Sound_No, Volume);
		break;
	case Co_Sound_Category_Warning:
		C_Sound_Warning_Manager WarningManager;
		m_SoundManager.push_back(WarningManager.Get_Warning(&Data->Sound_No));
		PlayFlg = true;
		break;
	case Co_Sound_Category_Click:
		C_Sound_Click_Manager ClickManager;
		m_SoundManager.push_back(ClickManager.Get_Click(&Data->Sound_No));
		PlayFlg = true;
		break;
	case Co_Sound_Category_Explosion:
		C_Sound_Explosion_Manager ExplosionManager;
		m_SoundManager.push_back(ExplosionManager.Get_Sound(Data));
		PlayFlg = true;
		break;
	case Co_Sound_Category_Bullet_Hit:
		break;
	default:
		return false;
		break;
	}

	if (PlayFlg == true) {
		m_SoundManager[m_SoundManager.size() - 1]->Update(&M_CamPos, &PlayFlg, Volume);
	}

	return true;
}

void c_GameSoundManager::New(const int * Volume)
{
	if (Get_Sound_Data_Num() < 1)return;

	for (unsigned int d = 0; d < Get_Sound_Data_Num(); d++) {

		if (Order(&Get_Sound_Data(&d), Volume) == true) {

			Delete_Sound(&d);
		}
	}
}

