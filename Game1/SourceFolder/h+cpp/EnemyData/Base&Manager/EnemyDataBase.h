#pragma once
#include<d3dx9.h>
#include"../../GameSource/Struct.h"
#include"EnemyDataNoConst.h"
#include"EnemyGunMoveBase.h"
#include"EnemySpeed.h"
#include"../Base&Manager/PartsMoveBase.h"
#include"../../Draw3DBase/Draw3DManager/TireMeshManager.h"
#include"../../Draw3DBase/Draw3DManager/StandMeshManager.h"
#include"../../Draw3DBase/Draw3DManager/PartsMeshManager.h"
#include"EnemyAiPhaseBase.h"
#include"../../Gun/GunDraw/NewGun/GunLaser.h"

class C_EnemyDataBase {
public:
	C_EnemyDataBase();

	//�ԏ��n���ƌ���
	virtual S_ENEMYBODYDATA GetBodyData(void) = 0;
	//�W���p�[�c���n���ƌ���
	virtual C_PartsMoveBase* GetPartsData(const int *PartsNo) = 0;
	//�W���p�[�c���n���ƌ���
	virtual XFILE GetPartsMesh(const int *PartsNo) = 0;
	//�e�̏��n���ƌ���
	virtual C_E_GunMoveBase* GetGunData(const int *GunNo,S_ENEMYGUNDATA *s_Data) = 0;
	//�Ԉړ��n��
	virtual Speed* GetSpeed(void) = 0;
	//Ai�n��
	virtual C_E_AiPhaseBase* GetAiPhase(void) = 0;
	//�e��
	int Get_GunNum(void) {
		return GunNum;
	}
	//�e�̕\���n��
	virtual C_GunLaser*Get_Gun(const int *EnemyGunNo)=0;
protected:
	int GunNum;
private:

};