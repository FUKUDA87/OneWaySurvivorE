#pragma once
#include"EnemyBase.h"
#include"Data/Base&Manager/EnemySpeed.h"
#include"Data/Const/PhaseConst.h"
#include"Data/Base&Manager/EnemyAiPhaseBase.h"

class C_EnemyAi :public C_EnemyBase {
public:
	C_EnemyAi();
	~C_EnemyAi();
	//�v�l
	bool UpdateAi(const CHARAData *cd,const int *Data_Num,const bool *End_Flg);
	//�A�b�v�f�[�g
	bool UpdateAll(std::vector<C_Ground_Object*>ground);

	void SetParts(std::vector<C_Ground_Object*>ground);

	void SetPlaEnd(bool Flg);
	//Ai�̋N��
	bool StartAi(const unsigned int *GNo);

	bool GetDeadFlg(void) {
		return DeadFlg;
	}
	void SetDeadFlg(const bool Flg) {
		DeadFlg = Flg;
	}

protected:
	//�X�s�[�h�̏�����
	void InitSpeedMove(C_Speed_Update* Initspeed);

	C_E_AiPhaseBase *m_Ai;
private:


	//------------------------
	//�X�s�[�h�Ǘ�
	C_Speed_Update *speed;
	float SpeedMul;
	int NowCount, MaxCount;
	//------------------------

	bool DeadFlg;
};