#pragma once
#include"Gun_Trigger_Base.h"

//�ЂƂ̏e������
class C_Gun_Trigger_2 :public C_Gun_Trigger_Base {
public:
	C_Gun_Trigger_2();
	//�e���̃g���K�[���I���ɂ��鏈��
	void Trigger(std::vector<C_Gun_Parts_Category*>Category, const bool *TriggerFlg);
	//�e���̃`�F���W
	void Gun_Mouth_Change(void);
protected:
	//������
	void Init(void);

	//�e��No
	unsigned int MouthNo;
};