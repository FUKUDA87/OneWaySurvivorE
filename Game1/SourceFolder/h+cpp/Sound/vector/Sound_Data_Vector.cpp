#include "Sound_Data_Vector.h"

C_Sound_Data_Vector::~C_Sound_Data_Vector()
{
	if (M_C_Data.size() < 1)return;

	for (unsigned int d = 0; d < M_C_Data.size(); d++) {
		delete M_C_Data[d];
		M_C_Data.erase(M_C_Data.begin() + d);
		d--;
	}
}

S_SOUND_DATA C_Sound_Data_Vector::Get_Data(const unsigned int *No)
{
	if((M_C_Data.size()<1)||(*No<0)||(*No>=M_C_Data.size()))return S_SOUND_DATA();

	return M_C_Data[*No]->Get_Data();
}

unsigned int C_Sound_Data_Vector::Get_Data_Num(void)
{
	return M_C_Data.size();
}

void C_Sound_Data_Vector::Delete(unsigned int * No)
{
	if ((M_C_Data.size() < 1) || (*No < 0) || (*No >= M_C_Data.size()))return;

	unsigned int d = *No;

	delete M_C_Data[d];
	M_C_Data.erase(M_C_Data.begin() + d);
	d--;

	*No = d;
}

void C_Sound_Data_Vector::New_Data(const S_SOUND_DATA * Set_Data)
{
	M_C_Data.push_back(new C_Sound_Data_Base(Set_Data));
}
