#pragma once
#include"../2DDraw/Window.h"
#include"../GameSource/Judgment.h"
#include"../Scene/SceneNo.h"
#include"Button/ButtonGameScene.h"
#include<vector>

class C_NextTouch:public Window {
public:
	C_NextTouch();
	~C_NextTouch();
	// �X�V����
	virtual bool UpdateAll(void);
	//�\��
	virtual void Draw2DAll(void);
	//�^�b�`�̊m�F
	virtual int Touch(void);

protected:
	std::vector<c_ButtonGameScene*>m_button;
private:

	int TouchNowNo;// �ŐV�ŉ����ꂽ�{�^���ԍ�

	// �폜
	void Delete(void);


};