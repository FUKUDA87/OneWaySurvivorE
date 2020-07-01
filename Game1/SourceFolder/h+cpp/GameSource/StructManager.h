#pragma once
#include"Struct.h"

class c_StructManager
{
public:
	s_CarType GetCarType(const int *Type, const unsigned int *Number1, const unsigned int *Number2, const unsigned int *Number3);
	s_CarType GetCarType(const int *Type, const unsigned int *Number1, const unsigned int *Number2);
	s_CarType GetCarType(const int *Type, const unsigned int *Number1);
	s_CarType GetCarType(const int *Type);

	BULLETJUDGDATA GetBULLETJUDGDATA(const s_CarType *carType, const float *Dis);
};