#include "FadeIn.h"

C_FadeIn::C_FadeIn()
{
	CountNum = 50;
}

C_FadeMove * C_FadeIn::Action(bool * MoveFlg, int * Alpha, int alphaUp)
{
	if (*MoveFlg == true) {
		*Alpha += alphaUp;
		if (*Alpha >= 255) {
			*Alpha = 255;
			CountNum -= 1;
			if (CountNum <= 0) {
				*MoveFlg = false;
				return new C_FadeOut();
			}
		}
	}
	return nullptr;
}
