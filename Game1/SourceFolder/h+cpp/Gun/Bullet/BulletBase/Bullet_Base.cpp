#include "Bullet_Base.h"
#include"../../../Data/Bullet/Bullet_Data_Base/BulletData_Manager.h"
#include"../../../GameSource/Judgment.h"

C_Bullet_Base::C_Bullet_Base(const int * BulletNo, const D3DXMATRIX *Mat)
{
	//s—ñ‚Ì‰Šú‰»
	Set_Mat(Mat);
	//•\¦‚Ì‰Šú‰»
	Init_Draw(BulletNo);

	Init();
}

C_Bullet_Base::C_Bullet_Base(const int * BulletNo, const D3DXMATRIX * Mat, const S_RAY_HIT_JUDG_DATA * RayData)
{
	//s—ñ‚Ì‰Šú‰»
	Set_Mat(Mat);

	//’e‚ğŒX‚¯‚éˆ—
	RayPos_Bullet(RayData);

	//•\¦‚Ì‰Šú‰»
	Init_Draw(BulletNo);

	Init();
}

C_Bullet_Base::~C_Bullet_Base()
{
	M_Draw_Delete_All();
}

void C_Bullet_Base::Draw(const D3DXVECTOR3 * CameraPos)
{
	if (M_Draw.size() < 1)return;

	for (auto && b:M_Draw) {
		b->Draw3D(CameraPos);
	}
}

void C_Bullet_Base::MoveVec(const D3DXVECTOR3 * MoveVec)
{
	if (M_Draw.size() < 1)return;

	Judg judg;

	judg.VecMatIn(&M_Base.Mat, *MoveVec);

	for (auto && b : M_Draw) {
		b->Set_MoveVec(MoveVec);
	}
}

void C_Bullet_Base::Set_S_BULLET(const int * BulletTypeNo)
{

}

void C_Bullet_Base::Set_Mat(const D3DXMATRIX * Mat)
{
	M_Base.Mat = *Mat;
}

bool C_Bullet_Base::Move(void)
{
	if (M_Count->Update_Count() != true)return false;

	D3DXMATRIX TmpMat;
	D3DXMatrixTranslation(&TmpMat, 0.0f, 0.0f, M_S_Bullet.Speed);

	M_Base.Mat = TmpMat * M_Base.Mat;

	if (M_Draw.size() < 1)return true;

	for (auto && b : M_Draw) {
		b->Set_Mat(&M_Base.Mat);
	}

	return true;
}

void C_Bullet_Base::Delete_Count(void)
{
	if (M_Count == nullptr)return;

	delete M_Count;
}

void C_Bullet_Base::Init_S_Bullet(void)
{
	M_S_Bullet.Damage = 1;
	M_S_Bullet.Speed = 1.0f;
}

void C_Bullet_Base::M_Draw_Delete_All(void)
{
	if (M_Draw.size() < 1)return;

	for (unsigned int b = 0; b < M_Draw.size(); b++) {
		delete M_Draw[b];
		M_Draw.erase(M_Draw.begin() + b);
		b--;
	}

}

void C_Bullet_Base::Init_Draw(const int * BulletNo)
{
	C_BulletData_Manager Manager;
	C_BulletData_Base *Data;
	Data=Manager.Get_Data(BulletNo);

	M_S_Bullet = Data->Get_Data().BULLET;

	if (Data->Get_DrawNum() < 1)return;

	for (int b = 0; b < Data->Get_DrawNum(); b++) {
		M_Draw.push_back(Data->Get_Draw(&b,&M_Base.Mat));
	}

}

void C_Bullet_Base::RayPos_Bullet(const S_RAY_HIT_JUDG_DATA * RayData)
{
	if (RayData->Flg != true)return;

	Judg judg;

	//’e‚ªÆ€‚Ì•û‚ÉŒü‚©‚¤ˆ—
	double Ang, ang = 0.0f;
	D3DXMATRIX RotMat;
	judg.CroDot(M_Base.Mat, &RotMat, judg.SetPosM(RayData->Mat), D3DXVECTOR3(0.0f, 0.0f, 1.0f), &Ang, ang, false);
	M_Base.Mat = RotMat* M_Base.Mat;
}

void C_Bullet_Base::Init(void)
{
	M_GroWal_Judg_Flg = true;

	int t = 600;
	M_Count = new C_Count(&t);
}
