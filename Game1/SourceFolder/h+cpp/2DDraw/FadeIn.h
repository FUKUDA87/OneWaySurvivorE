#pragma once
#include"FadeMove.h"
#include"FadeOut.h"

class C_FadeIn :public C_FadeMove {
public:
	C_FadeIn();
	C_FadeMove* Action(bool *MoveFlg, int *Alpha, int alphaUp);
private:
	int CountNum;
};