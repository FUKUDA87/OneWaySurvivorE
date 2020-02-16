#pragma once
#include<d3dx9.h>

class C_Flg_No1 {
public:
	C_Flg_No1(const int *No);

	bool Get_Flg(void) {
		return M_Flg;
	}

	int Get_No(void) {
		return M_No;
	}

	void Init(void) {
		M_Flg = false;
	}
private:
	int M_No;
	bool M_Flg;
};