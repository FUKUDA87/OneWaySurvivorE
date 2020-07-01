#pragma once
#include"ground.h"
#include"Ground_Object_Parts/Object_Base.h"

class C_Ground_Object :public C_Ground {
public:
	C_Ground_Object(const int *i);
	C_Ground_Object(const D3DXMATRIX *Mat3, const D3DXMATRIX *Mat4, const S_GROUND_INIT_DATA * Init_Data_Ground);

	~C_Ground_Object();

	// �X�V����
	bool Update();

	// �\��
	void Draw3D();

	//�\�����̓n��
	unsigned int Get_Object_Draw_Num(void) {
		return M_Object.size();
	}

	//���n��
	S_Base3D_2 Get_Object_Data(const unsigned int *No);

	//�\����Flg�̃Z�b�g
	void Set_DrawFlg_Object(const unsigned int *No,const bool *Flg);

	//�����̏�����
	void Init_Bill(void);

	//�O���̏�����
	void Init_Light(void);

protected:
	//�X�V
	void Update_Object(void);
private:
	//�\��
	void Draw_Object(void);

	std::vector<C_Object_Base*>M_Object;

	//�\���̍폜
	void Delete_All_Object(void);

	//�\���̍s��̎擾
	D3DXMATRIX Get_Object_SetMat(const unsigned int *No);
};