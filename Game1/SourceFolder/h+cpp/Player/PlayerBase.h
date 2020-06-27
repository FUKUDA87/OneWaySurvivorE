#pragma once
#include"../Car/CarBulletManager.h"

class C_PlayerBase :public C_CarBulletManager {
public:
	C_PlayerBase();
	~C_PlayerBase();
	//������
	void InitPlayer(void);
	//�A�b�v�f�[�g
	virtual bool UpdatePlayer(void);
	//�p���̃A�b�v�f�[�g
	virtual bool UpdateAll(void);
	virtual bool UpdateAll(const D3DXMATRIX *CamMat);
	virtual bool UpdateEndAll(void);
	virtual bool UpdateDeadAll(void);

	//�p���̕\��
	virtual void Draw3DAll(const D3DXVECTOR3 *CameraPos);
	virtual void Draw2DAll(void);

	float GetRadF(void) {
		return RadField;
	}
	void SetRadF(float rad) {
		RadField = rad;
	}

	//�J�[�u��Ang����
	void SetRodAngY(float Inc, bool KeyFlg);
	//CurEnd
	void SetCurRotMat(void);

	//�e�̏����ύX
	//�e�����Ɖ���Key
	bool UpdateBulPla(const bool *KeyFlg, const bool *BirthFlg, const SoundCamera *sc);

	//�J�����̍s��̃Z�b�g
	void Set_CameraMat(const D3DXMATRIX *CameraMat);

	//���C�̍��W�n��
	S_RAY_HIT_JUDG_DATA Get_Gun_Ray_Data(void) {
		return M_Gun_Ray_Data;
	}

	//���C�̏�����
	void Set_Gun_Ray_Data(const S_RAY_HIT_JUDG_DATA *Data) {
		M_Gun_Ray_Data = *Data;
	}

	//�e�̏o��
	void Init_Bullet(void);

private:
	
	FILE* fp;
	//�n�ʂ̕\���͈�
	float RadField;
	//�J�[�u�p�x
	float CurAng;
	D3DXMATRIX CurRotMatY;

	//���C����e�̍��W�̎擾
	S_RAY_HIT_JUDG_DATA M_Gun_Ray_Data;

	//������
	void Init_Ray_Data(void);
};