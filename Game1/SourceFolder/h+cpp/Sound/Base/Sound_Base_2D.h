#pragma once
#include<d3dx9.h>
#include<dsound.h>
#include"../../GameSource/Struct.h"
#include"../../Const/Const_Sound_Type.h"
#include<string>


class C_Sound_Base_2D {
public:
	C_Sound_Base_2D();
	~C_Sound_Base_2D();

	// �X�V����
	virtual bool Update(const S_CAMERA_POS* CamPos, const bool *PlayFlg,const int *Volume);

	// �Ȃ��ŏ��ɖ߂�
	void Reset(void);

	// ���f
	virtual void Stop(void);

	// �ĊJ
	virtual void Restart(const int *Volume);

	S_SOUND_DATA Get_Data(void) {
		return M_Sound_Data;
	}
protected:
	//���̃T�E���h
	int NowSound;
	//�T�E���h�ϐ�
	SoundCol soundCol;

	//�T�E���h�ԍ�
	S_SOUND_DATA M_Sound_Data;

	//������
	void Init_Sound(const int *CategoryNo,const int *No, std::string FileName);

	int M_MoveFlg;

	//�������[�v�����鏈��
	void Loop_Mode(void);

	bool Loop_Mode_Flg;

	bool M_Init_Flg;

	int DeleteFlg;
private:
	
};