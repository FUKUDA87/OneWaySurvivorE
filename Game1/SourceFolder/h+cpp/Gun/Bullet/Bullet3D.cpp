#include "Bullet3D.h"
#include"../../GameSource/XfileManager.h"
#include"../../GameSource/Judgment.h"

extern Judg judg;
extern XfileManager xfileManager;
extern LPDIRECT3DDEVICE9		lpD3DDevice;	// Direct3DDeviceインターフェイス

void DrawMesh(XFILE *XFile);

C_Bullet3D::C_Bullet3D()
{
	Init();
}

C_Bullet3D::C_Bullet3D(const D3DXMATRIX *GunMat)
{
	Init();
	BulletMesh.Base.Mat = *GunMat;
	//x軸計算
	judg.InitRotX(&BulletMesh.Base.Mat, &BulletMesh.Base.RotX);
	BulletMesh.Base.Mat = BulletMesh.Base.RotX*BulletMesh.Base.Mat;

}

C_Bullet3D::~C_Bullet3D()
{
}

void C_Bullet3D::Init()
{
	//メッシュの読み込み
	xfileManager.GetXfile(&BulletMesh.Mesh, "../GameFolder/Material/XFile/Bullet1-3.x");
	//位置の初期化
	D3DXMatrixTranslation(&BulletMesh.Base.Mat, 0.0f, 0.0f, 0.0f);
	//弾の時間の初期化
	NowCount = 0;
	MaxCount = 1 * 60/2;
	//拡大行列の初期化
	BulletMesh.Base.ScaPos = D3DXVECTOR3(0.15f, 0.15f, 0.15f);
	judg.ScalingMat(&BulletMesh.Base.Scal, &BulletMesh.Base.ScaPos);

	IncFlg = false;

	int Big = 40, Small = -20;
	Big = Big - Small;
	yUp = 0.065f+ (float)(rand() % Big + Small) / 1000.0f;
}

bool C_Bullet3D::Update(void)
{
	NowCount += 1;
	if (NowCount > MaxCount) {
		NowCount = MaxCount;
		return false;
	}
	return true;
}

bool C_Bullet3D::Update(const D3DXVECTOR3 * MoveVec)
{
	if (IncFlg == true) {
		judg.VecMatIn(&BulletMesh.Base.Mat, *MoveVec);
	}
	else {
		IncFlg = true;
	}

	//弾の横移動
	D3DXMATRIX Tmp;
	D3DXMatrixTranslation(&Tmp, 0.07f, 0.0f, 0.0f);
	BulletMesh.Base.Mat = Tmp * BulletMesh.Base.Mat;

	//弾のジャンプ処理
	BulletMesh.Base.Mat._42 += yUp;
	yUp -= 0.01f;
	return Update();
}

void C_Bullet3D::Draw3D(void)
{
	lpD3DDevice->SetTransform(D3DTS_WORLD, &GetMat());
	DrawMesh(&BulletMesh.Mesh);
}
