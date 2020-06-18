#include "Sound_Base_3D.h"

extern LPDIRECTSOUND3DLISTENER8 lpSListener;

C_Sound_Base_3D::C_Sound_Base_3D(const S_SOUND_DATA * Data, std::string FileName)
{
	M_Sound_Data = *Data;
	Init_Sound(&M_Sound_Data.Sound_CategoryNo, &M_Sound_Data.Sound_No, FileName);
}

bool C_Sound_Base_3D::Update(const S_CAMERA_POS * CamPos, const bool * Flg,const int *Volume)
{
	if (DeleteFlg > 1)return false;

	DWORD SFlg;
	soundCol.Sound3D->SetPosition(M_Sound_Data.Pos.x, M_Sound_Data.Pos.y, M_Sound_Data.Pos.z, DS3D_IMMEDIATE);//�����̈ʒu
	lpSListener->SetPosition(CamPos->Pos.x, CamPos->Pos.y, CamPos->Pos.z, DS3D_IMMEDIATE);//���X�i�[�̈ʒu
		//���X�i�[�����Ă�������v�Z
	D3DXVECTOR3 Vec;
	Vec = CamPos->Look - CamPos->Pos;
	D3DXVec3Normalize(&Vec, &Vec);

	lpSListener->SetOrientation(Vec.x, Vec.y, Vec.z, CamPos->Head.x, CamPos->Head.y, CamPos->Head.z, DS3D_IMMEDIATE);//���X�i�[�����Ă�������ƃ��X�i�[�̓��̕���
	soundCol.Sound->GetStatus(&SFlg);
	if (M_MoveFlg != 2) {
		if ((SFlg&DSBSTATUS_PLAYING) == 0) {
			Loop_Mode();
			if ((*Flg == true) || (Loop_Mode_Flg == true)) {
				soundCol.Sound->Play(0, 0, 0);
				soundCol.Sound->SetVolume(*Volume);

				M_MoveFlg = 1;
			}
		}
	}
	
	return true;
}
