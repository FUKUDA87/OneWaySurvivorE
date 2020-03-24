#include"StageSelectScene.h"
#include"GameScene.h"
#include"TitleScene.h"
#include"SceneManager.h"

extern SceneManager sceneManager;

#define	SCRW		1280	// �E�B���h�E���iWidth
#define	SCRH		720		// �E�B���h�E�����iHeight
#define GameNo 2
#define TitleNo 1

StageSelectScene::StageSelectScene()
{
	Init_New();

	mouse = new C_Mouse();
	mouse->ChaDrawFlg(true);
	sky = new StageSky();

	//�v���C���[�̏������O�ɏ�����
	PlayerBody = new C_PlayerBody();

	car = new StageCar(&PlayerBody->GetPData());
	cam = new StageCam();
	modoru = new Modoru();

	//�V�[���̐؂�ւ�������
	SceneChangeFlg = false;
	//�t�F�[�h�̏�����
	fade = new Fade();
	fade->ChaFlg(false);

	key.Init();

	//�T�E���h�̏�����
	if (M_C_Sound_Manager == nullptr)M_C_Sound_Manager = new C_Sound_Manager_Base();


	//�I�����[�h�̏������̑O�ɏ�����
	Ok = new C_OK(&D3DXVECTOR3(1.1f, 1.1f, 0.0f), &D3DXVECTOR3(1280.0f/2.0f, 720.0f*0.93f, 0.0f), &D3DXVECTOR3(0.25f, 0.11f, 0.0f));

	//�Ԃ̕\���̖߂��p�Z�b�g
	BodyData_Init = car->Get_BODYDATA();

	//�I�����[�h�̏�����
	InitStaSel();

	M_CarSet = new C_CarSet();

	GameScene_DebugFlg = false;

	int No = 3;
	C_Struct_Init C_S_Init;
	M_C_Sound_Manager->New_Sound_Data(&C_S_Init.Get_S_SOUND_DATA(
		&Co_Sound_Type_2D, &Co_Sound_Category_BGM, &No, &Co_Sound_Change));

}

StageSelectScene::~StageSelectScene()
{
	if (M_C_Sound_Manager != nullptr) {
		M_C_Sound_Manager->Stop_Sound_All();
		delete M_C_Sound_Manager;
	}

	delete sky;
	delete car;
	delete cam;
	delete modoru;

	//�}�E�X�̍폜
	delete mouse;
	//�t�F�[�h�̍폜
	delete fade;

	DeleteCarSel();

	DeleteStaSel();

	//�v���C���[�̏��폜
	delete PlayerBody;
	//Ok�{�^���̍폜
	delete Ok;

	EndFlg = false;

	if (M_CarSet != nullptr) {
		delete M_CarSet;
	}

	if (M_C_Garage_Stand != nullptr) {
		delete M_C_Garage_Stand;
	}

}

void StageSelectScene::Render2D(void)
{
	//////////////////////////////////////////////////
	///	�X�v���C�g�̕`�揈��
	//////////////////////////////////////////////////
	// �`��J�n
	lpSprite->Begin(D3DXSPRITE_ALPHABLEND);
	Draw2D_Normal();
	// �`��I��
	lpSprite->End();

	M_CarSet->DrawTxt();
}

void StageSelectScene::Render3D(void)
{
	M_CarSet->Draw3D(&cam->GetPos());

	//�X�e�[�W�O

	//�K���[�W
	sky->Draw();

	if (M_C_Garage_Stand != nullptr) {
		M_C_Garage_Stand->Draw_Garage_Stand(&cam->GetPos());
	}

	Draw3D_Normal();
}

bool StageSelectScene::Update(void)
{
	if (Change_TitleScene() != true)return false;

	if (M_C_Sound_Manager != nullptr) {
		M_C_Sound_Manager->Update_Sound();

		M_C_Sound_Manager->Set_Sound();
	}

	mouse->Update();

	//�t�F�[�h�̃A�b�v�f�[�g
	if (fade->Update() == true) {
		//�L�[�̖��͉�

	}
	else {
		if (fade->GetMoveEndFlg() == true) {
			if (SceneChangeFlg == true)return SetScene();
		}
	}

	ChangeMode_Car();

	

	Update_Normal();
	Update_Car();

	car->UpdateAll();

	D3DXMATRIX tmp;
	D3DXMatrixTranslation(&tmp, 0.0f, 2.0f, 0.0f);
	sky->Update(&tmp);
	return true;
}

void StageSelectScene::SetCamera(void)
{
	D3DXMATRIX mView, mProj;
	D3DXMatrixLookAtLH(&mView,
		&cam->GetPos(),//�J�����̈ʒu
		&cam->GetLook(),// �J�����̎��_
		&D3DXVECTOR3(0.0f, 1.0f, 0.0f)	// �J�����̓��̕���
	);

	// ���e�s��̐ݒ�
	D3DXMatrixPerspectiveFovLH(&mProj, D3DXToRadian(60), (float)SCRW / (float)SCRH, 1.0f, 1000.0f);

	//�s��ݒ�
	lpD3DDevice->SetTransform(D3DTS_VIEW, &mView);
	lpD3DDevice->SetTransform(D3DTS_PROJECTION, &mProj);
}

void StageSelectScene::ChangeSceneFade(int ChangeSceneNo)
{
	if (fade->GetMoveFlg() == false) {
		if (SceneChangeFlg == false) {
			SceneNo = ChangeSceneNo;
			if (ChangeSceneNo == GameNo)return;
			StartFade();
			return;
		}
	}
}

void StageSelectScene::ChangeSceneFade(int ChangeSceneNo, int NextStageNo)
{

	ChangeSceneFade(ChangeSceneNo);
	ChangeStageNo = NextStageNo;
}

bool  StageSelectScene::SetScene(void)
{
	if (SceneNo == TitleNo) {
		sceneManager.changeScene(new TitleScene());
		return false;
	}
	if (SceneNo = GameNo) {
		sceneManager.changeScene(new GameScene(ChangeStageNo,&GameScene_DebugFlg));
		return false;
	}
	return true;
}

void StageSelectScene::DeleteCarSel(void)
{
	//�폜
	if (CarSel.size() > 0) {
		for (unsigned int c = 0; c < CarSel.size(); c++) {
			delete CarSel[c];
			CarSel.erase(CarSel.begin() + c);
			c--;
		}
	}
}

void StageSelectScene::DeleteStaSel(void)
{
	//�폜
	if (stage.size() > 0) {
		for (unsigned int i = 0; i < stage.size(); i++) {
			delete stage[i];
			stage.erase(stage.begin() + i);
			i--;
		}
	}
}

void StageSelectScene::ChangeMode()
{
	//�X�e�[�W�I�����[�h
	if (StageModeFlg == true) {
		StageSelectMode();
		return;
	}
	//�ԑI�����[�h
	if(CarModeFlg == true) {
		CarSelectMode();
		return;
	}
}

bool StageSelectScene::StageSelectMode()
{
	//�L�[�m�F
	bool KeyFlg = key.LClickF();
	//�߂�{�^��
	if (modoru->UpdateSu() == false) {
		mouse->SetTouchFlg();
		if (KeyFlg == true) {
			ChangeSceneFade(TitleNo);
			StageModeFlg = false;
			CarModeFlg = false;
			return true;
		}
	}
	//�X�e�[�W�I���{�^��
	if (stage.size() > 0) {
		for (unsigned int s = 0; s < stage.size(); s++) {
			if (stage[s]->UpdateSu() == false) {
				mouse->SetTouchFlg();
				if (KeyFlg == true) {
					ChangeSceneFade(GameNo, stage[s]->GetStageNo());
					InitCarSel();
					return true;
				}
			}
		}
	}
	return true;
}

void StageSelectScene::InitStaSel(void)
{
	//�t���O�̃Z�b�g
	StageModeFlg = true;
	CarModeFlg = false;

	//�\���̍폜
	DeleteCarSel();
	//Ok�{�^���̕\���Z�b�g
	Ok->SetDrawFlg(false);

	//�X�e�[�W�I���A�C�R���쐬
	for (int s = 0; s < 1; s++) {
		stage.push_back(new StageTex(s + 1, D3DXVECTOR3((float)SCRW / 6.0f*(float)(s + 1), (float)SCRH / 4.0f, 0.0f)));
	}

	//�Ԃ̕\���߂�
	car->SetBody(&BodyData_Init);

	//�f�[�^�ɃZ�b�g
	PlayerBody->SetPData(&car->Get_BODYDATA());
}

bool StageSelectScene::CarSelectMode()
{
	//�L�[�m�F
	bool KeyFlg = key.LClickF();
	//�߂�{�^��
	if (modoru->UpdateSu() == false) {
		mouse->SetTouchFlg();
		if (KeyFlg == true) {
			InitStaSel();
			return true;
		}
	}
	//�ԃ{�^��
	if (CarSel.size() > 0) {
		int tNo;
		for (auto && c: CarSel) {
			tNo = c->Touch();
			if (tNo > 0) {
				if (KeyFlg==true) {
					if (tNo == 1) {
						int No = c->GetNo() - 1;
						ChangeCar(&No);
						c->UpdateNo(&No);
						return true;
					}
					if (tNo == 2) {
						int No = c->GetNo() +1;
						ChangeCar(&No);
						c->UpdateNo(&No);
						return true;
					}
				}
			}
		}
	}
	//Ok�{�^��
	if (KeyFlg == true) {
		if (Ok->Touch() == true) {
			Set_GameScene_DebugFlg();
			StartFade();
			return true;
		}
	}
	
	return true;
}

void StageSelectScene::InitCarSel(void)
{
	//�t���O�̃Z�b�g
	StageModeFlg = false;
	CarModeFlg = true;

	DeleteStaSel();
	//Ok�{�^���̕\���Z�b�g
	Ok->SetDrawFlg(true);

	//�I���̏�����
	CarSel.push_back(new C_CarSelect(
		&D3DXVECTOR3(1280.0f / 5.0f*4.0f, 720.0f / 4.0f*3.0f, 0.0f), &D3DXVECTOR3(0.15f, 0.11f, 0.0f), &D3DXVECTOR3(0.33f, 0.31f, 0.0f), &D3DXVECTOR3(-100.0f, 0.0f, 0.0f), &D3DXVECTOR3(0.85f, 0.85f, 0.0f)
	));
	int No = PlayerBody->GetPData().CarBodyNo;
	CarSel[CarSel.size() - 1]->UpdateNo(&No);

	//�Ԃ̕\���̖߂��p�Z�b�g
	BodyData_Init = car->Get_BODYDATA();

}

void StageSelectScene::StartFade(void)
{
	SceneChangeFlg = true;
	bool BlackFlg = true;
	if (SceneNo == GameNo)BlackFlg = false;
	fade->SetIn(BlackFlg);
}

void StageSelectScene::ChangeCar(int * No)
{
	//���b�V���̎�ޕς�
	if (*No > 2)*No = 1;
	if (*No < 1)*No = 2;

	BODYDATA pData = PlayerBody->GetPData();
	pData.CarBodyNo = *No;
	//�Ԃɔ��f
	car->SetBody(&pData);

	//�f�[�^�ɃZ�b�g
	PlayerBody->SetPData(&car->Get_BODYDATA());

}

void StageSelectScene::ChangeMode_Car(void)
{
	if (fade->GetMoveFlg() != false)return;

	if (CarModeFlg != true)return;

	if (key.RETURNKeyF() != true)return;

	if (GetAsyncKeyState('8') & 0x8000) {
		if (GetAsyncKeyState('9') & 0x8000) {
			M_CarSet->ChangeMode(true);
			if (M_CarSet->GetModeFlg() == true)mouse->Init();
		}
	}
}

bool StageSelectScene::Update_Normal(void)
{
	if (M_CarSet->GetModeFlg() != false)return false;

	ChangeMode();

	D3DXMATRIX cTmp;
	D3DXMatrixTranslation(&cTmp, 0.0f, 1.0f, 0.0f);
	cam->Update(car->GetMatCar(), cTmp, true);

	return false;
}

bool StageSelectScene::Update_Car(void)
{
	if (M_CarSet->GetModeFlg() != true)return false;

	D3DXVECTOR3 l_Pos = M_CarSet->GetPartsPos();
	if (key.AKey() == true)l_Pos.x -= M_CarSet->GetUp();
	if (key.FKey() == true)l_Pos.x += M_CarSet->GetUp();

	if (key.WKey() == true)l_Pos.y += M_CarSet->GetUp();
	if (key.SKey() == true)l_Pos.y -= M_CarSet->GetUp();

	if (key.EKey() == true)l_Pos.z += M_CarSet->GetUp();
	if (key.DKey() == true)l_Pos.z -= M_CarSet->GetUp();
	M_CarSet->SetPartsPos(&l_Pos);

	if (key.XKeyF() == true)M_CarSet->ChangeCar();

	cam->UpdateCar(mouse);

	mouse->Init();

	float y = cam->GetHeight();

	if (key.TKey() == true)y += M_CarSet->GetUp();
	if (key.GKey() == true)y -= M_CarSet->GetUp();

	cam->SetHeight(&y);

	if (key.ZKeyF() == true)M_CarSet->ChangePartsMeshFlg(true);
	if (key.CKeyF() == true)M_CarSet->ChangePartsMesh(true);

	//�p�[�c���W�ύX��
	if (M_CarSet->Get_Mesh_JudgFlg() != Co_Draw_Mesh)return false;
	l_Pos = M_CarSet->GetPartsPos();
	float l_Dis;
	Judg judg;
	if (judg.Mesh(l_Pos, D3DXVECTOR3(0.0f, -1.0f, 0.0f), sky->GetDrawSkyMat(), sky->GetSkyMesh(), &l_Dis) == true) {
		D3DXVECTOR3 l_Pos2 = l_Pos + D3DXVECTOR3(0.0f, -1.0f, 0.0f)*l_Dis;
		
		D3DXMATRIX Mat;
		D3DXMatrixTranslation(&Mat, l_Pos.x, l_Pos.y, l_Pos.z);
		if (judg.Mesh(l_Pos2, D3DXVECTOR3(0.0f, 1.0f, 0.0f), Mat, M_CarSet->Get_Mesh(), &l_Dis) == true) {
			l_Pos2 = l_Pos2 + D3DXVECTOR3(0.0f, 1.0f, 0.0f)*l_Dis;

			M_CarSet->GroundSize(&l_Pos2.y);
		}
	}

	return false;
}

void StageSelectScene::Draw3D_Normal(void)
{
	if (M_CarSet->GetModeFlg() != false)return;

	//�ԑ�
	car->Draw3DAll(&cam->GetPos());
}

void StageSelectScene::Draw2D_Normal(void)
{
	if (M_CarSet->GetModeFlg() != false)return;

	//�߂�
	modoru->DrawSu();
	//�X�e�[�W
	if (stage.size() > 0) {
		for (unsigned int s = 0; s < stage.size(); s++) {
			stage[s]->DrawSu();
		}
	}

	if (CarSel.size() > 0) {
		for (unsigned int c = 0; c < CarSel.size(); c++) {
			CarSel[c]->Draw2DAll();
		}
	}

	Ok->Draw2DOK();

	fade->Draw();
	mouse->Draw2D();
}

bool StageSelectScene::Change_TitleScene(void)
{
	if (key.EscapeKey_F() == true) {
		sceneManager.changeScene(new TitleScene());
		return false;
	}

	return true;
}

void StageSelectScene::Car_Ground_Vec(void)
{
}

void StageSelectScene::Init_New(void)
{
	//M_C_Garage_Stand = new C_Stage_Room_Stand(&D3DXVECTOR3(0.0f, 0.0f, 0.0f), "../GameFolder/Material/XFile/Car_Stand_O_1.x");
}

void StageSelectScene::Set_GameScene_DebugFlg(void)
{
	if (key.Num7Key() != true)return;

	if (key.Num8Key() != true)return;

	if (key.Num9Key() != true)return;

	GameScene_DebugFlg = true;
}
