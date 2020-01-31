#pragma once
#include"SceneBase.h"
#include<vector>
#include<d3dx9.h>

//�\��
#include"../TitleParts/TitleSky.h"
#include"../StageParts/StageCar.h"
#include"../StageParts/StageCamera.h"
#include"../2DDraw/modoru.h"
#include"../StageParts/StageTex.h"
#include"../Key/CMouse.h"
#include"../Key/KeyTrue.h"
#include"../2DDraw/Fade.h"
#include"../StageParts/CarSelect.h"
#include"../Player2/PlayerBody.h"
#include"../StageParts/OkButton.h"
#include"../StageParts/CarSet.h"


class StageSelectScene :public SceneBase {
public:
	StageSelectScene();
	~StageSelectScene();
	void Render2D(void);
	void Render3D(void);
	bool Update(void);
	void SetCamera(void);

	//�`�F���W�V�[���p
	void ChangeSceneFade(int ChangeSceneNo);
	void ChangeSceneFade(int ChangeSceneNo,int NextStageNo);
	bool SetScene(void);

	//�ԑI���̍폜
	void DeleteCarSel(void);

	//�X�e�[�W�I���̍폜
	void DeleteStaSel(void);

	//�I��-----------------------------------------------------------------
	//�I�����[�h�ؑ�
	void ChangeMode();
	//�X�e�[�W�I�����[�h
	bool StageSelectMode(void);
	void InitStaSel(void);
	//�Ԑ؂�ւ����[�h
	bool CarSelectMode(void);
	void InitCarSel(void);

	void StartFade(void);

	//�Ԃ̃{�f�B�ς�
	void ChangeCar(int *No);

protected:
	//�`�F���WMode
	void ChangeMode_Car(void);

	//�ʏ탂�[�h�A�b�v�f�[�g
	bool Update_Normal(void);
	//�J�X�^�����[�h�A�b�v�f�[�g
	bool Update_Car(void);
	//�\���RD�̒ʏ탂�[�h
	void Draw3D_Normal(void);
	//�\���QD�̒ʏ탂�[�h
	void Draw2D_Normal(void);

	//�^�C�g���V�[���ɋ����ړ�
	bool Change_TitleScene(void);

private:
	StageSky *sky;
	//�v���C���[�̏��
	C_PlayerBody *PlayerBody;
	StageCar *car;

	StageCam *cam;
	Modoru *modoru;
	std::vector<StageTex*>stage;

	//�}�E�X
	C_Mouse *mouse;
	//�L�[
	C_KeyTrue key;
	//�t�F�[�h
	Fade *fade;
	//�`�F���W�V�[���p
	int SceneNo;
	bool SceneChangeFlg;
	int ChangeStageNo;

	//�I������
	bool EndFlg;


	//�I��\��
	std::vector<C_CarSelect*>CarSel;

	//�I�����[�hFlg
	bool StageModeFlg;
	bool CarModeFlg;

	//OK�{�^��
	C_OK *Ok;

	C_CarSet *M_CarSet;

	BODYDATA BodyData_Init;
};