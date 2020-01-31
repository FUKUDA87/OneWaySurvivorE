#pragma once
#include"PartsBase.h"
#include<vector>
#include"BaseDataManager/CarDataManager.h"
#include"../Draw3DBase/Draw3DManager/TireMeshManager.h"
#include"../Draw3DBase/Draw3DManager/StandMeshManager.h"
#include"../Draw3DBase/TireParts.h"
#include"../GameSource/Judgment.h"
#include"Draw3DManager/PartsMeshManager.h"
#include"EnemyParts.h"
#include"../EnemyData/Base&Manager/EnemyDataManager.h"
#include"Car_Parts_Data.h"
#include"Car_Parts_Joint.h"
#include"../Const/Const_PartsTypeNo.h"

class C_CarParts:public C_Car_Parts_Data {
public:
	~C_CarParts();

	//�p�[�c�̕\��
	void Draw_Car_Parts(const D3DXVECTOR3* CameraPos);
	//�p�[�c�̍X�V
	bool Update_Car_Parts(void);
	//�p�[�c�̏��n��

	//�p�[�c�̍폜
	void Delete_Parts(unsigned int *PartsNo);

	//�p�[�c�Ƀ_���[�W

	//�J�����ɍs��n��
	D3DXMATRIX Get_Camera_Mat(void);

protected:
	//�p�[�c�\���ϐ�
	std::vector<C_Car_Parts_Joint*>M_Car_Parts;

	BODYDATA BodyData;

	//�p�[�c�̏�����
	virtual void New_Set_Car_Parts(const BODYDATA *CarData, const bool *SaveFlg,const bool *Data_DeleteFlg);

	//�p�[�c�̑S�폜
	void Delete_ALL_Parts(void);

	//�p�[�c�̏�����(�v���C���[)
	void New_CarParts(const BODYDATA *CarData, const bool *SaveFlg);
	//�p�[�c�̏�����(�G�l�~�[)

private:

};