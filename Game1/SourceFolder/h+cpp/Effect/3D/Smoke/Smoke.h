#pragma once
#include<d3dx9.h>
#include"../../../GameSource/Struct.h"
#include"../../EffectBase.h"

class c_Smoke:public c_EffectBase {
public:
	c_Smoke(const D3DXMATRIX *Mat, const S_Smog *H_Smog,const float *HpPer, const int *NowHp);
	
	// �X�V����
	bool Update(const s_CarEffectUpdateData *updateData);
	
	//�\��
	void Draw3D(const D3DXVECTOR3 *CameraPos);

private:
	Pol smog;
	//�����폜�p
	int NowCount;
	//�g��p
	float ScalSize;
	// ���̎��
	int Draw_No;

	//�\�����@�̍\����
	S_Smog M_S_Smog;

	//�����x�̃A�b�v�f�[�g
	void Update_Alpha(void);
	//�����̐��l�쐬
	float RandPlus(const int *Num);
	//�|���S���T�C�Y�̕ω�
	float GetPolSize(void);

	//������
	bool CountUpdate(void);

	// ���̔Z��
	int InitDrawNo(const float *HpPer, const int *NowHp);
};