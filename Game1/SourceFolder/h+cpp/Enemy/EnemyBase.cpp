#include "EnemyBase.h"

C_EnemyBase::C_EnemyBase()
{
	InitEnemy();
}

C_EnemyBase::~C_EnemyBase()
{
	//矢印の削除
	delete Vect;

}

void C_EnemyBase::InitEnemy(void)
{
	int MaxHp = 50;// rand() % 10 + 45;
	SetHp(&MaxHp);
	Car.Con.DFlg = false;
	//前進用のクォータニオンの初期化
	Car.Con.SpeedMulJudg = 1.0f;

	//矢印の初期化
	Vect = new Vector();

	M_DriverNo = co_EnemyCar;
}

bool C_EnemyBase::UpdateCar(void)
{
	D3DXVECTOR3 pos, vec;
	judg.SetPosM(&pos, Car.Base.Mat);
	vec = D3DXVECTOR3(0.0f, 1.5f, 0.0f);
	CHARABASE c=GetCharaBase();
	
	return true;
}

void C_EnemyBase::Draw3DAll(const D3DXVECTOR3 * CamPos)
{

	Draw3DCar();
	Draw_Car_Parts(CamPos);

	Draw_Gun(CamPos);
	if (Car.Base.Flg == true) {
		//ボス以外なら表示
		if (BodyData.CarBodyNo < 200) {
			CHARABASE c = GetCharaBase();
			Hp_Draw3D(CamPos, &Car.Base.Mat, 1.5f*Car.Base.ScaPos.y);
		}
	}
	Draw_Bullet(CamPos);
	Draw_Effect(CamPos);
}

void C_EnemyBase::Draw2DAll(void)
{
	if (Car.Base.Flg == true) {
		Vect->Draw(Car.Base.Flg);
		Hp_Draw2D();
	}
}

void C_EnemyBase::GetPos2DSet(const D3DXMATRIX *mProj, const D3DXMATRIX *mView, const D3DVIEWPORT9 *Viewport)
{
	judg.Pos2Dpvv(*mProj, *mView, *Viewport);
	D3DXMATRIX Pmat = judg.SetMatP(M_S_Gun_Update_Data.TargetPos);
	Pos2D = judg.Pos2DPE(Car.Base.Mat, Pmat);//矢印Pos作成
	Vect->Update(Pos2D, Car.Base.Mat);
}

bool C_EnemyBase::GetDeleFlg(void)
{
	if (Car.Base.Flg == true)return true;
	//if (BulletE.size() > 0)return true;
	return false;
}

void C_EnemyBase::SetParts(std::vector<C_Ground_Object*> ground)
{
	
}

void C_EnemyBase::UpdateBullet(void)
{
	//UpdateBME(brj.MoveVec, gunEA->GetBullet(), &gun.BulletFlg,0);
}
