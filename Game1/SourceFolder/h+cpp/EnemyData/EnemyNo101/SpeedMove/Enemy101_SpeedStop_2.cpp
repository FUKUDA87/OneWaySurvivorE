#include "Enemy101_SpeedStop_2.h"
#include"../../../Move/Speed/Speed_Dead_A.h"
#include"Enemy101_Speed_3.h"

C_Speed_Update * C_Enemy101_SpeedStop_2::Update(int * Now_Speed,
	const bool * Car_Flg, const unsigned int * Now_GroNo,
	const int * Now_Phase, const int * Target_Speed,
	const unsigned int * Target_GroNo, const bool * UpdateStop_Flg)
{
	//HPÇ™É[ÉçÇ…Ç»Ç¡ÇΩéû
	if (*Car_Flg != true)return new Speed_Dead_A();

	switch (*Now_Phase)
	{
	case 1:
	case 3:
	case 5:
		return new C_Enemy101_Speed_3();
		break;
	}

	return nullptr;
}
