#include"Stand1.h"
#include"../GameSource/XfileManager.h"

extern XfileManager xfileManager;
extern LPDIRECT3DDEVICE9 lpD3DDevice;

void DrawMesh(XFILE *XFile);

Stand1::Stand1() {
	y = 0.75f;
	z = -0.2f;//-0.4
	xfileManager.GetXfile(&standMesh, "../GameFolder/Material/XFile/stand1.x");
	D3DXMatrixTranslation(&standMat, player.Base.Mat._41, player.Base.Mat._42+y, player.Base.Mat._43+z);
}
Stand1::~Stand1() {
	
}
bool Stand1::SUpdate(void) {
	//D3DXMatrixTranslation(&standMat, player.Base.Mat._41, player.Base.Mat._42 + y, player.Base.Mat._43+z);
	D3DXMATRIX tmp;
	D3DXMatrixTranslation(&tmp,0.0f, y,z);
	standMat = tmp * player.Base.Mat;

	return true;
}
void Stand1::SDraw(void) {
	lpD3DDevice->SetTransform(D3DTS_WORLD, &standMat);
	DrawMesh(&standMesh);
}