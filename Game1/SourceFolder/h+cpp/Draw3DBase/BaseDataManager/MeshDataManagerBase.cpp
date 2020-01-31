#include "MeshDataManagerBase.h"


void C_MeshDataManagerBase::SaveDN(int CarNo, int DrawNum)
{
	sprintf_s(FName, sizeof(FName), "../GameFolder/Data/CarData/CarNo%d/CarNo%d.txt", CarNo, CarNo);
	//txt�Z�[�u
	if (fopen_s(&fp, FName, "w") == 0) {
		fprintf_s(fp, "%d", DrawNum);
		fclose(fp);
	}
	//dat�Z�[�u
	sprintf_s(FName, sizeof(FName), "../GameFolder/Data/CarData/CarNo%d/CarNo%d.dat", CarNo, CarNo);
	if (fopen_s(&fp_b, FName, "wb") == 0) {
		fwrite(&DrawNum, sizeof(int), 1, fp_b);
		fclose(fp_b);
	}
}

int C_MeshDataManagerBase::LoadDN(int CarNo)
{
	int DrawNum;
	//���[�h
	sprintf_s(FName, sizeof(FName), "../GameFolder/Data/CarData/CarNo%d/CarNo%d.dat", CarNo, CarNo);
	//���[�h
	if (fopen_s(&fp_b, FName, "rb") == 0) {
		fread(&DrawNum, sizeof(int), 1, fp_b);
		fclose(fp_b);
	}
	else {
		//���[�h���ł��Ȃ�������
		DrawNum = 5;
		SaveDN(CarNo, DrawNum);
	}

	return DrawNum;
}

void C_MeshDataManagerBase::LoadSaveDN(int CarNo)
{
	int DrawNum;

	sprintf_s(FName, sizeof(FName), "../GameFolder/Data/CarData/CarNo%d/CarNo%d.txt", CarNo, CarNo);
	//���[�htxt
	if (fopen_s(&fp, FName, "r") == 0) {
		fscanf_s(fp, "%d\n", &DrawNum);
		fclose(fp);
	}
	else {
		//���[�h���ł��Ȃ�������
		DrawNum = 5;
		SaveDN(CarNo, DrawNum);
	}

	//dat�Z�[�u
	sprintf_s(FName, sizeof(FName), "../GameFolder/Data/CarData/CarNo%d/CarNo%d.dat", CarNo, CarNo);
	if (fopen_s(&fp_b, FName, "wb") == 0) {
		fwrite(&DrawNum, sizeof(int), 1, fp_b);
		fclose(fp_b);
	}
}

void C_MeshDataManagerBase::Save_Car_Parts_Data(int CarNo, const int * DrawNo, const S_CAR_PARTS_DATA * Par)
{
	S_CAR_PARTS_DATA p=*Par;

	sprintf_s(FName, sizeof(FName), "../GameFolder/Data/CarData/CarNo%d/DrawNo%d.txt", CarNo,*DrawNo);
	//txt�Z�[�u
	if (fopen_s(&fp, FName, "w") == 0) {
		fprintf_s(fp, "%f %f %f\n", p.TransPos.x, p.TransPos.y, p.TransPos.z);
		fprintf_s(fp, "%f %f %f\n", p.Ang.x, p.Ang.y, p.Ang.z);
		fprintf_s(fp, "%d\n", p.MeshTypeNo);
		fprintf_s(fp, "%d\n", p.MeshJointNo);
		fclose(fp);
	}

	//dat�Z�[�u
	sprintf_s(FName, sizeof(FName), "../GameFolder/Data/CarData/CarNo%d/DrawNo%d.dat", CarNo, *DrawNo);
	if (fopen_s(&fp_b, FName, "wb") == 0) {
		fwrite(&p, sizeof(S_CAR_PARTS_DATA), 1, fp_b);
		fclose(fp_b);
	}
}

S_CAR_PARTS_DATA C_MeshDataManagerBase::Load_Car_Parts_Data(int CarNo, const int * DrawNo)
{
	S_CAR_PARTS_DATA p;
	
	sprintf_s(FName, sizeof(FName), "../GameFolder/Data/CarData/CarNo%d/DrawNo%d.dat", CarNo, *DrawNo);
	//���[�h
	if (fopen_s(&fp_b, FName, "rb") == 0) {
		fread(&p, sizeof(S_CAR_PARTS_DATA), 1, fp_b);
		fclose(fp_b);
	}
	else {
		//���[�h���ł��Ȃ�������
		p = InitPartsDS();
		Save_Car_Parts_Data(CarNo, DrawNo, &p);
	}

	return p;
}

void C_MeshDataManagerBase::LoadSave_Car_Parts_Data(int CarNo, const int * DrawNo)
{
	S_CAR_PARTS_DATA p;

	sprintf_s(FName, sizeof(FName), "../GameFolder/Data/CarData/CarNo%d/DrawNo%d.txt", CarNo, *DrawNo);
	//���[�htxt
	if (fopen_s(&fp, FName, "r") == 0) {
		fscanf_s(fp, "%f %f %f\n", &p.TransPos.x, &p.TransPos.y, &p.TransPos.z);
		fscanf_s(fp, "%f %f %f\n", &p.Ang.x, &p.Ang.y, &p.Ang.z);
		fscanf_s(fp, "%d\n", &p.MeshTypeNo);
		fscanf_s(fp, "%d\n",& p.MeshJointNo);
		fclose(fp);
	}
	else {
		//���[�h���ł��Ȃ�������
		p = InitPartsDS();
		Save_Car_Parts_Data(CarNo, DrawNo,&p);
	}

	//dat�Z�[�u
	sprintf_s(FName, sizeof(FName), "../GameFolder/Data/CarData/CarNo%d/DrawNo%d.dat", CarNo, *DrawNo);
	if (fopen_s(&fp_b, FName, "wb") == 0) {
		fwrite(&p, sizeof(S_CAR_PARTS_DATA), 1, fp_b);
		fclose(fp_b);
	}
}

S_CAR_PARTS_DATA C_MeshDataManagerBase::InitPartsDS(void)
{
	S_CAR_PARTS_DATA p;
	p.Ang = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	p.TransPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	p.MeshTypeNo = 0;
	p.MeshJointNo = 1;
	return p;
}

