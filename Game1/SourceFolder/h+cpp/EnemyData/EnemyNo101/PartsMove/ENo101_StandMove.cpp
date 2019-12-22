#include "ENo101_StandMove.h"

C_PartsMoveBase * C_ENo101_StandMove::Move(PARTS * Parts, const D3DXMATRIX * Mat, const int * Speed, const int * MaxSpeed, int * NowPhase)
{
	Parts->Base.Mat = Parts->Base.Trans**Mat;
	Parts->MeshDrawFlg = 0;
	return nullptr;
}
