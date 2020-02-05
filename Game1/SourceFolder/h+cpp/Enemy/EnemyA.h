#pragma once
#include"EnemyAi.h"
#include"../GameSource/Const.h"
#include"../Draw3DBase/TireParts.h"
#include"../GameSource/CharaBase.h"
#include"../EnemyData/Base&Manager/EnemyDataManager.h"
#include"../GameSource/StructClass/Parts_Set_Data.h"

class C_EnemyA :public C_EnemyAi {
public:
	C_EnemyA(D3DXMATRIX GroundMat, float *TransX);
	~C_EnemyA();
protected:
	//�������{�f�B
	void InitBody(void);

	//�e�̂�����
	void New_Car_Parts_Gun(const BODYDATA *CarData) {
		return;
	}
	void New_Car_Parts_Gun(std::vector<C_Parts_Set_Data*>M_Set_Data) {
		return;
	}

	//�����ʒu
	void InitPos(D3DXMATRIX GroundMat, float *TransX);

	//�Ԃ̃p�[�c�̐ݒ�
	std::vector<C_Parts_Set_Data*>M_Parts_Set_Data;

	//�p�[�c�̏��̍폜
	void Delete_All_Parts_Set_Data(void);
private:

};