#include"TitleScene.h"
#include"SceneManager.h"
#include"GameScene.h"
#include"../MaterialManager/TextureManager.h"
#include"../MaterialManager/XfileManager.h"
#include"StageSelectScene.h"
#include"../Fade/Fade.h"

extern TextureManager textureManager;
extern XFileManager xfileManager;
extern LPD3DXSPRITE lpSprite;	// �X�v���C�g
extern SceneManager sceneManager;
extern LPDIRECT3DDEVICE9		lpD3DDevice;	// Direct3DDevice�C���^�[�t�F�C�X
extern C_Fade fade;

#define	SCRW		1280	// �E�B���h�E���iWidth
#define	SCRH		720		// �E�B���h�E�����iHeight
#define StageSelectNo 1

void LoadTexture(LPDIRECT3DTEXTURE9 *lpTex, const char fname[], int W, int H, D3DCOLOR Color);


TitleScene::TitleScene()
{
	// �I�v�V�����̃C���X�^���X��
	option = new C_Option();
	option->Read();

	// �t�F�[�h�C���̊J�n
	fade.StartFadein();

	//�v���C���[�̏������̑O�ɏ�����
	PlaBodData = new C_PlayerBody();

	player = new C_PlayerA(&PlaBodData->GetPData());
	//�n�ʏ�����--------------------------------------------------------
	
	groundManager = new c_GroundManager(player);

	//---------------------------------------------------------------------
	//�}�E�X�̏�����
	mouse = new C_Mouse();
	mouse->ChaDrawFlg(true);

	titleTex = new TitleTex();
	startTex = new StartTex();

	camera = new TitleCamera();
	sky = new Sky();

	key.Init();

	//�T�E���h�̏�����
	int BGMVolume = option->GetOptionData().BGMVolume, SEVolume = option->GetOptionData().SEVolume;
	M_C_Sound_Manager = new c_GameSoundManager(&BGMVolume, &SEVolume);

	//�e���̏�����
	if (false) {
		float AngZ = -90.0f;
		BulHol.push_back(new C_BulletHole(&D3DXVECTOR3(250.0f, 720.0f / 4.0f*3.0f, 0.0f), &AngZ, &D3DXVECTOR3(2.1f, 2.1f, 1.0f), 1));
		BulHol.push_back(new C_BulletHole(&D3DXVECTOR3(250.0f, 720.0f / 4.0f*3.0f, 0.0f), &AngZ, &D3DXVECTOR3(2.1f, 2.1f, 1.0f), 2));
		AngZ = (70.0f)*-1.0f;
		BulHol.push_back(new C_BulletHole(&D3DXVECTOR3(1050.0f, 500.0f, 0.0f), &AngZ, &D3DXVECTOR3(2.1f, 2.1f, 1.0f), 1));
		AngZ += 50.0f;
		BulHol.push_back(new C_BulletHole(&D3DXVECTOR3(990.0f, 380.0f, 0.0f), &AngZ, &D3DXVECTOR3(2.1f, 2.1f, 1.0f), 1));
		AngZ -= 50.0f;
		BulHol.push_back(new C_BulletHole(&D3DXVECTOR3(1050.0f, 500.0f, 0.0f), &AngZ, &D3DXVECTOR3(2.1f, 2.1f, 1.0f), 2));
		AngZ += 50.0f;
		BulHol.push_back(new C_BulletHole(&D3DXVECTOR3(990.0f, 380.0f, 0.0f), &AngZ, &D3DXVECTOR3(2.1f, 2.1f, 1.0f), 2));
		AngZ = -0.0f;
		//BulHol.push_back(new C_BulletHole(&D3DXVECTOR3(455.0f, 85.0f, 0.0f), &AngZ, &D3DXVECTOR3(1.2f, 1.2f, 1.0f)));
		BulHol.push_back(new C_BulletHole(&D3DXVECTOR3(300.0f, 200.0f, 0.0f), &AngZ, &D3DXVECTOR3(2.1f, 2.1f, 1.0f), 1));
		BulHol.push_back(new C_BulletHole(&D3DXVECTOR3(300.0f, 200.0f, 0.0f), &AngZ, &D3DXVECTOR3(2.1f, 2.1f, 1.0f), 2));

		BulHol.push_back(new C_BulletHole(&D3DXVECTOR3(1100.0f, 100.0f, 0.0f), &AngZ, &D3DXVECTOR3(2.1f, 2.1f, 1.0f), 1));
		BulHol.push_back(new C_BulletHole(&D3DXVECTOR3(1100.0f, 100.0f, 0.0f), &AngZ, &D3DXVECTOR3(2.1f, 2.1f, 1.0f), 2));
	}

	int No = 2;
	M_C_Sound_Manager->BGMStart(&No);

}
TitleScene::~TitleScene()
{

	delete player;
	delete titleTex;
	delete startTex;
	delete camera;
	delete sky;
	//�n�ʂ̍폜
	if (groundManager != nullptr)delete groundManager;
	//�e���폜
	if (BulHol.size() > 0) {
		for (unsigned int b = 0; b < BulHol.size(); b++) {
			delete BulHol[b];
			BulHol.erase(BulHol.begin() + b);
			b--;
		}
	}
	//�}�E�X�̍폜
	delete mouse;

	delete PlaBodData;

	if (M_C_Sound_Manager != nullptr) {
		M_C_Sound_Manager->Reset();
		delete M_C_Sound_Manager;
	}

	// �I�v�V�����̍폜
	option->Write();
	if (option != nullptr) delete option;

}
bool TitleScene::Update(void)
{

	if (M_C_Sound_Manager != nullptr) {

		S_OptionData l_OptionData = option->GetOptionData();

		M_C_Sound_Manager->UpdateVolume(&l_OptionData.BGMVolume, &l_OptionData.SEVolume);

		M_C_Sound_Manager->Update();

		M_C_Sound_Manager->New();

	}

	Game_End();

	//bgm�̃A�b�v�f�[�g
	bool bFlg = true;
	SoundCamera scB;
	scB.CamPos = camera->GetPos();
	scB.CamLook = camera->GetLook();
	scB.CamHead = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	mouse->Update();

	//�t�F�[�h�̃A�b�v�f�[�g
	if (fade.Update() == true) {
		//�L�[�̖��͉�

	}
	else {
		// �t�F�[�h�A�E�g������������
		if (fade.GetMoveEndFlg() == true) {
			sceneManager.changeScene(new StageSelectScene());
			return false;
		}
	}

	//�X�e�[�W�I���V�[���ֈړ�
	Next_StageScene_Switch();

	//================================================================================
	//�n��
	//================================================================================
	if (groundManager != nullptr)groundManager->Update(player);
	// �v���C���[�ƒn�ʔ���
	float Dis;
	unsigned int num;
	if (groundManager->JudgNowGround(&num, &Dis, player->GetMatCar()) == true) {
		player->SetGroNum(&num);//�n�ʂ̎擾
	}
	player->UpdateCarFM(groundManager->GetGround());
	D3DXMATRIX Mat = player->GetMatCar();
	judg.SetMatP(&Mat, &D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	player->UpdateAll(&Mat);
	camera->Update(player->GetMatCar());
	sky->Update(&player->GetMatCar());

	
	return true;
}

void TitleScene::Render2D(void)
{
	//////////////////////////////////////////////////
	///	�X�v���C�g�̕`�揈��
	//////////////////////////////////////////////////
	// �`��J�n
	lpSprite->Begin(D3DXSPRITE_ALPHABLEND);

	//titleTex�̕\��
	titleTex->Draw();

	startTex->DrawSu();

	fade.Draw();

	//�e���\��
	if (BulHol.size() > 0) {
		for (unsigned int b = 0; b < BulHol.size(); b++) {
			BulHol[b]->Draw2DBH();
		}
	}
	

	mouse->Draw2D();
	// �`��I��
	lpSprite->End();
}

void TitleScene::Render3D(void)
{
	if (groundManager != nullptr)groundManager->Draw3D();
	player->Draw3DAll(&camera->GetPos());
	sky->Draw();
}

void TitleScene::SetCamera(void)
{
	D3DXMATRIX mView, mProj;
	D3DXMatrixLookAtLH(&mView,
		&camera->GetPos(),//�J�����̈ʒu
		&camera->GetLook(),// �J�����̎��_
		&D3DXVECTOR3(0.0f, 1.0f, 0.0f)	// �J�����̓��̕���
	);

	// ���e�s��̐ݒ�
	D3DXMatrixPerspectiveFovLH(&mProj, D3DXToRadian(60), (float)SCRW / (float)SCRH, 0.1f, 1200.0f);

	//�s��ݒ�
	lpD3DDevice->SetTransform(D3DTS_VIEW, &mView);
	lpD3DDevice->SetTransform(D3DTS_PROJECTION, &mProj);

}

bool TitleScene::Game_End(void)
{
	if (key.EscapeKey_F() == true) {
		PostQuitMessage(0);
		return false;
	}
	return true;
}

void TitleScene::Next_StageScene_Switch(void)
{
	//�X�C�b�`�̍X�V�Ɠ���̊m�F
	if (startTex->UpdateSu() != false) return;

	//�}�E�X�J�[�\������ɂ��鏈��
	mouse->SetTouchFlg();

	//�X�C�b�`�����쒆���̊m�F
	if (startTex->GetMoveFlg() != false)return;

	//�V�[���؂�ւ���Ԃł��邩�̊m�F
	if (fade.GetMoveFlg() != false) return;

	//�N���b�N�������̊m�F
	if (key.LClickF() != true) return;

	//�X�C�b�`�̓���J�n
	startTex->SetMoveFlg(true);

	//�t�F�[�h�A�E�g�̊J�n
	fade.StartFadeout();

	//BGM�̍폜
	M_C_Sound_Manager->BGMDelete();

	//�N���b�N��
	M_C_Sound_Manager->New_Sound_Data(&Co_Sound_Type_2D, &Co_Sound_Category_Click, 1, &Co_SoundNew);
}
