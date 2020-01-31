#include "Enemy_No1_Gun_1_Lockon.h"
#include"Enemy_No1_Gun_1_Shot.h"
#include"Ene_1_Gun_1_Stop.h"

C_Enemy_No1_Gun_1_Lockon::C_Enemy_No1_Gun_1_Lockon()
{
	InitFlg = true;
	RayCount=RayCountMax = 20;
	InitFlg2 = true;
}

C_GunMoveBase_A * C_Enemy_No1_Gun_1_Lockon::Update(S_GUN_DATA * s_Data, const S_GUN_UPDATE_DATA * s_Update, CHARABASE *Chara)
{
	s_Data->BulletFlg = false;

	if (s_Update->NowPhase <= Phase0)return Get_Move(s_Data, &s_Update->StandMat);

	if(Chara->NowHp<=0)return Get_Move(s_Data, &s_Update->StandMat,new C_Ene_1_Gun_1_Stop());

	//if(s_Data->MoveFlg!=true)

	Init_Init(s_Data);

	s_Data->Ray_Judg_Flg = true;

	if(Ray_Judg(s_Data)!=true)return Get_Move(s_Data, &s_Update->StandMat, new C_Enemy_No1_Gun_1_Shot());

	Init(s_Data, s_Update);

	//if (s_Data->RayJudgFlg != true)return nullptr;

	D3DXMATRIX StartMat, EndMat, NowMat, TmpMat;
	TmpMat = s_Update->StandMat;
	StartMat = Start.RotXMat*(Start.RotYMat*TmpMat);
	EndMat = End.RotXMat*(End.RotYMat*TmpMat);

	Judg judg;

	//回転
	if (judg.Quaternion(&NowMat, StartMat, EndMat, &NowAnime, FrameAnime, true) == false) {
		//if (s_Data->RayHitFlg != true) {
			InitFlg = true;
		//}
	}

	D3DXVECTOR3 Pos;
	D3DXVec3TransformCoord(&Pos, &D3DXVECTOR3(0.0f, 0.0f, 1.0f), &NowMat);

	judg.TarEndMat(&NowMat, TmpMat, &s_Data->NowRot.RotXMat, &s_Data->NowRot.RotYMat, Pos, D3DXVECTOR3(0.0f, 0.0f, 1.0f));

	return Get_Move(s_Data, &s_Update->StandMat);
}

void C_Enemy_No1_Gun_1_Lockon::Init(S_GUN_DATA * s_Data,const S_GUN_UPDATE_DATA * s_Update)
{
	if (InitFlg != true)return;

	InitFlg = false;

	//回転の初期化

	Start.RotXMat = s_Data->NowRot.RotXMat;
	Start.RotYMat = s_Data->NowRot.RotYMat;

	D3DXMATRIX TmpMat;
	TmpMat = s_Update->StandMat;

	Judg judg;

	judg.TarEndMat(&TmpMat, TmpMat, &End.RotXMat, &End.RotYMat, s_Update->TargetPos, D3DXVECTOR3(0.0f, 0.0f, 1.0f));

	NowAnime = 0.0f;
	FrameAnime = 0.05f;
}

void C_Enemy_No1_Gun_1_Lockon::Init_Init(S_GUN_DATA * s_Data)
{
	if (InitFlg2 != true)return;

	InitFlg2 = false;

	s_Data->RayDis = 30;
}

void C_Enemy_No1_Gun_1_Lockon::End_Move(S_GUN_DATA * s_Data)
{
	s_Data->Ray_Judg_Flg = false;
}

bool C_Enemy_No1_Gun_1_Lockon::Ray_Judg(S_GUN_DATA * s_Data)
{
	if (s_Data->Ray_Hit_Flg != true) return true;

	RayCount--;

	if (RayCount > 0) return true;

	RayCount = 0;


	if (InitFlg != true)return true;

	return false;
}
