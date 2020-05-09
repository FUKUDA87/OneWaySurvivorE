#include "E_101_Phase_0.h"
#include"ENo101_AiPhase_1.h"
/*
�t�F�[�Y�O�F����
Speed���ŏ���̈ʒu�ɒ����ƃt�F�[�Y�P
�t�F�[�Y�P�F�e(1)�̉�]
�e(1)��Hp���O�ɂȂ�ƃt�F�[�Y�Q
�t�F�[�Y�Q�F�h�A�̃I�[�v���A�e(�Q)�̉�]�A�{��HP����true
�{��Hp���U�U���ȉ��ɂȂ�΃t�F�[�Y�R
�t�F�[�Y�R�F�t�F�[�Y�P�Ɠ���
�t�F�[�Y�S�Ŗ{��Hp��33���ȉ��ɂȂ�΃t�F�[�Y�T
�t�F�[�Y6�Ŗ{��Hp��0�ɂȂ�΃t�F�[�Y�V

*/

C_E_No101_Phase_0::C_E_No101_Phase_0()
{
	InitFlg = true;
}

C_E_AiPhaseBase * C_E_No101_Phase_0::Action(const CHARABASE * Chara,
	std::vector<C_Car_Parts_Joint*> M_Car_Parts, std::vector<C_GunLaser*> M_Gun,
	S_GUN_UPDATE_DATA * s_Update, const unsigned int * GroNo, const unsigned int * Traget_GroNo)
{
	if (InitFlg == true) {
		InitFlg = false;
		s_Update->NowPhase = 0;
	}

	if (*GroNo > *Traget_GroNo-2)return new C_E_No101_AiPhase_1();

	return nullptr;
}
