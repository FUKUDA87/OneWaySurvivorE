#pragma once
#include<d3dx9.h>
#include"../GameSource/Struct.h"
#include"../Const/Const_Sound_Type.h"
#include"Base/Sound_Base_2D.h"
#include"vector/Sound_Data_Vector.h"
#include"../Const/Const_Damage.h"
#include<vector>

//�T�E���h�̗����N���X
class c_GameSoundManager:public C_Sound_Data_Vector {
public:
	c_GameSoundManager(const int *g_BGMVolume, const int *g_SEVolume);
	~c_GameSoundManager();

	//���̍X�V
	bool Update(void);
	bool Update(const D3DXVECTOR3 *CamPos, const D3DXVECTOR3 *CamLook, const D3DXVECTOR3 *CamHead);
	void UpdateVolume(const int *g_BGMVolume, const int *g_SEVolume);

	// �����ύX
	bool Order(const S_SOUND_DATA* M_Data);

	// �V�K�Đ�
	void New(void);// DataVector��New

	// �T�E���h�̏�����
	void Reset(void);

	// �T�E���h�̒�~
	void Stop(void);
	void Stop(const S_SOUND_DATA * M_Data);

	// ��~���Ă���T�E���h�̍Đ�
	void Restart(void);
	void Restart(const S_SOUND_DATA * M_Data);

	//��e���𗬂�����
	void Set_Bullet_Hit_Sound(const int * BulletHit_Type, const D3DXVECTOR3 * Sound_Pos);

	//��e�������̂����G��Ԃ̔���Ɖ��𗬂�����
	void Set_Bullet_Hit_Sound(const int * BulletHit_Type, const D3DXVECTOR3 * Sound_Pos,const bool *DamageFlg);

	/*BGM*/

	// �Đ��J�n
	void BGMStart(const int *No);
	// �폜
	void BGMDelete(void);
	// �Đ��ĊJ
	void BGMRestart(void);
	// ��~
	void BGMStop(void);
	// ������
	void BGMReset(void);

private:
	std::vector<C_Sound_Base_2D*>m_SoundManager;
	C_Sound_Base_2D *m_BGMSound;

	S_CAMERA_POS M_CamPos;

	//���̌���
	bool JudgData(const S_SOUND_DATA* M_Data, const S_SOUND_DATA* Set_Data);

	// �S�폜
	void Delete(void);
	void Delete(unsigned int *count);  // 1�����폜
	bool Delete(const S_SOUND_DATA* M_Data, const bool Flg);// �폜

	//�����O������New
	bool SearchNew(const S_SOUND_DATA* Data);

	int BGMVolume, SEVolume;
};