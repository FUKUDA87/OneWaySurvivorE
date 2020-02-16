#include "Flg_vector.h"

void C_Flg_vector::Init_Flg(void)
{
	if (M_Flg.size() < 1)return;

	for (auto && f : M_Flg) {
		f->Init();
	}
}
