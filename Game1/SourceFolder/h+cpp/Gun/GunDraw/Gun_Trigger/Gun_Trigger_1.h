#pragma once
#include"Gun_Trigger_Base.h"

//�S�e������
class C_Gun_Trigger_1:public C_Gun_Trigger_Base {
public:
	//�e���̃g���K�[���I���ɂ��鏈��
	void Trigger(std::vector<C_Gun_Parts_Category*>Category, const bool *TriggerFlg);
	//�e���̃`�F���W
	void Gun_Mouth_Change(void);
protected:

};