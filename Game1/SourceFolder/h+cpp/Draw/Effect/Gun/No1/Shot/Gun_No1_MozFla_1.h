#pragma once
#include"../../../../../Draw/DrawBase2/Draw_Pol_A.h"

class C_Gun_No1_MuzFla_1 :public C_Draw_Pol_BASE_A {
public:
	C_Gun_No1_MuzFla_1(const D3DXMATRIX *Gun_Mouth_Mat);

	//�\���֐�
	void Draw3D(const D3DXVECTOR3 *CameraPos);

	bool Update(void);
protected:

	//�e�N�X�`���̃��[�h
	void Init_Load(void);

	//�s��̏�����
	void Init_Mat(const D3DXMATRIX *Gun_Mouth_Mat);

	//�|���S���̏�����
	void Init_Pol_Set(void);

	bool AliveFlg;
private:

};