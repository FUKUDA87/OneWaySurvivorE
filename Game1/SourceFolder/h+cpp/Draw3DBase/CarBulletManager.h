#pragma once
#include"CarGun.h"
#include"../Gun/Bullet/BulletBase/Bullet_Base.h"
#include"../Effect/Effect_Base.h"
#include"../GameSource/Count.h"

class C_CarBulletManager :public C_CarGun {
public:
	C_CarBulletManager();
	~C_CarBulletManager();

	//�e�̍X�V
	bool Update_ALL_Bullet(void);

	//�S����
	void AllDelete(void);
	//�ЂƂ폜
	void Delete_Bullet(unsigned int *NowBulletNo);
	//�e���n��
	unsigned int Get_BulletNum(void) {
		return M_Bullet.size();
	}

	//���̔ԍ��̒e�����邩����
	bool Bullet_NoJudg(const unsigned int *NowBulletNo);

	//�\���s��n��

	//�ʒu�s��n��
	D3DXMATRIX Get_Bullet_Mat(const unsigned int *BulletNo);

	//�ړ��ʓn��
	float Get_Bullet_MoveDis(const unsigned int *NowBulletNo) {
		return M_Bullet[*NowBulletNo]->Get_S_BULLET().Speed;
	}

	//�g���K�[
	virtual void Init_Bullet(void);

	//�g���K�[�Q

	//MoveVec����

	//�X�V
	bool Update_Bullet(void);

	//�\��
	void Draw_Bullet(const D3DXVECTOR3 *CameraPos);

	//�ړ��ʂ��炵
	void MoveVec_Bullet(void);

	//�e���ǂƒn�ʂ̔�������邩Flg�n��
	bool Get_Bullet_GroWal_Judg_Flg(const unsigned int *BulletNo);

	//�e���ǂƒn�ʂ̔�������邩Flg���
	void Set_Bullet_GroWal_Judg_Flg(const unsigned int *BulletNo,const bool *Flg);

	//�_���[�W���n��
	int Get_Bullet_Damage(const unsigned int *NowBulletNo) {
		return M_Bullet[*NowBulletNo]->Get_S_BULLET().Damage;
	}

protected:
	std::vector<C_Bullet_Base*>M_Bullet;

	std::vector<C_Effect_Base*>M_Effect;

	//�G�t�F�N�g�̑S�폜
	void Delete_All_Effect(void);

	//�G�t�F�N�g�̕\��
	void Draw_Effect(const D3DXVECTOR3 *CameraPos);

	//�G�t�F�N�g�Ɉړ��ʂ̉��Z
	void Set_MoveVec_Effect(const D3DXVECTOR3 *MoveVec);

	//�G�t�F�N�g�̍X�V
	bool Update_Effect(void);

private:
	
};