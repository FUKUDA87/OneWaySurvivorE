#pragma once
#include"Departure_Gun_Auto_Base.h"

//���˂���e���̐��������Ɣ��ˉ񐔏���
class C_Departure_A :public C_Departure_Gun_Auto_Base {
public:
	C_Departure_A(const int *Count);
protected:
	//���̃J�E���g�̕ύX����
	virtual void Update_NowCount(const int *Count);
};