#pragma once
#include<d3dx9.h>
#include"../../GameSource/Struct.h"

class C_Sound_Data_Base {
public:

	C_Sound_Data_Base(const S_SOUND_DATA *Set_Data);

	//î•ñ“n‚µ
	S_SOUND_DATA Get_Data(void) {
		return M_S_Data;
	}
protected:

private:
	S_SOUND_DATA M_S_Data;
};