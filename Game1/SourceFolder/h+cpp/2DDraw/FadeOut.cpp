#include "FadeOut.h"

C_FadeMove * C_FadeOut::Action(bool * MoveFlg, int * Alpha, int alphaUp)
{
	if (*MoveFlg == true) {
		*Alpha -= alphaUp;
		if (*Alpha <= 0) {
			*Alpha = 0;
			*MoveFlg = false;
			return new C_FadeNoMove();
		}
	}
	return nullptr;
}
