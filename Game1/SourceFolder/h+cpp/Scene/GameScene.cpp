#include"GameScene.h"
#include"TitleScene.h"
#include"StageSelectScene.h"
#include"SceneManager.h"
#include"../GameSource/Enum.h"
#include"../MaterialManager/TextureManager.h"
#include"../MaterialManager/XfileManager.h"
#include"../GameSource/Motion.h"
#include"../Car/Data/Draw3DManager/CarSmogManager.h"
#include"../Enemy/Data/Base&Manager/Enemy_Manager.h"
#include"../Const/Const_Wave_Type.h"
#include"../Const/Const_Rail_Type.h"
#include"../Const/Const_Stage_Type.h"
#include"../GameSource/StructClass/Struct_Init.h"
#include"../Gun/Bullet/Const_Bullet_No.h"
#include"../Fade/Fade.h"
#include"../Draw/Effect/3D/BulletHole/BulletHole3D.h"
#include"../Draw/Effect/3D/Explosion/Explosion3D.h"
#include"../Draw/Effect/3D/Spark/SparkDamege.h"
#include"../Draw/Effect/3D/Spark/BulletGround.h"

extern int CountManager;
extern Motion motion;
extern TextureManager textureManager;
extern XFileManager xfileManager;
extern SceneManager sceneManager;
extern LPDIRECT3DDEVICE9		lpD3DDevice;	// Direct3DDevice�C���^�[�t�F�C�X
extern LPD3DXSPRITE lpSprite;	// �X�v���C�g
extern LPD3DXFONT lpFont;		// �t�H���g
extern C_Fade fade;

#define	SCRW		1280	// �E�B���h�E���iWidth
#define	SCRH		720		// �E�B���h�E�����iHeight
#define RadJudgF 100
#define StageSelectNo 2
#define GameNo 3
#define TitleNo 1

GameScene::GameScene(const int stageNum)
{
	StageNo = stageNum;
	Init();
}
GameScene::GameScene(const int stageNum, const bool * DebugFlg)
{
	StageNo = stageNum;

	if (*DebugFlg == true)StageNo = Co_Stage_Type_Debug;

	Init();

	if (*DebugFlg != true)return;

	if (player != nullptr) {
		unsigned int i = 0;
		player->Set_Gun_Bullet_No(&i, &Co_Bullet_No99);
	}
}
GameScene::~GameScene() 
{
	Debug_Screen_End();

	if (M_Text_Num != nullptr)delete M_Text_Num;

	if (groundManager != nullptr)delete groundManager;

	//�G�̍폜
	for (unsigned int i = 0; i < enemy.size(); i++) {
		delete enemy[i];
		enemy.erase(enemy.begin() + i); i--;
	}
	
	delete player;
	delete sky;
	delete camera;
	delete aiming;
	delete debug;

	if (M_C_Game_End != nullptr) {
		delete M_C_Game_End;
	}

	delete war;
	delete pause;
	delete spear;
	//�X�R�A�̍폜
	delete score;

	//�Ԃ̏����폜
	if (M_C_Car_Pop != nullptr) {
		delete M_C_Car_Pop;
	}

	//�}�E�X�̍폜
	delete mouse;

	if (effect.size() > 0) {
		for (unsigned int ec = 0; ec < effect.size(); ec++) {
			delete effect[ec];
			effect.erase(effect.begin() + ec);
			ec--;
		}
	}

	//�v���C���[�̏��폜
	delete PlayerBody;
	

	//���̊Ǘ��̍폜
	if (M_C_Sound_Manager != nullptr) {
		M_C_Sound_Manager->Reset();
		delete M_C_Sound_Manager;
	}

	if (M_Damage_Num_Draw.size() > 0) {
		for (unsigned int v = 0; v < M_Damage_Num_Draw.size(); v++) {
			Delete_Damage_Num_Draw(&v);
		}
	}

	// �I�v�V�����̍폜
	option->Write();
	if (option != nullptr) delete option;

	//���j���[�̍폜
	if (Menu != nullptr)delete Menu;
}
void GameScene::Render3D(void) {
	/*if (player->GetBulSiz() > 0) {
		spear->Draw3DV(player->GetBulMat(0));
	}*/
	sky->Draw();
	
	if (groundManager != nullptr)groundManager->Draw3D();

	if (enemy.size() > 0) {
		for (unsigned int i = 0; i < enemy.size(); i++) {
			enemy[i]->Draw3DAll(&camera->GetPos());
		}
	}

	player->Draw3DAll(&camera->GetPos());

	if (effect.size() > 0) {
		for (auto && e : effect) e->Draw3D(&camera->GetPos());
	}

}
void GameScene::Render3D_Screen(void)
{
	if (M_S_Screen.DrawFlg != true)return;

	lpD3DDevice->SetRenderTarget(0, M_S_Screen.lpTmpBackBuffer);
	lpD3DDevice->SetDepthStencilSurface(M_S_Screen.lpTmpZBuffer);
	D3DVIEWPORT9 Viewport;
	Viewport.X = 0;
	Viewport.Y = 0;
	Viewport.Width = 1280 / 2;
	Viewport.Height = 720 / 2;
	Viewport.MinZ = 0;
	Viewport.MaxZ = 1;
	lpD3DDevice->SetViewport(&Viewport);
	// �o�b�N�o�b�t�@�� Z �o�b�t�@���N���A
	lpD3DDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 255), 1.0f, 0);
	//    �o�b�N�o�b�t�@�@�@�@Z�o�b�N�o�b�t�@

	D3DXMATRIX mView, mProj;

	//�J�����̈ʒu�̍s��쐬
	D3DXMATRIX CamMat;
	D3DXMatrixTranslation(&CamMat, 45.0f, 50.0f, -1.0f);
	CamMat = CamMat * player->GetCon().JudgMat;

	D3DXMATRIX L_CameraLook_Mat = player->GetCon().JudgMat;

	// ���_�s��̐ݒ�
	D3DXMatrixLookAtLH(&mView,
		&judg.SetPosM(&CamMat),	// �J�����̈ʒu
		&judg.SetPosM(&L_CameraLook_Mat) ,	// �J�����̎��_
		&D3DXVECTOR3(0.0f, 1.0f, 0.0f)	// �J�����̓��̕���
	);

	// ���e�s��̐ݒ�
	D3DXMatrixPerspectiveFovLH(&mProj, D3DXToRadian(60), (float)SCRW / (float)SCRH, 0.1f, 600.0f);

	//�s��ݒ�
	lpD3DDevice->SetTransform(D3DTS_VIEW, &mView);
	lpD3DDevice->SetTransform(D3DTS_PROJECTION, &mProj);

	Render3D();
	lpD3DDevice->SetRenderTarget(0, M_S_Screen.lpBackBuffer);
	lpD3DDevice->SetDepthStencilSurface(M_S_Screen.lpZBuffer);
}
void GameScene::Render2D(void) {
	//////////////////////////////////////////////////
	///	�X�v���C�g�̕`�揈��
	//////////////////////////////////////////////////
	// �`��J�n
	lpSprite->Begin(D3DXSPRITE_ALPHABLEND);

	if (M_Damage_Num_Draw.size() > 0) {
		for (auto && v : M_Damage_Num_Draw) {
			v->Draw_2D();
		}
	}

	if (enemy.size() > 0) {
		for (unsigned int i = 0; i < enemy.size(); i++) {
			enemy[i]->Draw2DAll();
		}
	}

	aiming->Draw();
	player->Draw2DAll();

	Debug_Screen_Draw();

	//�X�R�A�̕\��
	score->Draw2D();
	//�N���A�ƃI�[�o�[�̕\��
	if (M_C_Game_End != nullptr) {
		M_C_Game_End->Draw_2D();
	}
	//�{�X�o���\��
	war->Draw2D();

	//�|�[�Y�̕\��
	pause->Draw();

	//���j���[�̕\��
	if (Menu != nullptr)Menu->Draw2DAll();

	//�t�F�[�h�C���A�E�g�̕\��
	fade.Draw();
	mouse->Draw2D();
	// �`��I��
	lpSprite->End();

	//�f�o�b�N�p�̕����\��
	Debug_Text();
}
bool GameScene::Update(void) {

	if (Change_TitleScene() != true)return false;

	/*�T�E���h�̍X�V����*/
	if (M_C_Sound_Manager != nullptr)
	{

		S_OptionData l_OptionData = option->GetOptionData();

		M_C_Sound_Manager->Update(&camera->GetPos(), &camera->GetLook(), &D3DXVECTOR3(0.0f, 1.0f, 0.0f), &l_OptionData.BGMVolume);

		M_C_Sound_Manager->New(&l_OptionData.BGMVolume);

		/*/Sound���v���C���[���Ŗ炷*/
		if (player != nullptr) {
			for (unsigned int s = 0; s < player->Get_Sound_Data_Num(); s++) {
				if (M_C_Sound_Manager->Order(&player->Get_Sound_Data(&s), &l_OptionData.BGMVolume) == true) {
					player->Delete_Sound(&s);
				}
			}
		}

		if (war != nullptr) {
			for (unsigned int d = 0; d < war->Get_Sound_Data_Num(); d++) {
				if (M_C_Sound_Manager->Order(&war->Get_Sound_Data(&d), &l_OptionData.BGMVolume) == true) {
					war->Delete_Sound(&d);
				}
			}
		}

	}

	/*�f�o�b�O����*/
	/*if (StageNo != Co_Stage_Type_Debug)return true;*/

	//�t���[�����̑���

	if (GetAsyncKeyState('2') & 0x8000) {
		MaxCount += 1;
		if (MaxCount > 60)MaxCount = 60;
	}
	if (GetAsyncKeyState('3') & 0x8000) {
		MaxCount -= 1;
		if (MaxCount < 1)MaxCount = 1;
	}

	if (key.Num1_Key_F())judg.ReverseFlg(&M_S_Screen.DrawFlg);

	if (key.XKeyF() == true)player->SetHP(1);
	
	// �}�E�X�̍X�V����
	mouse->Update();

	// �t�F�[�h�̍X�V����
	if (fade.Update() == true) {
		//�L�[�̖��͉�
		key.SetFlg(true);
	}
	else {
		if (fade.GetMoveEndFlg() == true) {
			// �V�[���؂�ւ�
			sceneManager.changeScene(fade.GetNextScene());
			return false;
		}
	}

	Update_Game();

	//���j���[�̍X�V
	UpdateMenu();

	return true;
}

void GameScene::Init(void)
{
	// �I�v�V�����̃C���X�^���X��
	option = new C_Option();
	option->Read();

	// �t�F�[�h�C���̊J�n
	fade.StartFadein();

	Debug_Screen_Init();

	if (M_Text_Num == nullptr)M_Text_Num = new C_Text_Num();

	//�}�E�X�̏�����
	mouse = new C_Mouse();
	mouse->Init();
	mouse->ChaDrawFlg(false);

	//�v���C���[�̏������O�ɏ�����
	PlayerBody = new C_PlayerBody();

	player = new C_PlayerA(&PlayerBody->GetPData());

	//�n�ʏ�����--------------------------------------------------------

	groundManager = new c_GroundManager(player);
	eneFlg = true;

	//---------------------------------------------------------------------

	//�X�R�A�̏�����
	score = new C_Score();
	sky = new Sky();
	camera = new Camera(player->GetMatCar());
	aiming = new Aiming();
	debug = new Debug();
	eneFlg = false;//�G�̏o��OFF
	M_C_Game_End = new C_Game_End_Now();

	key.Init();

	war = new Warning();

	pause = new Pause();

	//BulletBirthFlg���ŏ��͏o�Ȃ��悤�ɂ���
	BulletBirthFlg = false;

	//�Ԃ̏o���̏�����
	M_C_Car_Pop = new C_Car_Pop_New(&StageNo);

	CountNum = MaxCount = 1;
	spear = new Spear();
	D3DXMatrixTranslation(&SpeMat, 0.0f, 0.0f, 0.0f);

	//�T�E���h�̏�����
	if (M_C_Sound_Manager == nullptr)M_C_Sound_Manager = new c_GameSoundManager();

	int No = 1, Volume = option->GetOptionData().BGMVolume;
	M_C_Sound_Manager->BGMStart(&No, &Volume);
}

bool GameScene::UpdateEnemy(void)
{
	//=======================================================================================================================
	//�G�l�~�[Update
	//=======================================================================================================================

	if (enemy.size() > 0) {
		//�n�ʔ���2
		for (unsigned int e = 0; e < enemy.size(); e++) {

			if (enemy[e]->GetFlgCar() != true) continue;

			//enemy�ƒn�ʔ���
			unsigned int num;
			float dis;
			if (groundManager->JudgNowGround(&num, &dis, enemy[e]->GetMatCar()) == true) {
				enemy[e]->SetGroNum(&num);
			}
			else {
				delete enemy[e];
				enemy.erase(enemy.begin() + e);
				e--;
			}
			
		}
		for (unsigned int e = 0; e < enemy.size(); e++) {
			EnemyDelete(&e);
		}
		for (unsigned int i = 0; i < enemy.size(); i++) {

			if (enemy[i]->GetDeleFlg() != false)continue;

			float L_Radius = 400.0f;

			if (judg.BallJudg(&judg.SetPosM(&enemy[i]->GetMatCar()), &judg.SetPosM(&player->GetMatCar()), &L_Radius) != false) continue;

			delete enemy[i];
			enemy.erase(enemy.begin() + i);
			i--;
			
		}
	}
	if (Get_End_Flg() == true) {
		return true;
	}

	return true;
}
void GameScene::SetCamera(void){
	D3DXMATRIX mView, mProj;
	D3DXMatrixLookAtLH(&mView,
		&camera->GetPos(),//�J�����̈ʒu
		&camera->GetLook(),// �J�����̎��_
		&D3DXVECTOR3(0.0f, 1.0f, 0.0f)	// �J�����̓��̕���
	);


	// ���e�s��̐ݒ�
	D3DXMatrixPerspectiveFovLH(&mProj, D3DXToRadian(60), (float)SCRW / (float)SCRH, 0.1f, 600.0f);

	//�s��ݒ�
	lpD3DDevice->SetTransform(D3DTS_VIEW, &mView);
	lpD3DDevice->SetTransform(D3DTS_PROJECTION, &mProj);

	//Pos2D�̂�������
	D3DVIEWPORT9 Viewport;
	lpD3DDevice->GetViewport(&Viewport);
	//Pos2D���g��
	Pos2DUpdate(&mProj, &mView, &Viewport);

	FrustumCulling(&mProj, &mView, &Viewport);

}

void GameScene::BulletJudg(const int * TypeCar, const unsigned int * No)
{
	BULLETJUDGDATA Bullet;

	RAYDATA BulletRay;

	float Dis,Rad=(float)RadJudgF;

	//�v���C���[�̒e����
	if (*TypeCar == co_PlayerCar) {
		if (player->Get_BulletNum() <= 0)return;

		for (unsigned int b = 0; b < player->Get_BulletNum(); b++) {
			//������
			Dis = player->Get_Bullet_MoveDis(&b);
			Bullet = GetInitBJD(&Dis);
			Bullet.Character_Type = co_PlayerCar;

			BulletRay.Mat = player->Get_Bullet_Mat(&b);
			D3DXVec3TransformNormal(&BulletRay.Ray, &D3DXVECTOR3(0.0f, 0.0f, 1.0f), &BulletRay.Mat);

			//�n��
			if (player->Get_Bullet_GroWal_Judg_Flg(&b) == true) {
				bool GroWalJudgFlg;
				if (groundManager != nullptr)groundManager->BulletJudg(&Bullet, &BulletRay,&GroWalJudgFlg,&Rad);
				//�����ǂƒn�ʂ𔻒�ł��邩�̑��
				player->Set_Bullet_GroWal_Judg_Flg(&b, &GroWalJudgFlg);
			}

			//�G
			BulletJudgEnemy(&Bullet, &BulletRay,&Rad,nullptr);
			//�G�̋��p�[�c����
			BulletJudgEnemy_Ball(&Bullet, &BulletRay, &Rad);
			//���茋�ʂƒe�̍폜
			if (SetBulletDamage(&Bullet, &BulletRay, player->Get_Bullet_Damage(&b)) == true)player->Delete_Bullet(&b);
		}
		//����I��
		return;
	}
	//�G�̒e����
	if (*TypeCar == co_EnemyCar) {
		if (enemy[*No]->Get_BulletNum() <= 0)return;

		for (unsigned int b = 0; b < enemy[*No]->Get_BulletNum(); b++) {
			//������
			Dis = enemy[*No]->Get_Bullet_MoveDis(&b);
			Bullet = GetInitBJD(&Dis);
			Bullet.Character_Type = co_EnemyCar;

			BulletRay.Mat = enemy[*No]->Get_Bullet_Mat(&b);
			D3DXVec3TransformNormal(&BulletRay.Ray, &D3DXVECTOR3(0.0f, 0.0f, 1.0f), &BulletRay.Mat);

			//�v���C���[
			BulletJudgPlayer(&Bullet, &BulletRay,&Rad);
			//�n��
			if (enemy[*No]->Get_Bullet_GroWal_Judg_Flg(&b) == true) {
				bool GroWalJudgFlg;
				if (groundManager != nullptr)groundManager->BulletJudg(&Bullet, &BulletRay, &GroWalJudgFlg, &Rad);
				//�����ǂƒn�ʂ𔻒�ł��邩�̑��
				enemy[*No]->Set_Bullet_GroWal_Judg_Flg(&b, &GroWalJudgFlg);
			}
			//�G
			BulletJudgEnemy(&Bullet, &BulletRay, &Rad,No);
			//���茋�ʂƒe�̍폜
			if (SetBulletDamage(&Bullet, &BulletRay, enemy[*No]->Get_Bullet_Damage(&b)) == true)enemy[*No]->Delete_Bullet(&b);
		}
		//����I��
		return;
	}

}

void GameScene::Side_Judg(const int * Car_Type, const unsigned int * Car_No)
{
	//��
	bool Left_Flg = true;
	Side_Judg(&Left_Flg, Car_Type, Car_No);

	//�E
	Left_Flg = false;
	Side_Judg(&Left_Flg, Car_Type, Car_No);
}

bool GameScene::Side_Judg(const bool * Left_Flg, const int * Car_Type, const unsigned int * Car_No)
{
	//���肷��Ԃ̏��
	S_SideJudgChara Judg_Car;
	Judg_Car.LeftFlg = *Left_Flg;
	Judg_Car.Car_Type = *Car_Type;
	if (Car_No !=nullptr) Judg_Car.No = *Car_No;

	//�Ԃ̔���̃��C�̐�(�O�A���ԁA��)
	int L_JudgNum = 3;

	//
	D3DXMATRIX *L_JudgMat = new D3DXMATRIX[L_JudgNum];

	//�����������C�̔ԍ�
	int Ray_Hit_No;

	//���������s��
	D3DXMATRIX Ray_Hit_Mat;

	//�ǂɓ������Ă���ΉԂ��o���Ȃ�Flg
	bool Spark_Init_Flg = true;

	//20��܂ŉ����肷��
	for (int f_c = 0; f_c < 20;f_c++) {

		/*����̏���*/

		//���ɔ��肷��Ԃ̏��
		S_SideJudgChara Next_Car;

		Next_Car.JudgeType = Co_Judge_YES;

		//����p���C
		D3DXVECTOR3 JudgVec;

		//���C�����trueCar��
		int CountCar = 0;

		//����p���C�̋����A�ǂ��o���p�̃��C�̒���
		float SmallDis,L_Over_Dis;

		//�Ԃ̒ǂ��o������̊m�F
		bool L_OverFlg = false;

		//���C����̏������ł��Ȃ������ꍇ�A���̏Փ˔�����I��������
		if (SideJudg_Preparation(&Judg_Car, L_JudgMat, &JudgVec, &SmallDis,&L_Over_Dis, &L_JudgNum) != true)break;


		/*���C����*/

		//player����
		CountCar += Side_Judg_Player(&Next_Car, &SmallDis, &Ray_Hit_No, &Ray_Hit_Mat,
			&L_Over_Dis, &L_OverFlg, &Judg_Car, &L_JudgNum, L_JudgMat, &JudgVec);

		//enemy����
		CountCar += Side_Judg_Enemy(&Next_Car, &SmallDis, &Ray_Hit_No, &Ray_Hit_Mat,
			&L_Over_Dis, &L_OverFlg, &Judg_Car, &L_JudgNum, L_JudgMat, &JudgVec);

		//�ǔ���
		float L_Radius = (float)RadJudgF;
		bool WallJudgFlg = groundManager->SideJudg(&Judg_Car, &L_JudgMat[Const_Middle], &JudgVec,
			&SmallDis, &Ray_Hit_No, &Ray_Hit_Mat,&L_Radius);


		/*���C�����̏���*/

		//�S�Ẵ��C����I����
		//����Ȃ������̌v�Z
		float RadDis = Judg_Car.Rad;
		if (RadDis < 0.0f)RadDis *= -1.0f;
		if ((L_OverFlg == true) && (WallJudgFlg != true) && (CountCar < 2))SmallDis = L_Over_Dis;
		RadDis = RadDis - SmallDis;
		//���Ε����ɂ���
		if (Judg_Car.LeftFlg == false) RadDis *= -1.0f;
		//�������蔻�肵�Ă���Ԃ����炷
		D3DXMATRIX Trans2;
		D3DXMatrixTranslation(&Trans2, RadDis, 0.0f, 0.0f);
		//���f�p�s��
		D3DXMATRIX TmpMat;

		//�ǂɓ���������
		if (WallJudgFlg == true) {
			switch (Judg_Car.Car_Type)
			{
			case Hit_Type_Player:
				TmpMat = Trans2 * (player->GetTransMatCar());
				player->SetTransMatCar(&TmpMat);
				TmpMat = player->GetTransMatCar()*player->GetCon().JudgMat;
				player->SetMatCar(&TmpMat);
				break;
			case Hit_Type_Enemy:
				TmpMat = Trans2 * (enemy[Judg_Car.No]->GetTransMatCar());
				enemy[Judg_Car.No]->SetTransMatCar(&TmpMat);
				TmpMat = enemy[Judg_Car.No]->GetTransMatCar()*enemy[Judg_Car.No]->GetCon().JudgMat;
				enemy[Judg_Car.No]->SetMatCar(&TmpMat);
				//Hp����鏈��
				if (Spark_Init_Flg == true) {
					enemy[Judg_Car.No]->SetHP(1, true);
					unsigned int eNo = Judg_Car.No;
					EnemyDelete(&eNo);
				}
				break;
			}


			//���C�̍��W
			D3DXVECTOR3 Ray_Pos = judg.SetPosM(&L_JudgMat[Ray_Hit_No]) + JudgVec * (SmallDis - 0.1f);

			//�ΉԂ��o������
			Wall_Spark_Init(&Spark_Init_Flg, &Ray_Hit_Mat, &Ray_Pos, &Judg_Car.LeftFlg);

			continue;
		}
		
		//�����ɓ����������A�������͓��������Ԃ��{�X�������ꍇ
		if ((CountCar >= 2)||(Next_Car.JudgeType==Co_Judge_BOSS)) {
			//�������蔻�肵�Ă����
			switch (Judg_Car.Car_Type)
			{
			case Hit_Type_Player:
				TmpMat = Trans2 * (player->GetTransMatCar());
				player->SetTransMatCar(&TmpMat);
				TmpMat = player->GetTransMatCar()*player->GetCon().JudgMat;
				player->SetMatCar(&TmpMat);
				break;
			case Hit_Type_Enemy:
				TmpMat = Trans2 * (enemy[Judg_Car.No]->GetTransMatCar());
				enemy[Judg_Car.No]->SetTransMatCar(&TmpMat);
				TmpMat = enemy[Judg_Car.No]->GetTransMatCar()*enemy[Judg_Car.No]->GetCon().JudgMat;
				enemy[Judg_Car.No]->SetMatCar(&TmpMat);
				break;
			}
			//���o�[�X
			judg.ReverseFlg(&Judg_Car.LeftFlg);

			continue;
		}

		//�{�f�B���Ń��C���肵���ꍇ�̏���
		if (L_OverFlg == true) {

			//�����o��
			D3DXMatrixTranslation(&Trans2, RadDis*-1.0f, 0.0f, 0.0f);

			//�������蔻�肵�Ă����
			switch (Judg_Car.Car_Type)
			{
			case Hit_Type_Player:
				TmpMat = Trans2 * (player->GetTransMatCar());
				player->SetTransMatCar(&TmpMat);
				TmpMat = player->GetTransMatCar()*player->GetCon().JudgMat;
				player->SetMatCar(&TmpMat);
				break;
			case Hit_Type_Enemy:
				TmpMat = Trans2 * (enemy[Judg_Car.No]->GetTransMatCar());
				enemy[Judg_Car.No]->SetTransMatCar(&TmpMat);
				TmpMat = enemy[Judg_Car.No]->GetTransMatCar()*enemy[Judg_Car.No]->GetCon().JudgMat;
				enemy[Judg_Car.No]->SetMatCar(&TmpMat);
				break;
			}
			continue;
		}
			
		//1�Ԃ̂ݓ���������
		if (CountCar == 1) {
			//�����o��
			D3DXMatrixTranslation(&Trans2, RadDis*-1.0f, 0.0f, 0.0f);
			//���������Ԕ���
			Judg_Car.Car_Type = Next_Car.Car_Type;
			Judg_Car.No = Next_Car.No;

			//����������
			switch (Judg_Car.Car_Type)
			{
			case Hit_Type_Player://�v���C���[
				TmpMat = Trans2 * (player->GetTransMatCar());
				player->SetTransMatCar(&TmpMat);
				TmpMat = player->GetTransMatCar()*player->GetCon().JudgMat;
				player->SetMatCar(&TmpMat);
				//Hp����鏈��
				/*if (Spark_Init_Flg==true) {
					player->SetHP(1,true);
				}*/
				break;
			case Hit_Type_Enemy://�G
				enemy[Judg_Car.No]->SetTransMatCar(&judg.GetMatY(&Trans2, &enemy[Judg_Car.No]->GetTransMatCar()));
				TmpMat = enemy[Judg_Car.No]->GetCon().JudgMat;
				enemy[Judg_Car.No]->SetMatCar(&judg.GetMatY(&enemy[Judg_Car.No]->GetTransMatCar(), &TmpMat));

				//�Փ˂ɂ��G��Ai�Əe��Stop������
				Enemy_Stop(&Judg_Car.No, Car_Type);

				//Hp����鏈��
				if (Spark_Init_Flg == true) {
					enemy[Judg_Car.No]->SetHP(1, true);
					unsigned int eNo = Judg_Car.No;
					EnemyDelete(&eNo);
				}

				break;

			}

			//���C�̍��W
			D3DXVECTOR3 Ray_Pos = judg.SetPosM(&L_JudgMat[Ray_Hit_No]) + JudgVec * (SmallDis - 0.1f);

			//�ΉԂ��o���锻��
			Car_Spark_Init(&Spark_Init_Flg, &Ray_Hit_Mat, &Ray_Pos);

			continue;
		}
				
		//�������Ă��Ȃ���
		break;
		
	}

	//���
	if (L_JudgMat != nullptr)delete[] L_JudgMat;

	return true;
	
}

bool GameScene::UpdateEnemyAI(void)
{
	//�G�l�~�[�̏o��
	Pop_Enemy();

	//�o�����Ă���G�̐����[���̏ꍇ�ɒn�ʔ�������Ȃ�
	if (enemy.size() <= 0) return false;

	//�n�ʔ���
	for (unsigned int e = 0; e < enemy.size(); e++) {
		//enemy�ƒn�ʔ���
		unsigned int num;
		float dis;
		if (groundManager->JudgNowGround(&num, &dis, enemy[e]->GetMatCar()) == true) {
			enemy[e]->SetGroNum(&num);
		}
		else {
			if (Get_End_Flg() == true) {
				delete enemy[e];
				enemy.erase(enemy.begin() + e);
				e--;
			}
		}
	}

	//�o�����Ă���G�̐����[���̏ꍇ��AI�̏��������Ȃ�
	if (enemy.size() <= 0) return false;

	/*Ai�̓��쏀��*/

	//�v���C���[���̏��̍쐬
	CHARAData*Data;
	int ChaNum = 0;
	ChaNum += 1;
	Data = new CHARAData[ChaNum];
	Data[0] = player->GetData();

	/*Ai�̓��쏈��*/

	for (unsigned int i = 0; i < enemy.size(); i++) {

		//�S�Ă̐퓬�I��Flg
		bool L_EndFlg = Get_End_Flg();

		//Ai�̓��쏈��
		enemy[i]->UpdateAi(Data, &ChaNum,&L_EndFlg);

	}

	//���̍폜
	if (Data != nullptr)delete Data;

	return true;
}

bool GameScene::UpdateEnemyMove(void)
{
	if (enemy.size() <= 0) return false;

	float L_ResetSize = 1.0f;

	for (unsigned int i = 0; i < enemy.size(); i++) {
		enemy[i]->UpdateAll(groundManager->GetGround());//Update
		//�ړ��x�N�g���̃T�C�Y�̏�����
		enemy[i]->SetQuaVecSize(&L_ResetSize);
	}

	return false;
}

bool GameScene::ForMoveJudg(const CONSTITUTION * Con, const D3DXMATRIX * StartMat, const D3DXMATRIX * EndMat,
	const int * Car_Type, const unsigned int * Car_No, const D3DXVECTOR3 * RayVec1, const D3DXVECTOR3 * RayVec2,
	const D3DXVECTOR3 * RayVec3, float * SpeedMul2, const D3DXVECTOR3 * ScalPos, const bool *CollisionJudg_TrueFlg)
{
	//�Ԃ�vector�i���o�[
	unsigned int L_Car_No = 0;

	if (Car_No != nullptr)L_Car_No = *Car_No;

	int VecNum = 3;

	D3DXVECTOR3 *MoveVec = new D3DXVECTOR3[VecNum];//�ړ��x�N�g��
	float *VecSize = new float[VecNum];//�x�N�g���̒���

	MoveVec[0] = *RayVec1;
	MoveVec[1] = *RayVec2;
	MoveVec[2] = *RayVec3;

	for (int i = 0; i < VecNum; i++) {
		VecSize[i] = D3DXVec3Length(&MoveVec[i]);
		if (VecSize[i] < 0.0f)VecSize[i] *= -1.0f;
		VecSize[i] += 0.1f;
		D3DXVec3Normalize(&MoveVec[i], &MoveVec[i]);//�ړ��x�N�g���̐��K��
	}

	//�^�񒆂ƃT�C�h�̃��C���ˈʒu
	D3DXMATRIX *TransMat=new D3DXMATRIX[VecNum];

	TransMat[0] = judg.GetTransMatScal(&D3DXVECTOR3(Con->PosSmall.x, 0.0f, Con->PosBig.z), ScalPos);
	TransMat[1] = judg.GetTransMatScal(&D3DXVECTOR3(Con->PosBig.x, 0.0f, Con->PosBig.z), ScalPos);
	TransMat[2] = judg.GetTransMatScal(&D3DXVECTOR3(0.0f, 0.0f, Con->PosBig.z), ScalPos);

	TransMat[0] = TransMat[0] * (*StartMat);
	TransMat[1] = TransMat[1] * (*StartMat);
	TransMat[2] = TransMat[2] * (*StartMat);

	//���C�̒����ƍŏ�
	float Dis, *SmallDis = new float[VecNum];

	for (int i = 0; i < VecNum; i++) SmallDis[i] = VecSize[i];

	bool *JudgFlg = new bool[VecNum];

	for (int i = 0; i < VecNum; i++) JudgFlg[i] = false;

	int L_Hit_CarType;
	unsigned int L_Hit_CarNumber;

	//player����
	M_ForMoveJudg_Player(JudgFlg, SmallDis, &L_Hit_CarType, &L_Hit_CarNumber, Car_Type, StartMat,
		EndMat, TransMat, &VecNum, MoveVec,&Con->PosBig, &Con->PosSmall, ScalPos, CollisionJudg_TrueFlg);

	//�G����
	M_ForMoveJudg_Enemy(JudgFlg, SmallDis, &L_Hit_CarType, &L_Hit_CarNumber, Car_Type, &L_Car_No, StartMat,
		EndMat, TransMat, &VecNum, MoveVec, &Con->PosBig, &Con->PosSmall, ScalPos, CollisionJudg_TrueFlg);
	
	//���C����������
	if ((JudgFlg[0] == true) || (JudgFlg[1] == true) || (JudgFlg[2] == true)) {
		for (int i = 0; i < VecNum; i++) {
			SmallDis[i] = (VecSize[i]) / (VecSize[1])*((SmallDis[i]) / (VecSize[i]));
		}
		if (JudgFlg[0] == true) {
			Dis = SmallDis[0];
			if (JudgFlg[1] == true) {
				if (Dis > SmallDis[1])Dis = SmallDis[1];
			}
			if (JudgFlg[2] == true) {
				if (Dis > SmallDis[2])Dis = SmallDis[2];
			}
		}
		else {
			if (JudgFlg[1] == true) {
				Dis = SmallDis[1];
				if (JudgFlg[2] == true) {
					if (Dis > SmallDis[2])Dis = SmallDis[2];
				}
			}
			else {
				Dis = SmallDis[2];
			}
		}
		*SpeedMul2 = *SpeedMul2*Dis;
		if (*SpeedMul2 > 1.0f)*SpeedMul2 = 1.0f;
		/*if ((SmallDis - Con.PosBig.z) < (VecSize - Con.PosBig.z)) {
			float ESize;
			ESize = (SmallDis - Con.PosBig.z - 0.01f) / (VecSize - Con.PosBig.z);
			*SpeedMul2 = *SpeedMul2*ESize;
		}*/


		//�Փ˂����Ԃ̎��S�m�F
		if (Get_Dead_Flg(&L_Hit_CarType, &L_Hit_CarNumber) == true) {

			//���肵�Ă�Ԃ����S������
			M_Dead_Car(Car_Type, &L_Car_No);

		}


	}

	/*�������̉��*/

	if (TransMat != nullptr)delete[] TransMat;

	if (MoveVec != nullptr)delete[] MoveVec;

	if (VecSize != nullptr)delete[] VecSize;

	if (SmallDis != nullptr)delete[] SmallDis;

	if (JudgFlg != nullptr)delete[] JudgFlg;

	return true;
}

void GameScene::ForMoveEnd(D3DXMATRIX * Mat, const CONSTITUTION * Con, const QuaForMove * q, const D3DXMATRIX * TransMat)
{
	QuaForMove  L_q = *q;

	motion.Formove(&L_q, Con, groundManager->GetGround());

	*Mat = *TransMat * L_q.NowMat;
}

bool GameScene::GetBulletBirthFlg(void)
{
	if (Get_End_Flg() == true)return false;
	if ((key.LClickF_N() == true) && (BulletBirthFlg == false))return false;
	return true;
}

void GameScene::BombInit(const D3DXMATRIX * Mat)
{
	effect.push_back(new c_Explosion3D(Mat));
	New_Sound(&Co_Sound_Category_Explosion, 1, &judg.SetPosM(Mat), &Co_SoundNew);
	return;
}

bool GameScene::EnemyDelete(const unsigned int * EnemyNo)
{
	if ((*EnemyNo < 0) || (*EnemyNo > enemy.size() - 1))return false;

	if (enemy[*EnemyNo]->GetFlgCar() == false) {
		if (enemy[*EnemyNo]->GetDeadFlg() == false) {
			enemy[*EnemyNo]->SetDeadFlg(true);

			//���S�����G���{�X�Ȃ瑼�̓G��HP���[���ɂ���
			if ((enemy[*EnemyNo]->Get_BossFlg() == true) && (enemy.size() > 0)) {
				int L_Hp = 0;
				for (auto && e : enemy)e->SetNowHp(&L_Hp);
			}

			BombInit(&enemy[*EnemyNo]->GetMatCar());
			int sc = 1000;
			score->ScoreUp(&sc);
			return true;
		}
	}
	return false;
}

void GameScene::SetMenu(bool PauseFlg, bool ClearFlg, bool OverFlg)
{
	//�|�[�Y------------------------------------
	if (PauseFlg == true) {
		
		if (Menu != nullptr)delete Menu;

		Menu=new C_PauseTouch();
		return;
	}
	//�X�e�[�W�N���A---------------------------------------
	if (ClearFlg == true) {
		
		if (Menu != nullptr)delete Menu;

		Menu = new C_ClearTouch();
		return;
	}
	//�Q�[���I�[�o�[---------------------------------------
	if (OverFlg == true) {
		
		if (Menu != nullptr)delete Menu;

		Menu = new C_OverTouch();
		return;
	}

	return;
}

bool GameScene::UpdateMenu(void)
{
	if (Menu==nullptr)return false;

	int Touch = Menu->Touch();

	if (Touch > 0) {
		//mouse->SetTouchFlg();
	}
	else {
		return false;
	}

	if (fade.GetMoveFlg() != false)return false;

	if (key.LClickF() != true)return false;

	// �^�C�g��������������
	if (Touch == co_TitleScene) {
		fade.SetNextScene(co_TitleScene, true);
		return true;
	}

	// �Z���N�g����������
	if (Touch == co_StageSelectScene) {
		fade.SetNextScene(co_StageSelectScene, true);
		return true;
	}

	// ���g���C������������
	if (Touch == co_GameScene) {
		bool DebugFlg = false;
		if (StageNo == Co_Stage_Type_Debug)DebugFlg = true;
		fade.SetNextStageNo(StageNo);
		fade.SetNextStageNo(&DebugFlg);
		fade.SetNextScene(co_GameScene, true);
		return true;
	}

	// �v���C����������
	if (Touch == co_PlayGame) {
		pause->SetDFlg(false);
		mouse->Init();
		mouse->ChaDrawFlg(false);
		pause->SetStaSavFlg(false);
		if (M_C_Sound_Manager != nullptr) {

			S_OptionData l_OptionData = option->GetOptionData();

			M_C_Sound_Manager->Restart(&l_OptionData.BGMVolume);
		}

		//���j���[�폜
		if (Menu != nullptr)delete Menu;
		Menu = new C_NextTouch();

		return true;
	}

	return true;
}

void GameScene::Pos2DUpdate(const D3DXMATRIX * mProj, const D3DXMATRIX * mView, const D3DVIEWPORT9 * Viewport)
{

	if (M_Damage_Num_Draw.size() > 0) {
		D3DXVECTOR3 Pos3D,Pos2D;
		Judg L_judg;
		for (auto && v : M_Damage_Num_Draw) {

			D3DXMATRIX L_JudgMat = player->GetCon().JudgMat;

			Pos3D = v->Get_Pos_3D(&L_JudgMat);
			L_judg.Pos2D(&Pos2D, &Pos3D, mProj, mView, Viewport);
			v->Set_Pos_2D(&Pos2D);
		}
	}

	if (enemy.size() <= 0)return;
	for (unsigned int e = 0; e < enemy.size(); e++) {
		//���v�Z
		enemy[e]->GetPos2DSet(mProj, mView, Viewport,&camera->GetPos());
	}
}

bool GameScene::Change_TitleScene(void)
{
	if (key.EscapeKey_F() == true) {
		sceneManager.changeScene(new TitleScene());
		return false;
	}
	return true;
}

bool GameScene::Update_Game(void)
{
	//�|�[�Y
	if (pause->GetDFlg() != false)return true;

	//�|�[�Y��ʂɈړ��̏���
	if (Update_Game_Pause() != true)return true;

	if (Judg_Game_Frame() != true)return true;
	
	if (groundManager != nullptr)groundManager->Update(player);

	//�Ԃ̏��̍X�V
	if (M_C_Car_Pop != nullptr) {
		bool MoveFlg = Get_Car_Pop_Update_MoveFlg();
		M_C_Car_Pop->Update(&MoveFlg);
	}

	//========================================
	//�v���C���[
	//========================================

	Update_Car_SetMat();

	//�J����-------------------------------------
	if (Get_End_Flg() == false) {
		if (fade.GetMoveFlg() == false) {
			camera->UpdateM(true, mouse);
		}
		else {
			mouse->Init();
		}
	}
	//�J�����������
	camera->RotXJudg(&player->GetMatCar());

	//�v���C���[�ƒn�ʔ���
	float Dis;
	unsigned int num;
	if (groundManager->JudgNowGround(&num, &Dis, player->GetMatCar()) == true) {
		player->SetGroNum(&num);//�n�ʂ̎擾
		eneFlg = true;//�G�̏o���J�n
	}
	//�G
	UpdateEnemyAI();

	//�v���C���[�̉��ړ�����
	Update_Player_XTrans();

	//�O�i����
	Update_Car_ForMove();


	//player======================================================================
	//player�̈ړ�
	player->UpdateCarFM(groundManager->GetGround());

	float L_ResetSize = 1.0f;

	//�ړ��x�N�g���̃T�C�Y�̏�����
	player->SetQuaVecSize(&L_ResetSize);
	//�G�̈ړ�
	UpdateEnemyMove();

	//������
	Update_Car_SideJudg();

	//�ŏIUpdate
	//player->SetParts(camera->GetAngX(),camera->GetAngY());
	if (enemy.size() > 0) {
		for (unsigned int e = 0; e < enemy.size(); e++) {
			//if (enemy[e]->GetFlgCar() == true) {
				enemy[e]->SetParts(groundManager->GetGround());
			//}
		}
	}

	//�J�����̑O���Ɍ�������
	Update_Camera_Car();
	//�J�����̃N�H�[�^�j�I���̃A�b�v�f�[�g
	camera->UpdateQua();

	//�J�[�u�̎ԑ̂̊p�x�𔽉f
	player->SetCurRotMat();

	//�J�����s��̎擾
	Update_CameraMat();

	//player�̃p�[�c�ړ�
	Update_Player();

	//�J�����̃A�b�v�f�[�g
	unsigned int i = 0;
	D3DXMATRIX Mat = player->Get_Camera_Mat();
	camera->Update(Mat);

	//�J�����ƕǔ���
	int RadF = RadJudgF;
	camera->WallJudg(&RadF, groundManager);

	//�v���C���[�ƒn�ʔ���2
	if (groundManager->JudgNowGround(&num, &Dis, player->GetMatCar()) == true) {
		player->SetGroNum(&num);//�n�ʂ̎擾
		eneFlg = true;//�G�̏o���J�n
	}

	//--------------------------------------------
	//�Ԃ̓���������̏���
	//--------------------------------------------

	Update_Bullet();

	//================================================================================
	// �G
	//================================================================================
	if (UpdateEnemy() == false) {
		if (Get_End_Flg() == false) {
			Geme_End_Change(&Co_Stage_End_Clear);
			SetMenu(false, true, false);
		}
	}

	// ��
	sky->Update(&player->GetMatCar());

	Update_Damage_Num_Draw();

	war->Update();

	if (effect.size() > 0) 
	{
		for (unsigned int ec = 0; ec < effect.size(); ec++) 
		{
			if (effect[ec]->Update()!=true) 
			{
				delete effect[ec];
				effect.erase(effect.begin() + ec);
				ec--;
			}
		}
	}

	Update_Pop_End();

	return true;
}

bool GameScene::Update_Game_Pause(void)
{
	//�I�������
	if (Get_End_Flg() == true) {
		mouse->ChaDrawFlg(true);
	}
	else {
		//�|�[�Y
		if (key.RETURNKeyF() == true) {
			if (pause->GetDFlg() == false) {
				pause->SetDFlg(true);
				mouse->ChaDrawFlg(true);
				//���[�h�̋���
				if ((GetAsyncKeyState('8') & 0x8000) && (GetAsyncKeyState('9') & 0x8000) && (GetAsyncKeyState('0') & 0x8000)) {
					pause->SetStaSavFlg(true);
				}
				SetMenu(true, false, false);

				if (M_C_Sound_Manager != nullptr) {
					M_C_Sound_Manager->Stop();
				}

				return false;
			}
		}
	}

	return true;
}

bool GameScene::Judg_Game_Frame(void)
{
	//�X���[�Đ�
	if (CountNum >= MaxCount) {
		CountNum = 1;
		return true;
	}
	else {
		CountNum += 1;
	}
	return false;
}

bool GameScene::Update_Camera_Car(void)
{
	//�J������plaeyr�̑O���ɐU���������N�H�[�^�j�I���̏�����
	if (Get_End_Flg() != false) return false;
	//�O���ɐU������v�Z
	if ((key.RClickF() != true) || (camera->GetQuaFlg() != false))return false;

	D3DXVECTOR3 cVec, ccVec, pVec, ppVec;
	D3DXVec3TransformNormal(&cVec, &D3DXVECTOR3(0.0f, 0.0f, 1.0f), &camera->GetMat());
	D3DXVec3TransformNormal(&pVec, &D3DXVECTOR3(0.0f, 0.0f, 1.0f), &player->GetMatCar());
	ccVec = cVec;
	ppVec = pVec;

	float Dot, Ang, FrameUp;

	//�N�H�[�^�j�I���̃t���[�������v�Z
	Dot = D3DXVec3Dot(&pVec, &cVec);
	if (Dot > 1.0f)Dot = 1.0f;
	if (Dot < -1.0f)Dot = -1.0f;
	Ang = D3DXToDegree(acos(Dot));
	FrameUp = 1.0f / Ang * 6.0f;

	//RotY�̌v�Z
	D3DXMATRIX CamRotY, CamRotX;
	ppVec.y = 0;

	//����
	Dot = D3DXVec3Dot(&D3DXVECTOR3(0.0f, 0.0f, 1.0f), &ppVec);
	if (Dot > 1.0f)Dot = 1.0f;
	if (Dot < -1.0f)Dot = -1.0f;
	Ang = D3DXToDegree(acos(Dot));
	if (ppVec.x < 0.0f)Ang *= -1.0f;
	D3DXMatrixRotationY(&CamRotY, D3DXToRadian(Ang));
	//camera->SetRotY(&CamRotY);


	//RotX�̌v�Z
	D3DXMATRIX Mat = player->GetMatCar();
	D3DXMatrixRotationY(&CamRotX, D3DXToRadian(-Ang));
	Mat = CamRotX * Mat;
	D3DXVec3TransformNormal(&pVec, &D3DXVECTOR3(0.0f, 0.0f, 1.0f), &Mat);
	//����
	Dot = D3DXVec3Dot(&D3DXVECTOR3(0.0f, 0.0f, 1.0f), &pVec);
	if (Dot > 1.0f)Dot = 1.0f;
	if (Dot < -1.0f)Dot = -1.0f;
	Ang = D3DXToDegree(acos(Dot));
	if (pVec.y > 0.0f)Ang *= -1.0f;
	D3DXMatrixRotationX(&CamRotX, D3DXToRadian(Ang));
	//camera->SetRotX(&CamRotX);

	//�N�H�[�^�j�I���̏����l���Z�b�g
	camera->SetQuaMat(&CamRotX, &CamRotY, &FrameUp);

	return true;
}

bool GameScene::Update_Player_Bullet(void)
{
	//�Ə��̃��C����
	S_RAY_HIT_JUDG_DATA Hit_Data;
	Hit_Data.Flg = false;

	BULLETJUDGDATA l_DisD;
	float Dis = 2000.0f;
	l_DisD = GetInitBJD(&Dis);
	RAYDATA l_RayR;
	l_RayR.Mat = judg.SetMatP(&camera->GetPos());
	l_RayR.Ray = camera->GetVec();
	float Rad = 400.0f;
	//�G�̃��C����
	unsigned int EnemyNo = -1;
	BulletJudgEnemy(&l_DisD, &l_RayR, &Rad,&EnemyNo);
	if (l_DisD.Type > 0)Hit_Data.Flg = true;
	//�Ə��̕ω�
	if (Hit_Data.Flg == true) {
		aiming->ChaFlg();
	}
	else {
		aiming->ResFlg();
	}
	//�n��
	if(groundManager!=nullptr)groundManager->BulletJudg(&l_DisD, &l_RayR, nullptr, &Rad);
	if (l_DisD.Type > 0)Hit_Data.Flg = true;
	//�����̃��C����
	//�o���b�g�̏o������
	if (Hit_Data.Flg == false) {
		player->Set_Gun_Ray_Data(&Hit_Data);
	}
	else {

		//���C�������������W
		D3DXVECTOR3 Ray_Hit_Pos;

		//���C�������������W�����߂�
		judg.Get_Ray_Pos3D(&Ray_Hit_Pos, &camera->GetPos(), &l_RayR.Ray, &l_DisD.SamllDis);

		//���C�������������W���s��ɕϊ�
		Hit_Data.Mat = judg.SetMatP(&Ray_Hit_Pos);

		player->Set_Gun_Ray_Data(&Hit_Data);
	}

	bool T_Flg = false;
	if (key.LClickF_N() == true) {
		T_Flg = true;
	}
	unsigned int GunNo = 0;

	player->Set_Gun_Trigger(&GunNo, &T_Flg);

	return true;
}

bool GameScene::Update_Car_ForMove(void)
{
	/*�ړ���̍쐬*/

	//�ړ���̕ϐ�
	D3DXMATRIX EndMat;
	D3DXVECTOR3 EndPos;

	//player
	//�ړ���̍s��쐬
	ForMoveEnd(&EndMat, &player->GetCon(), &player->GetQuaForMove(), &player->GetTransMatCar());
	player->SetForMoveEndMat(&EndMat);
	//�ړ��x�N�g���v�Z
	D3DXMATRIX TransMat1, TransMat2, Trans;//�����̃��C���ˈʒu
	D3DXVECTOR3 ScalPosB = player->GetScalPosCar();
	TransMat1 = judg.GetTransMatScal(&D3DXVECTOR3(player->GetCon().PosSmall.x, 0.0f, player->GetCon().PosBig.z), &ScalPosB);
	TransMat2 = judg.GetTransMatScal(&D3DXVECTOR3(player->GetCon().PosBig.x, 0.0f, player->GetCon().PosBig.z), &ScalPosB);
	Trans = judg.GetTransMatScal(&D3DXVECTOR3(0.0f, 0.0f, player->GetCon().PosBig.z), &ScalPosB);
	player->SetForMoveVec(&judg.MatMatVec(TransMat1*player->GetMatCar(), TransMat1*player->GetForMoveEndMat()), &Const_Left);
	player->SetForMoveVec(&judg.MatMatVec(Trans*player->GetMatCar(), Trans*player->GetForMoveEndMat()), &Const_Middle);
	player->SetForMoveVec(&judg.MatMatVec(TransMat2*player->GetMatCar(), TransMat2*player->GetForMoveEndMat()), &Const_Right);

	//enemy
	if (enemy.size() > 0) {//enemy�̑��݊m�F
		//enemy�̐�
		for (unsigned int e = 0; e < enemy.size(); e++) {
			//�ړ���̍s��쐬
			ForMoveEnd(&EndMat, &enemy[e]->GetCon(), &enemy[e]->GetQuaForMove(), &enemy[e]->GetTransMatCar());
			enemy[e]->SetForMoveEndMat(&EndMat);
			//�ړ��x�N�g���v�Z
			D3DXMATRIX TransMat1, TransMat2, Trans;//�����̃��C���ˈʒu
			ScalPosB = enemy[e]->GetScalPosCar();

			TransMat1 = judg.GetTransMatScal(&D3DXVECTOR3(enemy[e]->GetCon().PosSmall.x, 0.0f, enemy[e]->GetCon().PosBig.z), &ScalPosB);
			TransMat2 = judg.GetTransMatScal(&D3DXVECTOR3(enemy[e]->GetCon().PosBig.x, 0.0f, enemy[e]->GetCon().PosBig.z), &ScalPosB);
			Trans = judg.GetTransMatScal(&D3DXVECTOR3(0.0f, 0.0f, enemy[e]->GetCon().PosBig.z), &ScalPosB);

			enemy[e]->SetForMoveVec(&judg.MatMatVec(TransMat1*enemy[e]->GetMatCar(), TransMat1*enemy[e]->GetForMoveEndMat()), &Const_Left);
			enemy[e]->SetForMoveVec(&judg.MatMatVec(Trans*enemy[e]->GetMatCar(), Trans*enemy[e]->GetForMoveEndMat()), &Const_Middle);
			enemy[e]->SetForMoveVec(&judg.MatMatVec(TransMat2*enemy[e]->GetMatCar(), TransMat2*enemy[e]->GetForMoveEndMat()), &Const_Right);

		}
	}
	/*�ړ���̍쐬����*/


	/*�����蔻��*/

	//�ړ��x�N�g���̃T�C�Y
	float Mul;
	//�����蔻��̉�
	int MaxJudg = 2;
	//�����蔻���MaxJudg��J��Ԃ�
	for (int i = 0; i < MaxJudg; i++) {

		//player
		//player��Vec�T�C�Y
		Mul = player->GetQuaForMove().SpeedMulJudg;

		bool L_CollisionJudg_TrueFlg = player->Get_CollisionJudg_TrueFlg();

		//����
		ForMoveJudg(&player->GetCon(), &player->GetDrawMatCar(), &player->GetForMoveEndMat(),&Hit_Type_Player,nullptr,
			&player->GetForMoveVec(&Const_Left), &player->GetForMoveVec(&Const_Middle), &player->GetForMoveVec(&Const_Right), &Mul,
			&player->GetScalPosCar(),&L_CollisionJudg_TrueFlg);
		//Mul��{�̂ɓ����
		player->SetQuaVecSize(&Mul);
		//�Ō�̌J��Ԃ��ȊO
		if (i != MaxJudg - 1) {
			//�V�����ړ�����쐬
			ForMoveEnd(&EndMat, &player->GetCon(), &player->GetQuaForMove(), &player->GetTransMatCar());
			player->SetForMoveEndMat(&EndMat);

			float L_ResetSize = 1.0f;

			//Mul�̏�����
			player->SetQuaVecSize(&L_ResetSize);
		}

		//enemy
		if (enemy.size() > 0) {
			for (unsigned int e = 0; e < enemy.size(); e++) {

				if (enemy[e]->Get_JudgeType() == Co_Judge_NO)continue;

				//enemy��Vec�T�C�Y
				Mul = enemy[e]->GetQuaForMove().SpeedMulJudg;

				L_CollisionJudg_TrueFlg = enemy[e]->Get_CollisionJudg_TrueFlg();

				//����
				ForMoveJudg(&enemy[e]->GetCon(), &enemy[e]->GetMatCar(), &enemy[e]->GetForMoveEndMat(), &Hit_Type_Enemy, &e,
					&enemy[e]->GetForMoveVec(&Const_Left), &enemy[e]->GetForMoveVec(&Const_Middle), &enemy[e]->GetForMoveVec(&Const_Right), &Mul,
					&enemy[e]->GetScalPosCar(),&L_CollisionJudg_TrueFlg);
				//Mul��{�̂ɓ����
				enemy[e]->SetQuaVecSize(&Mul);
				//�Ō�̌J��Ԃ��ȊO
				if (i != MaxJudg - 1) {
					//�V�����ړ�����쐬
					ForMoveEnd(&EndMat, &enemy[e]->GetCon(), &enemy[e]->GetQuaForMove(), &enemy[e]->GetTransMatCar());
					enemy[e]->SetForMoveEndMat(&EndMat);

					float L_ResetSize = 1.0f;

					//Mul�̏�����
					enemy[e]->SetQuaVecSize(&L_ResetSize);
				}
			}
		}
	}

	/*�����蔻�芮��*/

	return true;
}

bool GameScene::Update_Car_SideJudg(void)
{
	//�v���C���[�̉�����
	if (player != nullptr) {
		Side_Judg(&Hit_Type_Player,nullptr);
	}

	//�G�̉�����
	if (enemy.size() <1) return true;
	
	for (unsigned int e = 0; e < enemy.size(); e++) {
		if (enemy[e]->Get_JudgeType() != Co_Judge_NO) Side_Judg(&Hit_Type_Enemy, &e);
	}

	return true;
}

bool GameScene::Update_Player_XTrans(void)
{
	//������
	//===========================================
	//�Ԑ��ύX
	//===========================================
	//���̎Ԑ��ɕύX
	//�J�[�u�������ǂ�����Flg
	bool LRKeyFlg = false;

	if (Get_End_Flg() != true) {

		if ((key.AKey() == true)) {
			D3DXMATRIX Trans;
			D3DXMatrixTranslation(&Trans, -1.0f*0.08f, 0.0f, 0.0f);
			Trans = Trans * player->GetTransMatCar();
			player->SetTransMatCar(&Trans);
			Trans = player->GetTransMatCar()*player->GetCon().JudgMat;
			player->SetMatCar(&Trans);
			//������
			bool LeftFlg = true;
			Side_Judg(&LeftFlg, &Hit_Type_Player, nullptr);
			//�J�[�u
			player->SetRodAngY(-0.3f, true);
			LRKeyFlg = true;


		}
		//�E�̎Ԑ��ɕύX
		if (key.DKey() == true) {
			D3DXMATRIX Trans;
			D3DXMatrixTranslation(&Trans, 1.0f*0.08f, 0.0f, 0.0f);
			Trans = Trans * player->GetTransMatCar();
			player->SetTransMatCar(&Trans);
			Trans = player->GetTransMatCar()*player->GetCon().JudgMat;
			player->SetMatCar(&Trans);
			//������
			bool LeftFlg = false;
			Side_Judg(&LeftFlg, &Hit_Type_Player, nullptr);
			//�J�[�u
			player->SetRodAngY(0.3f, true);
			LRKeyFlg = true;
		}

	}
	if (LRKeyFlg == false)player->SetRodAngY(0.3f, false);

	return true;
}

bool GameScene::Update_Player(void)
{

	if (player->UpdateAll(&camera->GetMat()) != false)return true;
	
	Set_Game_Over();

	return false;
}

bool GameScene::Update_Car_SetMat(void)
{
	if (player != nullptr) {
		player->SetCarMoveMat();
	}

	if (enemy.size() > 0) {
		for (auto && e : enemy) {
			e->SetCarMoveMat();
		}
	}


	return true;
}

bool GameScene::Update_CameraMat(void)
{
	player->Set_CameraMat(&camera->GetMat());

	return true;
}

bool GameScene::Update_Pop_End(void)
{
	if (M_C_Car_Pop == nullptr) return false;

	if (Get_End_Flg() == true) return false;

	//���݂̐������Ă���G���̒���
	int Num = 0;

	if (enemy.size() > 0) {

		for (auto && e : enemy) if (e->GetFlgCar() == true)Num++;

	}

	M_C_Car_Pop->Set_Now_Enemy_Num_N(&Num);

	//�o�����Ă���Ԃ���Ԃ̏o���̕ύX
	M_Car_Pop_Data_Update();

	// ���H�̌`��ύX
	int RoadNo = M_C_Car_Pop->Get_GroundNo();
	if (groundManager != nullptr)groundManager->SetGroundPop(&RoadNo);

	if (M_C_Car_Pop->Get_Change_Class_EndFlg() == true) {
		if (M_C_Car_Pop->Get_Now_Wave_Data_N().WaveType_Now == Co_Wave_Type_Boss) {
			war->SetFlg(true);
			M_C_Sound_Manager->BGMDelete();
			New_Sound(&Co_Sound_Type_2D, &Co_Sound_Category_Warning, 1, &Co_SoundNew);
			war->New_Sound_Data_Change_No(&Co_Sound_Type_2D, &Co_Sound_Category_BGM, 4, &Co_SoundNew);
			return true;
		}
		if (M_C_Car_Pop->Get_Now_Wave_Data_N().WaveType_Now == Co_Wave_Type_Normal) {
			int No = 1, Volume = option->GetOptionData().BGMVolume;
			M_C_Sound_Manager->BGMStart(&No, &Volume);
			return true;
		}
	}
	
	//Pop�̏I���m�F����
	if (M_C_Car_Pop->Get_Now_Wave_Data_N().WaveType_Now == Co_Wave_Type_End) {

		//�Q�[���N���A��Ԃɂ���
		Set_Game_Clear();

		return false;
	}

	return true;
}

bool GameScene::Get_Car_Pop(const int * Car_Type)
{
	//�Q�[���I��Flg
	if (Get_End_Flg() == true)return false;

	//�v���C���[���n��No�̎擾Flg
	if (eneFlg != true)return false;

	//�o��������Ԃ̏��
	if (M_C_Car_Pop == nullptr)return false;

	if (M_C_Car_Pop->Get_Car_Pop_Flg_N() != true)return false;

	if (M_C_Car_Pop->Get_Next_Car_Data_N().CarType != *Car_Type)return false;

	//�o���\
	return true;
}

bool GameScene::Get_Car_Pop_Update_MoveFlg(void)
{
	if (Get_End_Flg() == true)return false;

	if (war->GetFlg() == true)return false;

	return true;
}

void GameScene::Set_Game_Over(void)
{
	if (Get_End_Flg() == true)return;

	//player�����񂾂Ƃ��̏���
	BombInit(&player->GetMatCar());
	
	Geme_End_Change(&Co_Stage_End_Over);

	for (unsigned int e = 0; e < enemy.size(); e++) {
		enemy[e]->SetPlaEnd(true/*, player->GetSpeedCar()*/);
	}
	player->SetSpeedCar(&(player->GetCon().Speed *0.0f));
	war->SetFlg(false);
	//���j���[�̕\��
	SetMenu(false, false, true);
}

void GameScene::Set_Game_Clear(void)
{
	if (Get_End_Flg() == true)return;

	Geme_End_Change(&Co_Stage_End_Clear);
	SetMenu(false, true, false);

	int No = 5, Volume = option->GetOptionData().BGMVolume;
	M_C_Sound_Manager->BGMStart(&No, &Volume);
}

bool GameScene::Update_Bullet(void)
{
	//�e��MoveVec�̉��Z
	Update_Bullet_MoveVec();

	//�e�̏o������
	Update_Player_Bullet();
	Update_Bullet_Enemy_Init();

	//�e�̏o��
	Update_Bullet_Init();

	//�e�̔���
	Update_Bullet_Judg();

	//�e�̍X�V
	Update_Bullet_Move();

	return true;
}

bool GameScene::Update_Bullet_MoveVec(void)
{
	if (player != nullptr) {
		player->MoveVec_Bullet();
	}

	if (enemy.size() < 1)return true;

	for (auto && e : enemy) {
		e->MoveVec_Bullet();
	}

	return true;
}

bool GameScene::Update_Bullet_Enemy_Init(void)
{
	if (enemy.size() < 1)return true;

	for (unsigned int i = 0; i < enemy.size(); i++) {

		if (enemy[i]->Get_Gun_Num() <= 0) continue;

		for (unsigned int g = 0; g < enemy[i]->Get_Gun_Num(); g++) {

			if (enemy[i]->Get_Gun_Data(&g).Ray_Judg_Flg != true) continue;

			//���C����
			BULLETJUDGDATA b;
			b.SamllDis = enemy[i]->Get_Gun_Data(&g).RayDis;
			RAYDATA r;
			r.Mat = enemy[i]->Get_Gun_Data(&g).DrawBase.Mat;
			D3DXVec3TransformNormal(&r.Ray, &D3DXVECTOR3(0.0f, 0.0f, 1.0f), &r.Mat);
			float Rad = (float)RadChara*2.0f;

			//���C����
			BulletJudgPlayer(&b, &r, &Rad);
			BulletJudgEnemy(&b, &r, &Rad,&i);

			//���C��������������Flg
			bool Ray_HitFlg = false;
			if (b.Type > 0)Ray_HitFlg = true;

			enemy[i]->Set_Ray_Hit_Flg(&g, &Ray_HitFlg);
			enemy[i]->Set_Ray_Dis(&g, &b.SamllDis);
		}
	}

	return true;
}

bool GameScene::Update_Bullet_Init(void)
{
	if (player != nullptr) {
		if (Get_End_Flg() != true) {
			player->Init_Bullet();
		}
	}

	if (enemy.size() < 1)return true;

	for (auto && e : enemy) {
		e->Init_Bullet();
	}

	return true;
}

bool GameScene::Update_Bullet_Judg(void)
{
	if (player != nullptr) {
		BulletJudg(&co_PlayerCar, NULL);
	}

	if (enemy.size() < 1)return true;

	for (unsigned int e = 0; e < enemy.size(); e++) {
		BulletJudg(&co_EnemyCar, &e);
	}

	return true;
}

bool GameScene::Update_Bullet_Move(void)
{
	if (player != nullptr) {
		player->Update_Bullet();
	}

	if (enemy.size() < 1)return true;

	for (auto && e : enemy) {
		e->Update_Bullet();
	}

	return true;
}

void GameScene::New_Sound(const int * Type, const int * Category, const int No, const int * Change)
{
	if (M_C_Sound_Manager == nullptr)return;

	C_Struct_Init C_S_Init;
	M_C_Sound_Manager->New_Sound_Data(&C_S_Init.Get_S_SOUND_DATA(Type, Category, &No, Change));
}

void GameScene::New_Sound(const int * Category, const int No, const D3DXVECTOR3 * Pos, const int * Change)
{
	if (M_C_Sound_Manager == nullptr)return;

	M_C_Sound_Manager->New_Sound_Data(Category, No, Pos, Change);
}

bool GameScene::Update_Damage_Num_Draw(void)
{
	if (M_Damage_Num_Draw.size() <1) return false;

	for (unsigned int v = 0; v < M_Damage_Num_Draw.size(); v++) {
		if (M_Damage_Num_Draw[v]->Update() != true) {
			Delete_Damage_Num_Draw(&v);
		}
	}

	return true;
}

bool GameScene::Get_End_Flg(void)
{
	if (M_C_Game_End == nullptr)return true;

	return M_C_Game_End->Get_EndFlg();
}

void GameScene::Geme_End_Change(const int * Mode)
{
	if (M_C_Game_End == nullptr)return;

	C_Game_End_Base* Game_End;

	Game_End=M_C_Game_End->Change(Mode);

	if (Game_End != nullptr) {
		delete M_C_Game_End;
		M_C_Game_End = Game_End;
	}
}

void GameScene::Pop_Enemy(void)
{
	//�G�l�~�[�̏o��
	if (Get_Car_Pop(&co_EnemyCar) != true) return;

	//�Ԃ̏��擾
	S_CAR_INIT_DATA L_Data = M_C_Car_Pop->Get_Next_Car_Data_N();

	//�n�ʂ̃i���o�[
	unsigned int gNo;
	//�n�ʂ̈ʒu
	D3DXMATRIX GroundMat;
	//�n�ʂ̏����ʒu�̉���
	float TransX;

	if (groundManager == nullptr)return;
	unsigned int playerGroundNo = player->GetCon().GroNum;
	groundManager->InitCarPopData(&gNo,&GroundMat,&TransX,&playerGroundNo,&L_Data);

	//�o���ł��邩�̔���
	if (Car_Pop_Judg(&GroundMat, &TransX) != true)return;

	//�{�X���o�����鎞�̔���
	if (L_Data.CarNo > 100) {
		if (enemy.size() > 0) {
			for (auto && e : enemy) {
				if (e->GetCon().GroNum > gNo)return;
			}
		}
	}

	//�G�̎��
	C_Enemy_Manager Manager;

	//�o��
	enemy.push_back(Manager.Get_Enemy(&L_Data.CarNo, &GroundMat, &TransX));

	// �n�ʂ̓����蔻��
	unsigned int num;
	float dis;
	if (groundManager->JudgNowGround(&num, &dis, enemy[(enemy.size() - 1)]->GetMatCar()) == true) {
		enemy[(enemy.size() - 1)]->SetGroNum(&num);
	}

	//�o����̏���
	M_C_Car_Pop->Car_Init_Rear_N();
}

bool GameScene::Car_Pop_Judg(const D3DXMATRIX * GroundMat, const float * TransX)
{
	D3DXMATRIX TmpMat;

	//�n�ʂ̉����̍s��쐬
	D3DXMatrixTranslation(&TmpMat, *TransX, 0.0f, 0.0f);

	//�o�����鏉���ʒu�̍s��̍���
	TmpMat = TmpMat * (*GroundMat);

	//�o���ʒu�A���s���̎Ԃ̈ʒu
	D3DXVECTOR3 Pop_Pos, Car_Pos;

	//�o���ʒu�̏�����
	judg.SetPosM(&Pop_Pos, &TmpMat);

	//�o���\���a
	float Radius = 4.0f*2.0f;

	//�v���C���[�Ƃ̔���
	if (Car_Pop_Judg_Player(&Pop_Pos, &Radius) == true)return false;

	//�G�l�~�[�Ƃ̔���
	if (Car_Pop_Judg_Enemy(&Pop_Pos, &Radius) == true)return false;

	//�o���\
	return true;
}

bool GameScene::Car_Pop_Judg_Player(const D3DXVECTOR3 * Pop_Pos, const float * Pop_Radius)
{
	if (player == nullptr)return false;

	D3DXVECTOR3 Pos;

	judg.SetPosM(&Pos, &player->GetMatCar());

	return judg.Pop_BallJudg(Pop_Pos, &Pos, Pop_Radius);
}

bool GameScene::Car_Pop_Judg_Enemy(const D3DXVECTOR3 * Pop_Pos, const float * Pop_Radius)
{
	if (enemy.size() <= 0) return false;

	for (auto && e : enemy) {
		
		D3DXVECTOR3 Pos;

		judg.SetPosM(&Pos, &e->GetMatCar());

		if (judg.Pop_BallJudg(Pop_Pos, &Pos, Pop_Radius) == true)return true;

	}

	return false;
}

void GameScene::Debug_Text(void)
{
	if (M_Text_Num == nullptr)return;

	/*if (enemy.size() > 0) {
		if (enemy[enemy.size() - 1]->Get_Gun_Num() > 0) {
			char Text[200];
			unsigned int L_GunNo = 0;
			D3DXMATRIX Mat = enemy[enemy.size() - 1]->Get_Gun_Data(&L_GunNo).DrawBase.Mat;
			D3DXVECTOR3 Pos = judg.SetPosM(&Mat);
			sprintf_s(Text, sizeof(Text), "%f,%f,%f", Pos.x, Pos.y, Pos.z);
			M_Text_Num->Draw_Text_char(&Text[0], &D3DXVECTOR2(0, 0));
		}
	}*/
}

void GameScene::Delete_Damage_Num_Draw(unsigned int * vector_No)
{
	delete M_Damage_Num_Draw[*vector_No];
	M_Damage_Num_Draw.erase(M_Damage_Num_Draw.begin() + *vector_No);
	*vector_No -= 1;
}

void GameScene::New_Damage_Num_Draw(const int * Character_Type, const D3DXMATRIX * Ray_Mat,
	const D3DXVECTOR3 * Ray_Vec,const float * Ray_Dis, const int * Damage, const bool * DamageFlg)
{
	return;//��\����

	if (*Character_Type != co_PlayerCar) return;

	if (*DamageFlg != true)return;

	Judg L_judg;

	D3DXVECTOR3 Ray_Hit_Pos;

	L_judg.Get_Ray_Pos3D(&Ray_Hit_Pos,&judg.SetPosM(Ray_Mat), Ray_Vec, Ray_Dis);

	int L_Damage = *Damage;
	if (*DamageFlg != true)L_Damage = 0;

	D3DXMATRIX L_JudgMat = player->GetCon().JudgMat;

	M_Damage_Num_Draw.push_back(new C_Damage_Move_B(&Ray_Hit_Pos, &L_JudgMat, &L_Damage));
}

BULLETJUDGDATA GameScene::GetInitBJD(const float * InitDis)
{
	BULLETJUDGDATA BJD;
	BJD.Type = -1;
	BJD.JudgNo1 = -1;
	BJD.JudgNo2 = -1;
	BJD.JudgNo3 = -1;
	BJD.SamllDis = *InitDis;
	return BJD;
}

void GameScene::BulletJudgPlayer(BULLETJUDGDATA * BJD, const RAYDATA * RD, const float *Rad)
{
	D3DXVECTOR3 BPos;//BulletPos
	judg.SetPosM(&BPos, &RD->Mat);

	float Dis;

	if (judg.BallJudg(&judg.SetPosM(&RD->Mat), &judg.SetPosM(&player->GetMatCar()), Rad) == true) {//�i�荞��
	//���C����
		//�{�f�B
		if (judg.RayJudg_Mesh(&BPos, &RD->Ray, &player->GetDrawMatCar(), player->GetMeshCar(), &Dis) == true) {
			//���C�������������ɒe�̈ړ���Vec�̒������Z�������ׂ�
			if (Dis < BJD->SamllDis) {
				//�Z����
				BJD->SamllDis = Dis;
				BJD->Type = co_PlayerCar;
			}
		}
		//�p�[�c
		//if (player->GetPartsNum() > 0) {
		//	for (unsigned int p = 0; p < player->GetPartsNum(); p++) {
		//		//�{�f�B
		//		if (judg.Mesh(BPos, RD->Ray, player->GetPartsMat(&p), player->GetPartsData(&p).Mesh.DrawMesh.lpMesh, &Dis) == true) {
		//			//�ő��菬������
		//			if (Dis < BJD->SamllDis) {
		//				//�Z����
		//				BJD->SamllDis = Dis;
		//				BJD->Type = co_PlayerParts;
		//				BJD->JudgNo1 = p;
		//			}
		//		}
		//	}
		//}

	}
	return;
}

void GameScene::BulletJudgEnemy(BULLETJUDGDATA * BJD, const RAYDATA * RD, const float * Rad, const unsigned int * EnemyNo)
{
	if (enemy.size() <= 0)return;

	D3DXVECTOR3 BPos;
	judg.SetPosM(&BPos, &RD->Mat);

	//���肵�Ȃ��G
	unsigned int No_Judg_EnemyNo = -1;
	if (EnemyNo != nullptr)No_Judg_EnemyNo = *EnemyNo;

	//enemy�̐�
	for (unsigned int e = 0; e < enemy.size(); e++) {

		if (e == No_Judg_EnemyNo)continue;

		if (judg.BallJudg(&judg.SetPosM(&RD->Mat), &judg.SetPosM(&enemy[e]->GetMatCar()), Rad) != true)continue;

		//���C����
		//�{�f�B
		if (judg.RayJudg_Mesh_SmallDis(&BPos, &RD->Ray, &enemy[e]->GetDrawMatCar(), enemy[e]->GetMeshCar(), &BJD->SamllDis) == true) {

			BJD->Type = co_EnemyCar;
			BJD->JudgNo1 = e;

		}
		//�p�[�c
		if (enemy[e]->Get_Car_Parts_Num() > 0) {
			for (unsigned int p = 0; p < enemy[e]->Get_Car_Parts_Num(); p++) {
				//if (enemy[e]->GetPartsData(&p).MeshDrawFlg <= 0)continue;

				//���b�V������
				if (enemy[e]->Get_Parts_Draw_Draw_JudgFlg(&p) == Co_Draw_Mesh) {

					//�\���s��
					D3DXMATRIX DrawMat = enemy[e]->Get_Parts_Draw_DrawMat(&p);

					//���C����
					if (judg.RayJudg_Mesh_SmallDis(&BPos, &RD->Ray, &DrawMat
						, enemy[e]->Get_Parts_Draw_Mesh(&p), &BJD->SamllDis) != true) continue;

					BJD->Type = co_EnemyParts;
					BJD->JudgNo1 = e;
					BJD->JudgNo2 = p;

				}
				else {
					//�|���S������
					if (enemy[e]->Get_Parts_Draw_Draw_JudgFlg(&p) == Co_Draw_Pol) {

						int a = 0, b = 1, c = 2, d = 3;

						//���C����
						if (judg.RayJudg_Polygon_SmallDis(&BPos, &RD->Ray, &enemy[e]->Get_Parts_Draw_DrawMat(&p),
							&enemy[e]->Get_Parts_Draw_Pol_Pos(&p, &a), &enemy[e]->Get_Parts_Draw_Pol_Pos(&p, &b)
							, &enemy[e]->Get_Parts_Draw_Pol_Pos(&p, &c), &enemy[e]->Get_Parts_Draw_Pol_Pos(&p, &d)
							, &BJD->SamllDis) != true) continue;

						BJD->Type = co_EnemyParts;
						BJD->JudgNo1 = e;
						BJD->JudgNo2 = p;

					}
				}
			}
		}
		//�e
		if (enemy[e]->Get_Gun_Num() > 0) {
			for (unsigned int g = 0; g < enemy[e]->Get_Gun_Num(); g++) {
				//if (enemy[e]->GetGunData(&g).Base.DrawFlg != true)continue;

				if (enemy[e]->Ray_Judg_Gun_Flg(&g) != true) continue;

				if (enemy[e]->Get_Gun_Draw_Parts_Num(&g) <= 0) continue;

				for (unsigned int g_p = 0; g_p < enemy[e]->Get_Gun_Draw_Parts_Num(&g); g_p++) {

					if (enemy[e]->Get_Gun_Draw_Parts_Draw_JudgFlg(&g, &g_p) != Co_Draw_Mesh) continue;

					//���C����
					if (judg.RayJudg_Mesh_SmallDis(&BPos, &RD->Ray, &enemy[e]->Get_Gun_Draw_Parts_Draw_Mat(&g, &g_p)
						, enemy[e]->Get_Gun_Draw_Parts_Mesh(&g, &g_p), &BJD->SamllDis) != true) continue;

					BJD->Type = co_EnemyGun;
					BJD->JudgNo1 = e;
					BJD->JudgNo2 = g;
					BJD->JudgNo3 = g_p;

				}

			}
		}

	}
	return;
}

void GameScene::BulletJudgEnemy_Ball(BULLETJUDGDATA * BJD, const RAYDATA * RD, const float * Rad)
{
	if (enemy.size() <= 0)return;

	D3DXVECTOR3 BPos;
	judg.SetPosM(&BPos, &RD->Mat);

	//enemy�̐�
	for (unsigned int e = 0; e < enemy.size(); e++) {

		//
		if (judg.BallJudg(&judg.SetPosM(&RD->Mat), &judg.SetPosM(&enemy[e]->GetMatCar()), Rad) != true) continue;

		/*�p�[�c*/
		if (enemy[e]->Get_Car_Parts_Num() <= 0) continue;

		for (unsigned int p = 0; p < enemy[e]->Get_Car_Parts_Num(); p++) {

			if (enemy[e]->Get_Parts_Draw_Draw_JudgFlg(&p) != Co_Draw_Ball) continue;

			float L_Radius = enemy[e]->Get_Parts_Draw_Dis(&p);

			if (judg.BallJudg(&BPos, &judg.SetPosM(&enemy[e]->Get_Parts_Draw_DrawMat(&p)),
				&L_Radius) != true) continue;

			//�ő��菬������
			BJD->Type = co_EnemyParts;
			BJD->JudgNo1 = e;
			BJD->JudgNo2 = p;

		}
	}
}

bool GameScene::SetBulletDamage(const BULLETJUDGDATA * BJD, const RAYDATA * RD, const int Damage)
{
	if (BJD->Type < 0)return false;

	//�n��///////////////////////////////////////////////////////////////////////////////////
	//�n��
	if (SetBulletDamageGround(BJD, RD) == true)return true;
	//��
	if (SetBulletDamageWall(BJD, RD) == true)return true;

	//�v���C���[/////////////////////////////////////////////////////////////////////////////
	//�ԑ�
	if (SetBulletDamagePlaCar(BJD,RD, &Damage) == true)return true;
	//�W���p�[�c
	if (SetBulletDamagePlaParts(BJD, RD, &Damage) == true)return true;
	//�e
	if (SetBulletDamagePlaGun(BJD, RD, &Damage) == true)return true;

	//�G�l�~�[//////////////////////////////////////////////////////////////////////////////
	//�ԑ�
	if (SetBulletDamageEneCar(BJD, RD, &Damage) == true)return true;
	//�W���p�[�c
	if (SetBulletDamageEneParts(BJD, RD, &Damage) == true)return true;
	//�e
	if (SetBulletDamageEneGun(BJD, RD, &Damage) == true)return true;

	//�������Ă��Ȃ�
	return false;
}

bool GameScene::SetBulletDamageGround(const BULLETJUDGDATA* BJD, const RAYDATA *RD)
{
	if (BJD->Type != co_Ground)return false;
	//�Ή�
	D3DXVECTOR3 Ray_Hit_Pos;
	judg.Get_Ray_Pos3D(&Ray_Hit_Pos, &judg.SetPosM(&RD->Mat), &RD->Ray, &BJD->SamllDis);

	int SpeType = 0;
	float Ang = 0.0f;
	effect.push_back(new C_BulGro(&groundManager->GetGroundMat(&BJD->JudgNo1), &Ray_Hit_Pos));

	//�e���RD
	float Ray_Dis = BJD->SamllDis - 0.01f;

	judg.Get_Ray_Pos3D(&Ray_Hit_Pos, &judg.SetPosM(&RD->Mat), &RD->Ray, &Ray_Dis);

	effect.push_back(new C_BulletHole3D(&groundManager->GetGroundMat(&BJD->JudgNo1), &Ray_Hit_Pos, 2));

	//��e���̏�����
	Set_BulletHit_Sound(&Hit_Type_Ground, &Ray_Hit_Pos);
	
	return true;
}

bool GameScene::SetBulletDamageWall(const BULLETJUDGDATA* BJD, const RAYDATA *RD)
{
	if (BJD->Type != co_Wall)return false;
	//�Ή�
	D3DXVECTOR3 Ray_Hit_Pos;
	judg.Get_Ray_Pos3D(&Ray_Hit_Pos, &judg.SetPosM(&RD->Mat), &RD->Ray, &BJD->SamllDis);

	int SpeType = 1;
	float Ang = 0.0f;
	//�Ή�
	int i = (int)BJD->JudgNo2;
	for (int s = 0; s < 5; s++) {
		effect.push_back(new C_SparkDamage(&groundManager->GetWallMat(&BJD->JudgNo1,&i), &Ray_Hit_Pos, &SpeType, &Ang));
	}
	//�e���RD
	float Ray_Dis = BJD->SamllDis - 0.01f;

	judg.Get_Ray_Pos3D(&Ray_Hit_Pos, &judg.SetPosM(&RD->Mat), &RD->Ray, &Ray_Dis);

	effect.push_back(new C_BulletHole3D(&groundManager->GetWallMat(&BJD->JudgNo1,&i), &Ray_Hit_Pos, 1));

	//��e���̏�����
	Set_BulletHit_Sound(&Hit_Type_Wall, &Ray_Hit_Pos);

	return true;
}

bool GameScene::SetBulletDamagePlaCar(const BULLETJUDGDATA* BJD, const RAYDATA * RD, const int * Damage)
{
	if (BJD->Type != co_PlayerCar)return false;

	if (player->SetHP(*Damage, false) == true) {
		//�_���[�W���󂯂���
		int sc = -10;
		score->ScoreUp(&sc);

		//��e���W
		D3DXVECTOR3 RayPos;

		//��e���̏�����
		Set_BulletHit_Sound(&Hit_Type_Player, &RayPos);
	}
	return true;
}

bool GameScene::SetBulletDamagePlaParts(const BULLETJUDGDATA* BJD, const RAYDATA * RD, const int * Damage)
{
	if (BJD->Type != co_PlayerParts)return false;

	/*if (player->SetDamageParts(HitMesh, Damage) == true) {

	}*/

	return true;
}

bool GameScene::SetBulletDamagePlaGun(const BULLETJUDGDATA* BJD, const RAYDATA * RD, const int * Damage)
{
	return false;
}

bool GameScene::SetBulletDamageEneCar(const BULLETJUDGDATA* BJD, const RAYDATA * RD, const int * Damage)
{
	if (BJD->Type != co_EnemyCar)return false;

	if (enemy[BJD->JudgNo1]->GetFlgCar() == false)return true;

	bool DamageFlg = enemy[BJD->JudgNo1]->SetHP(*Damage, false);

	New_Damage_Num_Draw(&BJD->Character_Type, &RD->Mat, &RD->Ray, &BJD->SamllDis, Damage, &DamageFlg);

	//��e���̏�����
	Set_BulletHit_Sound(&Hit_Type_Enemy, BJD, RD,&DamageFlg);

	return true;
}

bool GameScene::SetBulletDamageEneParts(const BULLETJUDGDATA* BJD, const RAYDATA * RD, const int * Damage)
{
	if (BJD->Type != co_EnemyParts)return false;

	bool DamageFlg=enemy[BJD->JudgNo1]->Damage_CarParts(&BJD->JudgNo2, Damage);

	New_Damage_Num_Draw(&BJD->Character_Type, &RD->Mat, &RD->Ray, &BJD->SamllDis, Damage, &DamageFlg);

	//��e���̏�����
	Set_BulletHit_Sound(&Hit_Type_Enemy, BJD, RD, &DamageFlg);

	return true;
}

bool GameScene::SetBulletDamageEneGun(const BULLETJUDGDATA* BJD, const RAYDATA * RD, const int * Damage)
{
	if (BJD->Type != co_EnemyGun)return false;

	bool DamageFlg = enemy[BJD->JudgNo1]->Damage_Gun(&BJD->JudgNo2, Damage);

	New_Damage_Num_Draw(&BJD->Character_Type, &RD->Mat, &RD->Ray, &BJD->SamllDis, Damage, &DamageFlg);

	//��e���̏�����
	Set_BulletHit_Sound(&Hit_Type_Enemy, BJD, RD, &DamageFlg);

	return true;
}

bool GameScene::SideJudg_Preparation(S_SideJudgChara * Judg_Car, D3DXMATRIX * JudgMat,
	D3DXVECTOR3 * JudgVec, float * SmallDis,float *Over_Dis, const int * JudgMat_Num)
{
	//����pMat
	D3DXMATRIX TransMat;
	//��Ԑ��l�̍���Z�ƒႢZ
	float BigZ, SmallZ;
	//�g����W
	D3DXVECTOR3 ScalPosB;
	//��������Ă���Ԃ̏��
	switch (Judg_Car->Car_Type)
	{
	case Hit_Type_Player://�v���C���[
		ScalPosB = player->GetScalPosCar();
		//Mat�̍쐬
		JudgMat[1] = player->GetCon().JudgMat;
		BigZ = player->GetCon().PosBig.z*ScalPosB.z;
		SmallZ = player->GetCon().PosSmall.z*ScalPosB.z;
		TransMat = player->GetTransMatCar();
		//Rad������
		if (Judg_Car->LeftFlg == true) {
			//��
			Judg_Car->Rad = player->GetCon().PosSmall.x*ScalPosB.x;
		}
		else {
			//�E
			Judg_Car->Rad = player->GetCon().PosBig.x*ScalPosB.x;
		}
		break;
	case Hit_Type_Enemy://�G

		if (enemy.size() <= 0) return false;

		//�G�l�~�[
		ScalPosB = enemy[Judg_Car->No]->GetScalPosCar();
		//Mat�̍쐬
		JudgMat[1] = enemy[Judg_Car->No]->GetCon().JudgMat;
		BigZ = enemy[Judg_Car->No]->GetCon().PosBig.z*ScalPosB.z;
		SmallZ = enemy[Judg_Car->No]->GetCon().PosSmall.z*ScalPosB.z;
		TransMat = enemy[Judg_Car->No]->GetTransMatCar();
		//Rad������
		if (Judg_Car->LeftFlg == true) {
			//��
			Judg_Car->Rad = enemy[Judg_Car->No]->GetCon().PosSmall.x*ScalPosB.x;
		}
		else {
			//�E
			Judg_Car->Rad = enemy[Judg_Car->No]->GetCon().PosBig.x*ScalPosB.x;
		}
		break;
	default:
		return false;
		break;
	}
	if (Judg_Car->Rad < 0.0f)Judg_Car->Rad *= -1.0f;
	Judg_Car->Rad += 0.01f;
	//Mat�̍쐬
	D3DXMATRIX Trans;
	for (int i = 0; i < *JudgMat_Num; i++) {
		JudgMat[i] = TransMat * JudgMat[1];
	}
	D3DXMatrixTranslation(&Trans, 0.0f, 0.0f, BigZ);
	JudgMat[0] = Trans * JudgMat[1];
	D3DXMatrixTranslation(&Trans, 0.0f, 0.0f, SmallZ);
	JudgMat[2] = Trans * JudgMat[1];
	//���C�̕���
	if (Judg_Car->LeftFlg == true) {
		D3DXVec3TransformNormal(JudgVec, &D3DXVECTOR3(-1.0f, 0.0f, 0.0f), &JudgMat[1]);
	}
	else {
		D3DXVec3TransformNormal(JudgVec, &D3DXVECTOR3(1.0f, 0.0f, 0.0f), &JudgMat[1]);
	}

	//����p���C�̋���
	*SmallDis = Judg_Car->Rad;
	if (*SmallDis < 0.0f)*SmallDis *= -1.0f;

	*Over_Dis = Judg_Car->Rad;
	if (*Over_Dis < 0.0f)*Over_Dis *= -1.0f;

	return true;
}

int GameScene::Side_Judg_Player(S_SideJudgChara * Next_Data, float * Small_Dis,
	int * RayHit_No, D3DXMATRIX * RayHit_Mat, float * Over_Dis, bool * Over_Flg,
	const S_SideJudgChara * Data, const int * JudgMat_Num, const D3DXMATRIX * JudgMat,
	const D3DXVECTOR3 * Ray_Vec)
{
	if (Data->Car_Type == Hit_Type_Player)return 0;

	if (Get_End_Flg() != false) return 0;

	float L_Radius = (float)RadJudgF;

	//�͈͓�����
	if (judg.BallJudg(&judg.SetPosM(&JudgMat[Const_Middle]), &judg.SetPosM(&player->GetMatCar()),
		&L_Radius) != true) return 0;

	if (Side_Judg_Ray(Next_Data, Small_Dis, RayHit_No, RayHit_Mat, Over_Dis, Over_Flg,
		&Hit_Type_Player, nullptr, Data, JudgMat_Num, JudgMat, Ray_Vec) > 0) {
		Next_Data->JudgeType = player->Get_JudgeType();
		return 1;
	}

	return 0;
}

int GameScene::Side_Judg_Enemy(S_SideJudgChara * Next_Data, float * Small_Dis, int * RayHit_No,
	D3DXMATRIX * RayHit_Mat, float * Over_Dis, bool * Over_Flg, const S_SideJudgChara * Data,
	const int * JudgMat_Num, const D3DXMATRIX * JudgMat, const D3DXVECTOR3 * Ray_Vec)
{
	if (enemy.size() <= 0) return 0;

	int Hit_Car_Count = 0;

	//enemy�̐�
	for (unsigned int e = 0; e < enemy.size(); e++) {
		//���肵�Ȃ�����
		if (((Data->Car_Type == Hit_Type_Enemy) && (Data->No == e)) || (enemy[e]->Get_JudgeType()==Co_Judge_NO))continue;

		float L_Radius = (float)RadJudgF;

		//�͈͓�����
		if (judg.BallJudg(&judg.SetPosM(&JudgMat[Const_Middle]),
			&judg.SetPosM(&enemy[e]->GetMatCar()), &L_Radius) != true)continue;

		//���C����
		if (Side_Judg_Ray(Next_Data, Small_Dis, RayHit_No, RayHit_Mat, Over_Dis, Over_Flg,
			&Hit_Type_Enemy, &e, Data, JudgMat_Num, JudgMat, Ray_Vec) > 0) {
			Hit_Car_Count++;

			//���������Ԃ̏�Ԃ̃Z�b�g
			Next_Data->JudgeType = enemy[e]->Get_JudgeType();
		}
	}

	return Hit_Car_Count;
}

int GameScene::Side_Judg_Ray(S_SideJudgChara * Next_Data, float * Small_Dis, int * RayHit_No,
	D3DXMATRIX * RayHit_Mat, float * Over_Dis, bool * Over_Flg, const int * Judg_Car_Type,
	const unsigned int * Car_No, const S_SideJudgChara * Data, const int * JudgMat_Num,
	const D3DXMATRIX * JudgMat, const D3DXVECTOR3 * Ray_Vec)
{
	int Hit_Count = 0;

	float Dis;

	for (int RayPos_No = 0; RayPos_No < *JudgMat_Num; RayPos_No++) {

		D3DXVECTOR3 Ray_Pos = judg.SetPosM(&JudgMat[RayPos_No]);

		//
		D3DXMATRIX Car_Mat;

		//���������|���S����
		int L_PolNum;

		//���C����
		switch (*Judg_Car_Type)
		{
		case Hit_Type_Player:

			//���C����
			L_PolNum = judg.RayJudg_Mesh_PolNum(&Ray_Pos, Ray_Vec,
				&player->GetMatCar(), player->GetColMod(), &Dis);

			if (L_PolNum >= 2) Car_Mat = player->GetMatCar();

			break;
		case Hit_Type_Enemy:

			//���C����
			L_PolNum = judg.RayJudg_Mesh_PolNum(&Ray_Pos, Ray_Vec,
				&enemy[*Car_No]->GetDrawMatCar(), enemy[*Car_No]->GetColMod(), &Dis);

			if (L_PolNum >= 2) Car_Mat = enemy[*Car_No]->GetMatCar();

			break;
		}

		if (L_PolNum == 1) {
			if (Data->Car_Type != Hit_Type_Player) {

				float L_Over_Dis = *Over_Dis;

				if (L_Over_Dis < 0.0f)L_Over_Dis *= -1.0f;

				if ((L_Over_Dis > Dis) || (*Over_Flg != true)) {
					*Over_Flg = true;
					*Over_Dis = Dis * -1.0f;
				}
			}
			continue;
		}

		//���C����Ń��C�������������̏���
		if (L_PolNum >= 2) {
			Hit_Count += Side_Judg_Ray(Judg_Car_Type, Car_No, &Data->Rad, Next_Data, Small_Dis, RayHit_No, RayHit_Mat,
				&Dis, &Car_Mat, &RayPos_No);
		}
	}

	return Hit_Count;
}

int GameScene::Side_Judg_Ray(const int * Judg_Car_Type, const unsigned int * Car_No, const float * Car_Rad,
	S_SideJudgChara * Next_Data, float * Small_Dis,int * RayHit_No, D3DXMATRIX * RayHit_Mat,
	const float * Ray_Hit_Dis, const D3DXMATRIX * Judg_Car_Mat, const int * RayPos_No)
{
	//��������
	if (*Ray_Hit_Dis < *Small_Dis) {
		*Small_Dis = *Ray_Hit_Dis;
		Next_Data->Car_Type = *Judg_Car_Type;
		if (Car_No != nullptr)Next_Data->No = *Car_No;
		*RayHit_No = *RayPos_No;
		*RayHit_Mat = *Judg_Car_Mat;
	}
	if (*Car_Rad > *Ray_Hit_Dis) return 1;

	//�������Ă��Ȃ�
	return 0;
}

void GameScene::Wall_Spark_Init(bool * Spark_Init_Flg, const D3DXMATRIX * RayHit_Mat, const D3DXVECTOR3 * RayHit_Pos, bool * LeftFlg)
{
	if (*Spark_Init_Flg != true)return;

	//�ΉԂ��o������
	//�����o��
	bool InitFlg = false;
	for (int i = 0; i < 20; i++) {
		effect.push_back(new C_Spark2(RayHit_Mat, RayHit_Pos, LeftFlg, &InitFlg));
	}
	InitFlg = true;
	for (int i = 0; i < 15; i++) {
		effect.push_back(new C_Spark2(RayHit_Mat, RayHit_Pos, LeftFlg, &InitFlg));
	}

	//���o�[�X
	judg.ReverseFlg(LeftFlg);

	//�ǔ����͉ΉԂ��o���Ȃ�
	*Spark_Init_Flg = false;
}

void GameScene::Car_Spark_Init(const bool * Spark_Init_Flg, const D3DXMATRIX * RayHit_Mat, const D3DXVECTOR3 * RayHit_Pos)
{
	//�ΉԂ��o���锻��
	if (*Spark_Init_Flg != true) return;

	//�����o��
	bool InitFlg = false;
	for (int i = 0; i < 15; i++) {
		effect.push_back(new C_Spark2(RayHit_Mat, RayHit_Pos, &InitFlg));
	}
	InitFlg = true;
	for (int i = 0; i < 12; i++) {
		effect.push_back(new C_Spark2(RayHit_Mat, RayHit_Pos, &InitFlg));
	}
}

bool GameScene::Ray_Judg_Player_ColModel(const D3DXVECTOR3 * Ray_Pos, const D3DXVECTOR3 * Ray_Vec, float * Dis)
{
	return judg.RayJudg_Mesh(Ray_Pos, Ray_Vec, &player->GetMatCar(), player->GetColMod(), Dis);
}

bool GameScene::Ray_Judg_Enemy_ColModel(const unsigned int * Enemy_No, const D3DXVECTOR3 * Ray_Pos, const D3DXVECTOR3 * Ray_Vec, float * Dis)
{
	return judg.RayJudg_Mesh(Ray_Pos, Ray_Vec, &enemy[*Enemy_No]->GetDrawMatCar(), enemy[*Enemy_No]->GetColMod(), Dis);
}

void GameScene::Enemy_Stop(const unsigned int * e, const int * Side_Judg_Car_Type)
{
	if (*Side_Judg_Car_Type != Hit_Type_Player)return;

	if (enemy[*e]->GetFlgCar() != true)return;

	if (enemy[*e]->Get_Move_Stop_Time() > 0)return;

	int Time = 60 * 8, L_Speed = player->GetCon().NowSpeed;

	enemy[*e]->Set_Move_Stop_Time(&Time,&L_Speed);
}

void GameScene::Debug_Screen_Init(void)
{
	M_S_Screen.DrawFlg = false;

	lpD3DDevice->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &M_S_Screen.lpBackBuffer);
	lpD3DDevice->GetDepthStencilSurface(&M_S_Screen.lpZBuffer);//DepthStencilSurface=Z�o�b�t�@
	D3DXCreateTexture(lpD3DDevice, 2048, 1024, 1, D3DUSAGE_RENDERTARGET, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &M_S_Screen.lpTmpTex);//X=2048,Y=1024,���o�b�N�o�b�t�@���Q�ׂ̂���T�C�Y
	M_S_Screen.lpTmpTex->GetSurfaceLevel(0, &M_S_Screen.lpTmpBackBuffer);
	lpD3DDevice->CreateDepthStencilSurface(2048, 1024, D3DFMT_D16, D3DMULTISAMPLE_NONE, 0, FALSE, &M_S_Screen.lpTmpZBuffer, NULL);
}

void GameScene::Debug_Screen_End(void)
{
	M_S_Screen.lpBackBuffer->Release();
	M_S_Screen.lpZBuffer->Release();
	M_S_Screen.lpTmpBackBuffer->Release();
	M_S_Screen.lpTmpZBuffer->Release();
	M_S_Screen.lpTmpTex->Release();
}

void GameScene::Debug_Screen_Draw(void)
{
	if (M_S_Screen.DrawFlg != true)return;

	RECT rcTmp = { 0,0,1280,720 };
	D3DXMATRIX tmp;
	D3DXMatrixTranslation(&tmp, 0.0f, 0.0f, NULL);
	lpSprite->SetTransform(&tmp);
	lpSprite->Draw(M_S_Screen.lpTmpTex, &rcTmp, &D3DXVECTOR3(0, 0, 0), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));//�Q�T�T�`�P�O�c�����ł���
}

void GameScene::FrustumCulling(const D3DXMATRIX * mProj, const D3DXMATRIX * mView, const D3DVIEWPORT9 * Viewport)
{
	S_Frustum_Vec FV_Data;

	judg.Get_Frustum_NormalVec(&FV_Data, mProj, mView, Viewport);

	if (groundManager != nullptr)groundManager->FrustumCulling(&FV_Data,&camera->GetPos());
}

void GameScene::Set_BulletHit_Sound(const int * BulletHit_Type, const D3DXVECTOR3 * Sound_Pos)
{
	if (M_C_Sound_Manager == nullptr)return;

	//M_C_Sound_Manager->Set_Bullet_Hit_Sound(BulletHit_Type, Sound_Pos);
}

void GameScene::Set_BulletHit_Sound(const int * BulletHit_Type, const D3DXVECTOR3 * Sound_Pos, const bool * DamageFlg)
{
	if (M_C_Sound_Manager == nullptr)return;

	//M_C_Sound_Manager->Set_Bullet_Hit_Sound(BulletHit_Type, Sound_Pos,DamageFlg);
}

void GameScene::Set_BulletHit_Sound(const int * BulletHit_Type, const BULLETJUDGDATA * BJD, const RAYDATA * RD, const bool * DamageFlg)
{
	//��e���W
	D3DXVECTOR3 RayPos = judg.SetPosM(&RD->Mat) + RD->Ray * BJD->SamllDis;

	Set_BulletHit_Sound(BulletHit_Type, &RayPos, DamageFlg);
}

void GameScene::M_ForMoveJudg_Player(bool * JudgFlg, float * SmallDis, int * Hit_CarType,
	unsigned int * Hit_CarNumber, const int * Car_Type, const D3DXMATRIX * StartMat,
	const D3DXMATRIX * EndMat, const D3DXMATRIX * TransMat, const int * TransNum,
	const D3DXVECTOR3 * MoveVec, const D3DXVECTOR3 * PosBig, const D3DXVECTOR3 * PosSmall,
	const D3DXVECTOR3 * ScalPos, const bool * CollisionJudg_TrueFlg)
{
	//�v���C���[�ƃv���C���[�Ŕ��肵�Ȃ��悤�ɂ���
	if (*Car_Type == Hit_Type_Player)return;

	//�S�Ă̐퓬���I�����Ă���Ƃ��v���C���[�Ɣ��肵�Ȃ�
	if (Get_End_Flg() != false) return;

	//����ł��Ȃ���Ԃ̏ꍇ��������Ȃ�
	if (*CollisionJudg_TrueFlg != true)return;

	float L_Radius = (float)RadJudgF;

	//���肷��Ԃ��߂��ɂ��邩���肷��
	if (judg.BallJudg(&judg.SetPosM(StartMat), &judg.SetPosM(&player->GetMatCar()), &L_Radius) != true) return;

	D3DXVECTOR3 JudgPos;//���C�̎n�_
	//�����珇�Ԃ�
	for (int i = 0; i < *TransNum; i++) {

		JudgPos = judg.SetPosM(&TransMat[i]);

		float Dis;

		//���C����
		if (judg.RayJudg_Mesh(&JudgPos, &MoveVec[i], &player->GetForMoveEndMat(), player->GetColMod(), &Dis) != true) continue;

		float Dis2;
		D3DXVECTOR3 Pos2, Vec2;
		for (int n = 0; n < *TransNum; n++) {

			//���C�̔��ˈʒu�ƃx�N�g���̍쐬
			if (M_ForMoveJudg_AfterMovingRay(&Pos2, &Vec2, &n, PosBig, PosSmall, ScalPos, EndMat) != true)continue;

			//���C����
			if (judg.RayJudg_Mesh(&Pos2, &Vec2, &player->GetForMoveEndMat(), player->GetColMod(), &Dis2) != true) continue;

			if (Dis < SmallDis[i]) {
				SmallDis[i] = Dis;
				JudgFlg[i] = true;
				*Hit_CarType = Hit_Type_Player;
			}

		}
	}
}

void GameScene::M_ForMoveJudg_Enemy(bool * JudgFlg, float * SmallDis, int * Hit_CarType,
	unsigned int * Hit_CarNumber, const int * Car_Type, const unsigned int * Car_No,
	const D3DXMATRIX * StartMat, const D3DXMATRIX * EndMat, const D3DXMATRIX * TransMat,
	const int * TransNum, const D3DXVECTOR3 * MoveVec, const D3DXVECTOR3 * PosBig,
	const D3DXVECTOR3 * PosSmall, const D3DXVECTOR3 * ScalPos, const bool * CollisionJudg_TrueFlg)
{
	//�o�����Ă���G�����Ȃ��ꍇ���C���肵�Ȃ�
	if (enemy.size() <= 0)return;

	//�S�Ă̐퓬���I�������ꍇ�v���C���[�̎ԂƔ��肵�Ȃ�
	if ((Get_End_Flg() == true) && (*Car_Type == Hit_Type_Player))return;

	for (unsigned int e = 0; e < enemy.size(); e++) {

		//�����G�Ŕ��肵�Ȃ�
		if ((*Car_Type == Hit_Type_Enemy) && (*Car_No == e))continue;

		//�G�������ł���ꍇ���肵�Ȃ�
		if (enemy[e]->Get_JudgeType() == Co_Judge_NO)continue;

		//���肷��G������ł��Ȃ���ԂŃv���C���[�Ɣ��肷��ꍇ���肵�Ȃ�
		if ((*Car_Type == Hit_Type_Player) && (enemy[e]->Get_CollisionJudg_TrueFlg() != true))continue;

		float L_Radius = (float)RadJudgF;

		//�i�荞�݋�������
		if (judg.BallJudg(&judg.SetPosM(StartMat), &judg.SetPosM(&enemy[e]->GetMatCar()), &L_Radius) != true) continue;

		D3DXVECTOR3 JudgPos;//���C�̎n�_

		//�����珇�Ԃ�
		for (int i = 0; i < *TransNum; i++) {

			JudgPos = judg.SetPosM(&TransMat[i]);

			float Dis;

			//���C����
			if (judg.RayJudg_Mesh(&JudgPos, &MoveVec[i], &enemy[e]->GetForMoveEndMat(), enemy[e]->GetColMod(), &Dis) != true) continue;

			float Dis2;
			D3DXVECTOR3 Pos2, Vec2;
			for (int n = 0; n < *TransNum; n++) {

				//���C�̔��ˈʒu�ƃx�N�g���̍쐬
				if (M_ForMoveJudg_AfterMovingRay(&Pos2, &Vec2, &n, PosBig, PosSmall, ScalPos, EndMat) != true)continue;

				//���C����
				if (judg.RayJudg_Mesh(&Pos2, &Vec2, &enemy[e]->GetForMoveEndMat(), enemy[e]->GetColMod(), &Dis2) != true) continue;

				if (Dis < SmallDis[i]) {
					SmallDis[i] = Dis;
					JudgFlg[i] = true;
					*Hit_CarType = Hit_Type_Enemy;
					*Hit_CarNumber = e;

					/*if (*Car_Type == Hit_Type_Player) {
						bool Flg = false;
						enemy[e]->Set_CollisionJudg_TrueFlg(&Flg);
					}*/
				}

			}
		}
	}
}

bool GameScene::M_ForMoveJudg_AfterMovingRay(D3DXVECTOR3 *Ray_Pos, D3DXVECTOR3 *Ray_Vec, const int * Vec_No,
	const D3DXVECTOR3 * PosBig, const D3DXVECTOR3 * PosSmall,const D3DXVECTOR3 *ScalPos, const D3DXMATRIX * EndMat)
{
	D3DXVECTOR3 TmpPos;

	switch (*Vec_No)
	{
	case 0:
		TmpPos = D3DXVECTOR3(PosSmall->x, 0.0f, PosBig->z);
		break;
	case 1:
		TmpPos = D3DXVECTOR3(0.0f, 0.0f, PosBig->z);
		break;
	case 2:
		TmpPos = D3DXVECTOR3(PosBig->x, 0.0f, PosBig->z);
		break;
	default://�����ɂЂ�������Ȃ��ꍇ�A���������Ȃ�
		return false;
		break;
	}

	D3DXMATRIX Mat;

	judg.Get_TransMatScal(&Mat, &TmpPos, ScalPos);

	Mat = Mat * (*EndMat);

	//���C�̔��ˈʒu�̍쐬
	judg.SetPosM(Ray_Pos, &Mat);

	//���C�̃x�N�g���̍쐬
	D3DXVec3TransformNormal(Ray_Vec, &D3DXVECTOR3(0.0f, 0.0f, 1.0f), &Mat);

	//��������
	return true;
}

bool GameScene::Get_Dead_Flg(const int * Car_Type, const unsigned int * Car_Number)
{
	//�v���C���[�̎��S�m�F
	if ((player != nullptr) && (*Car_Type == Hit_Type_Player)) {
		if (player->Dead() == true)return true;
	}

	//�G�̎��S�m�F
	if (*Car_Type == Hit_Type_Enemy) {
		if ((enemy.size() > 0) && (*Car_Number < enemy.size())) {
			if (enemy[*Car_Number]->Dead() == true)return true;
		}
	}

	return false;
}

void GameScene::M_Dead_Car(const int * Car_Type, const unsigned int * Car_Number)
{
	//�v���C���[�̎��S�m�F
	if ((player != nullptr) && (*Car_Type == Hit_Type_Player)) return;

	//�G�̎��S�m�F
	if (*Car_Type == Hit_Type_Enemy) {
		if ((enemy.size() > 0) && (*Car_Number < enemy.size())) {
			if (enemy[*Car_Number]->Dead() == true)return;

			int L_Hp = 0;
			
			//HP���[���ɂ���
			enemy[*Car_Number]->SetNowHp(&L_Hp);

			return;
		}
	}

	return;
}

void GameScene::M_Car_Pop_Data_Update(void)
{
	/*�o�����Ă���G�̏��쐬*/

	////�o�����Ă���G�̐�
	//int L_Enemy_Num = (int)enemy.size();

	////���I�z��̏������p�z��
	//int L_Init_Num = L_Enemy_Num;

	//if (L_Init_Num <= 0)L_Init_Num = 1;

	////�G�̏��
	//S_ENEMY_DATA *L_Enemy_Data = new S_ENEMY_DATA[L_Init_Num];

	////�o�����Ă���G�̍쐬
	//if ((L_Enemy_Num > 0) && (L_Enemy_Data != nullptr)) {

	//	if (enemy.size() > 0) {

	//		for (unsigned int e = enemy.size() - 1; e >= 0; e--)
	//		{
	//			//���̍쐬
	//			L_Enemy_Data[(int)e].CarFlg = enemy[e]->GetFlgCar();
	//			L_Enemy_Data[(int)e].BossFlg = enemy[e]->Get_BossFlg();
	//			L_Enemy_Data[(int)e].Phase_Now = enemy[e]->Get_Gun_Update_Data().NowPhase;
	//		}

	//	}
	//}

	//�o�����Ă���Ԃ̏��ŎԂ̏��̍X�V
	if (M_C_Car_Pop != nullptr)M_C_Car_Pop->M_Car_Pop_Update_N(enemy);

	////�������̉��
	//if (L_Enemy_Data != nullptr)delete[] L_Enemy_Data;
}
