#pragma once
#include<d3dx9.h>
#include"../../../GameSource/Struct.h"
#include"../../../GameSource/Judgment.h"
#include"../../../Enemy/Data/Const/PhaseConst.h"
#include"../../../Move/GunMove/Auto/Departure_Gun_Auto_Base.h"

class C_GunMoveBase_A {
public:
	virtual C_GunMoveBase_A* Update(S_GUN_DATA *s_Data, const S_GUN_UPDATE_DATA* s_Update,CHARABASE *Chara) = 0;
protected:
	//�v���C���[�����삵�Ă��邩�̃Z�b�g
	void Set_PlayerFlg(S_GUN_DATA *s_Data, const bool *Flg) {
		s_Data->PlayerFlg = *Flg;
	}

	//�����e�����n��
	C_Departure_Gun_Auto_Base* Get_Departure(const S_BULLET_DEPAR *Data);
private:

};