#pragma once
#include<d3dx9.h>
#include<stdio.h>
#include"../../../GameSource/Struct.h"
#include"../../../GameSource/Const.h"
#include"../../../Const/Const_PartsTypeNo.h"

class C_MeshDataManagerBase {
public:
	//�\�����̓ǂݍ���
	virtual int GetDrawNum(int CarNo,bool SaveFlg)=0;
	//�\���ݒ�̓ǂݍ���
	virtual S_CAR_PARTS_DATA GetDrawSet(int CarNo,const int *DrawNo, bool SaveFlg) = 0;
protected:
	//�Z�[�u�E���[�h�p
	FILE* fp;
	FILE *fp_b;
	char FName[100];

	//�\����-----------------------------------------
	//�Z�[�u
	void SaveDN(int CarNo,int DrawNum);
	//���[�h
	int LoadDN(int CarNo);
	//txt���[�hdat�Z�[�u
	void LoadSaveDN(int CarNo);

	//�\�����----------------------------------------
	//�Z�[�u
	void Save_Car_Parts_Data(int CarNo, const int *DrawNo,const S_CAR_PARTS_DATA *Par);
	//���[�h
	S_CAR_PARTS_DATA Load_Car_Parts_Data(int CarNo, const int *DrawNo);
	//txt���[�hdat�Z�[�u
	void LoadSave_Car_Parts_Data(int CarNo, const int *DrawNo);
	//�������p�[�c
	S_CAR_PARTS_DATA InitPartsDS(void);
	
private:

};