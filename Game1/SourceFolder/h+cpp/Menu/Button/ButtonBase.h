#pragma once
#include<d3dx9.h>

class c_ButtonBase
{
public:
	c_ButtonBase();

	// �\��
	virtual void Draw2D(void){}

	// �X�V����
	virtual bool Update(void) { return false; }
	virtual bool Update(const D3DXVECTOR3 *pos);

	// �^�b�`����
	virtual bool TouchJudg(void);

	// �^�b�`�������Ɏ��̓����̔ԍ��n��
	int GetNextNo(void) { return nextNo; }
protected:
	int nextNo;

	D3DXVECTOR3 Pos,basePos,transPos;  // �ʒu�Ɗ�{�̈ʒu�ƈړ��̈ʒu
	float scalX, scalY;   // �g�kx,y
	int width, height;  // �摜�T�C�Y
};