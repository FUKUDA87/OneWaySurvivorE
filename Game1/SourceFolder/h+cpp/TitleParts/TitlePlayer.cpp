#include "TitlePlayer.h"

void TitlePlayer::Init()
{
	for (int i = 0; i < TNUM; i++) {
		tire[i].MoveFlg = false;
	}
}

void TitlePlayer::Draw()
{
	lpD3DDevice->SetTransform(D3DTS_WORLD, &player.Base.Mat);
	DrawMesh(&player.Mesh);
}

bool TitlePlayer::SuperUpdate(float AngX, float AngY, std::vector<BillBase*> ground)
{
	motion.Formove(player.Con, &player.Base.Mat, &Move.AnimeFrame, ground, &FMove.qGFlg, &FMove.qFlg, &player.Con.SpeedMul, player.Con.SpeedMulJudg, &Move.StartMat, &Move.EndMat, &qVec, &FMove.cFlg, &cVec, 0.5f);
	TUpdate();
	SUpdate();
	GUpdate();
	return true;
}

void TitlePlayer::SuperDraw()
{
	Draw();
	TDraw();
	SDraw();
	GDraw();
}
