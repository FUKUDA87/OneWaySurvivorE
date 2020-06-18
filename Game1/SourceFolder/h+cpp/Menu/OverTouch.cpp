#include "OverTouch.h"
#include"Button/RetryButton.h"
#include"Button/SelectButton.h"

C_OverTouch::C_OverTouch()
{
	float y = 40.0f;

	m_button.push_back(new c_RetryButton(&wind.Base.Pos, -y));
	m_button.push_back(new c_SelectButton(&wind.Base.Pos, y));
}
