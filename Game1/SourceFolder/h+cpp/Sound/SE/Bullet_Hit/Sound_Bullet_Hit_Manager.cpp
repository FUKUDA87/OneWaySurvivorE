#include "Sound_Bullet_Hit_Manager.h"

C_Sound_Base_2D * C_Sound_Bullet_Hit_Manager::Get_Sound(const S_SOUND_DATA * Data)
{
	switch (Data->Sound_No)
	{
	case 1:
		return Judg_Sound(Data, "../GameFolder/Material/wav/decision18.wav", -2500);
		break;
	}
	return Judg_Sound(Data, "../GameFolder/Material/wav/decision18.wav", -2500);
}

C_Sound_Base_2D * C_Sound_Bullet_Hit_Manager::Judg_Sound(const S_SOUND_DATA * Data, std::string FileName, const int Volume)
{
	//�����̎�ތ���
	switch (Data->Sound_Type)
	{
	case Co_Sound_Type_2D://�T�E���h2D
		return new C_Spund_2D_Bullet_Hit_Base(Data,FileName,Volume);
		break;
	case Co_Sound_Type_3D://�T�E���h3D
		return new C_Sound_Base_3D(Data, FileName, Volume);
		break;
	}

	//�����ɂȂ������ꍇ�A�T�E���h2D
	return new C_Spund_2D_Bullet_Hit_Base(Data, FileName, Volume);
}
