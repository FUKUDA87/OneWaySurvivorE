#include"player.h"
#include"../GameSource/XfileManager.h"
#include"../GameSource/option.h"
#include"../GameSource/Enum.h"
#include"../GameSource/Judgment.h"
#include"../Key/Key.h"

extern Key key;
extern Judg judg;
extern LPDIRECT3DDEVICE9 lpD3DDevice;
extern XfileManager xfileManager;
extern Option option;

void DrawMesh(XFILE *XFile,bool *DFlg);

void C_Player::Init()
{
	//ロードtxt
	/*if (fopen_s(&fp, "../GameFolder/Data/playerDate.txt", "r") == 0) {
		fscanf_s(fp, "%d", &player.Sta.MaxHp);
		fclose(fp);
	}*/
	xfileManager.GetXfile(&player.Mesh, "../GameFolder/Material/XFile/car1.x");
	xfileManager.GetXfile(&player.Con.ColModMesh, "../GameFolder/Material/XFile/PlayerCar1CM3.x");
	D3DXMatrixTranslation(&player.Base.Mat, 0, 0.5f, 0);
	D3DXMatrixTranslation(&player.Base.Trans, 0, 0.0f, 0);
	player.Base.AttRad = 1.0f/2.0f;
	//player.Base.BodRad = 1.25f;
	//player.Sta.NowHp =player.Sta.MaxHp;
	player.Con.Speed = D3DXVECTOR3(0.0f,0.0f,0.8f);//0.8f
	player.Con.CurFlg = false;
	radF = 1000.0f*0.6f;
	player.Con.GroNum = 0;
	player.Base.BodRad=judg.GetRad(&player.Con.ColModMesh, &player.Base.NumVertex,&player.Con.PosBig,&player.Con.PosSmall);
	ball = new Ball(player.Base.BodRad);//(player.Base.rad);
	hp = new HpD();
	player.Con.PEFlg = false;
	player.Base.Flg = true;
	DFlg = false;

	D3DXMATRIX spS, spE;
	D3DXMatrixTranslation(&spS, 0.0f, 0.0f, 1.1f);
	D3DXMatrixTranslation(&spE, 0.0f, 0.0f, -1.1f);
	spear = new Spear(spS, spE);
	vector= new Vector();

	//クォータニオンの初期化
	Move.AnimeFrame = 0.0f;
	cur.MoveFlg = false;
	cur.ReverseFlg = false;
	FMove.qFlg = false;
	FMove.qGFlg = false;
	FMove.cFlg = false;
	player.Con.SpeedMulJudg = 1.0f;

	//カーブ
	CurAng = 0.0f;
}

C_Player::C_Player() {
	Init();
}
C_Player::~C_Player() {
	delete ball;
	delete hp;
	delete spear;
	delete vector;
	//セーブtxt
	/*if (fopen_s(&fp, "../GameFolder/Data/playerDate.txt", "w") == 0) {
		fprintf_s(fp, "%d", player.Sta.MaxHp);
		fclose(fp);
	}*/
}

bool C_Player::Update(void) {
	ball->Update(player.Base.Mat);
	//hp->UpdateAll(player.Sta.MaxHp, player.Sta.NowHp,true);
	spear->Update(player.Base.Mat,false);
	return true;
}

bool C_Player::SuperUpdate(float AngX, float AngY, std::vector<BillBase*>ground)
{
	Update();
	return true;
}

void C_Player::Draw(void) {
	lpD3DDevice->SetTransform(D3DTS_WORLD, &player.Base.Mat);
	DrawMesh(&player.Mesh,&DFlg);
	//spear->Draw3D();
	/*D3DXMATRIX Tmp;
	D3DXMatrixRotationX(&Tmp, D3DXToRadian(180.0f));
	spear->Draw3D(Tmp*player.Base.Mat);*/
	//ball->Draw();
}
void C_Player::Draw2()
{
	hp->DrawAll();
	vector->Draw(false);
}
void C_Player::SuperDraw()
{
	Draw();
}
D3DXMATRIX C_Player::GetMat(void) {
	return player.Base.Mat;
}
void C_Player::SetMat(D3DXMATRIX mat) {
	player.Base.Mat = mat;
}
float C_Player::GetRad(void) {
	return player.Base.AttRad;
}

void C_Player::SetHP(int Damage)
{
	/*int NowHp = player.Sta.NowHp;
	player.Sta.NowHp -= Damage;
	if (player.Sta.NowHp <= 0)player.Sta.NowHp = 0;
	if (player.Sta.NowHp < NowHp)DFlg = true;*/
}

void C_Player::SetHP(int * Hp)
{
	//player.Sta.NowHp = *Hp;
}

void C_Player::CurReverse(bool b)
{
	/*if (b == true) {
			if (player.Con.CurFlg == true) {
				if (curMoveFlg == true) {
					curMoveFlg = false;
				}
				else {
					curMoveFlg = true;
				}
				cur.Reverse = -1.0f;
				cur.FrameUp *= cur.Reverse;
				if (player.Con.NextRail != player.Con.NowRail) {
					player.Con.NextRail = player.Con.NowRail;
				}
			}
		}*/
}

CHARAData C_Player::GetData(void)
{
	CHARAData c;
	c.NowMat = player.Base.Mat;
	c.Rad = player.Base.AttRad;
	c.CurFlg = player.Con.CurFlg;
	c.NowGround = player.Con.GroNum;
	c.DrawFlg = player.Base.Flg;
	c.Mesh = player.Mesh.lpMesh;
	//c.Speed = player.Con.Speed;
	return c;
}

void C_Player::SetRodAngY(float Inc, bool KeyFlg)
{
	float MaxInc, SmallInc;
	if (Inc < 0.0f) {
		MaxInc = Inc * -1.0f;
		SmallInc = Inc;
	}
	else {
		MaxInc = Inc ;
		SmallInc = Inc * -1.0f;
	}
	if (KeyFlg == true) {
		CurAng += Inc;
		if (CurAng < -15.0f)CurAng = -15.0f;
		if (CurAng > 15.0f)CurAng = 15.0f;
	}
	else {
		if (CurAng < 0.0f) {
			if (CurAng < SmallInc) {
				CurAng+= MaxInc;
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

void C_Player::SetCurRotMat(void)
{
	D3DXMatrixRotationY(&CurRotMatY, D3DXToRadian(CurAng));
	player.Base.Mat = CurRotMatY * player.Base.Mat;
}
