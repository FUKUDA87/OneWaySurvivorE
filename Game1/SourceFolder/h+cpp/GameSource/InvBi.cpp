#include "InvBi.h"

bool Inv::GetInvRotateMat(D3DXVECTOR3 camPos, D3DXVECTOR3 camLook, D3DXVECTOR3 camHead)
{
	caPos = camPos;
	D3DXMatrixIdentity(&Inv);
	D3DXMatrixLookAtLH(&Inv, &camPos, &camLook, &camHead);
	D3DXMatrixInverse(&Inv, NULL, &Inv);
	return true;
}
