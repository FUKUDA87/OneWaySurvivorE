#include "ENo101_GNo1_Attack.h"
#include"ENo101_GNo1_Shoot.h"
#include"ENo101_GNo1_NoMove.h"

C_ENo101_GNo1_Attack::C_ENo101_GNo1_Attack(S_ENEMYGUNDATA * s_Data)
{
	*s_Data = InitData();
	Init();
}

C_ENo101_GNo1_Attack::C_ENo101_GNo1_Attack()
{
	Init();
}

C_E_GunMoveBase * C_ENo101_GNo1_Attack::Move(S_ENEMYGUNDATA * s_Data, int * NowPhase)
{
	if (*NowPhase < Phase2)return nullptr;

	InitRot(s_Data);

	if (ChangePhase(s_Data, NowPhase) == true) {
		InitRayFlg(s_Data);
		return new C_ENo101_GNo1_NoMove();
	}

	if (s_Data->RayJudgFlg != true)return nullptr;

	if (Ray(s_Data) != true) {
		InitRayFlg(s_Data);
		s_Data->LockonEndFlg = true;
		return new C_ENo101_GNo1_Shoot();
	}

	D3DXMATRIX StartMat, EndMat, NowMat, TmpMat;
	TmpMat = s_Data->TransMat*s_Data->StandMat;
	StartMat = Start.RotXMat*(Start.RotYMat*TmpMat);
	EndMat = End.RotXMat*(End.RotYMat*TmpMat);

	//‰ñ“]
	if (judg.Quaternion(&NowMat, StartMat, EndMat, &NowAnime, FrameAnime, true) == false) {
		if (s_Data->RayHitFlg != true) {
			InitFlg = true;
		}
	}
	D3DXVECTOR3 Pos;
	D3DXVec3TransformCoord(&Pos, &D3DXVECTOR3(0.0f, 0.0f, 1.0f), &NowMat);

	judg.TarEndMat(&NowMat, TmpMat, &s_Data->NowRot.RotXMat, &s_Data->NowRot.RotYMat, Pos, D3DXVECTOR3(0.0f, 0.0f, 1.0f));
	return nullptr;
}

void C_ENo101_GNo1_Attack::InitRot(S_ENEMYGUNDATA * s_Data)
{
	if (InitFlg != true) return;

	Start.RotXMat = s_Data->NowRot.RotXMat;
	Start.RotYMat = s_Data->NowRot.RotYMat;

	D3DXMATRIX TmpMat;
	TmpMat = s_Data->TransMat*s_Data->StandMat;


	judg.TarEndMat(&TmpMat, TmpMat, &End.RotXMat, &End.RotYMat, s_Data->TargetPos, D3DXVECTOR3(0.0f, 0.0f, 1.0f));

	NowAnime = 0.0f;
	FrameAnime = 0.05f;

	InitFlg = false;

	s_Data->RayJudgFlg = true;

	return;
}

S_ENEMYGUNDATA C_ENo101_GNo1_Attack::InitData(void)
{
	S_ENEMYGUNDATA Data;
	Data.DrawNo = judg.GetInitGUNDRAWNOS(GunNo2, BulletNo101, 1, 1);
	Data.Gun = judg.InitSetPartsData(0.0f, 180.0f, 0.0f, &D3DXVECTOR3(0.0f, 0.1f, 0.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), true);
	Data.Gun.TransPos = judg.GetVecVec(&Data.Gun.TransPos, &Data.Gun.ScalPos);
	Data.Hp.NowHp = Data.Hp.MaxHp = 0;
	Data.Hp.DamageSetFlg = true;
	D3DXMatrixRotationX(&Data.NowRot.RotXMat, D3DXToRadian(Data.Gun.AngX));
	D3DXMatrixRotationY(&Data.NowRot.RotYMat, D3DXToRadian(Data.Gun.AngY));
	judg.SetTransMat(&Data.TransMat, &Data.Gun.TransPos);
	Data.RayJudgFlg = false;
	Data.RayHitFlg = false;
	Data.RayDis = 50.0f;
	Data.LockonEndFlg = false;
	return Data;
}

void C_ENo101_GNo1_Attack::Init(void)
{
	InitFlg = true;
	RayCount = RayCountMax = 20;
}

bool C_ENo101_GNo1_Attack::Ray(S_ENEMYGUNDATA * s_Data)
{
	if (s_Data->RayHitFlg == true) {
		RayCount--;
		if (RayCount <= 0) {
			s_Data->RayJudgFlg = false;
			return false;
		}
	}
	else {
		RayCount++;
		if (RayCount > RayCountMax)RayCount = RayCountMax;
	}

	return true;
}
