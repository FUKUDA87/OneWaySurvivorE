#pragma once
#include<d3dx9.h>
#include<stdio.h>

//�Q�[�����̕����\���̃N���X
class C_Text_Num {
public:
	//float�̕����\��
	void Draw_Text_float(const float *Num,const D3DXVECTOR2 *Pos);
	//int�̕����\��
	void Draw_Text_int(const int *Num, const D3DXVECTOR2 *Pos);
	//char�̕����\��
	void Draw_Text_char(const char *Text, const D3DXVECTOR2 *Pos);
};