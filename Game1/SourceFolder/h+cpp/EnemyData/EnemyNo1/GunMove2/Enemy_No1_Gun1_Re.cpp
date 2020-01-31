#include "Enemy_No1_Gun1_Re.h"
#include"Enemy_No1_Gun_1_Lockon.h"
#include"Ene_1_Gun_1_Stop.h"

C_Enemy_No1_Gun_1_Re::C_Enemy_No1_Gun_1_Re()
{
	Count = 60*5;
}

C_GunMoveBase_A * C_Enemy_No1_Gun_1_Re::Update(S_GUN_DATA * s_Data, const S_GUN_UPDATE_DATA * s_Update, CHARABASE *Chara)
{
	s_Data->BulletFlg = false;

	if (Chara->NowHp <= 0)return Get_Move(s_Data, &s_Update->StandMat, new C_Ene_1_Gun_1_Stop());

	Count--;
	if (s_Data->RateFlg != false)return Get_Move(s_Data, &s_Update->StandMat);

	if(Count<=0)return Get_Move(s_Data, &s_Update->StandMat,new C_Enemy_No1_Gun_1_Lockon());

	return Get_Move(s_Data, &s_Update->StandMat);
}
