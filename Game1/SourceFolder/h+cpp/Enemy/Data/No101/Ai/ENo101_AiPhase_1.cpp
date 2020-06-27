#include "ENo101_AiPhase_1.h"
#include"Ene_101_Pha_2.h"
#include"Ene_101_Pha_3.h"
#include"Enemy101_Phase5.h"
#include"Enemy101_Phase7.h"

C_E_No101_AiPhase_1::C_E_No101_AiPhase_1()
{
	InitFlg = true;
}

C_E_AiPhaseBase * C_E_No101_AiPhase_1::Action(const CHARABASE *Chara,
	std::vector<C_Car_Parts_Joint*>M_Car_Parts, std::vector<C_GunLaser*>M_Gun,
	S_GUN_UPDATE_DATA* s_Update, const unsigned int *GroNo, const unsigned int *Traget_GroNo)
{
	//������
	if (InitFlg == true) {
		InitFlg = false;

		s_Update->NowPhase = 1;

		//�e�̏�����
		if (M_Gun.size() > 0) {
			M_Gun[0]->Init_Hp(20,&Co_Damage_Yes);
		}

		//�ԓ��̏e�̏�����
		if (M_Gun.size() > 1) {
			M_Gun[1]->Init_Hp(0, &Co_Damage_No);
		}

		//�_���[�W���󂯂镔���̃_���[�W����̖�����
		for (auto && p : M_Car_Parts) {
			if ((p->Get_Parts_Data().MeshTypeNo == Co_Parts_Judg) && (p->Get_Parts_Data().MeshJointNo == 1))p->Init_Hp(1, &Co_Damage_No);
			if ((p->Get_Parts_Data().MeshTypeNo == Co_Parts_Judg) && (p->Get_Parts_Data().MeshJointNo == 2))p->SetDamageFlg(&Co_Damage_No);
		}
	}

	//����̏e�̈���������
	if (M_Gun.size() > 0) {
		bool L_Flg = true;
		M_Gun[0]->Update_Trigger(&L_Flg);
	}

	//�Ԃ̂Ƃт瑀��
	if (M_Car_Parts.size() > 0) {
		for (unsigned int p = 0; p < M_Car_Parts.size(); p++) {
			if (M_Car_Parts[p]->Get_Parts_Data().MeshTypeNo == Co_Parts_Door) {
				M_Car_Parts[p]->Set_I_MoveFlg(2);
			}
		}
	}

	//�����̊����Ńt�F�[�Y�ω�
	float Hp=(float)Chara->NowHp, MaxHp = (float)Chara->MaxHp;
	float S = Hp / MaxHp;
	if (S < 0.67f) {
		if (S < 0.34f) {
			if (Chara->NowHp <= 0) {
				return new C_EnemyNo101_Phase7();
			}
			else {
				return new C_EnemyNo101_Phase5();
			}
		}
		else {
			return new C_EnemyNo101_Phase3();
		}
	}

	//�e�����񂾎��Ɏ��̃t�F�[�Y�ֈړ�
	if (M_Gun[0]->Dead() == true)return new C_Enemy_No101_Phase_2();


	return nullptr;
}
