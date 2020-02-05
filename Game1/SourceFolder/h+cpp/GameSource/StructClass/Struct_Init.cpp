#include "Struct_Init.h"
#include"../../Const/Const_Ground_Type.h"

S_GROUND_INIT_DATA C_Struct_Init::Get_S_GROUND_INIT_DATA(const int gType, const float Ang, const float Length, const bool LengthAuto)
{
	S_GROUND_INIT_DATA Data;

	Data.gType = gType;
	Data.Ang = Ang;
	Data.Length = Length;
	Data.LengthAuto = LengthAuto;

	return Data;
}

S_GROUND_INIT_DATA C_Struct_Init::Get_S_GROUND_INIT_DATA(const int gType)
{
	if (gType != Co_Ground_Type_Straight) {
		return Get_S_GROUND_INIT_DATA(gType, 90.0f / 5.0f, 5.0f, false);
	}
	
	return Get_S_GROUND_INIT_DATA(gType, 0.0f, 0.0f, true);
}
