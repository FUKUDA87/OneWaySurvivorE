#pragma once
#include"../../Gun/Bullet/BulletBase/Bullet_Base.h"

class C_Bullet_No2 :public C_Bullet_Base {
public:
	//�e�̔ԍ��Əe���̍s��
	C_Bullet_No2(const D3DXMATRIX *Mat);
	//�v���C���[���Ə������킹�����̃R���X�g���N�^
	C_Bullet_No2(const D3DXMATRIX *Mat, const S_RAY_HIT_JUDG_DATA* RayData);
private:
	//������
	void Init_No2(void);
};