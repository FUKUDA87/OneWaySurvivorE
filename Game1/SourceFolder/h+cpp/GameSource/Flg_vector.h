#pragma once
#include"Flg_No1.h"
#include<vector>

class C_Flg_vector {
public:

protected:
	void Init_Flg(void);

	void Init_Flg(const int *No) {
		M_Flg.push_back(new C_Flg_No1(No));
	}

	std::vector<C_Flg_No1*>M_Flg;
};