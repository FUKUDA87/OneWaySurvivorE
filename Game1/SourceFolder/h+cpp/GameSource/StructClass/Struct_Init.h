#pragma once
#include<d3dx9.h>
#include"../Struct.h"

class C_Struct_Init {
public:
	//’n–Ê‚Ì‰Šú‰»î•ñ
	S_GROUND_INIT_DATA Get_S_GROUND_INIT_DATA(const int gType, const float Ang, const float Length, const bool LengthAuto);
	S_GROUND_INIT_DATA Get_S_GROUND_INIT_DATA(const int gType);

};