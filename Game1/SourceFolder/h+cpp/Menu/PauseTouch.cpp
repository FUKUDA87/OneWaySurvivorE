#include "PauseTouch.h"
#include"Button/PlayButton.h"
#include"Button/SelectButton.h"

C_PauseTouch::C_PauseTouch()
{
	float y = 40.0f;

	m_button.push_back(new c_PlayButton(&wind.Base.Pos, -y));
	m_button.push_back(new c_SelectButton(&wind.Base.Pos, y));
}
