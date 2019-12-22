#pragma once
#include"FadeIn.h"

class C_FadeOut :public C_FadeMove {
public:
	C_FadeMove* Action(bool *MoveFlg, int *Alpha, int alphaUp);
};