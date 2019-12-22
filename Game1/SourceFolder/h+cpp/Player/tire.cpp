#include"tire.h"
#include<stdio.h>
#include"../GameSource/XfileManager.h"

extern LPDIRECT3DDEVICE9 lpD3DDevice;
extern LPD3DXFONT lpFont;
extern XfileManager xfileManager;

void DrawMesh(XFILE *XFile);


C_Tire::C_Tire() {
	xfileManager.GetXfile(&tireMesh, "../GameFolder/Material/XFile/tireP5.x");
	D3DXVECTOR3 tPos = D3DXVECTOR3(0.4f, -0.02f, 0.7f);
	D3DXMatrixTranslation(&tire[0].Trans, -tPos.x, tPos.y, tPos.z);
	D3DXMatrixTranslation(&tire[1].Trans, tPos.x, tPos.y, tPos.z);
	tPos = D3DXVECTOR3(0.4f, -0.02f, 0.85f);
	D3DXMatrixTranslation(&tire[2].Trans, tPos.x, tPos.y, -tPos.z);
	D3DXMatrixTranslation(&tire[3].Trans, -tPos.x, tPos.y, -tPos.z);
	for (int i = 0; i < TNUM; i++) {
		tire[i].Mat = tire[i].Trans * player.Base.Mat;
		tire[i].AngX = 0.0f;
		tire[i].MoveFlg = true;
	}
	D3DXMatrixRotationY(&tire[0].RotY, D3DXToRadian(0.0f));
	D3DXMatrixRotationY(&tire[1].RotY, D3DXToRadian(180.0f));
	D3DXMatrixRotationY(&tire[2].RotY, D3DXToRadian(180.0f));
	D3DXMatrixRotationY(&tire[3].RotY, D3DXToRadian(0.0f));
	for (int i = 0; i < 4; i++) {
		tire[i].Mat = tire[i].RotY *tire[i].Mat;
		D3DXMatrixScaling(&tire[i].Scal, 0.75f, 1.0f, 1.0f);
	}
	
}
C_Tire::~C_Tire() {
	//ReleaseMesh(&tireMesh);
}

bool C_Tire::TUpdate(void) {
	for (int i = 0; i < TNUM; i++) {
		if (tire[i].MoveFlg == true) {
			tire[i].AngX += 14.0f;
			if (tire[i].AngX > 360.0f)tire[i].AngX -= 360.0f;
			D3DXMatrixRotationX(&tire[i].RotX, D3DXToRadian((float)tire[i].AngX));
			tire[i].Mat = tire[i].Scal*tire[i].RotY *tire[i].RotX*tire[i].Trans * player.Base.Mat;
		}
		else {
			tire[i].Mat = tire[i].Scal*tire[i].RotY *tire[i].Trans * player.Base.Mat;
		}
		if (player.Con.CurFlg == true) {
			if (player.Con.CurLFlg == true) {

			}
			else {
				if (player.Con.CurRFlg == true) {

				}
			}
		}
	}

	return true;
}

void C_Tire::TDraw(void) {
	for (int i = 0; i < TNUM; i++) {
		lpD3DDevice->SetTransform(D3DTS_WORLD, &tire[i].Mat);
		DrawMesh(&tireMesh);
	}
}
