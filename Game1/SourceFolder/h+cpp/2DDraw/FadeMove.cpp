#include "FadeMove.h"
#include"FadeOut.h"

C_FadeMove * C_FadeNoMove::Action(bool * MoveFlg, int * Alpha, int alphaUp)
{
	if (*MoveFlg == true) {
		return new C_FadeIn();
	}
	return nullptr;
}
