#include "Motion.h"
#include"../GameSource/Judgment.h"

Motion::Motion()
{
	CurSize = 0.0365f;
}

void Motion::CurveFloat(float * P, const float * A, const float * B, const float * C, const float * AnimeFlame)
{
	*P = pow((1.0f - *AnimeFlame), 2.0f)*(*A) +
		2 * (1.0f - *AnimeFlame)*(*AnimeFlame)*(*B) + pow(*AnimeFlame, 2.0f)*(*C);
}

void Motion::CurvePos(D3DXVECTOR3 * Pos, const D3DXMATRIX * Start_Mat, const D3DXVECTOR3 * PosV,
	const D3DXMATRIX * End_Mat, const float * AnimeFlame)
{
	CurveFloat(&Pos->x, &Start_Mat->_41, &PosV->x, &End_Mat->_41, AnimeFlame);
	CurveFloat(&Pos->y, &Start_Mat->_42, &PosV->y, &End_Mat->_42, AnimeFlame);
	CurveFloat(&Pos->z, &Start_Mat->_43, &PosV->z, &End_Mat->_43, AnimeFlame);
}

bool Motion::Formove(QuaForMove * CarFM, const CONSTITUTION * Con, std::vector<C_Ground_Object*> ground)
{
	Judg judg;

	bool OverFlg = false;//�N�H�[�^�j�I����1.0f�𒴂����Ƃ���Flg

	bool EndFlg = false;//�N�H�[�^�j�I���I��Flg

	float VecSize, CurDrawSpeed = 1.0f;

	while (EndFlg != true) {
		//�n�ʂ̃i���o�[�Ǝ��̃i���o�[
		unsigned int GNo = Con->GroNum, NextGNo = GNo + 1;
		//AnimeFrame��1.0f�𒴂��Ă�������
		if (OverFlg == true) {
			//�n�ʂ��L���m�F
			if (ground.size() <= 0) {
				return false;
			}
			//���C���莞�̃��C�̒�������p
			float Dis;
			//�n�ʃ��C����
			bool JudgFlg = false;
			for (unsigned int g = 0; g < ground.size(); g++) {

				float L_Radius = 40.0f;
				//�����̎��͂̒n�ʂ����𔻒�
				if (judg.BallJudg(&judg.SetPosM(&CarFM->NowMat),
					&judg.SetPosM(&ground[g]->GetMat()), &L_Radius) != true) continue;
				D3DXVECTOR3 v[4];
				for (int i = 0; i < 4; i++) {
					v[i] = ground[g]->GetVer(i);
				}

				bool L_IdenFlg = ground[g]->GetIdenFlg();

				//���C����
				if (judg.RayJudg_Polygon(&judg.SetPosM(&CarFM->NowMat), &D3DXVECTOR3(0.0f, -1.0f, 0.0f),
					&ground[g]->GetMat(),&v[0], &v[1], &v[2], &v[3], &Dis, &L_IdenFlg) == true) {

					//���C�������������̏���

					GNo = g;
					NextGNo = GNo + 1;
					JudgFlg = true;
					break;

				}

			}
			//����
			if (JudgFlg == false) {
				//�������Ă��Ȃ�
				return false;
			}
		}
		//���̒n�ʂ̗L��
		if (ground.size() - 1 < (unsigned int)(NextGNo)) {
			//�����Ƃ�
			return false;
		}
		bool CurInitFlg = false, CurveFlg = true;
		//�n�ʂ̌`
		unsigned int Type = ground[GNo]->GetWay().WayType;
		//������
		if (CarFM->QuaInitFlg == false) {
			//����������
			CarFM->QuaInitFlg = true;
			//Flg = true;
			D3DXVECTOR3 Vec;
			//�J�[�u����Flg
			bool CurHeikinFlg = false;
			//�J�[�u�̑��x��������
			if ((Type == 0) && (ground[NextGNo]->GetWay().WayType == 0)) {
				CurveFlg = false;
			}
			//�J�[�u�̔���
			if (CurveFlg == true) {
				float Ang;
				if (Type != 0) {
					Ang = ground[GNo]->GetWay().Ang;
				}
				else {
					Ang = 0.0f;
				}
				bool NoFlg = false;
				//�J�[�u�̒T��
				for (unsigned int g = NextGNo; g < ground.size(); g++) {
					if ((ground[g]->GetWay().WayType == Type) || (Type == 0)) {
						Type = ground[g]->GetWay().WayType;
					}
					else {
						NextGNo = g;
						NoFlg = true;
						break;
					}
					if (Ang < 90.0f) {
						Ang += ground[g]->GetWay().Ang;
						if (Ang > 90.0f) {
							NextGNo = g - 1;
							NoFlg = true;
							break;
						}
					}
				}
				//������Ȃ�������
				if (NoFlg == false) {
					return false;
				}
			}
			//�J�[�u�̑��x����
			if (Type != 0) {
				//�J�[�u
				CarFM->SpeedMul = 1.1f;
			}
			else {
				//�X�g���[�g
				CarFM->SpeedMul = 1.0f;
			}
			//start����end�܂ł�Vec�v�Z
			judg.MatMatVec(&Vec, ground[GNo]->GetWay().StartMat, ground[NextGNo]->GetWay().StartMat);
			CarFM->WayVec = Vec;
			//�x�W�F�Ȑ��̔���
			if (Type != 0) {
				CarFM->CurFlg = true;
				CurInitFlg = true;
			}
			else {
				CarFM->CurFlg = false;
			}
		}
		//startMat��endMat�̃Z�b�g
		if (CarFM->QuaMatInitFlg == false) {
			CarFM->StartMat = ground[GNo]->GetWay().StartMat;
			CarFM->EndMat = ground[NextGNo]->GetWay().StartMat;
			CarFM->QuaMatInitFlg = true;
		}
		//�x�W�F�Ȑ��̌v�Z
		if (CurInitFlg == true) {
			D3DXMATRIX Mat, MatE, RotX, RotY;
			D3DXVECTOR3 wVec = CarFM->WayVec / 2.0f, wPos;
			D3DXMatrixTranslation(&Mat, 0.0f, 0.0f, 0.0f);
			judg.TarEndMat(&MatE, Mat, &RotX, &RotY, CarFM->WayVec, D3DXVECTOR3(0.0f, 0.0f, 1.0f));
			judg.SetPosM(&wPos, &CarFM->StartMat);
			judg.SetMatP(&MatE, &(wPos + wVec));
			float Size = 0.0f, LR = 1.0f;
			if (Type == 1) {
				LR *= -1.0f;
			}
			D3DXVECTOR3 Vec;
			for (unsigned int i = GNo; i < NextGNo; i++) {
				judg.MatMatVec(&Vec, ground[i]->GetWay().StartMat, ground[i + 1]->GetWay().StartMat);
				Size += D3DXVec3Length(&Vec);
			}
			Size += D3DXVec3Length(&CarFM->WayVec);
			D3DXVec3TransformCoord(&CarFM->CurVec,
				&D3DXVECTOR3(CurSize*(float)(NextGNo - GNo)*Size*LR, 0.0f, 0.0f), &MatE);
		}
		//�X�s�[�h�̌v�Z
		if (OverFlg == false) {
			if (CarFM->CurFlg == true) {//�J�[�u���ɃX�s�[�h��x������
				CurDrawSpeed = 0.8f;
			}
			else {
				CurDrawSpeed = 1.0f;
			}
			float Size = D3DXVec3Length(&CarFM->WayVec), NowSpeed = D3DXVec3Length(&Con->Speed)*CarFM->SpeedMulJudg;
			Size *= CarFM->SpeedMul;
			float Speed = NowSpeed * CurDrawSpeed / Size;
			CarFM->AnimeFrame += Speed;
		}
		else {
			//�I�[�o�[���̏���
			float wVec;
			wVec = D3DXVec3Length(&CarFM->WayVec);
			wVec *= CarFM->SpeedMul;
			wVec = VecSize / wVec;
			CarFM->AnimeFrame += wVec;
		}
		bool qeFlg = false;
		//�I�[�o�[���̌v�Z
		if (CarFM->AnimeFrame > 1.0f) {
			D3DXVECTOR3 Vec;
			Vec = CarFM->WayVec;
			VecSize = D3DXVec3Length(&(Vec*CarFM->AnimeFrame - Vec));
			CarFM->AnimeFrame = 1.0f;
			OverFlg = true;
			qeFlg = true;
		}
		else {
			EndFlg = true;
		}
		//�N�H�[�^�j�I��
		judg.AnimeProc(&CarFM->NowMat, CarFM->StartMat, CarFM->EndMat, CarFM->AnimeFrame);
		//�x�W�F�Ȑ��̃N�H�[�^�j�I��
		if (CarFM->CurFlg == true) {
			D3DXVECTOR3 Pos;
			CurvePos(&Pos, &CarFM->StartMat, &CarFM->CurVec, &CarFM->EndMat, &CarFM->AnimeFrame);
			judg.SetMatP(&CarFM->NowMat, &Pos);
		}
		//�N�H�[�^�j�I���̏I������
		if (qeFlg == true) {//�O�i
			CarFM->QuaInitFlg = false;
			CarFM->QuaMatInitFlg = false;
			CarFM->AnimeFrame = 0.0f;
		}

		//��������
		D3DXMATRIX Tmp;
		D3DXMatrixTranslation(&Tmp, 0.0f, CarFM->BodyHeight, 0.0f);
		CarFM->NowMat = Tmp * (CarFM->NowMat);

		//�I������
		if (EndFlg == true) break;

	}
	return true;
}

