#include "MeshDataManagerBase.h"


void C_MeshDataManagerBase::SaveDN(int CarNo, int DrawNum)
{
	sprintf_s(FName, sizeof(FName), "../GameFolder/Data/CarData/CarNo%d/CarNo%d.txt", CarNo, CarNo);
	//txtセーブ
	if (fopen_s(&fp, FName, "w") == 0) {
		fprintf_s(fp, "%d", DrawNum);
		fclose(fp);
	}
	//datセーブ
	sprintf_s(FName, sizeof(FName), "../GameFolder/Data/CarData/CarNo%d/CarNo%d.dat", CarNo, CarNo);
	if (fopen_s(&fp_b, FName, "wb") == 0) {
		fwrite(&DrawNum, sizeof(int), 1, fp_b);
		fclose(fp_b);
	}
}

int C_MeshDataManagerBase::LoadDN(int CarNo)
{
	int DrawNum;
	//ロード
	sprintf_s(FName, sizeof(FName), "../GameFolder/Data/CarData/CarNo%d/CarNo%d.dat", CarNo, CarNo);
	//ロード
	if (fopen_s(&fp_b, FName, "rb") == 0) {
		fread(&DrawNum, sizeof(int), 1, fp_b);
		fclose(fp_b);
	}
	else {
		//ロードができなかった時
		DrawNum = 5;
		SaveDN(CarNo, DrawNum);
	}

	return DrawNum;
}

void C_MeshDataManagerBase::LoadSaveDN(int CarNo)
{
	int DrawNum;

	sprintf_s(FName, sizeof(FName), "../GameFolder/Data/CarData/CarNo%d/CarNo%d.txt", CarNo, CarNo);
	//ロードtxt
	if (fopen_s(&fp, FName, "r") == 0) {
		fscanf_s(fp, "%d\n", &DrawNum);
		fclose(fp);
	}
	else {
		//ロードができなかった時
		DrawNum = 5;
		SaveDN(CarNo, DrawNum);
	}

	//datセーブ
	sprintf_s(FName, sizeof(FName), "../GameFolder/Data/CarData/CarNo%d/CarNo%d.dat", CarNo, CarNo);
	if (fopen_s(&fp_b, FName, "wb") == 0) {
		fwrite(&DrawNum, sizeof(int), 1, fp_b);
		fclose(fp_b);
	}
}

void C_MeshDataManagerBase::SaveDS(int CarNo, const int * DrawNo, const PARTSBASE * Par)
{
	PARTSBASEINT p;
	p = ChangePBI(Par);

	sprintf_s(FName, sizeof(FName), "../GameFolder/Data/CarData/CarNo%d/DrawNo%d.txt", CarNo,*DrawNo);
	//txtセーブ
	if (fopen_s(&fp, FName, "w") == 0) {
		fprintf_s(fp, "%f\n%f\n%f\n", p.AngX, p.AngY, p.AngZ);
		fprintf_s(fp, "%f %f %f\n", p.TransPos.x, p.TransPos.y, p.TransPos.z);
		fprintf_s(fp, "%f %f %f\n", p.ScalPos.x, p.ScalPos.y, p.ScalPos.z);
		fprintf_s(fp, "%d\n", p.MeshNo);
		fprintf_s(fp, "%d\n", p.MeshDrawFlg);
		fprintf_s(fp, "%d\n%d\n%d\n", p.JudgFlg,p.MoveFlg,p.GunFlg);
		fprintf_s(fp, "%d\n", p.ReverseFlg);
		fprintf_s(fp, "%d\n", p.MeshPartsNo);
		fclose(fp);
	}

	//datセーブ
	sprintf_s(FName, sizeof(FName), "../GameFolder/Data/CarData/CarNo%d/DrawNo%d.dat", CarNo, *DrawNo);
	if (fopen_s(&fp_b, FName, "wb") == 0) {
		fwrite(&p, sizeof(PARTSBASEINT), 1, fp_b);
		fclose(fp_b);
	}
}

PARTSBASE C_MeshDataManagerBase::LoadDS(int CarNo, const int * DrawNo)
{
	PARTSBASEINT p;
	
	sprintf_s(FName, sizeof(FName), "../GameFolder/Data/CarData/CarNo%d/DrawNo%d.dat", CarNo, *DrawNo);
	//ロード
	if (fopen_s(&fp_b, FName, "rb") == 0) {
		fread(&p, sizeof(PARTSBASEINT), 1, fp_b);
		fclose(fp_b);
	}
	else {
		//ロードができなかった時
		p = InitPartsDS();
		SaveDS(CarNo, DrawNo, &ChangePB(&p));
	}

	return ChangePB(&p);
}

void C_MeshDataManagerBase::LoadSaveDS(int CarNo, const int * DrawNo)
{
	PARTSBASEINT p;

	sprintf_s(FName, sizeof(FName), "../GameFolder/Data/CarData/CarNo%d/DrawNo%d.txt", CarNo, *DrawNo);
	//ロードtxt
	if (fopen_s(&fp, FName, "r") == 0) {
		fscanf_s(fp, "%f\n%f\n%f\n", &p.AngX, &p.AngY, &p.AngZ);
		fscanf_s(fp, "%f %f %f\n", &p.TransPos.x, &p.TransPos.y, &p.TransPos.z);
		fscanf_s(fp, "%f %f %f\n", &p.ScalPos.x, &p.ScalPos.y, &p.ScalPos.z);
		fscanf_s(fp, "%d\n", &p.MeshNo);
		fscanf_s(fp, "%d\n",& p.MeshDrawFlg);
		fscanf_s(fp, "%d\n%d\n%d\n", &p.JudgFlg, &p.MoveFlg, &p.GunFlg);
		fscanf_s(fp, "%d\n", &p.ReverseFlg);
		fscanf_s(fp, "%d\n", &p.MeshPartsNo);
		fclose(fp);
	}
	else {
		//ロードができなかった時
		p = InitPartsDS();
		SaveDS(CarNo, DrawNo,&ChangePB(&p));
	}

	//datセーブ
	sprintf_s(FName, sizeof(FName), "../GameFolder/Data/CarData/CarNo%d/DrawNo%d.dat", CarNo, *DrawNo);
	if (fopen_s(&fp_b, FName, "wb") == 0) {
		fwrite(&p, sizeof(PARTSBASEINT), 1, fp_b);
		fclose(fp_b);
	}
}

PARTSBASEINT C_MeshDataManagerBase::InitPartsDS(void)
{
	PARTSBASEINT p;
	p.AngX = 0.0f;
	p.AngY = 0.0f;
	p.AngZ = 0.0f;
	p.TransPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	p.ScalPos = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	p.MeshNo = 2;
	p.MeshDrawFlg = 1;
	p.JudgFlg = 0;
	p.MoveFlg = 0;
	p.GunFlg = 0;
	p.ReverseFlg = 0;
	p.MeshPartsNo = -1;
	return p;
}

PARTSBASE C_MeshDataManagerBase::ChangePB(const PARTSBASEINT * Par)
{
	PARTSBASE p;
	p.AngX = Par->AngX;
	p.AngY = Par->AngY;
	p.AngZ = Par->AngZ;
	p.TransPos = Par->TransPos;
	p.ScalPos = Par->ScalPos;
	p.MeshNo = Par->MeshNo;
	p.MeshDrawFlg = Par->MeshDrawFlg;
	p.MeshPartsNo = Par->MeshPartsNo;

	p.JudgFlg = false;
	if (Par->JudgFlg != 0)p.JudgFlg = true;

	p.MoveFlg = false;
	if (Par->MoveFlg != 0)p.MoveFlg = true;

	p.GunFlg = Par->GunFlg;

	p.ReverseFlg = false;
	if (Par->ReverseFlg != 0)p.ReverseFlg = true;

	return p;
}

PARTSBASEINT C_MeshDataManagerBase::ChangePBI(const PARTSBASE * Par)
{
	PARTSBASEINT p;
	p.AngX = Par->AngX;
	p.AngY = Par->AngY;
	p.AngZ = Par->AngZ;
	p.TransPos = Par->TransPos;
	p.ScalPos = Par->ScalPos;
	p.MeshNo = Par->MeshNo;
	p.MeshDrawFlg = Par->MeshDrawFlg;
	p.MeshPartsNo = Par->MeshPartsNo;

	p.JudgFlg = 0;
	if (Par->JudgFlg != false)p.JudgFlg = 1;

	p.MoveFlg = 0;
	if (Par->MoveFlg != false)p.MoveFlg = 1;

	p.GunFlg = Par->GunFlg;

	p.ReverseFlg = 0;
	if (Par->ReverseFlg != false)p.ReverseFlg = 1;

	return p;
}

