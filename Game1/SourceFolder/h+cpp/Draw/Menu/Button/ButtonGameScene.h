#pragma once
#include"ButtonBase.h"

class c_ButtonGameScene:public c_ButtonBase
{
public:
	c_ButtonGameScene();

	// �\��
	void Draw2D(void);

	bool GetDrawChangeFlg(void) { return DrawChangeFlg; }
	void SetDrawChangeFlg(const bool Flg) { DrawChangeFlg = Flg; }
protected:
	LPDIRECT3DTEXTURE9 buttonTex[2];

	int width2, height2;  // �摜�T�C�Y

	// �����̃T�C�Y�𕽋ς̃T�C�Y�ɏ���������
	void InitScal(const int ChaNum, const float Size);

private:
	bool DrawChangeFlg;  // �\���ύXFl
};