#pragma once
#include"CarSet.h"
#include<string>

class C_Stage_Room_Stand {
public:
	C_Stage_Room_Stand(const D3DXVECTOR3 *Set_Pos, std::string FileName);
	~C_Stage_Room_Stand();

	//�\��
	void Draw_Garage_Stand(const D3DXVECTOR3 *CameraPos);

	//�X�V
	bool Update_Garage_Stand(void);

private:
	C_Draw3D_Base2 * M_Garage_Stand;

	D3DXVECTOR3 M_Stand_Pos;

	//�폜
	void Delete_Garage_Stand(void);

	//�s��̍X�V
	void Set_Mat_Garage_Stand(void);

	//�\���̏�����
	void New_Garage_Stand(std::string FileName);
};