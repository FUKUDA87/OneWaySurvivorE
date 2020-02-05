#include "GunBullet.h"

C_GunBullet::C_GunBullet()
{
	BulletNo = 1;
}

bool C_GunBullet::Get_TriggerFlg(const unsigned int * MouthNo)
{
	if (Judg_MouthNo(MouthNo) != true)return false;

	if (M_GunParts[*MouthNo]->Get_Bullet_Shot_Flg() != true)return false;

	if (M_S_GunData.BulletFlg != true)return false;

	if (M_Category_Data[*MouthNo]->Get_Bullet_Shot_Flg() != true)return false;

	return true;
}

void C_GunBullet::Bullet_Shot_Update(const unsigned int * MouthNo)
{
	if (Judg_MouthNo(MouthNo) != true)return;

	if (M_Category_Data.size() < 1)return;

	M_S_GunData.Departure_Num++;


	for (unsigned int g = 0; g < M_GunParts.size(); g++) {
		if (M_Category_Data[*MouthNo]->Get_CategoryNo() == M_GunParts[g]->Get_M_Data().CategoryNo) {
			int i = M_GunParts[g]->Get_M_Data().Rate;
			M_Category_Data[*MouthNo]->Set_NowRate(&i);
			bool Flg = false;
			M_Category_Data[*MouthNo]->Set_TriggerFlg(&Flg);
			break;
		}
	}

	Gun_Mouth_Change();
}

bool C_GunBullet::Judg_MouthNo(const unsigned int * MouthNo)
{
	if (*MouthNo < 0)return false;
	if (*MouthNo >= M_Category_Data.size())return false;

	return true;
}
