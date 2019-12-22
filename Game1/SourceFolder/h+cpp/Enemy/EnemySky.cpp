#include "EnemySky.h"
#include"../GameSource/XfileManager.h"

extern XfileManager xfileManager;

C_EnemySky::C_EnemySky(D3DXMATRIX GroundMat, float * TransX):MoveE(GroundMat,TransX)
{
	InitESky();
}

void C_EnemySky::InitESky(void)
{
	SkyType = true;
	CarFM.BodyHeight = 5.0f;
	xfileManager.GetXfile(&enemy.CH.Mesh, "../GameFolder/Material/XFile/AirPlane.x");
}
