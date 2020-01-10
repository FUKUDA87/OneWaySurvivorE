#include "PlayerBase.h"

C_PlayerBase::C_PlayerBase()
{
	InitPlayer();
}

C_PlayerBase::~C_PlayerBase()
{
	//セーブtxt
	if (fopen_s(&fp, "../GameFolder/Data/playerDate.txt", "w") == 0) {
		fprintf_s(fp, "%d", Car.Sta.CharaBase.MaxHp);
		fclose(fp);
	}
}

void C_PlayerBase::InitPlayer(void)
{
	//必須初期化-------------------------------------------------------------------------------
	//HPの初期化
	//ロードtxt
	if (fopen_s(&fp, "../GameFolder/Data/playerDate.txt", "r") == 0) {
		fscanf_s(fp, "%d", &Car.Sta.CharaBase.MaxHp);
		fclose(fp);
	}
	SetHp(&Car.Sta.CharaBase.MaxHp);

	Car.Base.AttRad = 1.0f / 2.0f;
	//スピードの初期化
	Car.Con.NowSpeed = 80;
	Car.Con.MaxSpeed = 150;
	Car.Con.Speed = D3DXVECTOR3(0.0f, 0.0f, (float)Car.Con.NowSpeed/100.0f);//0.8f

	Car.Con.CurFlg = false;
	RadField = 1000.0f*0.55f;
	Car.Con.GroNum = 0;
	//ball = new Ball(player.Base.BodRad);//(player.Base.rad);
	hp = new HpD();
	Car.Con.PEFlg = false;

	/*D3DXMATRIX spS, spE;
	D3DXMatrixTranslation(&spS, 0.0f, 0.0f, 1.1f);
	D3DXMatrixTranslation(&spE, 0.0f, 0.0f, -1.1f);*/
	/*spear = new Spear(spS, spE);
	vector = new Vector();*/

	//カーブ
	CurAng = 0.0f;

}

bool C_PlayerBase::UpdatePlayer(void)
{
	CHARABASE c = GetCharaBase();
	hp->UpdateAll(c.MaxHp, c.NowHp, true);
	return true;
}

bool C_PlayerBase::UpdateAll(void)
{
	return false;
}

bool C_PlayerBase::UpdateAll(const D3DXMATRIX * CamMat)
{
	UpdatePlayer();
	if (Car.Base.Flg == true) {
		//移動ベクトル計算
		judg.MatMatVec(&brj.MoveVec, PlaMovMat, Car.Base.Mat);
		UpdateCar();

		//無敵のアップデート
		UpdateCountM();

		//銃のくっつく行列探し
		D3DXMATRIX GunMat= GetMatCar();
		//標準パーツのアップデート
		if (Parts.size() > 0) {
			for (unsigned int p = 0; p < Parts.size(); p++) {
				Parts[p]->SetSpeed(&Car.Con.NowSpeed, &Car.Con.MaxSpeed);
				Parts[p]->UpdateParts(&GetMatCar());
				//銃のくっつき判定
				if (Parts[p]->GetParts().GunFlg >0) {
					GunMat = Parts[p]->GetParts().Base.Mat;
				}
			}
		}

		//銃のアップデート
		D3DXMATRIX Tmp;
		D3DXMatrixTranslation(&Tmp,0.0f, 0.0f, 0.0f);
		ConnectGunMat = Tmp * GunMat;
		UpdateGun(CamMat);
	}
	if (Dead()==true) {
		if (Car.Base.Flg == true) {
			Car.Base.Flg = false;
		}
		return false;
	}
	return true;
}

bool C_PlayerBase::UpdateEndAll(void)
{
	return false;
}

bool C_PlayerBase::UpdateDeadAll(void)
{
	return false;
}

void C_PlayerBase::Draw3DAll(void)
{
	Draw3DCar();
	if (Car.Base.Flg == true) {
		if (Parts.size() > 0) {
			for (unsigned int p = 0; p < Parts.size(); p++) {
				Parts[p]->Draw3DParts();
			}
		}
		Draw3DGun();
	}
}

void C_PlayerBase::Draw2DAll(void)
{
	hp->DrawAll();
}

void C_PlayerBase::SetRodAngY(float Inc, bool KeyFlg)
{
	float MaxInc, SmallInc;
	if (Inc < 0.0f) {
		MaxInc = Inc * -1.0f;
		SmallInc = Inc;
	}
	else {
		MaxInc = Inc;
		SmallInc = Inc * -1.0f;
	}
	if (KeyFlg == true) {
		CurAng += Inc;
		float Over = 10.0f;
		if (CurAng < -Over)CurAng = -Over;
		if (CurAng > Over)CurAng = Over;
	}
	else {
		if (CurAng < 0.0f) {
			if (CurAng < SmallInc) {
				CurAng += MaxInc;
			}
			else {
				CurAng = 0.0f;
			}
		}
		else {
			if (CurAng > MaxInc) {
				CurAng -= MaxInc;
			}
			else {
				CurAng = 0.0f;
			}
		}
	}
}

void C_PlayerBase::SetCurRotMat(void)
{
	D3DXMatrixRotationY(&CurRotMatY, D3DXToRadian(CurAng));
	Car.Base.Mat = CurRotMatY * Car.Base.Mat;
}

bool C_PlayerBase::UpdateBulPla(const bool * KeyFlg, const bool * BirthFlg, const SoundCamera * sc)
{
	//弾を撃つと音とKey
	UpdateBullet(&brj, KeyFlg, BirthFlg, sc);
	return true;
}
