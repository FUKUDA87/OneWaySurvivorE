#pragma once
#include<d3dx9.h>
#include"../../GameSource/Struct.h"

class C_Ground_Pop_Data {
public:
	C_Ground_Pop_Data(const S_GROUND_INIT_DATA* Data, const int *GroundNum);

	//�n�ʐ��̍폜
	bool GroundNum_Count(void);

	//�n�ʂ̏��n��
	S_GROUND_INIT_DATA Get_Data(void) {
		return M_S_Data;
	}
protected:

private:
	S_GROUND_INIT_DATA M_S_Data;

	int M_GroundNum;
};