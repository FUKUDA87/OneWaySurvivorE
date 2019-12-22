#include "GunE.h"
#include"../GameSource/XfileManager.h"
#include"../GameSource/Judgment.h"


extern Judg judg;
extern XfileManager xfileManager;
extern LPDIRECT3DDEVICE9 lpD3DDevice;

void DrawMesh(XFILE *XFile);

void GunE::InitGun()
{
	gunEA = new GunEA(stand.Base.Mat);
	bat = false;
	batF = false;
	//bul = new EBulletManager(100);
	laserMan = new LaserManager();
	laserMan->LaserCha(gunEA->GetLaser());
	lFlg = false;
	lDis = 0.0f;
	fAnim = 0.0f;

	D3DXVECTOR3 Pos;
	Pos = gunEA->GetPos();
	D3DXMatrixTranslation(&gun.Base.Trans, Pos.x, Pos.y, Pos.z);
	gun.Base.AngX = 0.0f;
	gun.Base.AngY = 0.0f;
	D3DXMatrixRotationX(&gun.Base.RotX, D3DXToRadian((float)gun.Base.AngX));
	D3DXMatrixRotationY(&gun.Base.RotY, D3DXToRadian((float)gun.Base.AngY));
	gun.Base.Mat = gun.Base.RotX*gun.Base.RotY*gun.Base.Trans * stand.Base.Mat;
	gunEA->Update(gun.Base.Mat);
}

bool GunE::GunUpdate()
{
	//移動行列
	if ((enemy.CH.Con.Speed < 0) || (enemy.CH.Con.Speed > 0)) {
		batF = false;
	}
	else {
		batF = true;
	}
	D3DXVECTOR3 Pos;
	Pos = gunEA->GetPos();
	D3DXMATRIX Trans;
	D3DXMatrixTranslation(&Trans, Pos.x, Pos.y, Pos.z);
	StartMat = Trans * stand.Base.Mat;
	if(batF==true){
		//銃をplayerに向ける処理
		D3DXVECTOR3 FrontVec(0.0f, 0.0f, 1.0f);
		judg.TarEndMat(&EndMat, StartMat, &gun.Base.RotX, &gun.Base.RotY, targetPos, FrontVec);
		bat = true;
	}
	else {
		EndMat = gun.Base.RotX*(gun.Base.RotY*StartMat);
	}
	judg.Quaternion(&gun.Base.Mat, StartMat, EndMat, &fAnim, 0.05f, bat);
	gunEA->Update(gun.Base.Mat);
	
	//レーザー
	D3DXMATRIX tmp;
	D3DXMatrixTranslation(&tmp, 0.1f, 0.15f, 0.2f);
	laserMan->UpdateS(gun.Base.Mat, tmp);

	return true;
}

bool GunE::GunVec()
{
	
	return true;
}

void GunE::GunDraw()
{
	gunEA->Draw3D();
	//laserMan->Draw3D();
}

bool GunE::UpdateB()
{
	static bool b=false;
	if (key.ZKeyF() == true) {
		if (b == false) {
			b = true;
		}
		else {
			b = false;
		}
	}
	if (b == true) {
		bat = false;
	}
	if (enemy.CH.Base.Flg == false) {
		bat = false;
	}
	D3DXVECTOR3 Vec = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//bul->UpdateBME(Vec,gunEA->GetBullet(), &bat);
	return true;
}

void GunE::DrawB()
{
	//bul->DrawBM();
}

bool GunE::UpdateAll()
{
	if (enemy.CH.Base.Flg == true) {
		EneUpdate();
		TiUpdate();
		StaUpdate();
		GunUpdate();
	}
	UpdateB();
	return true;
}

void GunE::DrawAll()
{
	EneDraw();
	TiDraw();
	if (enemy.CH.Base.Flg == true) {
		StaDraw();
		GunDraw();
	}
	DrawB();
	return;
}

bool GunE::LaserUpdate()
{
	laserMan->UpdateL(lDis, lFlg);
	return true;
}

bool GunE::UpdateEnd()
{
	VectorUpdate();
	LaserUpdate();
	return true;
}

bool GunE::GetFlgEA(void)
{
	if (GetFlgE() == true) {
		return true;
	}
	else {
		if (bul->GetBulSize() > 0) {
			return true;
		}
	}
	return false;
}

void GunE::SetLasDis(float Dis, bool b)
{
	lDis = Dis;
	lFlg = b;
}
