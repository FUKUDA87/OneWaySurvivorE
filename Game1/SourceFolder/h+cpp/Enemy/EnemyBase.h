#pragma once
#include"../Draw3DBase/CarBulletManager.h"
#include"../Enemy/Vector.h"

class C_EnemyBase :public C_CarBulletManager {
public:
	C_EnemyBase();
	~C_EnemyBase();
	//������
	void InitEnemy(void);
	//�A�b�v�f�[�g
	bool UpdateCar(void);
	//�\��
	void Draw3DAll(const D3DXVECTOR3 *CamPos);
	void Draw2DAll(void);
	//���쐬�ɕK�v�ȏ��̎擾�ƃA�b�v�f�[�g
	void GetPos2DSet(const D3DXMATRIX *mProj, const D3DXMATRIX *mView, const D3DVIEWPORT9 *Viewport, const D3DXVECTOR3 *CameraPos);

	//�G�l�~�[�̑��ݍ폜�n��
	bool GetDeleFlg(void);

	//�p�[�c�̈ʒu����
	void SetParts(std::vector<C_Ground_Object*>ground);

	void UpdateBullet(void);

	//�{�X�Ȃ̂��m�F
	bool Get_BossFlg(void) {
		return M_BossFlg;
	}

protected:
	//���
	Vector *Vect;

	D3DXVECTOR3 Pos2D;

	int m_EnemyNo;

	//�{�X�ł��邩�̊m�FFlg
	bool M_BossFlg;

	
private:
	
};