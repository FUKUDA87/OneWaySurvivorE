#include "StageCamera.h"

StageCam::StageCam()
{
	camAngY = -90.0f;
	camAngX = -10.0f;
	sizeZ = 3.5f;
	upY = 0.4f;
}

bool StageCam::Update(D3DXMATRIX mat, D3DXMATRIX tmp, bool MouFlg)
{
	D3DXMATRIX cMat;
	cMat = tmp * mat;
	judg.SetPosM(&camLook, cMat);
	D3DXMATRIX RotMat;
	if (MouFlg == true) {
		camAngY += upY;
	}
	D3DXMatrixRotationYawPitchRoll(&RotMat, D3DXToRadian(camAngY), D3DXToRadian(camAngX), 0.0f);
	D3DXVec3TransformCoord(&camPos, &D3DXVECTOR3(0.0f, 0.0f, sizeZ), &RotMat);
	camPos += camLook;
	return true;
}
