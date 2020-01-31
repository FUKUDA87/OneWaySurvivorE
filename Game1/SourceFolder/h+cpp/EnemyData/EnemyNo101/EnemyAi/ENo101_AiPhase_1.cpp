#include "ENo101_AiPhase_1.h"
#include"../../../Const/Const_PartsTypeNo.h"
/*
�t�F�[�Y�O�F����
Speed���ŏ���̈ʒu�ɒ����ƃt�F�[�Y�P
�t�F�[�Y�P�F�e(1)�̉�]
�e(1)��Hp���O�ɂȂ�ƃt�F�[�Y�Q
�t�F�[�Y�Q�F�h�A�̃I�[�v���A�e(�Q)�̉�]�A�{��HP����true
�{��Hp���U�U���ȉ��ɂȂ�΃t�F�[�Y�R
�t�F�[�Y�R�F�t�F�[�Y�P�Ɠ���
�t�F�[�Y�S�Ŗ{��Hp��33���ȉ��ɂȂ�΃t�F�[�Y�T
�t�F�[�Y6�Ŗ{��Hp��0���ȉ��ɂȂ�΃t�F�[�Y�V

*/

C_E_No101_AiPhase_1::C_E_No101_AiPhase_1()
{
	InitFlg = true;
}

C_E_AiPhaseBase * C_E_No101_AiPhase_1::Action(const CHARABASE *Chara, std::vector<C_Car_Parts_Joint*>M_Car_Parts, std::vector<C_GunLaser*>M_Gun, S_GUN_UPDATE_DATA* s_Update, const unsigned int *GroNo, const unsigned int *Traget_GroNo)
{
	s_Update->NowPhase = 1;

	if (M_Gun.size() > 0) {
		bool L_Flg = true;
		M_Gun[0]->Update_Trigger(&L_Flg);
	}

	if (M_Car_Parts.size() > 0) {
		for (unsigned int p = 0; p < M_Car_Parts.size(); p++) {
			if (M_Car_Parts[p]->Get_Parts_Data().MeshTypeNo == Co_Parts_Door) {
				M_Car_Parts[p]->Set_I_MoveFlg(2);
			}
		}
	}


	/*float Hp=(float)Chara->NowHp, MaxHp = (float)Chara->MaxHp;
	float S = Hp / MaxHp;
	if (S < 0.67f) {
		if (S < 0.34f) {
			if (Chara->NowHp <= 0) {
				*NewPhase = Phase7;
				return nullptr;
			}
			else {
				if (*NewPhase == Phase4)*NewPhase = Phase5;
				return nullptr;
			}
		}
		else {
			if (*NewPhase == Phase2)*NewPhase = Phase3;
			return nullptr;
		}
	}*/
	return nullptr;
}
