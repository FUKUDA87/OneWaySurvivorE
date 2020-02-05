#pragma once
#include<d3dx9.h>
#include"../../GameSource/Struct.h"
#include"../EnemyConst/PhaseConst.h"
#include"../../Gun/GunDraw/NewGun/GunLaser.h"
#include"../../Draw3DBase/Car_Parts_Joint.h"
#include<vector>
#include"../../Const/Const_PartsTypeNo.h"

class C_E_AiPhaseBase {
public:
	virtual C_E_AiPhaseBase* Action(const CHARABASE *Chara, std::vector<C_Car_Parts_Joint*>M_Car_Parts,std::vector<C_GunLaser*>M_Gun,S_GUN_UPDATE_DATA* s_Update,const unsigned int *GroNo,const unsigned int *Traget_GroNo) = 0;//=0:純粋仮想関数にする（必ず継承し、派生クラス側でオーバーライドしないといけない関数
protected:
	
};