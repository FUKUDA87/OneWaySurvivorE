#pragma once
#include"Car_Parts_Base.h"
#include"CarBase.h"

class C_Car_Parts_Data:public C_CarBase {
public:
	~C_Car_Parts_Data();
	
	//��񐔓n��
	unsigned int Get_Data_Num(void) {
		return M_Data.size();
	}
	//�Ԃ̃p�[�c�ʒu�̏��
	S_CAR_PARTS_DATA Get_Data(const unsigned int *PartsNo);

	//������
	void Set_Data(const S_CAR_PARTS_DATA *Data);
protected:
	std::vector<S_CAR_PARTS_DATA*>M_Data;

	//�S���폜
	void Delete_ALL_Data(void);

};