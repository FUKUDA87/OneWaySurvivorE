#include "Sound_Warning_Manager.h"

C_Sound_Base_2D * C_Sound_Warning_Manager::Get_Warning(const int * No)
{
	switch (*No)
	{
	case 1:
		return new C_Spund_Warning_Base(1, "../GameFolder/Material/wav/Warning_No1.wav", -3500);
		break;
	case 2:
		return new C_Spund_Warning_Base(2, "../GameFolder/Material/wav/Warning_No2.wav", -3500);
		break;
	default:
		return new C_Spund_Warning_Base(1, "../GameFolder/Material/wav/Warning_No1.wav", -3500);
		break;
	}
	return new C_Spund_Warning_Base(1, "../GameFolder/Material/wav/Warning_No1.wav", -3500);
}
