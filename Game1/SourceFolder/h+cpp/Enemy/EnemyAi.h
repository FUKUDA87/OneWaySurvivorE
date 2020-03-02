#pragma once
#include"EnemyBase.h"
#include"../EnemyData/Base&Manager/EnemySpeed.h"
#include"../EnemyData/EnemyConst/PhaseConst.h"
#include"../EnemyData/Base&Manager/EnemyAiPhaseBase.h"

class C_EnemyAi :public C_EnemyBase {
public:
	C_EnemyAi();
	~C_EnemyAi();
	//思考
	bool UpdateAi(CHARAData cd[], unsigned int NUM, std::vector<C_Ground_Object*>ground);
	//アップデート
	bool UpdateAll(std::vector<C_Ground_Object*>ground);

	void SetParts(std::vector<C_Ground_Object*>ground);

	void SetPlaEnd(bool Flg);
	//Aiの起動
	bool StartAi(const unsigned int *GNo);

	bool GetDeadFlg(void) {
		return DeadFlg;
	}
	void SetDeadFlg(const bool Flg) {
		DeadFlg = Flg;
	}

protected:
	//スピードの初期化
	void InitSpeedMove(Speed* Initspeed);

	C_E_AiPhaseBase *m_Ai;
private:


	//------------------------
	//スピード管理
	//SpeedMove EneSpe;
	Speed *speed;
	float SpeedMul;
	int NowCount, MaxCount;
	//------------------------

	bool DeadFlg;
};