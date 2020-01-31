#pragma once
#include"Draw_Pol_A.h"

class C_Draw_PolMat_Base_1 :public C_Draw_Pol_BASE_A {
public:
	C_Draw_PolMat_Base_1(std::string FileName, const S_TEX_POS *Pos);
	C_Draw_PolMat_Base_1(std::string FileName, const S_TEX_DRAW_DATA* Data);

	~C_Draw_PolMat_Base_1();

	//�\���֐�
	void Draw3D(const D3DXVECTOR3 *CameraPos);

	//�ړ��ʂ̃Z�b�g
	void Set_MoveVec(const D3DXVECTOR3 *MoveVec);

	//�s��̓n��
	void Set_Mat(const D3DXMATRIX*Mat) {
		Set_PolMat_Mat(Mat);
	}

protected:

	/*�����o�[�ϐ�*/


	//�|���S���Ǘ��̕ϐ�
	S_Pol M_Polygon;

	/*�����o�[�֐�*/

	//null�`�F�b�N�ƃ|���S�����̃`�F�b�N(<1)
	bool PolMat_Judg(void);

	//null�`�F�b�N�ƃ|���S�����̃`�F�b�N(<PolNum)
	bool PolMat_Judg(const int PolNum);

	//�\���|���S�����̍s��̕ύX
	void Init_PolMat(const int PolNum);

	//�|���S�����̍s��̍폜
	void Delete_PolMat(void);

	//�|���S�����̍s��ɒʏ�̍s�������
	void Init_PolMat_Mat(const D3DXMATRIX *Mat);

	//�|���S�����̍s��ɍs���n���Ȃ�������
	void Set_PolMat_Mat(const D3DXMATRIX *Mat);

	//
	virtual void PolMat_Set_MoveVec(const D3DXVECTOR3 *MoveVec);

	//�|���S������n��
	int Get_PolMatNum(void) {
		return M_Polygon.PolNum;
	}

	/*�\��*/

	//�e�Ɏg�p
	virtual void Draw_PolMat_No1(const D3DXVECTOR3 *CameraPos);

private:

};