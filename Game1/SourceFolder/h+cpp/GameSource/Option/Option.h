#pragma once
#include<d3dx9.h>
#include<stdio.h>
#include"../Struct.h"

class C_Option
{
public:
	// �f�[�^�̓ǂݍ���
	void Read(void);
	
	// �f�[�^�̏�������
	void Write(void);

	// �f�[�^�̕ύX
	void Change(void);

	// �f�[�^�̓n��
	S_OptionData GetOptionData(void) { return optionData; }

	// �f�[�^�̏�����
	void InitData(void);

private:
	S_OptionData optionData;
};