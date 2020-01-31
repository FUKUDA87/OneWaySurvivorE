#include "Car_Parts_Data.h"

C_Car_Parts_Data::~C_Car_Parts_Data()
{
	Delete_ALL_Data();
}

S_CAR_PARTS_DATA C_Car_Parts_Data::Get_Data(const unsigned int * PartsNo)
{
	return *M_Data[*PartsNo];
}

void C_Car_Parts_Data::Set_Data(const S_CAR_PARTS_DATA * Data)
{
	M_Data.push_back(new S_CAR_PARTS_DATA);
	*M_Data[M_Data.size()-1] = *Data;
}

void C_Car_Parts_Data::Delete_ALL_Data(void)
{
	if (M_Data.size() < 1)return;

	for (unsigned int d = 0; d < M_Data.size(); d++) {
		delete M_Data[d];
		M_Data.erase(M_Data.begin() + d);
		d--;
	}
}
