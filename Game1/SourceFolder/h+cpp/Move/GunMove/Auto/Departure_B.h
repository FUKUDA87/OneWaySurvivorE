#pragma once
#include"Departure_Gun_Auto_Base.h"

//���ˎ��Ԃ̏���
class C_Departure_B :public C_Departure_Gun_Auto_Base {
public:
	C_Departure_B(const int *Count);
private:
	//���̃J�E���g�̕ύX����
	virtual void Update_NowCount(const int *Count) {
		NowCount--;
	}

};