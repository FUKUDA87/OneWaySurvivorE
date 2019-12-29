#include "CarSet.h"
#include<stdio.h>
#include"../Draw3DBase/Draw3DManager/TireMeshManager.h"
#include"../GameSource/XfileManager.h"
#include"../Draw3DBase/Draw3DManager/CarNoManager.h"


extern XfileManager xfileManager;
extern LPD3DXFONT lpFontS;

extern LPDIRECT3DDEVICE9		lpD3DDevice;	// Direct3DDeviceインターフェイス


void DrawMesh(XFILE *XFile);

C_CarSet::C_CarSet()
{
	ModeFlg = false;
	C_TireMeshManager l_TireManager;
	Tire = l_TireManager.GetMesh(1);
	CarMeshNo = 0;
	ChangeCar();
	PartsPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	Vector = xfileManager.GetXfile("../GameFolder/Material/XFile/Vector1.x");
	PartsMeshFlg = 0;
	GroundY = 0.0f;
}

C_CarSet::~C_CarSet()
{
}

void C_CarSet::ChangeMode(const bool Flg)
{
	if (Flg != true)return;

	judg.ReverseFlg(&ModeFlg);
}

void C_CarSet::DrawTxt(void)
{
	if (ModeFlg != true)return;

	RECT rcCon = { 0,0,0,0 };
	char TextB[200];
	sprintf_s(TextB, sizeof(TextB), "Xキー(赤X：緑Y：青Z：尖り＋)\nX:%f(-A:+F)\nY:%f(+W:-S)\nZ:%f(+E:-D)\nG:%f\n"
		,PartsPos.x, PartsPos.y, PartsPos.z,GroundY);
	lpFontS->DrawTextA(NULL, TextB, -1, &rcCon, DT_LEFT | DT_NOCLIP, D3DCOLOR_ARGB(255, 255, 255, 255));
}

void C_CarSet::Draw3D(void)
{
	if (ModeFlg != true)return;

	D3DXMATRIX TmpMat;
	D3DXMatrixTranslation(&TmpMat, 0.0f, 0.0f, 0.0f);
	lpD3DDevice->SetTransform(D3DTS_WORLD, &TmpMat);
	DrawMesh(&Car);

	D3DXMATRIX PartsMat;
	judg.SetTransMat(&PartsMat, &PartsPos);
	lpD3DDevice->SetTransform(D3DTS_WORLD, &PartsMat);
	switch (PartsMeshFlg)
	{
	case 0:
		DrawMesh(&Tire);
		break;
	case 1:
		DrawMesh(&Vector);
		break;
	default:
		DrawMesh(&Tire);
		break;
	}


}

void C_CarSet::ChangeCar(void)
{
	C_CarNoManager l_CarManager;
	CarMeshNo = l_CarManager.GetNextNo(&CarMeshNo);

	Car = l_CarManager.GetMesh(CarMeshNo).Mesh1;

}

void C_CarSet::ChangePartsMeshFlg(const bool Flg)
{
	if (Flg != true)return;

	switch (PartsMeshFlg)
	{
	case 0:
		PartsMeshFlg = 1;
		break;
	case 1:
		PartsMeshFlg = 0;
		break;
	default:
		PartsMeshFlg = 0;
		break;
	}
}

void C_CarSet::GroundSize(const float * H_Y)
{
	GroundY = 0.0f - PartsPos.y+(PartsPos.y-*H_Y);
}
