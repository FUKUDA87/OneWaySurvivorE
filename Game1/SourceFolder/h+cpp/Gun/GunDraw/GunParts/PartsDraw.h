#pragma once
#include<d3dx9.h>
#include"../../../GameSource/Struct.h"
#include"../../../Draw/DrawBase2/Draw3D_Base2.h"

class C_PartsDraw_Base {
public:
	C_PartsDraw_Base(C_Draw3D_Base2 *NewDraw);
	~C_PartsDraw_Base();

	//�\��
	void Draw(const D3DXVECTOR3 *CameraPos);

	//�s��̃Z�b�g
	virtual void Set_Mat(const D3DXMATRIX *Mat);

	//�s��n��
	virtual D3DXMATRIX Get_Mat(void);
protected:
	/*�����o�[�ϐ�*/

	C_Draw3D_Base2 *M_Draw_Base;

	/*�����o�[�֐�*/

	//������

private:
	/*������*/

	//�폜
	void Delete_Draw(void);

	//�\���̏�����
	void Init_Draw(C_Draw3D_Base2 *NewDraw);
};