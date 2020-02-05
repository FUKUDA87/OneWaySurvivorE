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
	void GetPos2DSet(const D3DXMATRIX *mProj, const D3DXMATRIX *mView, const D3DVIEWPORT9 *Viewport);

	//�G�l�~�[�̑��ݍ폜�n��
	bool GetDeleFlg(void);

	//�p�[�c�̈ʒu����
	void SetParts(std::vector<BillBase*>ground);

	void UpdateBullet(void);

protected:
	//���
	Vector *Vect;

	D3DXVECTOR3 Pos2D;

	int m_EnemyNo;
private:
	
};