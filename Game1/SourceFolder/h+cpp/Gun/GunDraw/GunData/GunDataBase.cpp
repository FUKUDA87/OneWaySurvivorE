#include "GunDataBase.h"

C_GunDataBase::~C_GunDataBase()
{
	DeletePos();
}

int C_GunDataBase::GetGunMouthNum(void)
{
	return GunMouthNum;
}

D3DXVECTOR3 C_GunDataBase::GetGunMouthPos(const int * GunMouthNo)
{
	if(MouthPos==nullptr)return D3DXVECTOR3(0.0f,0.0f,0.0f);
	if(*GunMouthNo<0)return D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	if (*GunMouthNo >=GunMouthNum)return D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	return MouthPos[*GunMouthNo];

}

void C_GunDataBase::InitGun(const int Num)
{
	SetGunMouthNum(Num);
	SetInitGunMouthPos();
}

bool C_GunDataBase::SetGunMouthPos(const int * No, const D3DXVECTOR3 * Pos)
{
	if ((*No < 0) || (*No >= GunMouthNum))return false;

	MouthPos[*No] = *Pos;
	
	return true;
}

void C_GunDataBase::SetInitGunMouthPos(void)
{
	if (MouthPos != nullptr)DeletePos();

	if (GunMouthNum < 0)SetGunMouthNum(1);

	MouthPos = new D3DXVECTOR3[GunMouthNum];

	for (int m = 0; m < GunMouthNum; m++) {
		if (SetGunMouthPos(&m, &D3DXVECTOR3(0.0f, 0.0f, 0.0f)) == false)break;
	}
}

void C_GunDataBase::DeletePos(void)
{
	if (MouthPos != nullptr) {
		delete[] MouthPos;
	}
}

void C_GunDataBase::SetGunMouthNum(const int Num)
{
	if (Num < 0) {
		GunMouthNum = 1;
		return;
	}
	GunMouthNum = Num;

}
