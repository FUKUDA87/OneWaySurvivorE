#include "Sound_Click_Base.h"

C_Spund_Click_Base::C_Spund_Click_Base(const int No, std::string FileName, const int Volume)
{

	Init_Sound(&Co_Sound_Category_Click, &No, FileName, &Volume);
}

void C_Spund_Click_Base::Stop_Sound2(void)
{
}

void C_Spund_Click_Base::Start_Sound(void)
{
}
