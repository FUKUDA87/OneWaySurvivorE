#pragma once
#include"Object_Base.h"

class C_Bill_Object_1:public C_Object_Base {
public:
	C_Bill_Object_1();

	//�\���s��̍X�V
	void Update_DrawMat(const D3DXMATRIX *Mat);


protected:
	//������
	void Init(void);
private:

};