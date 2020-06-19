#include "EnemyAi.h"
#include"../EnemyData/EnemyNo1/SpeedData/SpeedUp.h"

C_EnemyAi::C_EnemyAi()
{
	NowCount = MaxCount = 1;
	InitSpeedMove(new SpeedUp1());
	SpeedMul = 1.0f;

	//�X�s�[�h�̏�����
	Car.Con.NowSpeed = 80;
	Car.Con.MaxSpeed = 150;

	DeadFlg = false;
}

C_EnemyAi::~C_EnemyAi()
{
	if (speed != nullptr) {
		delete speed;
	}
	if (m_Ai != nullptr) {
		delete m_Ai;
	}
}

bool C_EnemyAi::UpdateAi(const CHARAData * cd, const int * Data_Num, std::vector<C_Ground_Object*> ground, const bool * End_Flg)
{
	if (*Data_Num <= 0) {
		return false;
	}
	if (GetHp() <= 0)Car.Base.Flg = false;

	if ((Car.Base.Flg == true) && (*End_Flg != true)) {
		if (m_Ai != nullptr) {
			C_E_AiPhaseBase *L_Ai;
			L_Ai = m_Ai->Action(&GetCharaBase(), M_Car_Parts, M_Gun, &M_S_Gun_Update_Data, &Car.Con.GroNum, &cd[0].NowGround);
			if (L_Ai != nullptr) {
				delete m_Ai;
				m_Ai = L_Ai;
			}
		}

		M_S_Gun_Update_Data.TargetPos = judg.SetPosM(&cd[0].NowMat);

		unsigned int GNo = cd[0].NowGround - 5;
		bool Flg = StartAi(&GNo);

	}

	//�X�s�[�h�Ǘ�
	C_Speed_Update *NextSpeed;

	bool CarFlg = GetFlgCar(), L_StopFlg = Get_Stop_Flg();


	NextSpeed = speed->Update(&Car.Con.NowSpeed, &CarFlg, &Car.Con.GroNum,
		&M_S_Gun_Update_Data.NowPhase, &cd[0].Speed, &cd[0].NowGround, &L_StopFlg);
	if (NextSpeed != nullptr) {
		delete speed;
		speed = NextSpeed;
	}
	Car.Con.Speed = D3DXVECTOR3(0.0f, 0.0f, (float)Car.Con.NowSpeed / 100.0f);

	return true;
}

bool C_EnemyAi::UpdateAll(std::vector<C_Ground_Object*> ground)
{
	UpdateCarFM(ground);

	return true;
}

void C_EnemyAi::SetParts(std::vector<C_Ground_Object*> ground)
{
	judg.MatMatVec(&brj.MoveVec, PlaMovMat, Car.Base.Mat);//MoveVec�쐬
	UpdateCar();
	//�W���p�[�c�̃A�b�v�f�[�g
	Update_Car_Parts();

	//�e�̏��̍X�V
	Update_Gun_Data();

	//�e�̓����̍X�V
	Update_Gun();

	if (Car.Base.Flg == true) {
		//���G�̃A�b�v�f�[�g
		UpdateCountM();
	}

	Update_Move_Stop_Time();

	UpdateCarEffect();
}



void C_EnemyAi::SetPlaEnd(bool Flg)
{
	/*if (Flg == true) {
		gun.AIFlg = false;
		gun.RayJudgFlg = false;
	}
	else {
		gun.AIFlg = true;
	}*/
}

bool C_EnemyAi::StartAi(const unsigned int * GNo)
{
	if (Car.Base.Flg != true) return false;
	//if (gun.AIFlg != false) return false;
	if (Car.Con.GroNum < *GNo) return false;
	
	//gun.AIFlg = true;
	return true;
}

void C_EnemyAi::InitSpeedMove(C_Speed_Update * Initspeed)
{
	if (speed != nullptr) {
		delete speed;
	}
	speed = Initspeed;
}

