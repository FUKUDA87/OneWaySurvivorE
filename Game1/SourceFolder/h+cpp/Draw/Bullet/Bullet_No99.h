#pragma once
#include"Bullet_No2.h"

class C_Bullet_No99 :public C_Bullet_No2 {
public:
	//�e�̔ԍ��Əe���̍s��
	C_Bullet_No99(const D3DXMATRIX *Mat);
	//�v���C���[���Ə������킹�����̃R���X�g���N�^
	C_Bullet_No99(const D3DXMATRIX *Mat, const S_RayHitJudgData* RayData);
protected:
	void Init_99(void);
};