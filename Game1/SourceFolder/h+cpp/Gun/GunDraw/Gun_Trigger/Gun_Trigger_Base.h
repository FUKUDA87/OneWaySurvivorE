#pragma once
#include<d3dx9.h>
#include"../GunParts/Gun_Parts_Category.h"
#include<vector>

class C_Gun_Trigger_Base {
public:
	//�e���̃g���K�[���I���ɂ��鏈��
	virtual void Trigger(std::vector<C_Gun_Parts_Category*>Category, const bool *TriggerFlg) = 0;
	//�e���̃`�F���W
	virtual void Gun_Mouth_Change(void) = 0;
};