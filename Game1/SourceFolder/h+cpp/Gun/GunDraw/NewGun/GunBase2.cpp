#include "GunBase2.h"
#include"../../../Draw3DBase/Draw3DManager/GunMeshManager.h"

extern LPDIRECT3DDEVICE9 lpD3DDevice;
void DrawMesh(XFILE *XFile);

C_GunBase2::C_GunBase2(const GUNINITDATA * GunInitDataS)
{
	Init_Gun(GunInitDataS);
}

C_GunBase2::~C_GunBase2()
{
	if (m_Move != nullptr) {
		delete m_Move;
	}
}

void C_GunBase2::Init_Gun(const GUNINITDATA * GunInitDataS)
{
	//表示の変更
	Gun.DrawNo = GunInitDataS->DrawNo;
	SetMeshGun(Gun.DrawNo.GunNo);
	//表示設定
	Gun.Base=judg.InitGunParts(&GunInitDataS->InitGun);

	SetCharaBase(&GunInitDataS->CharaBase);

}

void C_GunBase2::Draw3D_Gun()
{
	if (Gun.Base.DrawFlg != true)return;

	if (Gun.Mesh.lpMesh == nullptr)return;

	lpD3DDevice->SetTransform(D3DTS_WORLD, &GetDrawMatGun());
	DrawMesh(&Gun.Mesh);
}

bool C_GunBase2::Update()
{
	if (GetDamageFlg() == true) {
		Gun.Base.DrawFlg = true;
	}
	if (Dead() == true) {
		Gun.Base.DrawFlg = false;
	}
	return true;
}

bool C_GunBase2::Update_Gun(const D3DXMATRIX *Mat,int *NowPhase)
{
	Update();
	s_Data.StandMat = *Mat;
	C_E_GunMoveBase* m;
	s_Data.Hp = GetCharaBase();
	while (true)
	{
		m = m_Move->Move(&s_Data, NowPhase);
		if (m != nullptr) {
			delete m_Move;
			m_Move = m;
		}

		//弾を打つ時を早める
		if (s_Data.LockonEndFlg == false)break;
		if (s_Data.LockonEndFlg == true)s_Data.LockonEndFlg = false;
	}
	Gun.Base.Mat = s_Data.NowRot.RotXMat*(s_Data.NowRot.RotYMat*(s_Data.TransMat*s_Data.StandMat));
	SetCharaBase(&s_Data.Hp);
	return true;
}

//bool C_GunBase2::Update_Gun(const D3DXMATRIX * Mat, int * NowPhase, const D3DXVECTOR3 * CamPos)
//{
//	Update_Gun(Mat, NowPhase);
//	return true;
//}

void C_GunBase2::SetMeshGun(int MeshNo)
{
	//メッシュの切り替え
	C_GunMeshManager l_GunMeshManager;
	Gun.Mesh = l_GunMeshManager.GetMesh(MeshNo);
}
