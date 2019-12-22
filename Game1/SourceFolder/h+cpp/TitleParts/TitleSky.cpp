#include "TitleSky.h"
#include"../GameSource/XfileManager.h"

extern XfileManager xfileManager;

StageSky::StageSky()
{
	xfileManager.GetXfile(&sky.Mesh, "../GameFolder/Material/XFile/garezi1.x");
	D3DXVECTOR3 Pos(4, 3, 4);
	D3DXMatrixScaling(&sky.Base.Scal, Pos.x, Pos.y, Pos.z);
}
