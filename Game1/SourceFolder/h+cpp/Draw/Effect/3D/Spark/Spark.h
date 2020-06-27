#pragma once
#include<d3dx9.h>
#include"../../EffectBase.h"
#include"../../../../GameSource/Struct.h"

class C_Spark:public c_EffectBase {
public:
	//Mat=�����p�x,Pos�����W
	C_Spark(const D3DXMATRIX *Mat,const D3DXVECTOR3 *Pos);
	~C_Spark();

	// �X�V����
	virtual bool Update(void);

	// �\��
	virtual void Draw3D(const D3DXVECTOR3 *CameraPos);
protected:
	//�ŏ���Vec�𑫂��Ȃ�Flg
	bool CarMoveFlg;
	//�|���S���\���p�\����
	Pol spark;
	//�|���S����
	int PNum;
	//�W�����v�ړ��̕ϐ�
	float yUp, yDown;
	//�������Ɉړ�������
	float zDown;
	//�\���p�s��
	D3DXMATRIX IdenMat;
	//���Ԃō폜
	int NowCount;
	//�|���S���T�C�Y
	float PolSize;

	//������
	void Init();

	//������
	bool CountUpdate(void);

	//�A�b�v�f�[�g
	virtual bool UpdateSpark(void);
	//Vec=�ԑ̂̈ړ���
	bool Update(const D3DXVECTOR3 *CarMoveVec);

	//�\��
	virtual void Draw3DSpark(const D3DXVECTOR3 *CameraPos);
private:
};