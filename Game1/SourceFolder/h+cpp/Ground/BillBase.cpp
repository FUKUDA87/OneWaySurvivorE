#include"BillBase.h"
#include"../GameSource/XfileManager.h"

extern LPDIRECT3DDEVICE9 lpD3DDevice;
extern XfileManager xfileManager;

void DrawMesh(XFILE *XFile);

void BillBase::InitBB()
{
	xfileManager.GetXfile(&bill.Mesh, "../GameFolder/Material/XFile/BillBase1A1.x");
	obj = true;
	//}
	float f = 200.0f;
	bill.Base.ScaPos=D3DXVECTOR3(f, f+1.0f, f);
	D3DXMatrixScaling(&bill.Base.Scal, bill.Base.ScaPos.x, bill.Base.ScaPos.y, bill.Base.ScaPos.z);
	bill.Base.AttRad = 30.0f;
	D3DXMatrixTranslation(&bill.Base.Trans, -(bill.Base.AttRad), 8.0f, 0.0f);
	//bill.Base.Mat = bill.Base.Trans*Wall3D[0].Base.Mat;
	//建物の表示Flg確認
	bill.Base.DrawFlg = true;

	/*ground.Base.DrawFlg = WallDrawFlg = bill.Base.DrawFlg = true;*/
}

BillBase::BillBase() {
	InitBB();
}
BillBase::~BillBase() {

}
bool BillBase::UpdateBil(void) {
	bool LeftFlg=true;
	bill.Base.Mat = bill.Base.Trans*GetWaMat(&LeftFlg,0);
	return true;
}
void BillBase::DrawBil(void) {
	//表示確認
	if (bill.Base.DrawFlg == true) {
		//建物の表示
		lpD3DDevice->SetRenderState(D3DRS_NORMALIZENORMALS, TRUE);
		D3DXMATRIX tmp;
		tmp = bill.Base.Scal*bill.Base.Mat;
		lpD3DDevice->SetTransform(D3DTS_WORLD, &tmp);
		DrawMesh(&bill.Mesh);
		lpD3DDevice->SetRenderState(D3DRS_NORMALIZENORMALS, FALSE);
	}
}