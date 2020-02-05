#pragma once
#include"Sound_Data_Base.h"
#include<vector>

class C_Sound_Data_Vector {
public:
	~C_Sound_Data_Vector();

	//î•ñ“n‚µ
	S_SOUND_DATA Get_Data(const unsigned int *No);

	//î•ñ”“n‚µ
	unsigned int Get_Data_Num(void);

	//íœ
	void Delete(unsigned int *No);

	//V‹K
	void New_Data(const S_SOUND_DATA *Set_Data);
protected:

private:
	std::vector<C_Sound_Data_Base*>M_C_Data;
};