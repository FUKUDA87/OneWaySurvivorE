#pragma once
#include<d3dx9.h>

class C_Departure_Gun_Auto_Base {
public:
	C_Departure_Gun_Auto_Base(const int *Count);
	//�e�������Ƃ��ł���Flg�n��
	bool Get_BulletFlg(const int *Count);
protected:
	int NowCount;

	//���̃J�E���g�̕ύX����
	virtual void Update_NowCount(const int *Count);
};