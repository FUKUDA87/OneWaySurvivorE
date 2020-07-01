#include "StructManager.h"

s_CarType c_StructManager::GetCarType(const int * Type, const unsigned int * Number1, const unsigned int * Number2, const unsigned int * Number3)
{
	s_CarType carType;

	carType.Type = *Type;

	if (Number1 != nullptr)
	{
		carType.Numbar[0] = *Number1;
	}
	else {
		carType.Numbar[0] = 0;
	}

	if (Number2 != nullptr)
	{
		carType.Numbar[1] = *Number2;
	}
	else {
		carType.Numbar[1] = 0;
	}

	if (Number3 != nullptr)
	{
		carType.Numbar[2] = *Number3;
	}
	else {
		carType.Numbar[2] = 0;
	}

	return carType;
}

s_CarType c_StructManager::GetCarType(const int * Type, const unsigned int * Number1, const unsigned int * Number2)
{
	return GetCarType(Type, Number1, Number2, nullptr);
}

s_CarType c_StructManager::GetCarType(const int * Type, const unsigned int * Number1)
{
	return GetCarType(Type,Number1,nullptr);
}

s_CarType c_StructManager::GetCarType(const int * Type)
{
	return GetCarType(Type, nullptr, nullptr);
}

BULLETJUDGDATA c_StructManager::GetBULLETJUDGDATA(const s_CarType * carType, const float * Dis)
{
	BULLETJUDGDATA BJD;
	BJD.JudgType = *carType;
	BJD.HitType.Type = -1;
	BJD.SamllDis = *Dis;
	return BJD;
}
