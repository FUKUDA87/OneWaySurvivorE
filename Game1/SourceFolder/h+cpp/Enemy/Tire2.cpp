#include"Tire2.h"
#include"../GameSource/XfileManager.h"

extern LPDIRECT3DDEVICE9 lpD3DDevice;
extern XfileManager xfileManager;

void DrawMesh(XFILE *XFile);

Tire2::Tire2() {
	xfileManager.GetXfile(&tire2Mesh, "../GameFolder/Material/XFile/Tire2.x");
	//D3DXMatrixTranslation(&tire2Mat, 0, 0, 0);
}
Tire2::Tire2(D3DXMATRIX GroundMat, float *TransX) :Enemy(GroundMat, TransX) {
	xfileManager.GetXfile(&tire2Mesh, "../GameFolder/Material/XFile/Tire2.x");
	D3DXVECTOR3 pos(0.65f,-0.5f,0.55f);
	int i=0;
	D3DXMatrixTranslation(&tire2TransMat[i], -pos.x, pos.y, pos.z); i++;
	D3DXMatrixTranslation(&tire2TransMat[i], pos.x, pos.y, pos.z); i++;
	pos=D3DXVECTOR3(0.65f, -0.5f, 0.75f);
	D3DXMatrixTranslation(&tire2TransMat[i], pos.x, pos.y, -pos.z); i++;
	D3DXMatrixTranslation(&tire2TransMat[i], -pos.x, pos.y, -pos.z); i=0;
	for (int i = 0; i < TNUM; i++) {
		if (i == 0 || i == 3) {
			D3DXMatrixRotationY(&tire2RotMatY[i], D3DXToRadian(180));
		}
		else {
			D3DXMatrixRotationY(&tire2RotMatY[i], D3DXToRadian(0));
		}
	}
	for (int n = 0; n < TNUM; n++) {
		tire2Mat[n] = tire2RotMatY[n] * tire2TransMat[n] * enemy.CH.Base.Mat;
	}
	radX = 0;
}
Tire2::~Tire2() {

}
bool Tire2::TiUpdate(void) {
	D3DXMATRIX tmp;
	radX += 20;
	if (radX > 360.0f)radX -= 360.0f;
	D3DXMatrixRotationX(&tmp, D3DXToRadian(radX));
	for (int n = 0; n < TNUM; n++) {
		tire2RotMatX[n] = tmp;
		tire2Mat[n] = tire2RotMatY[n]* tire2RotMatX[n] * tire2TransMat[n] * enemy.CH.Base.Mat;
	}

	return true;
}
bool Tire2::UpdateTiM()
{
	for (int n = 0; n < TNUM; n++) {
		tire2Mat[n] = tire2RotMatY[n] * tire2RotMatX[n] * tire2TransMat[n] * enemy.CH.Base.Mat;
	}
	return true;
}
void Tire2::TiDraw(void) {
	for (int i = 0; i < TNUM; i++) {
		lpD3DDevice->SetTransform(D3DTS_WORLD, &tire2Mat[i]);
		DrawMesh(&tire2Mesh);
	}
}
