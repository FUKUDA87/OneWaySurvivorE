#pragma once
#include<d3dx9.h>
#include"../Fade/FadeDraw.h"
#include"../GameSource/Struct.h"

class Pause  
{
public:
	Pause();
	~Pause();

	//�\��
	void Draw();
	//�\���̗L��Flg����
	void SetDFlg(bool Flg) {
		pau.Base.DrawFlg = Flg;
	}
	//�\���̗L��Flg�n��
	bool GetDFlg(void) {
		return pau.Base.DrawFlg;
	}

	//�X�e�[�W�Z�[�u�̗L��Flg����
	void SetStaSavFlg(bool Flg) {
		StageSaveFlg = Flg;
	}
	//�X�e�[�W�Z�[�u�̗L��Flg�n��
	bool GetStaSavFlg(void) {
		return StageSaveFlg;
	}
protected:
	CHARA2D pau;
private:
	//�X�e�[�W�̏��L�^�pFlg
	bool StageSaveFlg;

	C_FadeDraw *fadeDraw;
	int alpha;
	
};