#include"Enemy.h"
#include"../GameSource/XfileManager.h"
#include"../GameSource/Judgment.h"

extern LPDIRECT3DDEVICE9 lpD3DDevice;
extern XfileManager xfileManager;
extern Judg judg;

void DrawMesh(XFILE *XFile);

void Enemy::Init()
{
	xfileManager.GetXfile(&enemy.CH.Mesh, "../GameFolder/Material/XFile/EnemyCar2.x");
	xfileManager.GetXfile(&enemy.CH.Con.ColModMesh, "../GameFolder/Material/XFile/EnemyCar1CM2.x");
	xfileManager.GetXfile(&Dead, "../GameFolder/Material/XFile/EnemyCar1Dead.x");
	D3DXMatrixTranslation(&enemy.CH.Base.Mat, 0, 0, 0);
	//当たり判定用の半径
	enemy.CH.Base.AttRad = enemy.CH.Base.BodRad = judg.GetRad(&enemy.CH.Con.ColModMesh, &enemy.CH.Base.NumVertex, &enemy.CH.Con.PosBig, &enemy.CH.Con.PosSmall);
	enemy.CH.Base.Flg = true;
	//スピード管理//9.07
	enemy.EC.Size = 1000.0f;
	enemy.EC.SiFlg = false;
	//.CH.Sta.NowHp = enemy.CH.Sta.MaxHp = 50;
	enemy.CH.Con.DFlg = false;
	//前進用のクォータニオンの初期化
	enemy.CH.Con.SpeedMulJudg = 1.0f;

	vector = new Vector();
	ball = new Ball(enemy.CH.Base.AttRad);
	HpE = new HpEne();
}

Enemy::Enemy() {
	Init();
}
Enemy::Enemy(D3DXMATRIX GroundMat, float *TransX) {
	Init();
	D3DXMATRIX tmp;
	D3DXMatrixTranslation(&enemy.CH.Base.Trans, *TransX, 0.0f, 0.0f);
	D3DXMatrixTranslation(&tmp,0.0f, 0.5f, 0.0f);
	enemy.CH.Base.Mat = tmp* enemy.CH.Base.Trans*GroundMat;
	enemy.CH.Con.Speed = D3DXVECTOR3(0.0f,0.0f,1.0f);
}
Enemy::~Enemy() {
	delete ball;
	delete vector;
	delete HpE;
}
bool Enemy::EneUpdate(void) {
	ball->Update(enemy.CH.Base.Mat);
	D3DXVECTOR3 pos, vec;
	judg.SetPosM(&pos, enemy.CH.Base.Mat);
	vec = D3DXVECTOR3(0.0f, 1.5f, 0.0f);
	//HpE->Update(pos, vec,D3DXVECTOR2(0.7f,0.07f), enemy.CH.Sta.MaxHp, enemy.CH.Sta.NowHp, enemy.CH.Con.DFlg);
	
	return true;
}
void Enemy::EneDraw(void) {
	lpD3DDevice->SetTransform(D3DTS_WORLD, &enemy.CH.Base.Mat);
	DrawMesh(&enemy.CH.Mesh);
	//ball->Draw();
	if (enemy.CH.Base.Flg == true) {
		HpE->Draw();
	}
}

void Enemy::Ene2Draw()
{
	vector->Draw(true);
}

judgDeta Enemy::GetJudgDate(void)
{
	judgDeta jd;
	//jd = { enemy.CH.Base.Mat,enemy.CH.Base.AttRad,enemy.CH.Sta.NowHp,enemy.CH.Sta.MaxHp };
	return jd;
}

void Enemy::SetHp(int hp)
{
	//if (enemy.CH.Sta.NowHp > hp) {
	//	enemy.CH.Con.DFlg = true;
	//}
	//enemy.CH.Sta.NowHp = hp;
	////死んだのか確認
	//if (enemy.CH.Sta.NowHp <= 0) {
	//	enemy.CH.Base.Flg = false;
	//	enemy.CH.Mesh = Dead;
	//}
}

bool Enemy::UpdateAll()
{
	EneUpdate();
	return true;
}

bool Enemy::VectorUpdate()
{
	vector->Update(Pos2D, enemy.CH.Base.Mat);
	return true;
}

bool Enemy::UpdateEnd()
{
	VectorUpdate();
	return true;
}

bool Enemy::GetFlgE(void)
{
	return enemy.CH.Base.Flg;
}
