#include "Sound_Bullet_Hit_Manager.h"

C_Sound_Base_2D * C_Sound_Bullet_Hit_Manager::Get_Sound(const S_SOUND_DATA * Data)
{
	switch (Data->Sound_No)
	{
	case 1:
		return Judg_Sound(Data, "../GameFolder/Material/wav/decision18.wav");
		break;
	}
	return Judg_Sound(Data, "../GameFolder/Material/wav/decision18.wav");
}

C_Sound_Base_2D * C_Sound_Bullet_Hit_Manager::Judg_Sound(const S_SOUND_DATA * Data, std::string FileName)
{
	//�����̎�ތ���
	switch (Data->Sound_Type)
	{
	case Co_Sound_Type_2D://�T�E���h2D
		return new C_Spund_2D_Bullet_Hit_Base(Data,FileName);
		break;
	case Co_Sound_Type_3D://�T�E���h3D
		return new C_Sound_Base_3D(Data, FileName);
		break;
	}

	//�����ɂȂ������ꍇ�A�T�E���h2D
	return new C_Spund_2D_Bullet_Hit_Base(Data, FileName);
}
