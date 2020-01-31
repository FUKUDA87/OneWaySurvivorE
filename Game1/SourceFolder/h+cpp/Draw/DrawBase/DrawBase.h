#pragma once
#include<d3dx9.h>
#include"../../GameSource/Struct.h"

class C_DrawBase {
public:
	C_DrawBase();
	//�\���̂̏��n��
	S_DrawBase Get_S_DrawBase(void) {
		return M_S_DrawBase;
	}
	//�\���̂̃Z�b�g
	void Set_S_DrawBase(const S_DrawBase* s_db) {
		M_S_DrawBase = *s_db;
	}

	//�\���̂̍s��̑��
	void Set_S_DrawBase_Mat(const D3DXMATRIX *Mat) {
		M_S_DrawBase.Mat = *Mat;
	}
	//�\���̂̈ʒu�̑��
	void Set_S_DrawBase_Pos(const D3DXVECTOR3 *Pos) {
		M_S_DrawBase.Pos = *Pos;
	}
	//�\���̂̈ړ��̑��
	void Set_S_DrawBase_TransPos(const D3DXVECTOR3 *TransPos) {
		M_S_DrawBase.TransPos = *TransPos;
	}
	//�\���̂̃T�C�Y�̑��
	void Set_S_DrawBase_ScalPos(const D3DXVECTOR3 *ScalPos) {
		M_S_DrawBase.ScalPos = *ScalPos;
	}
	//�\���̂�X���̑��
	void Set_S_DrawBase_AngX(const float *AngX) {
		M_S_DrawBase.AngX = *AngX;
	}
	//�\���̂�Y���̑��
	void Set_S_DrawBase_AngY(const float *AngY) {
		M_S_DrawBase.AngY = *AngY;
	}
	//�\���̂�Z���̑��
	void Set_S_DrawBase_AngZ(const float *AngZ) {
		M_S_DrawBase.AngZ = *AngZ;
	}
protected:
	
private:
	/*�ϐ�*/
	S_DrawBase M_S_DrawBase;

	/*�֐�*/

	//�\���\���̂̏�����
	S_DrawBase Init_S_DrawBase(void);
};