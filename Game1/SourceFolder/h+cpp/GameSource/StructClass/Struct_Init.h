#pragma once
#include<d3dx9.h>
#include"../Struct.h"

class C_Struct_Init {
public:
	//地面の初期化情報
	S_GROUND_INIT_DATA Get_S_GROUND_INIT_DATA(const int gType, const float Ang, const float Length, const bool LengthAuto);
	S_GROUND_INIT_DATA Get_S_GROUND_INIT_DATA(const int gType);

};