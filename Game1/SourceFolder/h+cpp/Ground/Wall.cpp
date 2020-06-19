#include"Wall.h"
#include"../MaterialManager/TextureManager.h"
#include"../MaterialManager/XfileManager.h"
#include"../GameSource/Judgment.h"

extern XFileManager xfileManager;
extern LPDIRECT3DDEVICE9 lpD3DDevice;
extern TextureManager textureManager;

Wall::Wall(const int * i) : C_Ground(i)
{
	Init_Wall();
}

Wall::Wall(const D3DXMATRIX *Mat3, const D3DXMATRIX *Mat4, const S_GROUND_INIT_DATA * Init_Data_Ground)
	: C_Ground(Mat3,Mat4,Init_Data_Ground)
{
	Init_Wall();

}

#define	FVF_VERTEX (D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1)
void DrawMesh(XFILE *XFile);
void Wall::WaDraw(void) {
	//表示確

	//壁3D表示
	lpD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	for (int w = 0; w < 2; w++) {
		if (Wall3D[w].Base.DrawFlg == true) {

			lpD3DDevice->SetTransform(D3DTS_WORLD, &Get_DrawMat_Wall(&w));
			DrawMesh(&M_Wall.Mesh);
		}
	}
	lpD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}

void Wall::Init_Wall3D_All(void)
{
	for (int w = 0; w < Get_Wall_Num(); w++) {

		/*回転行列の初期化*/

		float AngY = 0.0f;

		if (w > 0)AngY = 180.0f;

		D3DXMatrixRotationY(&Wall3D[w].Base.RotY, D3DXToRadian(AngY));

		/*バウンディングスフィアの初期化*/

		judg.Get_Draw_Radius(&Wall3D[w].CullingRad,&M_Wall.PosBig, &M_Wall.PosSmall,&Wall3D[w].Base.ScaPos);
	}
}

void Wall::Init_Wall()
{
	//壁3Dの初期化
	//壁のロード
	M_Wall.Mesh=xfileManager.GetMesh("Wall3-3.x");

	//壁のコリジョンモデルのロード
	M_Wall.ColModMesh=xfileManager.GetMesh("Wall2CM1.x");

	//壁のサイズ計算
	static bool GetRadFlg = true;
	static DWORD NumVertex;
	static D3DXVECTOR3 PosSmall;
	static D3DXVECTOR3 PosBig;
	if (GetRadFlg == true) {
		judg.GetRad(&M_Wall.Mesh, &Wall3D[0].Base.NumVertex, &M_Wall.PosBig, &M_Wall.PosSmall);
		NumVertex = Wall3D[0].Base.NumVertex;
		PosSmall = M_Wall.PosSmall;
		PosBig = M_Wall.PosBig;
		GetRadFlg = false;
	}
	else {
		Wall3D[0].Base.NumVertex = NumVertex;
		M_Wall.PosSmall = PosSmall;
		M_Wall.PosBig = PosBig;
	}

	//サイズ調整
	Wall3D[0].Base.ScaPos = D3DXVECTOR3(1.0f*0.5f, 3.0f, M_Wall.PosSmall.z - M_Wall.PosBig.z);
	if (Wall3D[0].Base.ScaPos.z < 0.0f)Wall3D[0].Base.ScaPos.z *= -1.0f;

	//表示のFlgの初期化
	Wall3D[0].Base.DrawFlg = true;

	Wall3D[1] = Wall3D[0];

	Init_Wall_Mat();

	Init_Wall_Iden();

	Init_Wall3D_All();
}

void Wall::Init_Wall_Mat(void)
{
	if (IdenFlg == true)return;

	//2枚の壁の初期化
	for (int w = 0; w < 2; w++) {

		//行列の初期化
		Wall3D[w].Base.Mat = ground.Base.Mat;

		Wall3D[w].Base.TraPos = D3DXVECTOR3(ground.v[w].Pos.x, M_Wall.PosSmall.y*-1.0f, 0.0f);
		//幅の調整
		D3DXVECTOR3 Vec;
		if (w == 0) {
			//左
			Vec = ground.v[0].Pos - ground.v[3].Pos;
		}
		else {
			//右
			Vec = ground.v[1].Pos - ground.v[2].Pos;
		}

		Init_Wall_SizeZ(&Vec, &w);

		Wall3D[w].Base.TraPos.y *= Wall3D[w].Base.ScaPos.y;
		//反映
		judg.Set_TransMat(&Wall3D[w].Base.Trans, &Wall3D[w].Base.TraPos);
		//回転
		float AngY;
		if (w == 0) {
			AngY = 0.0f;
		}
		else {
			AngY = 180.0f;
		}
		D3DXMatrixRotationY(&Wall3D[w].Base.RotY, D3DXToRadian(AngY));
	}
}

void Wall::Init_Wall_Iden(void)
{
	if (IdenFlg != true)return;

	for (int w = 0; w < 2; w++) {
		//大きさの初期化
		//向き
		int s, e;
		if (w == 0) {
			s = 3;
			e = 0;
		}
		else {
			s = 2;
			e = 1;
		}
		D3DXVECTOR3 wVec = ground.v[e].Pos - ground.v[s].Pos
			, FrontVec = D3DXVECTOR3(0.0f, 0.0f, 1.0f);

		Init_Wall_SizeZ(&wVec, &w);

		//位置の代入
		D3DXVECTOR3 Pos = ground.v[s].Pos + wVec / 2.0f;
		judg.Set_TransMat(&Wall3D[w].Base.Mat, &Pos);
		//回転
		D3DXMATRIX RotX, RotY;
		judg.TarEndMat(&Wall3D[w].Base.Mat, Wall3D[w].Base.Mat, &RotX, &RotY, ground.v[e].Pos, FrontVec);
		//ｙ方向に移動させるTransMatの作成
		Pos.y = M_Wall.PosSmall.y*Wall3D[w].Base.ScaPos.y;
		if (Pos.y < 0.0f)Pos.y *= -1.0f;
		D3DXMatrixTranslation(&Wall3D[w].Base.Trans, 0.0f, Pos.y, 0.0f);

		//回転
		float AngY;
		if (w == 0) {
			AngY = 0.0f;
		}
		else {
			AngY = 180.0f;
		}
		D3DXMatrixRotationY(&Wall3D[w].Base.RotY, D3DXToRadian(AngY));

	}
}

void Wall::Init_Wall_SizeZ(const D3DXVECTOR3 * Ground_Vec, const int * Wall_No)
{
	if ((*Wall_No < 0) || (*Wall_No >= Get_Wall_Num()))return;

	int w = *Wall_No;

	Wall3D[w].Base.ScaPos.z = D3DXVec3Length(Ground_Vec) / Wall3D[w].Base.ScaPos.z;
	if (Wall3D[w].Base.ScaPos.z < 0.0f)Wall3D[w].Base.ScaPos.z *= -1.0f;
	Wall3D[w].Base.ScaPos.z += 0.02f;

	judg.ScalingMat(&Wall3D[w].Base.Scal, &Wall3D[w].Base.ScaPos);
}

void Wall::SuperDraw()
{
	Draw();
	WaDraw();
}

D3DXMATRIX Wall::Get_DrawMat_Wall(const int * Wall_Num)
{
	int w = Get_Wall_Num();
	w = judg.Judg_Data_Num2(Wall_Num, &w);

	D3DXMATRIX TmpMat= Get_Mat_Wall(&w);
	TmpMat = Wall3D[w].Base.Scal*TmpMat;
	return TmpMat;
}

D3DXMATRIX Wall::Get_Mat_Wall(const int * Wall_Num)
{
	int w = Get_Wall_Num();
	w = judg.Judg_Data_Num2(Wall_Num, &w);

	D3DXMATRIX TmpMat;
	TmpMat = Wall3D[w].Base.RotY*Wall3D[w].Base.Trans*Wall3D[w].Base.Mat;
	return TmpMat;
}

S_Base3D_2 Wall::Get_Data_Wall(const int * Wall_Num)
{
	int w = Get_Wall_Num();
	w = judg.Judg_Data_Num2(Wall_Num, &w);

	return Wall3D[w];
}

void Wall::Set_Draw_Flg_Wall(const int * Wall_Num, const bool * DrawFlg)
{
	int w = Get_Wall_Num();
	w = judg.Judg_Data_Num2(Wall_Num, &w);

	Wall3D[w].Base.DrawFlg = *DrawFlg;
}
