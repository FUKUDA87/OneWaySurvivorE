#include "CarBase.h"
#include"../GameSource/XfileManager.h"
#include"../GameSource/Motion.h"

extern XfileManager xfileManager;
extern LPDIRECT3DDEVICE9		lpD3DDevice;	// Direct3DDeviceインターフェイス
extern Motion motion;

void DrawMesh(XFILE *XFile, bool *Flg);


C_CarBase::C_CarBase()
{
	InitCar();
	Init_S_Gun_Update_Data();
}

C_CarBase::~C_CarBase()
{

}

void C_CarBase::InitCar(void)
{
	//生存のFlgの初期化
	Car.Base.Flg = true;

	//行列の初期化
	judg.InitMatPos(&Car.Base.Mat, &Car.Base.TraPos, &Car.Base.ScaPos);
	judg.Set_TransMat(&Car.Base.Trans, &Car.Base.TraPos);
	//メッシュの初期化
	SetMeshCar(1);
	//車の判定用

	//バレット情報初期化
	brj.JudgRayFlg = false;

	SkyType = false;

	//前進クォータニオンの初期化
	CarFM.AnimeFrame = 0.0f;
	CarFM.QuaInitFlg= false;
	CarFM.QuaMatInitFlg = false;
	CarFM.CurFlg = false;
	Car.Con.SpeedMulJudg = 1.0f;
	CarFM.BodyHeight = 0.5f;

	//無敵初期化
	CountMStart = 5;
	CountMNum = 0;

	//車判定
	SetDamageFlg(&Co_Damage_Yes);

	//時間の初期化
	MMove_Stop_Time = 0;
}

bool C_CarBase::UpdateCar(void)
{
	return false;
}

bool C_CarBase::UpdateCarFM(std::vector<C_Ground_Object*> ground)
{
	//前進処理
	CarFM.NowMat = Car.Base.Mat;
	motion.Formove(&Car.Con, &CarFM.NowMat, &CarFM.AnimeFrame
		, ground, &CarFM.QuaInitFlg, &CarFM.QuaMatInitFlg, &Car.Con.SpeedMul
		, Car.Con.SpeedMulJudg, &CarFM.StartMat, &CarFM.EndMat, &CarFM.WayVec, &CarFM.CurFlg, &CarFM.CurVec, CarFM.BodyHeight);
	//車体の方向を得るためにMatを入れる
	Car.Con.JudgMat = CarFM.NowMat;
	Car.Base.Mat = Car.Base.Trans*CarFM.NowMat;
	return true;
}

void C_CarBase::Draw3DCar(void)
{
	lpD3DDevice->SetTransform(D3DTS_WORLD, &GetDrawMatCar());
		DrawMesh(&Car.Mesh, &Body_DamageFlg);
	/*}
	else {
		DrawMesh(&Car.Con.DeadMesh, &Body_DamageFlg);
	}*/
}

void C_CarBase::SetParts(std::vector<C_Ground_Object*> ground)
{
}

bool C_CarBase::Dead(void)
{
	if (CharaBase.NowHp <= 0) {
		bool Flg = false;
		SetFlgCar(&Flg);
		return true;
	}
	return false;
}

bool C_CarBase::SetHP(int Damage)
{
	if (CountMNum > 0)return false;

	int NowHp = GetHp();

	if (HpDamage(&Damage) != true)return false;

	if (GetHp() < NowHp)Body_DamageFlg = true;
	//無敵の初期化
	CountMNum = CountMStart;

	return true;
}

bool C_CarBase::SetHP(int Damage, bool WallFlg)
{
	if (CountMNum > 0)return false;

	int NowHp = GetHp();
	
	if (HpDamage(&Damage) != true)return false;

	if (GetHp() < NowHp)Body_DamageFlg = true;

	if (WallFlg == false)return true;
	//無敵の初期化
	CountMNum = CountMStart;

	return true;
}

void C_CarBase::SetBPos(D3DXVECTOR3 RayPos, bool RayJudgFlg)
{
	brj.RayPos = RayPos;
	brj.JudgRayFlg = RayJudgFlg;
}

CHARAData C_CarBase::GetData(void)
{
	CHARAData c;
	c.NowMat = Car.Base.Mat;
	c.Rad = Car.Base.AttRad;
	c.CurFlg = Car.Con.CurFlg;
	c.NowGround = Car.Con.GroNum;
	c.DrawFlg = Car.Base.Flg;
	c.Mesh = Car.Mesh.lpMesh;
	c.Speed = Car.Con.NowSpeed;
	return c;
}

QuaForMove C_CarBase::GetQuaForMove(void)
{
	Q.AnimeFrame = CarFM.AnimeFrame;
	Q.BodyHeight = CarFM.BodyHeight;
	Q.CurFlg = CarFM.CurFlg;
	Q.CurVec = CarFM.CurVec;
	Q.EndMat = CarFM.EndMat;
	Q.NowMat = Car.Base.Mat;
	Q.QuaInitFlg = CarFM.QuaInitFlg;
	Q.QuaMatInitFlg = CarFM.QuaMatInitFlg;
	Q.SpeedMul = Car.Con.SpeedMul;
	Q.SpeedMul2 = Car.Con.SpeedMulJudg;
	Q.StartMat = CarFM.StartMat;
	Q.WayVec = CarFM.WayVec;
	return Q;
}

bool C_CarBase::UpdateCountM(void)
{
	CountMNum -= 1;
	if (CountMNum <= 0) {
		CountMNum = 0;
		return false;
	}
	return true;
}

void C_CarBase::Set_Move_Stop_Time(const int * Time)
{
	if (MMove_Stop_Time <= 0)return;

	MMove_Stop_Time += *Time;

	if (MMove_Stop_Time < 0)MMove_Stop_Time *= -1;
}

void C_CarBase::SetMeshCar(int MeshNo)
{
	XFILE3 X= carMeshManager.GetMesh(MeshNo);
	Car.Mesh = X.Mesh1;
	Car.Con.ColModMesh = X.Mesh2;
	Car.Con.DeadMesh = X.Mesh3;
	Car.Base.BodRad = judg.GetRad(&Car.Con.ColModMesh, &Car.Base.NumVertex, &Car.Con.PosBig, &Car.Con.PosSmall);
}

void C_CarBase::Update_Gun_Data(void)
{
	//銃の動きのDataの更新
	M_S_Gun_Update_Data.Gun_Stop_Flg = Judg_Gun_Move_Data();
}

void C_CarBase::Update_Move_Stop_Time(void)
{
	if (MMove_Stop_Time == 0)return;

	MMove_Stop_Time--;

	if (MMove_Stop_Time < 0)MMove_Stop_Time = 0;
}

void C_CarBase::Init_S_Gun_Update_Data(void)
{
	M_S_Gun_Update_Data.NowPhase = 0;
}

bool C_CarBase::Judg_Gun_Move_Data(void)
{
	if (Dead() == true)return true;

	if (Get_Move_Stop_Time() > 0)return true;

	return false;
}
