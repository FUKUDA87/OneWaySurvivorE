#pragma once
#include"../../Gun/Bullet/BulletBase/Bullet_Base.h"

class C_Bullet_No1 :public C_Bullet_Base {
public:
	//�e�̔ԍ��Əe���̍s��
	C_Bullet_No1(const D3DXMATRIX *Mat);
	//�v���C���[���Ə������킹�����̃R���X�g���N�^
	C_Bullet_No1(const D3DXMATRIX *Mat, const S_RayHitJudgData* RayData);
private:
	//������
	void Init_No1(void);
};