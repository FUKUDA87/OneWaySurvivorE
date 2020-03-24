#pragma once
#include"EnemyAi.h"
#include"../GameSource/Const.h"
#include"../GameSource/CharaBase.h"
#include"../GameSource/StructClass/Parts_Set_Data.h"

class C_EnemyA :public C_EnemyAi {
public:
	C_EnemyA(const D3DXMATRIX *GroundMat,const float *TransX);
	~C_EnemyA();
protected:
	//�������{�f�B
	void InitBody(void);

	//�Ԃ̃p�[�c��t���鏈��
	void New_Set_EnemyCar_Parts(const int *Car_No);

	//�e�̂�����
	void New_Car_Parts_Gun(const BODYDATA *CarData) {
		return;
	}
	void New_Car_Parts_Gun(std::vector<C_Parts_Set_Data*>M_Set_Data) {
		return;
	}

	//�Ԃ̃p�[�c���Z�b�g���邽�߂̏��̃Z�b�g
	void M_NewSet_CarPartsData(const int *CarParts_Type,const int CarParts_No,const int Draw_No);

private:
	//�����ʒu
	void InitPos(const D3DXMATRIX *GroundMat, const float * TransX);

	//�p�[�c�̏��̍폜
	void Delete_All_Parts_Set_Data(void);

	//�Ԃ̃p�[�c�̐ݒ�
	std::vector<C_Parts_Set_Data*>M_Parts_Set_Data;
};