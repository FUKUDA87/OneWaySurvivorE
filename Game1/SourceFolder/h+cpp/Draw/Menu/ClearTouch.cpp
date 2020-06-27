#include "ClearTouch.h"
#include"Button/TitleButton.h"
#include"Button/SelectButton.h"

C_ClearTouch::C_ClearTouch()
{
	float y = 40.0f;

	m_button.push_back(new c_SelectButton(&wind.Base.Pos, -y));
	m_button.push_back(new c_TitleButton(&wind.Base.Pos, y));
}
