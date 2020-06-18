#include "CarBulletManager.h"
#include"../Draw/Bullet/Bullet_DrawManager.h"

C_CarBulletManager::C_CarBulletManager()
{
	
}

C_CarBulletManager::~C_CarBulletManager()
{
	AllDelete();

	Delete_All_Effect();

	
}

bool C_CarBulletManager::Update_ALL_Bullet(void)
{
	MoveVec_Bullet();
	Init_Bullet();
	Update_Bullet();

	return true;
}

void C_CarBulletManager::AllDelete(void)
{
	if (Get_BulletNum() < 1) return;

	for (unsigned int b = 0; b < Get_BulletNum(); b++) {
		Delete_Bullet(&b);
	}
}

void C_CarBulletManager::Delete_Bullet(unsigned int * NowBulletNo)
{
	if (Bullet_NoJudg(NowBulletNo) != true)return;

	unsigned int No = *NowBulletNo;

	delete M_Bullet[No];
	M_Bullet.erase(M_Bullet.begin() + No);
	No--;

	*NowBulletNo = No;


}

bool C_CarBulletManager::Bullet_NoJudg(const unsigned int * NowBulletNo)
{
	if (Get_BulletNum() < 1) return false;
	unsigned int No = *NowBulletNo;
	if (No < 0)return false;
	if (No >= Get_BulletNum())return false;

	return true;
}

D3DXMATRIX C_CarBulletManager::Get_Bullet_Mat(const unsigned int * BulletNo)
{
	return M_Bullet[*BulletNo]->Get_BASE3D().Mat;
}

void C_CarBulletManager::Init_Bullet(void)
{
	if (M_Gun.size() < 1)return;

	C_Bullet_DrawManager Bullet_Manager;

	for (unsigned int g = 0; g < M_Gun.size(); g++) {
		M_Gun[g]->Init_Departure_Num();
		for (unsigned int i = 0; i < M_Gun[g]->Get_CategoryNum(); i++) {
			if (M_Gun[g]->Get_TriggerFlg(&i) == true) {
				int b = M_Gun[g]->Get_BulletNo();
				D3DXMATRIX Mat = M_Gun[g]->Get_GunMouth_Mat(&i);

				M_Bullet.push_back(Bullet_Manager.Get_Bullet(&b, &Mat));
				M_Gun[g]->Bullet_Shot_Update(&i);
				M_Effect.push_back(M_Gun[g]->Get_Bullet_Shot_Effect(&i));
			}
		}
	}
}

bool C_CarBulletManager::Update_Bullet(void)
{
	if (M_Bullet.size() < 1)return false;

	for (unsigned int b = 0; b < M_Bullet.size();b++) {
		if (M_Bullet[b]->Move() != true) {
			delete M_Bullet[b];
			M_Bullet.erase(M_Bullet.begin() + b);
			b--;
		}
	}

	return true;
}

void C_CarBulletManager::Draw_Bullet(const D3DXVECTOR3 * CameraPos)
{
	if (M_Bullet.size() < 1)return ;

	for (auto && b : M_Bullet) {
		b->Draw(CameraPos);
	}
}

void C_CarBulletManager::MoveVec_Bullet(void)
{
	if (M_Bullet.size() < 1)return;

	for (auto && b : M_Bullet) {
		b->MoveVec(&brj.MoveVec);
	}
}

bool C_CarBulletManager::Get_Bullet_GroWal_Judg_Flg(const unsigned int * BulletNo)
{
	return M_Bullet[*BulletNo]->Get_GroWal_Judg_Flg();
}

void C_CarBulletManager::Set_Bullet_GroWal_Judg_Flg(const unsigned int * BulletNo, const bool * Flg)
{
	M_Bullet[*BulletNo]->Set_GroWal_Jufg_Flg(Flg);
}

void C_CarBulletManager::Delete_All_Effect(void)
{
	if (M_Effect.size() < 1)return;

	for (unsigned int e = 0; e < M_Effect.size(); e++) {
		delete M_Effect[e];
		M_Effect.erase(M_Effect.begin() + e);
		e--;
	}
}

void C_CarBulletManager::Draw_Effect(const D3DXVECTOR3 * CameraPos)
{
	if (M_Effect.size() < 1)return;

	for (auto && e : M_Effect) {
		e->Draw(CameraPos);
	}
}

void C_CarBulletManager::Set_MoveVec_Effect(const D3DXVECTOR3 * MoveVec)
{
	if (M_Effect.size() < 1)return;

	for (auto && e : M_Effect) {
		e->Set_MoveVec(MoveVec);
	}
}

bool C_CarBulletManager::Update_Effect(void)
{
	if (M_Effect.size() < 1)return false;

	for (unsigned int e = 0; e < M_Effect.size(); e++) {
		if (M_Effect[e]->Update() != true) {
			delete M_Effect[e];
			M_Effect.erase(M_Effect.begin() + e);
			e--;
		}
	}

	return true;
}
