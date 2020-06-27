#include "NextTouch.h"

C_NextTouch::C_NextTouch()
{
	wind.Base.Pos = D3DXVECTOR3(1280.0f / 2.0f, 720.0f / 5.0f*4.0f, 0.0f);
	wind.Base.ScaPos.x *= 0.35f;
	wind.Base.ScaPos.y *= 0.4f;

	TouchNowNo = -1;
}


C_NextTouch::~C_NextTouch()
{
	Delete();
}

bool C_NextTouch::UpdateAll(void)
{
	if (m_button.size() < 1)return true;

	for (auto && b : m_button)b->Update(&wind.Base.Pos);

	return true;
}

void C_NextTouch::Draw2DAll(void)
{
	if (m_button.size() < 1)return;

	Draw2D();

	for (auto && b : m_button)b->Draw2D();
}

int C_NextTouch::Touch(void)
{
	if (m_button.size() < 1)return 0;

	int TouchNo = 0;
	int ButNo = -1;

	// �{�^���ɃJ�[�\���̓����蔻��
	for (unsigned int bc = 0; bc < m_button.size(); bc++) {
		if (m_button[bc]->TouchJudg()==true) {
			TouchNo = m_button[bc]->GetNextNo();
			ButNo = bc;
			break;
		}
	}

	if (ButNo < 0)return 0;

	// �ŐV�ŃJ�[�\���������Ă���{�^���̕\����ύX
	if (TouchNowNo != ButNo) {
		TouchNowNo = ButNo;
		for (unsigned int bc = 0; bc < m_button.size(); bc++) {
			if (bc == TouchNowNo) {
				m_button[bc]->SetDrawChangeFlg(true);
			}
			else {
				m_button[bc]->SetDrawChangeFlg(false);
			}
		}
	}

	return TouchNo;
}

void C_NextTouch::Delete(void)
{
	if (m_button.size() < 1)return;

	for (unsigned int bc = 0; bc < m_button.size(); bc++) {
		delete m_button[bc];
		m_button.erase(m_button.begin() + bc);
		bc--;
	}
}
