#pragma once
#include"../../Base&Manager/Enemy_Gun_Move_Base.h"

class C_Enemy_No1_Gun_1_Lockon:public C_Enemy_Gun_Move_Base {
public:
	C_Enemy_No1_Gun_1_Lockon();
	C_GunMoveBase_A* Update(S_GUN_DATA *s_Data, const S_GUN_UPDATE_DATA* s_Update, CHARABASE *Chara);
protected:
	bool InitFlg,InitFlg2;//������Flg
	QUAMAT Start, End;//��]�s��
	float NowAnime, FrameAnime;//��]���x
	int RayCount, RayCountMax;//���C�̓���������

	void Init(S_GUN_DATA * s_Data,const S_GUN_UPDATE_DATA* s_Update);

	//������
	void Init_Init(S_GUN_DATA* s_Data);

	//�I������
	void End_Move(S_GUN_DATA *s_Data);

	//���C����̔���
	bool Ray_Judg(S_GUN_DATA *s_Data);
private:

};