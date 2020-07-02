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
#include"../GameSource/StructManager.h"

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
	// �~�j��ʂ̍폜
	if (screen != nullptr)delete screen;

	if (textDraw != nullptr)delete textDraw;

	if (groundManager != nullptr)delete groundManager;

	//�G�̍폜
	if (enemy.size() > 0)
	{
		for (unsigned int ec = 0; ec < enemy.size(); ec++)
		{
			delete enemy[ec];
			enemy.erase(enemy.begin() + ec);
			ec--;
		}
	}
	
	delete player;
	delete sky;
	delete camera;
	delete aiming;
	delete debug;

	if (gameEnd != nullptr) {
		delete gameEnd;
	}

	delete war;
	delete pause;
	delete spear;
	//�X�R�A�̍폜
	delete score;

	//�Ԃ̏����폜
	if (carPop != nullptr) delete carPop;
	

	//�}�E�X�̍폜
	delete mouse;

	if (effect.size() > 0) 
	{
		for (unsigned int ec = 0; ec < effect.size(); ec++) 
		{
			delete effect[ec];
			effect.erase(effect.begin() + ec);
			ec--;
		}
	}

	//�v���C���[�̏��폜
	delete playerBody;
	

	//���̊Ǘ��̍폜
	if (soundGameManager != nullptr) {
		soundGameManager->Reset();
		delete soundGameManager;
	}

	if (damageNumDraw3DManager != nullptr)delete damageNumDraw3DManager;

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
void GameScene::Render3DScreen(void)
{
	if (screen == nullptr)return;

	D3DXMATRIX Mat = player->GetCon().JudgMat;

	if (screen->RenderStart(&Mat) != true)return;

	Render3D();

	screen->RenderEnd();

}
void GameScene::Render2D(void) {
	//////////////////////////////////////////////////
	///	�X�v���C�g�̕`�揈��
	//////////////////////////////////////////////////
	// �`��J�n
	lpSprite->Begin(D3DXSPRITE_ALPHABLEND);

	if (damageNumDraw3DManager != nullptr)damageNumDraw3DManager->Draw2D();

	if (enemy.size() > 0) {
		for (unsigned int i = 0; i < enemy.size(); i++) enemy[i]->Draw2DAll();
	}

	aiming->Draw();
	player->Draw2DAll();

	if (screen != nullptr)screen->Draw2D();

	//�X�R�A�̕\��
	score->Draw2D();
	//�N���A�ƃI�[�o�[�̕\��
	if (gameEnd != nullptr) gameEnd->Draw_2D();
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
	if (textDraw != nullptr){
	}
}
bool GameScene::Update(void) {

	if (key.EscapeKey_F() == true) {
		sceneManager.changeScene(new TitleScene());
		return false;
	}

	/*�T�E���h�̍X�V����*/
	if (soundGameManager != nullptr)
	{

		S_OptionData l_OptionData = option->GetOptionData();

		soundGameManager->UpdateVolume(&l_OptionData.BGMVolume, &l_OptionData.SEVolume);

		soundGameManager->Update();

		soundGameManager->New();

		/*/Sound���v���C���[���Ŗ炷*/
		if (player != nullptr) {
			for (unsigned int s = 0; s < player->Get_Sound_Data_Num(); s++) {
				if (soundGameManager->Order(&player->Get_Sound_Data(&s)) == true) {
					player->Delete_Sound(&s);
				}
			}
		}

		if (war != nullptr) {
			for (unsigned int d = 0; d < war->Get_Sound_Data_Num(); d++) {
				if (soundGameManager->Order(&war->Get_Sound_Data(&d)) == true) {
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

	if (screen != nullptr)screen->Update();

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

	UpdateGame();

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

	screen = new c_Screen();

	if (textDraw == nullptr)textDraw = new C_Text_Num();

	//�}�E�X�̏�����
	mouse = new C_Mouse();
	mouse->Init();
	mouse->ChaDrawFlg(false);

	//�v���C���[�̏������O�ɏ�����
	playerBody = new C_PlayerBody();

	player = new C_PlayerA(&playerBody->GetPData());

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
	gameEnd = new C_Game_End_Now();

	key.Init();

	war = new Warning();

	pause = new Pause();

	damageNumDraw3DManager = new c_DamageNumDraw3DManager();

	//BulletBirthFlg���ŏ��͏o�Ȃ��悤�ɂ���
	bulletBirthFlg = false;

	//�Ԃ̏o���̏�����
	carPop = new C_Car_Pop_New(&StageNo);

	CountNum = MaxCount = 1;
	spear = new Spear();
	D3DXMatrixTranslation(&SpeMat, 0.0f, 0.0f, 0.0f);

	//�T�E���h�̏�����
	int BGMVolume = option->GetOptionData().BGMVolume, SEVolume = option->GetOptionData().SEVolume;
	soundGameManager = new c_GameSoundManager(&BGMVolume, &SEVolume);

	int No = 1;
	soundGameManager->BGMStart(&No);
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
	if (GetEndFlg() == true) {
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

bool GameScene::SideJudg()
{
	if (groundManager == nullptr)return false;

	c_StructManager structManager;

	if (groundManager->GetGroundNum() > 0)
	{
		for (unsigned int gc = 0; gc < groundManager->GetGroundNum(); gc++) 
		{
			if (groundManager->GetWallNum(&gc) > 0) 
			{
				for (unsigned int wc = 0; wc < groundManager->GetWallNum(&gc); wc++) 
				{
					s_CarType judgCar = structManager.GetCarType(&Hit_Type_Wall, &gc, &wc);
					float X = 1.0f;
					if (wc > 0)X *= -1.0f;
					bool WallJudgFlg = false;
					SideJudg(&WallJudgFlg, &judgCar, &X);
				}
			}
		}
	}

	return true;
}

bool GameScene::SideJudg(const int * CarType, const unsigned int * CarNo, const float * MoveVecX)
{
	bool WallJudgFlg = false;

	c_StructManager structManager;

	s_CarType judgCar = structManager.GetCarType(CarType, CarNo);

	SideJudg(&WallJudgFlg, &judgCar, MoveVecX);

	return true;
}

bool GameScene::SideJudg(bool * WallJudgFlg, const s_CarType *carType, const float * MoveVecX)
{
	// ���ɔ��肷��Ԃ̏��
	s_CarType hitCar;

	bool judgFlg = false;
	float smallDis, radius;
	bool flg = false;
	D3DXMATRIX tmp;
	if ((player != nullptr) && (carType->Type == Hit_Type_Player))
	{
		player->SideJudgData(&tmp, &radius);
		flg = true;
	}
	else {
		if ((enemy.size() > 0) && (carType->Type == Hit_Type_Enemy) && (carType->Numbar[0] < enemy.size()))
		{
			enemy[carType->Numbar[0]]->SideJudgData(&tmp, &radius);
			flg = true;
		}
		else {
			if ((groundManager != nullptr)&&(carType->Type==Hit_Type_Wall))
			{
				D3DXVECTOR3 Pos;
				groundManager->GetBallJudgWall(&radius, &Pos, &carType->Numbar[0], &carType->Numbar[1]);
				D3DXMatrixTranslation(&tmp, Pos.x, Pos.y, Pos.z);
				flg = true;
			}
		}
	}

	if (flg == false)return false;

	// �v���C���[����
	BallJudgPlayer(&judgFlg, &smallDis, &hitCar, carType, &tmp, &radius, &flg);
	// �G����
	BallJudgEnemy(&judgFlg, &smallDis, &hitCar, carType, &tmp, &radius, &flg);
	// �ǔ���
	bool WallFlg;
	if (groundManager != nullptr) {
		WallFlg = groundManager->BallJudgWall(&judgFlg, &smallDis, &hitCar, carType, &tmp, &radius, &flg);
	}

	if (judgFlg == false)return false;

	float X = *MoveVecX, S = (smallDis / X);
	if (S < 0.0f)S *= -1.0f;
	X *= S;

	if (WallFlg == true) {
		if (*WallJudgFlg == true) {
			return false;
		}
		else {
			*WallJudgFlg = true;
		}

		X *= -1.0f;

		hitCar = *carType;
	}

	if (hitCar.Type == Hit_Type_Player) {
		player->SetSideTransMat(&X);
	}
	else {
		if ((enemy.size() > 0) && (hitCar.Type == Hit_Type_Enemy) && (hitCar.Numbar[0] < enemy.size()))
		{
			enemy[hitCar.Numbar[0]]->SetSideTransMat(&X);
		}
		else {
			return false;
		}
	}
	

	SideJudg(WallJudgFlg, &hitCar, &X);

	return true;
}

bool GameScene::UpdateEnemyAI(void)
{
	//�G�l�~�[�̏o��
	PopEnemy();

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
			if (GetEndFlg() == true) {
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
		bool L_EndFlg = GetEndFlg();

		//Ai�̓��쏈��
		enemy[i]->UpdateAi(Data, &ChaNum,&L_EndFlg);

	}

	//���̍폜
	if (Data != nullptr)delete Data;

	return true;
}

bool GameScene::ForMoveJudg(void)
{
	//�ړ���̕ϐ�
	D3DXMATRIX EndMat;
	D3DXVECTOR3 EndPos;

	//�ړ��x�N�g���̃T�C�Y
	float Mul;

	//player
	//�ړ���̍s��쐬
	ForMoveEnd(&EndMat, &player->GetCon(), &player->GetQuaForMove(), &player->GetTransMatCar());
	player->SetForMoveEndMat(&EndMat);
	//�ړ��x�N�g���v�Z
	player->SetForMoveVec(&judg.MatMatVec(player->GetMatCar(), player->GetForMoveEndMat()));

	//player��Vec�T�C�Y
	Mul = player->GetQuaForMove().SpeedMulJudg;

	bool L_CollisionJudg_TrueFlg = player->Get_CollisionJudg_TrueFlg();
	float Radius = player->GetBodRadCar();

	// ���̎Ԃ̍s��𐳂�
	if (enemy.size() > 0)
	{
		for (auto && e : enemy)
		{
			D3DXMATRIX tmp;
			D3DXMatrixTranslation(&tmp, 0.0f, -e->GetQuaForMove().BodyHeight, 0.0f);
			tmp = tmp * e->GetMatCar();
			e->SetForMoveEndMat(&tmp);
		}
	}

	//����
	ForMoveJudg(&player->GetForMoveEndMat(), &Hit_Type_Player, nullptr,
		&player->GetForMoveVec(), &Mul, &player->GetScalPosCar(), &Radius, &L_CollisionJudg_TrueFlg);
	//Mul��{�̂ɓ����
	player->SetQuaVecSize(&Mul);
	//�ړ���̍s��쐬
	ForMoveEnd(&EndMat, &player->GetCon(), &player->GetQuaForMove(), &player->GetTransMatCar());
	player->SetForMoveEndMat(&EndMat);


	//enemy
	if (enemy.size() > 0) {//enemy�̑��݊m�F
		//enemy�̐�
		for (unsigned int e = 0; e < enemy.size(); e++) {
			//�ړ���̍s��쐬
			ForMoveEnd(&EndMat, &enemy[e]->GetCon(), &enemy[e]->GetQuaForMove(), &enemy[e]->GetTransMatCar());
			enemy[e]->SetForMoveEndMat(&EndMat);
			//�ړ��x�N�g���v�Z
			enemy[e]->SetForMoveVec(&judg.MatMatVec(enemy[e]->GetMatCar(), enemy[e]->GetForMoveEndMat()));


			if (enemy[e]->Get_JudgeType() == Co_Judge_NO)continue;

			//enemy��Vec�T�C�Y
			Mul = enemy[e]->GetQuaForMove().SpeedMulJudg;

			L_CollisionJudg_TrueFlg = enemy[e]->Get_CollisionJudg_TrueFlg();
			Radius = enemy[e]->GetBodRadCar();

			//����
			ForMoveJudg(&enemy[e]->GetForMoveEndMat(), &Hit_Type_Enemy, &e,
				&enemy[e]->GetForMoveVec(), &Mul, &enemy[e]->GetScalPosCar(), &Radius, &L_CollisionJudg_TrueFlg);
			//Mul��{�̂ɓ����
			enemy[e]->SetQuaVecSize(&Mul);
			//�ړ���̍s��쐬
			ForMoveEnd(&EndMat, &enemy[e]->GetCon(), &enemy[e]->GetQuaForMove(), &enemy[e]->GetTransMatCar());
			enemy[e]->SetForMoveEndMat(&EndMat);
		}
	}

	/*�����蔻�芮��*/

	return true;
}

bool GameScene::ForMoveJudg(const D3DXMATRIX *EndMat, const int *CarType
	, const unsigned int *CarNo, const D3DXVECTOR3 *MoveVec, float *SpeedMul2
	, const D3DXVECTOR3 *ScalPos, const float *Radius, const bool *CollisionJudg_TrueFlg)
{
	//���肷��Ԃ̎��
	c_StructManager structManager;

	s_CarType judgCar = structManager.GetCarType(CarType, CarNo);

	//���C�̒����ƍŏ�
	float Dis, SmallDis, radius;

	Dis = D3DXVec3Length(MoveVec);
	if (Dis < 0.0f)Dis *= -1.0f;
	Dis += 0.1f;

	radius = *Radius*ScalPos->z;

	bool JudgFlg = false;

	s_CarType hitCar;

	//player����
	BallJudgPlayer(&JudgFlg, &SmallDis, &hitCar, &judgCar, EndMat, &radius, CollisionJudg_TrueFlg);

	//�G����
	BallJudgEnemy(&JudgFlg, &SmallDis, &hitCar, &judgCar, EndMat, &radius, CollisionJudg_TrueFlg);
	
	//���C����������
	if (JudgFlg == true) {
		// �ړ��ʂ̕ύX
		float Size = Dis - SmallDis;
		Dis = Size / Dis;
		*SpeedMul2 = *SpeedMul2*Dis;
		if (*SpeedMul2 > 1.0f)*SpeedMul2 = 1.0f;


		// �Փ˂����Ԃ̎��S���Ă��鎞���肵�Ă���Ԃ�Hp���O�ɂ��鏈��
		bool DeadFlg = false;

		//�v���C���[�̎��S�m�F
		if ((player != nullptr) && (hitCar.Type == Hit_Type_Player)) 
		{
			if (player->Dead() == true)DeadFlg = true;
		}
		else {
			//�G�̎��S�m�F
			if (hitCar.Type == Hit_Type_Enemy) 
			{
				if ((enemy.size() > 0) && (hitCar.Numbar[0] < enemy.size())) 
				{

					if (enemy[hitCar.Numbar[0]]->Dead() == true)DeadFlg = true;
				}
			}
		}
		if (DeadFlg == true) 
		{
			// �G�̎��S������
			if (judgCar.Type == Hit_Type_Enemy) 
			{
				if ((enemy.size() > 0) && (judgCar.Numbar[0] < enemy.size())) 
				{
					if (enemy[judgCar.Numbar[0]]->Dead() != true)
					{
						//HP���[���ɂ���
						int L_Hp = 0;
						enemy[judgCar.Numbar[0]]->SetNowHp(&L_Hp);
					}
				}
			}
		}


	}

	return true;
}

void GameScene::ForMoveEnd(D3DXMATRIX * Mat, const CONSTITUTION * Con, const QuaForMove * q, const D3DXMATRIX * TransMat)
{
	QuaForMove  L_q = *q;

	L_q.BodyHeight = 0;

	motion.Formove(&L_q, Con, groundManager->GetGround());

	*Mat = *TransMat * L_q.NowMat;
}

bool GameScene::GetBulletBirthFlg(void)
{
	if (GetEndFlg() == true)return false;
	if ((key.LClickF_N() == true) && (bulletBirthFlg == false))return false;
	return true;
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

			// ����
			effect.push_back(new c_Explosion3D(&enemy[*EnemyNo]->GetMatCar()));
			NewSound(&Co_Sound_Category_Explosion, 1, &judg.SetPosM(&enemy[*EnemyNo]->GetMatCar()), &Co_SoundNew);

			int sc = 1000;
			score->ScoreUp(&sc);
			return true;
		}
	}
	return false;
}

void GameScene::SetMenu(C_NextTouch * NewMenu)
{
	if (Menu != nullptr)delete Menu;

	Menu = NewMenu;
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
		if (soundGameManager != nullptr) {
			soundGameManager->Restart();
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
	D3DXMATRIX L_JudgMat = player->GetCon().JudgMat;
	if (damageNumDraw3DManager != nullptr)damageNumDraw3DManager->UpdatePos2D(mProj, mView, Viewport, &L_JudgMat);

	if (enemy.size() <= 0)return;
	for (unsigned int e = 0; e < enemy.size(); e++) {
		//���v�Z
		enemy[e]->GetPos2DSet(mProj, mView, Viewport,&camera->GetPos());
	}
}

bool GameScene::UpdateGame(void)
{
	//�|�[�Y
	if (pause->GetDFlg() != false)return true;

	//�|�[�Y��ʂɈړ��̏���
	if (UpdateGamePause() != true)return true;

	if (JudgGameFrame() != true)return true;
	
	if (groundManager != nullptr)groundManager->Update(player);

	//�Ԃ̏��̍X�V
	if (carPop != nullptr) {
		bool MoveFlg = GetCarPopUpdateMoveFlg();
		carPop->Update(&MoveFlg);
	}

	//========================================
	//�v���C���[
	//========================================

	//�Ԃ̍��̈ʒu�̍X�V
	if (player != nullptr) player->SetCarMoveMat();

	if (enemy.size() > 0)
	{
		for (auto && e : enemy) e->SetCarMoveMat();
	}

	//�J����-------------------------------------
	if (GetEndFlg() == false) {
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
	UpdatePlayerXTrans();

	// �O�i����
	ForMoveJudg();

	//player======================================================================
	//player�̈ړ�
	player->UpdateCarFM(groundManager->GetGround());

	float L_ResetSize = 1.0f;

	//�ړ��x�N�g���̃T�C�Y�̏�����
	player->SetQuaVecSize(&L_ResetSize);
	//�G�̈ړ�
	if (enemy.size() > 0)
	{
		float L_ResetSize = 1.0f;
		for (unsigned int i = 0; i < enemy.size(); i++) {
			enemy[i]->UpdateAll(groundManager->GetGround());//Update
			//�ړ��x�N�g���̃T�C�Y�̏�����
			enemy[i]->SetQuaVecSize(&L_ResetSize);
		}
	}

	//������
	SideJudg();

	//�ŏIUpdate
	//player->SetParts(camera->GetAngX(),camera->GetAngY());
	if (enemy.size() > 0) {
		for (unsigned int e = 0; e < enemy.size(); e++) {
			//if (enemy[e]->GetFlgCar() == true) {
				enemy[e]->SetParts(groundManager->GetGround());
			//}
		}
	}

	//�J�����̃N�H�[�^�j�I���̃A�b�v�f�[�g
	bool keyFlg = key.RClickF();
	if (GetEndFlg() != true)
	{
		keyFlg = key.RClickF();
	}
	camera->UpdateQua(&keyFlg, &player->GetMatCar());

	//�J�[�u�̎ԑ̂̊p�x�𔽉f
	player->SetCurRotMat();

	//�J�����s��̎擾
	player->Set_CameraMat(&camera->GetMat());

	//player�̃p�[�c�ړ�
	if (player->UpdateAll(&camera->GetMat()) != true) {
		SetGameOver();
	}

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

	UpdateBullet();

	//================================================================================
	// �G
	//================================================================================
	if (UpdateEnemy() == false) {
		if (GetEndFlg() == false) {
			GemeEndChange(&Co_Stage_End_Clear);
			SetMenu(new C_ClearTouch());
		}
	}

	// ��
	sky->Update(&player->GetMatCar());

	if (damageNumDraw3DManager != nullptr)damageNumDraw3DManager->Update();

	war->Update();

	if (effect.size() > 0) 
	{
		for (unsigned int ec = 0; ec < effect.size(); ec++) 
		{
			if (effect[ec]->Update() != true)
			{
				delete effect[ec];
				effect.erase(effect.begin() + ec);
				ec--;
			}
		}
	}

	UpdatePopEnd();

	return true;
}

bool GameScene::UpdateGamePause(void)
{
	//�I�������
	if (GetEndFlg() == true) {
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
				SetMenu(new C_PauseTouch());

				if (soundGameManager != nullptr) {
					soundGameManager->Stop();
				}

				return false;
			}
		}
	}

	return true;
}

bool GameScene::JudgGameFrame(void)
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

bool GameScene::UpdatePlayerXTrans(void)
{
	//������
	//===========================================
	//�Ԑ��ύX
	//===========================================
	//���̎Ԑ��ɕύX
	//�J�[�u�������ǂ�����Flg
	bool LRKeyFlg = false;

	if (GetEndFlg() != true) {

		if ((key.AKey() == true)) {
			D3DXMATRIX Trans;
			float X = -1.0f*0.08f;
			player->SetSideTransMat(&X);
			SideJudg(&Hit_Type_Player, nullptr, &X);
			//�J�[�u
			player->SetRodAngY(-0.3f, true);
			LRKeyFlg = true;


		}
		//�E�̎Ԑ��ɕύX
		if (key.DKey() == true) {
			D3DXMATRIX Trans;
			float X = 1.0f*0.08f;
			player->SetSideTransMat(&X);
			//������
			SideJudg(&Hit_Type_Player, nullptr, &X);
			//�J�[�u
			player->SetRodAngY(0.3f, true);
			LRKeyFlg = true;
		}

	}
	if (LRKeyFlg == false)player->SetRodAngY(0.3f, false);

	return true;
}

bool GameScene::UpdatePopEnd(void)
{
	if (carPop == nullptr) return false;

	if (GetEndFlg() == true) return false;

	//���݂̐������Ă���G���̒���
	int Num = 0;

	if (enemy.size() > 0) 
	{
		for (auto && e : enemy)
		{
			if (e->GetFlgCar() == true)Num++;
		}
	}

	carPop->Set_Now_Enemy_Num_N(&Num);

	//�o�����Ă���Ԃ���Ԃ̏o���̕ύX
	CarPopDataUpdate();

	// ���H�̌`��ύX
	int RoadNo = carPop->Get_GroundNo();
	if (groundManager != nullptr)groundManager->SetGroundPop(&RoadNo);

	if (carPop->Get_Change_Class_EndFlg() == true) {
		if (carPop->Get_Now_Wave_Data_N().WaveType_Now == Co_Wave_Type_Boss) {
			war->SetFlg(true);
			soundGameManager->BGMDelete();
			NewSound(&Co_Sound_Type_2D, &Co_Sound_Category_Warning, 1, &Co_SoundNew);
			war->New_Sound_Data_Change_No(&Co_Sound_Type_2D, &Co_Sound_Category_BGM, 4, &Co_SoundNew);
			return true;
		}
		if (carPop->Get_Now_Wave_Data_N().WaveType_Now == Co_Wave_Type_Normal) {
			int No = 1;
			soundGameManager->BGMStart(&No);
			return true;
		}
	}
	
	//Pop�̏I���m�F����
	if (carPop->Get_Now_Wave_Data_N().WaveType_Now == Co_Wave_Type_End) {

		//�Q�[���N���A��Ԃɂ���
		SetGameClear();

		return false;
	}

	return true;
}

bool GameScene::GetCarPop(const int * Car_Type)
{
	//�Q�[���I��Flg
	if (GetEndFlg() == true)return false;

	//�v���C���[���n��No�̎擾Flg
	if (eneFlg != true)return false;

	//�o��������Ԃ̏��
	if (carPop == nullptr)return false;

	if (carPop->Get_Car_Pop_Flg_N() != true)return false;

	if (carPop->Get_Next_Car_Data_N().CarType != *Car_Type)return false;

	//�o���\
	return true;
}

bool GameScene::GetCarPopUpdateMoveFlg(void)
{
	if (GetEndFlg() == true)return false;

	if (war->GetFlg() == true)return false;

	return true;
}

void GameScene::SetGameOver(void)
{
	if (GetEndFlg() == true)return;

	//player�����񂾂Ƃ��̏���

	// ����
	effect.push_back(new c_Explosion3D(&player->GetMatCar()));
	NewSound(&Co_Sound_Category_Explosion, 1, &judg.SetPosM(&player->GetMatCar()), &Co_SoundNew);
	
	GemeEndChange(&Co_Stage_End_Over);

	for (unsigned int e = 0; e < enemy.size(); e++) {
		enemy[e]->SetPlaEnd(true/*, player->GetSpeedCar()*/);
	}
	player->SetSpeedCar(&(player->GetCon().Speed *0.0f));
	war->SetFlg(false);
	//���j���[�̕\��
	SetMenu(new C_OverTouch());
}

void GameScene::SetGameClear(void)
{
	if (GetEndFlg() == true)return;

	GemeEndChange(&Co_Stage_End_Clear);
	SetMenu(new C_ClearTouch());

	int No = 5;
	soundGameManager->BGMStart(&No);
}

bool GameScene::UpdateBullet(void)
{
	//�e��MoveVec�̉��Z
	if (player != nullptr) player->MoveVec_Bullet();

	if (enemy.size() > 0)
	{
		for (auto && e : enemy) e->MoveVec_Bullet();
	}

	//�e�̏o������
	BulletInitPlayer();
	BulletInitEnemy();

	//�e�̏o��
	if (player != nullptr) 
	{
		if (GetEndFlg() != true) player->Init_Bullet();
	}

	if (enemy.size() > 0)
	{
		for (auto && e : enemy) e->Init_Bullet();
	}

	//�e�̓����蔻��
	UpdateBulletJudg();

	//�e�̍X�V
	if (player != nullptr) player->Update_Bullet();

	if (enemy.size() > 0)
	{
		for (auto && e : enemy) e->Update_Bullet();
	}

	return true;
}

void GameScene::BulletInitPlayer(void)
{
	//�Ə��̃��C����
	S_RayHitJudgData HitData;
	HitData.Flg = false;

	BULLETJUDGDATA l_DisD;
	float Dis = 2000.0f;
	c_StructManager structManager;
	l_DisD = structManager.GetBULLETJUDGDATA(&structManager.GetCarType(&co_PlayerCar), &Dis);

	RAYDATA l_RayR;
	l_RayR.Mat = judg.SetMatP(&camera->GetPos());
	l_RayR.Ray = camera->GetVec();
	float Rad = 400.0f;

	//�G�̃��C����
	RayJudgEnemy(&l_DisD, &l_RayR, &Rad);
	if (l_DisD.HitType.Type > 0)HitData.Flg = true;

	//�Ə��̕ω�
	if (HitData.Flg == true) {
		aiming->ChaFlg();
	}
	else {
		aiming->ResFlg();
	}

	//�n��
	if (groundManager != nullptr)groundManager->BulletJudg(&l_DisD, &l_RayR, nullptr, &Rad);

	if (l_DisD.HitType.Type > 0)HitData.Flg = true;
	//�����̃��C����
	//�o���b�g�̏o������
	if (HitData.Flg == false) {
		player->Set_Gun_Ray_Data(&HitData);
	}
	else {

		//���C�������������W
		HitData.HitPos = judg.GetRayHitPos(&camera->GetPos(), &l_RayR.Ray, &l_DisD.SamllDis);

		player->Set_Gun_Ray_Data(&HitData);
	}

	bool T_Flg = false;
	if (key.LClickF_N() == true) {
		T_Flg = true;
	}
	unsigned int GunNo = 0;

	player->Set_Gun_Trigger(&GunNo, &T_Flg);

}

void GameScene::BulletInitEnemy(void)
{
	if (enemy.size() < 1)return;

	for (unsigned int ec = 0; ec < enemy.size(); ec++) 
	{
		if (enemy[ec]->Get_Gun_Num() <= 0) continue;

		for (unsigned int gc = 0; gc < enemy[ec]->Get_Gun_Num(); gc++) 
		{
			if (enemy[ec]->Get_Gun_Data(&gc).Ray_Judg_Flg != true) continue;

			//���C����
			c_StructManager structManager;
			BULLETJUDGDATA b;
			b.SamllDis = enemy[ec]->Get_Gun_Data(&gc).RayDis;
			b.JudgType = structManager.GetCarType(&co_EnemyCar, &ec);
			RAYDATA r;
			r.Mat = enemy[ec]->Get_Gun_Data(&gc).DrawBase.Mat;
			D3DXVec3TransformNormal(&r.Ray, &D3DXVECTOR3(0.0f, 0.0f, 1.0f), &r.Mat);
			float Rad = (float)RadChara*2.0f;

			//���C����
			RayJudgPlayer(&b, &r, &Rad);
			RayJudgEnemy(&b, &r, &Rad);

			//���C��������������Flg
			bool Ray_HitFlg = false;
			if (b.HitType.Type > 0)Ray_HitFlg = true;

			enemy[ec]->Set_Ray_Hit_Flg(&gc, &Ray_HitFlg);
			enemy[ec]->Set_Ray_Dis(&gc, &b.SamllDis);
		}
	}

}

bool GameScene::UpdateBulletJudg(void)
{
	BULLETJUDGDATA Bullet;

	RAYDATA BulletRay;

	float Dis, Rad = (float)RadJudgF;

	if (player != nullptr) 
	{
		if (player->Get_BulletNum() > 0)
		{
			for (unsigned int bc = 0; bc < player->Get_BulletNum(); bc++)
			{
				//������
				Dis = player->Get_Bullet_MoveDis(&bc);
				c_StructManager structManager;
				Bullet = structManager.GetBULLETJUDGDATA(&structManager.GetCarType(&co_PlayerCar), &Dis);

				BulletRay = player->GetBulletJudgData(&bc);

				//�n��
				if (player->Get_Bullet_GroWal_Judg_Flg(&bc) == true) 
				{
					bool GroWalJudgFlg;
					if (groundManager != nullptr)groundManager->BulletJudg(&Bullet, &BulletRay, &GroWalJudgFlg, &Rad);
					//�����ǂƒn�ʂ𔻒�ł��邩�̑��
					player->Set_Bullet_GroWal_Judg_Flg(&bc, &GroWalJudgFlg);
				}

				//�G
				RayJudgEnemy(&Bullet, &BulletRay, &Rad);
				//�G�̋��p�[�c����
				BulletJudgEnemyBall(&Bullet, &BulletRay, &Rad);
				//���茋�ʂƒe�̍폜
				if (SetBulletDamage(&Bullet, &BulletRay, player->Get_Bullet_Damage(&bc)) == true)player->Delete_Bullet(&bc);
			}
		}
	}

	if (enemy.size() > 0)
	{
		for (unsigned int ec = 0; ec < enemy.size(); ec++) 
		{
			if (enemy[ec]->Get_BulletNum() <= 0)continue;

			for (unsigned int bc = 0; bc < enemy[ec]->Get_BulletNum(); bc++)
			{
				//������
				Dis = enemy[ec]->Get_Bullet_MoveDis(&bc);
				c_StructManager structManager;
				Bullet = structManager.GetBULLETJUDGDATA(&structManager.GetCarType(&co_EnemyCar, &ec), &Dis);

				BulletRay = enemy[ec]->GetBulletJudgData(&bc);

				//�v���C���[
				RayJudgPlayer(&Bullet, &BulletRay, &Rad);
				//�n��
				if (enemy[ec]->Get_Bullet_GroWal_Judg_Flg(&bc) == true)
				{
					bool GroWalJudgFlg;
					if (groundManager != nullptr)groundManager->BulletJudg(&Bullet, &BulletRay, &GroWalJudgFlg, &Rad);
					//�����ǂƒn�ʂ𔻒�ł��邩�̑��
					enemy[ec]->Set_Bullet_GroWal_Judg_Flg(&bc, &GroWalJudgFlg);
				}
				//�G
				RayJudgEnemy(&Bullet, &BulletRay, &Rad);
				//���茋�ʂƒe�̍폜
				if (SetBulletDamage(&Bullet, &BulletRay, enemy[ec]->Get_Bullet_Damage(&bc)) == true)enemy[ec]->Delete_Bullet(&bc);
			}
		}
	}

	return true;
}

void GameScene::NewSound(const int * Type, const int * Category, const int No, const int * Change)
{
	if (soundGameManager == nullptr)return;

	C_Struct_Init C_S_Init;
	soundGameManager->New_Sound_Data(&C_S_Init.Get_S_SOUND_DATA(Type, Category, &No, Change));
}

void GameScene::NewSound(const int * Category, const int No, const D3DXVECTOR3 * Pos, const int * Change)
{
	if (soundGameManager == nullptr)return;

	soundGameManager->New_Sound_Data(Category, No, Pos, Change);
}

bool GameScene::GetEndFlg(void)
{
	if (gameEnd == nullptr)return true;

	return gameEnd->Get_EndFlg();
}

void GameScene::GemeEndChange(const int * Mode)
{
	if (gameEnd == nullptr)return;

	C_Game_End_Base* Game_End;

	Game_End=gameEnd->Change(Mode);

	if (Game_End != nullptr) {
		delete gameEnd;
		gameEnd = Game_End;
	}
}

void GameScene::PopEnemy(void)
{
	//�G�l�~�[�̏o��
	if (GetCarPop(&co_EnemyCar) != true) return;

	//�Ԃ̏��擾
	S_CAR_INIT_DATA L_Data = carPop->Get_Next_Car_Data_N();

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
	if (CarPopJudg(&GroundMat, &TransX) != true)return;

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
	carPop->Car_Init_Rear_N();
}

bool GameScene::CarPopJudg(const D3DXMATRIX * GroundMat, const float * TransX)
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
	if (player != nullptr)
	{
		if(player->BallJudgCar(&Pop_Pos,&Radius))return false;
	}

	//�G�l�~�[�Ƃ̔���
	if (enemy.size() > 0)
	{
		for (auto && e : enemy)
		{
			if (e->BallJudgCar(&Pop_Pos, &Radius))return false;
		}
	}

	//�o���\
	return true;
}

void GameScene::RayJudgPlayer(BULLETJUDGDATA * BJD, const RAYDATA * RD, const float *Rad)
{
	if (player == nullptr)return;
	if (BJD->JudgType.Type == co_PlayerCar)return;

	player->RayJudg(BJD, nullptr, RD, Rad);
}

void GameScene::RayJudgEnemy(BULLETJUDGDATA * BJD, const RAYDATA * RD, const float * Rad)
{
	if (enemy.size() <= 0)return;

	//enemy�̐�
	for (unsigned int e = 0; e < enemy.size(); e++) {

		if ((BJD->JudgType.Type==co_EnemyCar)&&(e == BJD->JudgType.Numbar[0]))continue;

		enemy[e]->RayJudg(BJD, &e, RD, Rad);

	}
}

void GameScene::BulletJudgEnemyBall(BULLETJUDGDATA * BJD, const RAYDATA * RD, const float * Rad)
{
	if (enemy.size() <= 0)return;

	D3DXVECTOR3 BPos;
	judg.SetPosM(&BPos, &RD->Mat);

	//enemy�̐�
	for (unsigned int e = 0; e < enemy.size(); e++) {
		enemy[e]->BallJudgParst(BJD, &BPos, &co_EnemyCar, &e, &RD->Ray, Rad);
	}
}

bool GameScene::SetBulletDamage(const BULLETJUDGDATA * BJD, const RAYDATA * RD, const int Damage)
{
	if (BJD->HitType.Type < 0)return false;

	//�n��///////////////////////////////////////////////////////////////////////////////////
	//�n��
	if (BJD->HitType.Type == co_Ground) 
	{
		//�Ή�
		D3DXVECTOR3 RayHitPos = judg.GetRayHitPos(&judg.SetPosM(&RD->Mat), &RD->Ray, &BJD->SamllDis);

		int SpeType = 0;
		float Ang = 0.0f;
		effect.push_back(new C_BulGro(&groundManager->GetGroundMat(&BJD->HitType.Numbar[0]), &RayHitPos));

		//�e���RD
		float Ray_Dis = BJD->SamllDis - 0.01f;

		RayHitPos = judg.GetRayHitPos(&judg.SetPosM(&RD->Mat), &RD->Ray, &Ray_Dis);

		effect.push_back(new C_BulletHole3D(&groundManager->GetGroundMat(&BJD->HitType.Numbar[0]), &RayHitPos, 2));

		//��e���̏�����
		if (soundGameManager != nullptr)soundGameManager->Set_Bullet_Hit_Sound(&Hit_Type_Ground, &RayHitPos);

		return true;
	}

	//��
	if (BJD->HitType.Type == co_Wall)
	{
		//�Ή�
		D3DXVECTOR3  RayHitPos = judg.GetRayHitPos(&judg.SetPosM(&RD->Mat), &RD->Ray, &BJD->SamllDis);

		int SpeType = 1;
		float Ang = 0.0f;
		//�Ή�
		unsigned int i = (int)BJD->HitType.Numbar[1];
		for (int s = 0; s < 5; s++) {
			effect.push_back(new C_SparkDamage(&groundManager->GetWallMat(&BJD->HitType.Numbar[0], &i), &RayHitPos, &SpeType, &Ang));
		}
		//�e���RD
		float Ray_Dis = BJD->SamllDis - 0.01f;

		RayHitPos=judg.GetRayHitPos(&judg.SetPosM(&RD->Mat), &RD->Ray, &Ray_Dis);

		effect.push_back(new C_BulletHole3D(&groundManager->GetWallMat(&BJD->HitType.Numbar[0], &i), &RayHitPos, 1));

		//��e���̏�����
		if (soundGameManager != nullptr)soundGameManager->Set_Bullet_Hit_Sound(&Hit_Type_Wall, &RayHitPos);

		return true;
	}

	//�v���C���[/////////////////////////////////////////////////////////////////////////////
	//�ԑ�
	if (BJD->HitType.Type == co_PlayerCar)
	{
		if (player->SetHP(Damage, false) == true) {
			//�_���[�W���󂯂���
			int sc = -10;
			score->ScoreUp(&sc);

			//��e���W
			D3DXVECTOR3 RayPos;

			//��e���̏�����
			if (soundGameManager != nullptr)soundGameManager->Set_Bullet_Hit_Sound(&Hit_Type_Player, &RayPos);
		}
		return true;
	}
	//�W���p�[�c
	if (BJD->HitType.Type == co_PlayerParts)return true;
	//�e
	//if ()return true;

	//�G�l�~�[//////////////////////////////////////////////////////////////////////////////
	//�ԑ�
	if (BJD->HitType.Type == co_EnemyCar)
	{
		if (enemy[BJD->HitType.Numbar[0]]->GetFlgCar() == false)return true;

		bool DamageFlg = enemy[BJD->HitType.Numbar[0]]->SetHP(Damage, false);

		if (damageNumDraw3DManager != nullptr)
		{
			D3DXMATRIX L_JudgMat = player->GetCon().JudgMat;
			damageNumDraw3DManager->NewDamageNumDraw(&BJD->JudgType.Type, &RD->Mat, &RD->Ray, &BJD->SamllDis, &Damage, &DamageFlg, &L_JudgMat);
		}

		//��e���̏�����
		// ��e���W
		D3DXVECTOR3 RayPos = judg.GetRayHitPos(&judg.SetPosM(&RD->Mat), &RD->Ray, &BJD->SamllDis);
		if (soundGameManager == nullptr)soundGameManager->Set_Bullet_Hit_Sound(&Hit_Type_Enemy, &RayPos, &DamageFlg);

		return true;
	}
	//�W���p�[�c
	if (BJD->HitType.Type == co_EnemyParts)
	{
		bool DamageFlg = enemy[BJD->HitType.Numbar[0]]->Damage_CarParts(&BJD->HitType.Numbar[1], &Damage);

		if (damageNumDraw3DManager != nullptr)
		{
			D3DXMATRIX L_JudgMat = player->GetCon().JudgMat;
			damageNumDraw3DManager->NewDamageNumDraw(&BJD->JudgType.Type, &RD->Mat, &RD->Ray, &BJD->SamllDis, &Damage, &DamageFlg, &L_JudgMat);
		}

		//��e���̏�����
		// ��e���W
		D3DXVECTOR3 RayPos = judg.GetRayHitPos(&judg.SetPosM(&RD->Mat), &RD->Ray, &BJD->SamllDis);
		if (soundGameManager == nullptr)soundGameManager->Set_Bullet_Hit_Sound(&Hit_Type_Enemy, &RayPos, &DamageFlg);

		return true;
	}
	//�e
	if (BJD->HitType.Type == co_EnemyGun)
	{
		bool DamageFlg = enemy[BJD->HitType.Numbar[0]]->Damage_Gun(&BJD->HitType.Numbar[1], &Damage);

		if (damageNumDraw3DManager != nullptr)
		{
			D3DXMATRIX L_JudgMat = player->GetCon().JudgMat;
			damageNumDraw3DManager->NewDamageNumDraw(&BJD->JudgType.Type, &RD->Mat, &RD->Ray, &BJD->SamllDis, &Damage, &DamageFlg, &L_JudgMat);
		}

		//��e���̏�����
		// ��e���W
		D3DXVECTOR3 RayPos = judg.GetRayHitPos(&judg.SetPosM(&RD->Mat), &RD->Ray, &BJD->SamllDis);
		if (soundGameManager == nullptr)soundGameManager->Set_Bullet_Hit_Sound(&Hit_Type_Enemy, &RayPos, &DamageFlg);

		return true;
	}

	//�������Ă��Ȃ�
	return false;
}

void GameScene::WallSparkInit(bool * Spark_Init_Flg, const D3DXMATRIX * RayHit_Mat, const D3DXVECTOR3 * RayHit_Pos, bool * LeftFlg)
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

void GameScene::CarSparkInit(const bool * Spark_Init_Flg, const D3DXMATRIX * RayHit_Mat, const D3DXVECTOR3 * RayHit_Pos)
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

void GameScene::EnemyStop(const unsigned int * e, const int * Side_Judg_Car_Type)
{
	if (*Side_Judg_Car_Type != Hit_Type_Player)return;

	if (enemy[*e]->GetFlgCar() != true)return;

	if (enemy[*e]->Get_Move_Stop_Time() > 0)return;

	int Time = 60 * 8, L_Speed = player->GetCon().NowSpeed;

	enemy[*e]->Set_Move_Stop_Time(&Time,&L_Speed);
}

void GameScene::FrustumCulling(const D3DXMATRIX * mProj, const D3DXMATRIX * mView, const D3DVIEWPORT9 * Viewport)
{
	S_Frustum_Vec FV_Data;

	judg.Get_Frustum_NormalVec(&FV_Data, mProj, mView, Viewport);

	if (groundManager != nullptr)groundManager->FrustumCulling(&FV_Data,&camera->GetPos());
}

void GameScene::BallJudgPlayer(bool * JudgFlg, float * SmallDis, s_CarType * HitCar
	, const s_CarType * JudgCar, const D3DXMATRIX * EndMat, const float * Radius
	, const bool * CollisionJudg_TrueFlg)
{
	//�v���C���[�ƃv���C���[�Ŕ��肵�Ȃ��悤�ɂ���
	if (JudgCar->Type == Hit_Type_Player)return;

	//�S�Ă̐퓬���I�����Ă���Ƃ��v���C���[�Ɣ��肵�Ȃ�
	if (GetEndFlg() != false) return;

	//����ł��Ȃ���Ԃ̏ꍇ��������Ȃ�
	if (*CollisionJudg_TrueFlg != true)return;

	// ��������
	if (player->BallJudgCar(JudgFlg, SmallDis, EndMat, Radius) != true) return;

	*JudgFlg = true;
	HitCar->Type = Hit_Type_Player;
}

void GameScene::BallJudgEnemy(bool * JudgFlg, float * SmallDis, s_CarType * HitCar
	, const s_CarType * JudgCar, const D3DXMATRIX * EndMat, const float * Radius
	, const bool * CollisionJudg_TrueFlg)
{
	//�o�����Ă���G�����Ȃ��ꍇ���C���肵�Ȃ�
	if (enemy.size() <= 0)return;

	//�S�Ă̐퓬���I�������ꍇ�v���C���[�̎ԂƔ��肵�Ȃ�
	if ((GetEndFlg() == true) && (JudgCar->Type == Hit_Type_Player))return;

	for (unsigned int e = 0; e < enemy.size(); e++) {

		//�����G�Ŕ��肵�Ȃ�
		if ((JudgCar->Type == Hit_Type_Enemy) && (JudgCar->Numbar[0] == e))continue;

		//�G�������ł���ꍇ���肵�Ȃ�
		if (enemy[e]->Get_JudgeType() == Co_Judge_NO)continue;

		//���肷��G������ł��Ȃ���ԂŃv���C���[�Ɣ��肷��ꍇ���肵�Ȃ�
		//if ((*Car_Type == Hit_Type_Player) && (enemy[e]->Get_CollisionJudg_TrueFlg() != true))continue;

		// ��������
		if (enemy[e]->BallJudgCar(JudgFlg, SmallDis, EndMat, Radius) != true) continue;

		*JudgFlg = true;
		HitCar->Type = Hit_Type_Enemy;
		HitCar->Numbar[0] = e;

		/*if (*Car_Type == Hit_Type_Player) {
			bool Flg = false;
			enemy[e]->Set_CollisionJudg_TrueFlg(&Flg);
		}*/
	}
}

void GameScene::CarPopDataUpdate(void)
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
	if (carPop != nullptr)carPop->M_Car_Pop_Update_N(enemy);

	////�������̉��
	//if (L_Enemy_Data != nullptr)delete[] L_Enemy_Data;
}
