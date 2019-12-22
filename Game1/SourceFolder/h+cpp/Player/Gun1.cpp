#include"Gun1.h"
#include"../GameSource/XfileManager.h"
#include"../Gun/GunDraw/GunPA.h"
#include"../Key/Key.h"
#include"../GameSource/Motion.h"

extern Motion motion;
extern Key key;
extern XfileManager xfileManager;
extern LPDIRECT3DDEVICE9 lpD3DDevice;
extern D3DXMATRIX MatD;

void DrawMesh(XFILE *XFile);

void Gun1::Init()
{
	//bulletM = new BulletManager();
	gunBase = new GunPA(standMat);
	B = false;
	//SpeB = new float[5];
	Count = 0;
}

Gun1::Gun1() {
	Init();
}
Gun1::~Gun1() {
	//delete bulletM;
	delete gunBase;
	//delete[] SpeB;
}
bool Gun1::GUpdate(float AngX, float AngY) {
	gunBase->Update(AngX, AngY, standMat);
	return true;
}
bool Gun1::GUpdate(const D3DXMATRIX * CamMat)
{
	gunBase->Update(CamMat, standMat);
	return true;
}
bool Gun1::GUpdate(void)
{
	gunBase->Update(standMat);
	return true;
}
bool Gun1::GUpdateB(void)
{
	UpdateBM(bVec, gunBase->GetBullet(Pos, B), gunBase->GetMuzFla(),&gunBase->GetGMat());
	return true;
}
bool Gun1::GUpdateB(const bool * BirthFlg)
{
	UpdateBM(BirthFlg,bVec, gunBase->GetBullet(Pos, B), gunBase->GetMuzFla(), &gunBase->GetGMat());
	return true;
}
bool Gun1::GUpdateB(const bool * BirthFlg, const SoundCamera * sc)
{
	UpdateBM(BirthFlg, bVec, gunBase->GetBullet(Pos, B), gunBase->GetMuzFla(), &gunBase->GetGMat(),sc);
	return true;
}
bool Gun1::GUpdateB(const bool * KeyFlg, const bool * BirthFlg, const SoundCamera * sc)
{
	UpdateBM(KeyFlg,BirthFlg, bVec, gunBase->GetBullet(Pos, B), gunBase->GetMuzFla(), &gunBase->GetGMat(), sc);
	return true;
}
bool Gun1::GUpdateBEnd(void)
{
	UpdateBM();
	return true;
}
bool Gun1::MoveUpdate(std::vector<BillBase*> ground)
{
	if (player.Base.Flg == true) {
		PlaMovMat = player.Base.Mat;
		//前進処理
		Move.NowMat = player.Base.Mat;
		motion.Formove(player.Con, &Move.NowMat, &Move.AnimeFrame, ground, &FMove.qGFlg, &FMove.qFlg, &player.Con.SpeedMul,player.Con.SpeedMulJudg, &Move.StartMat, &Move.EndMat, &qVec, &FMove.cFlg, &cVec,0.5f);
	//車体の方向を得るためにMatを入れる
		player.Con.JudgMat = Move.NowMat;
		//===========================================
		//車線変更
		//===========================================
		////左の車線に変更
		//if ((key.AKey() == true)) {
		//	D3DXMATRIX Trans;
		//	D3DXMatrixTranslation(&Trans, -1.0f*0.1f, 0.0f, 0.0f);
		//	player.Base.Trans = Trans * player.Base.Trans;
		//	bool curFlg = cur.MoveFlg;//前の状態を記録
		//	cur.MoveFlg = true;
		//}
		//else {
		//	bool curFlg = cur.MoveFlg;//前の状態を記録
		//	cur.MoveFlg = false;
		//	//前と後の比較
		//	if ((curFlg == true) && (cur.MoveFlg = false)) {
		//		cur.MoveEndFlg = true;
		//	}
		//}
		////右の車線に変更
		//if (key.DKey() == true) {
		//	D3DXMATRIX Trans;
		//	D3DXMatrixTranslation(&Trans, 1.0f*0.1f, 0.0f, 0.0f);
		//	player.Base.Trans = Trans * player.Base.Trans;
		//	cur.MoveFlg = true;
		//}
		//else {
		//	bool curFlg = cur.MoveFlg;//前の状態を記録
		//	cur.MoveFlg = false;
		//	//前と後の比較
		//	if ((curFlg == true) && (cur.MoveFlg = false)) {
		//		cur.MoveEndFlg = true;
		//	}
		//}
		//車線変更回転
		//if ((cur.MoveFlg == true) || (cur.MoveEndFlg == true)) {
		//	if (cur.MoveEndFlg == false) {
		//		if (motion.CurveMove(&player.Base.Trans, cur.StartMat, cur.RotY, cur.EndMat, &cur.AnimeFrame, 0.03f, &cur.ReverseFlg) == false) {//移動
		//			cur.MoveEndFlg = true;
		//			cur.MoveFlg = false;
		//			player.Con.NowRail = player.Con.NextRail;
		//		}
		//	}
		//	player.Base.Mat = player.Base.Trans*player.Base.Mat;
		//}
		player.Base.Mat = player.Base.Trans*Move.NowMat;

	}
	return true;
}
bool Gun1::SuperUpdate(float AngX, float AngY)
{
	if (player.Base.Flg == true) {
		//移動ベクトル計算
		judg.MatMatVec(&bVec, PlaMovMat, player.Base.Mat);
		Update();
		TUpdate();
		SUpdate();
		GUpdate(AngX, AngY);
	}
	/*if (player.Sta.NowHp <= 0) {
		if (player.Base.Flg == true) {
			player.Base.Flg = false;
		}
		return false;
	}*/
	return true;
}
bool Gun1::SetParts(float AngX, float AngY)
{
	if (player.Base.Flg == true) {
		//移動ベクトル計算
		judg.MatMatVec(&bVec, PlaMovMat, player.Base.Mat);
		Update();
		TUpdate();
		SUpdate();
		GUpdate(AngX, AngY);
	}
	return true;
}
bool Gun1::SuperUpdate(const D3DXMATRIX * CamMat)
{
	if (player.Base.Flg == true) {
		//移動ベクトル計算
		judg.MatMatVec(&bVec, PlaMovMat, player.Base.Mat);
		Update();
		TUpdate();
		SUpdate();
		GUpdate(CamMat);
	}
	/*if (player.Sta.NowHp <= 0) {
		if (player.Base.Flg == true) {
			player.Base.Flg = false;
		}
		return false;
	}*/
	return true;
}
bool Gun1::SetParts(const D3DXMATRIX * CamMat)
{
	if (player.Base.Flg == true) {
		//移動ベクトル計算
		judg.MatMatVec(&bVec, PlaMovMat, player.Base.Mat);
		Update();
		TUpdate();
		SUpdate();
		GUpdate(CamMat);
	}
	return true;
}
void Gun1::GDraw(void) {
	DrawBM();
	gunBase->Draw3D();
	//spear->Draw3DV(MatD);
}
void Gun1::SuperDraw()
{
	if (player.Base.Flg == true) {
		Draw();
		TDraw();
		SDraw();
		GDraw();
	}
}
D3DXMATRIX Gun1::GetGMat(void) {
	return gunBase->GetGMat();
}

void Gun1::SetBPos(D3DXVECTOR3 pos, bool b)
{
	Pos = pos;
	B = b;
}

QuaForMove Gun1::GetQuaForMove(void)
{
	Q.AnimeFrame = Move.AnimeFrame;
	Q.BodyHeight = 0.5f;
	Q.CurFlg = FMove.cFlg;
	Q.CurVec = cVec;
	Q.EndMat = Move.EndMat;
	Q.NowMat = player.Base.Mat;
	Q.QuaInitFlg = FMove.qGFlg;
	Q.QuaMatInitFlg = FMove.qFlg;
	Q.SpeedMul = player.Con.SpeedMul;
	Q.SpeedMul2 = player.Con.SpeedMulJudg;
	Q.StartMat = Move.StartMat;
	Q.WayVec = qVec;
	return Q;
}
