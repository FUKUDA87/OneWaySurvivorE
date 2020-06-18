#pragma once
#include<d3dx9.h>
#include"../GameSource/Struct.h"
#include"FadeMove.h"
#include"FadeOut.h"
#include"FadeIn.h"
#include"FadeDraw.h"
#include"../Scene/SceneBase.h"
#include"../Scene/SceneNo.h"

class C_Fade 
{
public:
	
	// ������
	void Init();

	~C_Fade();

	// �X�V����
	bool Update();

	// �`�揈��
	void Draw();

	// �t�F�[�h�A�E�g�����鏈��
	void StartFadeout(void);

	// �t�F�[�h�C���������鏈��
	void StartFadein(void);

	//�����̃t���O�n��
	bool GetMoveFlg(void) {
		return MoveFlg;
	}
	//Move����Flg�n��
	bool GetMoveEndFlg(void) {
		return MoveEndFlg;
	}

	// ���̃V�[���̓n��
	SceneBase* GetNextScene(void);

	// ���̃V�[���̏��̃Z�b�g
	void SetNextScene(const int SceneNo,const bool BlackFlg);
	void SetNextStageNo(const int StageNo);
	void SetNextStageNo(const bool *GameSceneDebugFlg);
private:
	C_FadeMove *FadeMove;


	C_FadeDraw *fadeDraw;

	int alpha;
	
	//�t�F�[�h��Flg;
	bool MoveFlg, MoveEndFlg;

	//�t�F�[�h�F
	int FadeColor;

	int NextSceneNo;
	int NextStageNo;
	bool gameSceneDebugFlg;

	//�F�ς�
	void SetColor(bool BlackFlg);
};