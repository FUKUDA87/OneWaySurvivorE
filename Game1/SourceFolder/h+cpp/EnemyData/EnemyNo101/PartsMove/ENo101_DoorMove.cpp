#include "ENo101_DoorMove.h"

//C_ENo101_DoorMove::C_ENo101_DoorMove(const bool SetReverseFlg)
//{
//	if (SetReverseFlg == false) {
//		AngY = 160.0f;
//	}
//	else {
//		AngY = -160.0f;
//	}
//	D3DXMatrixRotationY(&StartMat, D3DXToRadian(0.0f));
//	D3DXMatrixRotationY(&EndMat, D3DXToRadian(AngY));
//	NowAnime = 0.0f;
//	AnimeFrame=0.04f;
//}
//
//C_PartsMoveBase * C_ENo101_DoorMove::Move(PARTS * Parts, const D3DXMATRIX * Mat, const int * Speed, const int * MaxSpeed, int * NowPhase)
//{
//
//	float l_AnimeFrame=AnimeFrame;
//	if ((*NowPhase % 2 == 1)||(*NowPhase==Phase0)) {
//		l_AnimeFrame *= -1.0f;
//	}
//	D3DXMATRIX NowMat;
//	judg.Quaternion(&NowMat, StartMat, EndMat, &NowAnime, l_AnimeFrame, true);
//
//	Parts->Base.Mat = NowMat * Parts->Base.Trans*(*Mat);
//
//	return nullptr;
//}
