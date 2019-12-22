#include "GunDataNo2.h"

C_GunDataNo2::C_GunDataNo2()
{
	SetInitGun();
}

void C_GunDataNo2::SetInitGun(void)
{
	InitGun(1);
	int No = 0;
	if(SetGunMouthPos(&No, &D3DXVECTOR3(0.0f, 0.03f, 0.75f))==false)return;
	No++;
}
