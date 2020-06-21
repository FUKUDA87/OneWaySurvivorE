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
	
	~c_GameSoundManager();


	//���̍X�V
	bool Update_Sound(const int *Volume);
	bool Update_Sound(const D3DXVECTOR3 *CamPos, const D3DXVECTOR3 *CamLook, const D3DXVECTOR3 *CamHead, const int *Volume);

	//���[�h�̌���
	bool Judg_Sound(const S_SOUND_DATA* M_Data, const int *Volume);

	//���̕ύX
	void Set_Sound(const int *Volume);

	void Stop_Sound_All(void);

	void Stop_Sound_2_All(void);

	void Stop_Sound_2_All(const int CategoryNo);

	void Strat_Sound_All(const int *Volume);

	//��e���𗬂�����
	void Set_Bullet_Hit_Sound(const int * BulletHit_Type, const D3DXVECTOR3 * Sound_Pos, const int *Volume);

	//��e�������̂����G��Ԃ̔���Ɖ��𗬂�����
	void Set_Bullet_Hit_Sound(const int * BulletHit_Type, const D3DXVECTOR3 * Sound_Pos,const bool *DamageFlg, const int *Volume);
protected:
	//2D�̌���
	bool Set_Sound_2D(const S_SOUND_DATA* Data, const int *Volume);

	void New_Sound_2D(C_Sound_Base_2D* Sound);

	std::vector<C_Sound_Base_2D*>m_SoundManager;

private:
	S_CAMERA_POS M_CamPos;

	//���̌���
	bool Judg_Data2(const S_SOUND_DATA* M_Data, const S_SOUND_DATA* Set_Data);
	bool Judg_Data(const S_SOUND_DATA* M_Data, const S_SOUND_DATA* Set_Data);

	//�e�̌���
	bool Judg_Bullet(const S_SOUND_DATA* Data, const int *Volume);

	//BGM�̌���
	bool Judg_BGM(const S_SOUND_DATA* Data, const int *Volume);

	//���̑S�폜
	void Delete_All(void);

	//���̍폜
	void Sound_Delete(unsigned int *No);

	//���̍폜
	bool Delete_All(const S_SOUND_DATA* M_Data,const bool Flg);

	//�����O������New
	bool Set_Sound(const S_SOUND_DATA* Data, const int *Volume);

	//�x�����𗬂�����
	bool Judg_Warning(const S_SOUND_DATA* Data, const int *Volume);

	//�N���b�N���𗬂�����
	bool Judg_Click(const S_SOUND_DATA* Data, const int *Volume);

	//�����̔���
	bool Judg_Explosion_3D(const S_SOUND_DATA* Data, const int *Volume);

	//�ŐV�̉����𗬂�����
	void New_Sound_Play(const int *Volume);


};