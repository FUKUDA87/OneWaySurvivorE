#include"GameScene.h"
#include"TitleScene.h"
#include"StageSelectScene.h"
#include"SceneManager.h"
#include"../GameSource/option.h"
#include"../GameSource/Enum.h"
#include"../GameSource/Judgment.h"
#include"../GameSource/TextureManager.h"
#include"../GameSource/XfileManager.h"
#include"../GameSource/InvBi.h"
#include"../GameSource/Motion.h"
#include"../Sound/Bgm.h"
#include"../Draw3DBase/Draw3DManager/CarSmogManager.h"
#include"../EnemyData/Base&Manager/Enemy_Manager.h"
#include"../Const/Const_Phase_Type.h"
#include"../Const/Const_Rail_Type.h"

extern C_Bgm *bgm;
extern int CountManager;
extern Motion motion;
extern Inv inv;
extern TextureManager textureManager;
extern XfileManager xfileManager;
extern SceneManager sceneManager;
extern Judg judg;
extern Option option;
extern LPDIRECT3DDEVICE9		lpD3DDevice;	// Direct3DDevice�C���^�[�t�F�C�X
extern LPD3DXSPRITE lpSprite;	// �X�v���C�g
extern LPD3DXFONT lpFont;		// �t�H���g
extern D3DXVECTOR3 CamPosG;
extern float AngD;
#define	SCRW		1280	// �E�B���h�E���iWidth
#define	SCRH		720		// �E�B���h�E�����iHeight
#define RadJudgF 100
#define StageSelectNo 2
#define GameNo 3
#define TitleNo 1

GameScene::GameScene(const int stageNum){
	AllNew();

	debugT = new DebugT();

	//�}�E�X�̏�����
	mouse = new C_Mouse();
	mouse->Init();
	mouse->ChaDrawFlg(false);

	//�v���C���[�̏������O�ɏ�����
	PlayerBody = new C_PlayerBody();

	player = new C_PlayerA(&PlayerBody->GetPData());

	//�n�ʏ�����--------------------------------------------------------
	//�O���̊Ԋu������
	int CountInit = 4;
	LightCount = new C_Count(&CountInit);

	cou = new Cou(0, 5, 1, true, false);
	int i = 0, z;
	ground.push_back(new BillBase(i));
	z = (int)ground[0]->GetPosZ() * 2;
	i = (int)player->GetRadF() / z;
	delete ground[0];
	ground.erase(ground.begin() + 0);
	for (int n = i * (-1); n < i; n++) {
		if (cou->CouJudge() == false) {
			cou->SetNum(0);
		}
		if (cou->GetNum() == 1) {
			ground.push_back(new BillBase(n)); //ground.push_back(new BillBase(n));
		}
		else {
			ground.push_back(new Bill(n));
		}
		//�O���̏�����
		if (LightCount->Update() == true) {
			int wNum = 2;
			ground[ground.size() - 1]->InitLight(&wNum);
		}
		cou->CouUpd();
	}
	for (unsigned int i = 0; i < ground.size(); i++) {
		if (judg.ball(player->GetMatCar(), ground[i]->GetMat(), player->GetRadF()) == false) {
			delete ground[i];
			ground.erase(ground.begin() + i);
			i--;
		}
	}
	int c = 2;
	/*for (int i = (ground.size() - 1); i >= 0; i--) {
		if (ground[i]->GetObjFlg() == true) {
			if (c == 4) c = 1;
			break;
		}
		else {
			c++;
		}
	}*/
	cou->SetNum(c);
	//player�̈ʒu����
	unsigned int num;
	float Dis;
	if (ground.size() > 100) {
		i = (int)((float)ground.size() *0.9f);
		D3DXMATRIX gMat, Trans;
		gMat = ground[i]->GetWay().StartMat;
		D3DXMatrixTranslation(&Trans, 0.0f, 0.1f, 0.0f);
		Trans = Trans * gMat;
		player->SetMatCar(&Trans);
		player->SetRadF(player->GetRadF() / 2.0f);
	}
	if (NowGroNum(player->GetMatCar(), &num, &Dis) == true) {
		player->SetGroNum(num);//�n�ʂ̎擾
		eneFlg = true;
	}

	//---------------------------------------------------------------------

	//�X�R�A�̏�����
	score = new C_Score();
	sky = new Sky();
	camera = new Camera(player->GetMatCar());
	aiming = new Aiming();
	debug = new Debug();
	eneFlg = false;//�G�̏o��OFF
	GaOv = new GameOver();

	//�V�[���̐؂�ւ�������
	SceneChangeFlg = false;
	//�t�F�[�h�̏�����
	fade = new Fade();
	fade->ChaFlg(false);

	EndFlg = false;
	key.Init();

	war = new Warning();

	pause = new Pause();

	//BulletBirthFlg���ŏ��͏o�Ȃ��悤�ɂ���
	BulletBirthFlg = false;

	//�Ԃ̏o���̏�����
	StageNo = stageNum;
	M_C_Car_Pop = new C_Car_Pop_New(&StageNo);

	CountNum = MaxCount = 1;
	spear = new Spear();
	D3DXMatrixTranslation(&SpeMat, 0.0f, 0.0f, 0.0f);


	//bgm������
	bgm->ChangeBgm(2);

	Size = 1.0f;

}
GameScene::~GameScene() {

	AllDelete();

	//���j���[�̍폜
	DeleteMenu();
}
void GameScene::Render3D(void) {
	/*if (player->GetBulSiz() > 0) {
		spear->Draw3DV(player->GetBulMat(0));
	}*/
	sky->Draw();
	for (unsigned int i = 0; i < ground.size(); i++) {
		ground[i]->SuperDraw();
	}
	for (unsigned int i = 0; i < explo.size(); i++) {
		explo[i]->ExplDraw();
	}
	if (enemy.size() > 0) {
		for (unsigned int i = 0; i < enemy.size(); i++) {
			enemy[i]->Draw3DAll(&camera->GetPos());
		}
	}

	player->Draw3DAll(&camera->GetPos());

	//�e���̕\��
	if (BHole3D.size() > 0) {
		for (unsigned int b = 0; b < BHole3D.size(); b++) {
			BHole3D[b]->Draw3DHol3D();
		}
	}

	//�ΉԂ̕\��
	if (SparkV.size() > 0) {
		for (unsigned int s = 0; s < SparkV.size(); s++) {
			SparkV[s]->Draw3DSuper();
		}
	}

	if (M_C_SmokeCar != nullptr) {
		M_C_SmokeCar->Draw3D_CS(&camera->GetPos());
	}

}
void GameScene::Render2D(void) {
	//////////////////////////////////////////////////
	///	�X�v���C�g�̕`�揈��
	//////////////////////////////////////////////////
	// �`��J�n
	lpSprite->Begin(D3DXSPRITE_ALPHABLEND);
	if (enemy.size() > 0) {
		for (unsigned int i = 0; i < enemy.size(); i++) {
			enemy[i]->Draw2DAll();
		}
	}
	aiming->Draw();
	player->Draw2DAll();
	//�X�R�A�̕\��
	score->Draw2D();
	//�N���A�ƃI�[�o�[�̕\��
	GaOv->Draw2D();
	//�{�X�o���\��
	war->Draw2D();

	//�|�[�Y�̕\��
	pause->Draw2DPau();

	//���j���[�̕\��
	if (Menu.size() > 0) {
		for (auto && m : Menu) {
			m->Draw2DAll();
		}
	}

	//�t�F�[�h�C���A�E�g�̕\��
	fade->Draw();
	mouse->Draw2D();
	// �`��I��
	lpSprite->End();
	/*debug->Draw();
	debugT->Draw2DT();
	debugT->Draw2DTd();*/
	/*float f=0.0f;
	debugT->Draw2DF(f, 0, 0);*/
}
bool GameScene::Update(void) {

	if (Change_TitleScene() != true)return false;

	Update_Bgm();

	Update_Debug();

	mouse->Update();

	if (Update_Fade() != true)return false;

	Update_Game();

	//���j���[�̍X�V
	UpdateMenu();

	return true;
}
bool GameScene::UpdateE(void)
{
	//=======================================================================================================================
	//�G�l�~�[Update
	//=======================================================================================================================

	if (enemy.size() > 0) {
		//�n�ʔ���2
		for (unsigned int e = 0; e < enemy.size(); e++) {
			if (enemy[e]->GetFlgCar() == true) {
				//enemy�ƒn�ʔ���
				unsigned int num;
				float dis;
				if (NowGroNum(enemy[e]->GetMatCar(), &num, &dis) == true) {
					enemy[e]->SetGroNum(num);
				}
				else {
					delete enemy[e];
					enemy.erase(enemy.begin() + e);
					e--;
				}
			}
		}
		for (unsigned int e = 0; e < enemy.size(); e++) {
			EnemyDelete(&e);
		}
		for (unsigned int i = 0; i < enemy.size(); i++) {
			//if (enemy[i]->Get_Gun_Num() > 0) {
			//	for (unsigned int g = 0; g < enemy[i]->Get_Gun_Num(); g++) {
			//		if (enemy[i]->Get_Gun_Data(&g).Ray_Judg_Flg == true) {
			//			//���C����
			//			BULLETJUDGDATA b;
			//			b.SamllDis = enemy[i]->Get_Gun_Data(&g).RayDis;
			//			RAYDATA r;
			//			r.Mat = enemy[i]->Get_Gun_Data(&g).DrawBase.Mat;
			//			D3DXVec3TransformNormal(&r.Ray, &D3DXVECTOR3(0.0f, 0.0f, 1.0f), &r.Mat);
			//			float Rad = (float)RadChara*2.0f;
			//			BulletJudgPlayer(&b, &r, &Rad);
			//			bool Flg=false;
			//			if (b.Type > 0)Flg = true;

			//			enemy[i]->Set_Ray_Hit_Flg(&g, &Flg);
			//			enemy[i]->Set_Ray_Dis(&g, &b.SamllDis);
			//		}
			//	}
			//}

			

			if (enemy[i]->GetFlgCar() == true) {
				debugT->Update(true);

				//�����蔻��i�G�l�~�[�ƒe�j
				judgDeta jd;
			}
			if ((enemy[i]->GetDeleFlg() == false)&&(judg.ball(enemy[i]->GetMatCar(),player->GetMatCar(),400.0f)==false)) {
				delete enemy[i];
				enemy.erase(enemy.begin() + i);
				i--;
			}

		}
	}
	if (EndFlg == true) {
		return true;
	}
	//�G�S�ł̊m�F



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

	inv.GetInvRotateMat(camera->GetPos(), camera->GetLook(), D3DXVECTOR3(0.0f, 1.0f, 0.0f));

	CamPosG = camera->GetPos();

	//Pos2D�̂�������
	D3DVIEWPORT9 Viewport;
	lpD3DDevice->GetViewport(&Viewport);
	//Pos2D���g��
	Pos2DUpdate(&mProj, &mView, &Viewport);
}
void GameScene::GDebug(void)
{
	//--------------------------
	//�ԓ��v�Z
	//--------------------------
	/*debug->KeyUpdate();
	debug->SetDebugMat(ground[debug->GetNum()]->GetVwMat(0));
	ground[debug->GetNum()]->SetVwMat(0, debug->GetDebugMat());
	if (key->RETURNKeyF()) {
		player->SetMat(debug->GetDebugMat());
	}*/
	//���
	//debug->SetFlo(enemy[0]->GetAng());
	/*D3DXMATRIX mat,Trans;
	mat = enemy[0]->GetEnemyMat();
	D3DXVECTOR3 Pos;
	//Pos=judg.Pos2D(Pos, D3DXVECTOR3(mat._41, mat._42, mat._43));
	D3DXMatrixTranslation(&Trans, Pos.x, Pos.y, Pos.z);
	debug->SetDebugMat(Trans);*/
	debug->SetDebugMat(player->GetMatCar());
}

bool GameScene::NowGroNum(D3DXMATRIX Mat,unsigned int *Num,float *Dis)
{
	if (ground.size() <= 0) {
		return false;
	}
	float size;
	//�n�ʃ��C����
	for (unsigned int g = 0; g<ground.size(); g++) {
		if (judg.ball(Mat, ground[g]->GetMat(), (float)RadJudgF) == true) {//�����̎��͂̒n�ʂ����𔻒�
			D3DXVECTOR3 v[4];
			for (int i = 0; i < 4; i++) {
				v[i] = ground[g]->GetVer(i);
			}
			if (ground[g]->GetIdenFlg() == false) {//�n�ʂ�IdentityMat�ŏo���Ă��邩�̔���
				if (judg.RayPolM(Mat, v[0], v[1], v[2], v[3], ground[g]->GetMat(), D3DXVECTOR3(0.0f, -1.0f, 0.0f), &size) == true)//�|���S���ƃ��C����
				{
					*Num = g;
					*Dis = size;
					return true;
				}
			}
			else {
				if (judg.RayPolM(Mat, v[0], v[1], v[2], v[3], D3DXVECTOR3(0.0f, -1.0f, 0.0f), &size) == true)//�|���S���ƃ��C����
				{
					*Num = g;
					*Dis = size;
					return true;
				}
			}
		}
	}
	return false;
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

			BulletRay.Mat = player->Get_Bullet_Mat(&b);
			D3DXVec3TransformNormal(&BulletRay.Ray, &D3DXVECTOR3(0.0f, 0.0f, 1.0f), &BulletRay.Mat);

			//�n��
			if (player->Get_Bullet_GroWal_Judg_Flg(&b) == true) {
				bool GroWalJudgFlg;
				BulletJudgGround(&Bullet, &BulletRay,&GroWalJudgFlg,&Rad);
				//�����ǂƒn�ʂ𔻒�ł��邩�̑��
				player->Set_Bullet_GroWal_Judg_Flg(&b, &GroWalJudgFlg);
			}

			//�G
			BulletJudgEnemy(&Bullet, &BulletRay,&Rad);
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

			BulletRay.Mat = enemy[*No]->Get_Bullet_Mat(&b);
			D3DXVec3TransformNormal(&BulletRay.Ray, &D3DXVECTOR3(0.0f, 0.0f, 1.0f), &BulletRay.Mat);

			//�v���C���[
			BulletJudgPlayer(&Bullet, &BulletRay,&Rad);
			//�n��
			BulletJudgGround(&Bullet, &BulletRay,NULL,&Rad);
			//���茋�ʂƒe�̍폜
			if (SetBulletDamage(&Bullet, &BulletRay, enemy[*No]->Get_Bullet_Damage(&b)) == true)enemy[*No]->Delete_Bullet(&b);
		}
		//����I��
		return;
	}

}

bool GameScene::WallJudg(bool LeftFlg, bool PlayerFlg, bool EnemyFlg, unsigned int No)
{
	//����̏I��Flg
	bool JudgEndFlg = false;
	struct WallJudgChara {
		bool LeftFlg;
		bool PlayerFlg;
		bool EnemyFlg;
		unsigned int No;
		float Rad;
	};
	WallJudgChara Body;
	Body.LeftFlg = LeftFlg;
	Body.PlayerFlg = PlayerFlg;
	Body.EnemyFlg = EnemyFlg;
	Body.No = No;
	int MaxJudgMatNum = 3;
	D3DXMATRIX *JudgMat;
	JudgMat = new D3DXMATRIX[MaxJudgMatNum];

	//�����������C�̔ԍ�
	int JudgRayNum;
	//��������Mat
	D3DXMATRIX BaseMat;

	//���EWhile������
	int CountNum=20;

	//�Ήԗp�ǔ����͏o�������Ȃ��pFlg
	bool WallSparkFlg = false;

	while (JudgEndFlg == false) {
		//���̔����
		WallJudgChara NextBody;
		int CarFlg = 0;//�v���C���[���G�l�~�[����ʎԂ����ʂ���Flg
		//����pMat
		D3DXMATRIX TransMat;
		//����p���C
		D3DXVECTOR3 JudgVec;
		//��Ԑ��l�̍���Z�ƒႢZ
		float BigZ, SmallZ;
		//�g����W
		D3DXVECTOR3 ScalPosB;
		//��������Ă���Ԃ̏��
		if (Body.PlayerFlg == true) {
			//�v���C���[
			CarFlg = 1;
			ScalPosB = player->GetScalPosCar();
			//Mat�̍쐬
			JudgMat[1] = player->GetCon().JudgMat;
			BigZ = player->GetCon().PosBig.z*ScalPosB.z;
			SmallZ = player->GetCon().PosSmall.z*ScalPosB.z;
			TransMat = player->GetTransMatCar();
			//Rad������
			if (Body.LeftFlg == true) {
				//��
				Body.Rad = player->GetCon().PosSmall.x*ScalPosB.x;
			}
			else {
				//�E
				Body.Rad = player->GetCon().PosBig.x*ScalPosB.x;
			}
		}
		else {
			if (Body.EnemyFlg == true) {
				if ((enemy.size() <= 0) || (enemy[Body.No]->GetFlgCar() == false)) {
					return false;
				}
				//�G�l�~�[
				CarFlg = 2;
				ScalPosB = enemy[Body.No]->GetScalPosCar();
				//Mat�̍쐬
				JudgMat[1] = enemy[Body.No]->GetCon().JudgMat;
				BigZ = enemy[Body.No]->GetCon().PosBig.z*ScalPosB.z;
				SmallZ = enemy[Body.No]->GetCon().PosSmall.z*ScalPosB.z;
				TransMat = enemy[Body.No]->GetTransMatCar();
				//Rad������
				if (Body.LeftFlg == true) {
					//��
					Body.Rad = enemy[Body.No]->GetCon().PosSmall.x*ScalPosB.x;
				}
				else {
					//�E
					Body.Rad = enemy[Body.No]->GetCon().PosBig.x*ScalPosB.x;
				}
			}
			else {
				//��ʎ�
				CarFlg = 3;
			}
		}
		if (Body.Rad < 0.0f)Body.Rad *= -1.0f;
		Body.Rad += 0.01f;
		//Mat�̍쐬
		D3DXMATRIX Trans;
		for (int i = 0; i < MaxJudgMatNum; i++) {
			JudgMat[i] = TransMat * JudgMat[1];
		}
		D3DXMatrixTranslation(&Trans, 0.0f, 0.0f, BigZ);
		JudgMat[0] = Trans * JudgMat[1];
		D3DXMatrixTranslation(&Trans, 0.0f, 0.0f, SmallZ);
		JudgMat[2] = Trans * JudgMat[1];
		//���C�̕���
		D3DXVECTOR3 Vec;
		if (Body.LeftFlg == true) {
			Vec = D3DXVECTOR3(-1.0f, 0.0f, 0.0f);
		}
		else {
			Vec = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
		}
		D3DXVec3TransformNormal(&JudgVec, &Vec, &JudgMat[1]);
		//����p���C�̋���
		float Dis, SmallDis = Body.Rad;
		if (SmallDis < 0.0f)SmallDis *= -1.0f;
		//���C�����trueCar��
		int CountCar = 0;
		//�����������̔���
		bool JudgFlg = false;
		//player����
		if (CarFlg != 1) {
			//
			if (EndFlg == false) {
				//�͈͓�����
				if (judg.ball(JudgMat[1], player->GetMatCar(), (float)RadJudgF) == true) {
					for (int i = 0; i < MaxJudgMatNum; i++) {
						D3DXVECTOR3 JudgPos = judg.SetPosM(JudgMat[i]);
						//���C����
						if (judg.Mesh(JudgPos, JudgVec, player->GetMatCar(), player->GetColMod(), &Dis) == true) {
							//��������
							if (Dis < SmallDis) {
								SmallDis = Dis;
								NextBody.PlayerFlg = true;
								NextBody.EnemyFlg = false;
								NextBody.No = 0;
								JudgRayNum = i;
								BaseMat = player->GetMatCar();
							}
							if (Body.Rad > Dis) {
								JudgFlg = true;
							}
						}
					}
					//�����
					if (JudgFlg == true) {
						CountCar += 1;
						JudgFlg = false;
					}
				}
			}
		}
		//enemy����
		if (enemy.size() > 0) {
			//enemy�̐�
			for (unsigned int e = 0; e < enemy.size(); e++) {
				if ((CarFlg == 2) && (Body.No == e)||(enemy[e]->GetSkyType()==true)) {
					//���肵�Ȃ�
				}
				else {
					//���肷��
					if (enemy[e]->GetFlgCar() == true) {
						//�͈͓�����
						if (judg.ball(JudgMat[1], enemy[e]->GetMatCar(), (float)RadJudgF) == true) {
							for (int i = 0; i < 3; i++) {
								D3DXVECTOR3 JudgPos = judg.SetPosM(JudgMat[i]);
								//���C����
								if (judg.Mesh(JudgPos, JudgVec, enemy[e]->GetDrawMatCar(), enemy[e]->GetColMod(), &Dis) == true) {
									//��������
									if (Dis < SmallDis) {
										SmallDis = Dis;
										NextBody.PlayerFlg = false;
										NextBody.EnemyFlg = true;
										NextBody.No = e;
										JudgRayNum = i;
										BaseMat = enemy[e]->GetMatCar();
									}
									if (Body.Rad > Dis) {
										JudgFlg = true;
									}
								}
							}
							//�����
							if (JudgFlg == true) {
								CountCar += 1;
								JudgFlg = false;
							}
						}
					}
				}
			}
		}
		//�ǔ���
		bool WallJudgFlg = false;
		//�n�ʐ�
		for (unsigned int g = 0; g < ground.size(); g++) {
			//�͈͓�����
			
			if (judg.ball(JudgMat[1], ground[g]->GetWaMat(&Body.LeftFlg,0), (float)RadJudgF) == true) {
				for (int i = 0; i < MaxJudgMatNum; i++) {
					//���C����
					if (judg.Mesh(judg.SetPosM(JudgMat[i]), JudgVec, ground[g]->GetWaMat(&Body.LeftFlg), ground[g]->GetColModWall(&Body.LeftFlg), &Dis) == true) {
						//��������
						if (i == 1) {
							if (Dis < SmallDis) {
								SmallDis = Dis;
								WallJudgFlg = true;
								JudgRayNum = i;
								BaseMat = ground[g]->GetWaMat(&Body.LeftFlg);
							}
						}
					}
				}
			}
		}
		//�S�Ẵ��C����I����
		//����Ȃ������̌v�Z
		float RadDis = Body.Rad;
		if (RadDis < 0.0f)RadDis *= -1.0f;
		RadDis = RadDis - SmallDis;
		//���Ε����ɂ���
		if (Body.LeftFlg == false) RadDis *= -1.0f;
		//�������蔻�肵�Ă���Ԃ����炷
		D3DXMATRIX Trans2;
		D3DXMatrixTranslation(&Trans2, RadDis, 0.0f, 0.0f);
		//���f�p�s��
		D3DXMATRIX TmpMat;

		//�ǂɓ���������
		if (WallJudgFlg == true) {
			if (CarFlg == 1) {
				TmpMat = Trans2 * (player->GetTransMatCar());
				player->SetTransMatCar(&TmpMat);
				TmpMat = player->GetTransMatCar()*player->GetCon().JudgMat;
				player->SetMatCar(&TmpMat);
			}
			if (CarFlg == 2) {
				TmpMat = Trans2 * (enemy[Body.No]->GetTransMatCar());
				enemy[Body.No]->SetTransMatCar(&TmpMat);
				TmpMat = enemy[Body.No]->GetTransMatCar()*enemy[Body.No]->GetCon().JudgMat;
				enemy[Body.No]->SetMatCar(&TmpMat);
				//Hp����鏈��
				if (WallSparkFlg == false) {
					enemy[Body.No]->SetHP(1,true);
					unsigned int eNo = Body.No;
					EnemyDelete(&eNo);
				}
			}
			//�ΉԂ��o������
			//�����o��
			bool InitFlg=false;
			for (int i = 0; i < 20; i++) {
				SparkV.push_back(new C_Spark2(&BaseMat, &(judg.SetPosM(JudgMat[JudgRayNum]) + JudgVec * (SmallDis - 0.1f)),&Body.LeftFlg,&InitFlg));
			}
			InitFlg = true;
			for (int i = 0; i < 15; i++) {
				SparkV.push_back(new C_Spark2(&BaseMat, &(judg.SetPosM(JudgMat[JudgRayNum]) + JudgVec * (SmallDis - 0.1f)), &Body.LeftFlg,&InitFlg));
			}
			//���o�[�X
			judg.ReverseFlg(&Body.LeftFlg);
			//�ǔ����͉ΉԂ��o���Ȃ�
			WallSparkFlg = true;
		}
		else {
			//�����ɓ���������
			if (CountCar >= 2) {
				//�������蔻�肵�Ă����
				if (CarFlg == 1) {
					TmpMat = Trans2 * (player->GetTransMatCar());
					player->SetTransMatCar(&TmpMat);
					TmpMat = player->GetTransMatCar()*player->GetCon().JudgMat;
					player->SetMatCar(&TmpMat);
				}
				if (CarFlg == 2) {
					TmpMat = Trans2 * (enemy[Body.No]->GetTransMatCar());
					enemy[Body.No]->SetTransMatCar(&TmpMat);
					TmpMat = enemy[Body.No]->GetTransMatCar()*enemy[Body.No]->GetCon().JudgMat;
					enemy[Body.No]->SetMatCar(&TmpMat);
				}
				//���o�[�X
				judg.ReverseFlg(&Body.LeftFlg);
			}
			else {
				//1�Ԃ̂ݓ���������
				if (CountCar == 1) {
					//�����o��
					D3DXMatrixTranslation(&Trans2, RadDis*-1.0f, 0.0f, 0.0f);
					//���������Ԕ���
					Body.PlayerFlg = NextBody.PlayerFlg;
					Body.EnemyFlg = NextBody.EnemyFlg;
					Body.No = NextBody.No;
					if (Body.PlayerFlg == true) {
						CarFlg = 1;
					}
					else {
						if (Body.EnemyFlg == true) {
							CarFlg = 2;
						}
						else {
							CarFlg = 3;
						}
					}
					//����������
					if (CarFlg == 1) {
						TmpMat = Trans2 * (player->GetTransMatCar());
						player->SetTransMatCar(&TmpMat);
						TmpMat = player->GetTransMatCar()*player->GetCon().JudgMat;
						player->SetMatCar(&TmpMat);
						//Hp����鏈��
						/*if (WallSparkFlg == false) {
							player->SetHP(1,true);
						}*/

					}
					if (CarFlg == 2) {
						enemy[Body.No]->SetTransMatCar(&judg.GetMatY(&Trans2,&enemy[Body.No]->GetTransMatCar()));
						TmpMat = enemy[Body.No]->GetCon().JudgMat;
						enemy[Body.No]->SetMatCar(&judg.GetMatY(&enemy[Body.No]->GetTransMatCar(),&TmpMat));
						//Hp����鏈��
						if (WallSparkFlg == false) {
							enemy[Body.No]->SetHP(1,true);
							unsigned int eNo = Body.No;
							EnemyDelete(&eNo);
						}
					}
					//�ΉԂ��o������
					if (WallSparkFlg == false) {
						//�����o��
						bool InitFlg = false;
						for (int i = 0; i < 15; i++) {
							SparkV.push_back(new C_Spark2(&BaseMat, &(judg.SetPosM(JudgMat[JudgRayNum]) + JudgVec * (SmallDis - 0.1f)), &InitFlg));
						}
						InitFlg = true;
						for (int i = 0; i < 12; i++) {
							SparkV.push_back(new C_Spark2(&BaseMat, &(judg.SetPosM(JudgMat[JudgRayNum]) + JudgVec * (SmallDis - 0.1f)), &InitFlg));
						}
					}
				}
				else {
					//�������Ă��Ȃ���
					break;
				}
			}
		}
		//����������
		CountNum--;
		if (CountNum <= 0) {
			break;
		}

	}//while���I��
	if (JudgMat != nullptr) {
		delete[] JudgMat;
	}
	return true;
}

bool GameScene::WallJudg(const D3DXMATRIX * JudgMat, D3DXMATRIX * TransMat, const SizePos * sizePos)
{
	return false;
}

bool GameScene::UpdateEnemyAI(void)
{
	//�G�l�~�[�̏o��
	if (Get_Car_Pop(&co_EnemyCar) == true) {
		//�Ԃ̏��擾
		S_CAR_INIT_DATA L_Data = M_C_Car_Pop->Get_Next_Car_Data_N();

		//�n�ʂ̃i���o�[
		unsigned int gNo;
		gNo = player->GetGroNum() + L_Data.GroundNo;
		//�n�ʂ����邩�̔���
		if (gNo < 0)gNo = 0;
		if (gNo > ground.size() - 1)gNo = ground.size() - 1;
		//�Ԑ������߂�
		int Ground_Rail_Num = ground[gNo]->GetWay().RailNum;
		int RailNum = Get_Rail_Num(&Ground_Rail_Num, &L_Data.WayNo);
		//�o���\���ǂ���
		//if (enemy.size() <= 0) {
			//�o���\
			//enemy�̃i���o�[��T��
		D3DXMATRIX GMat = ground[gNo]->GetWay().StartMat;
		if (EnemyBirth(&L_Data.CarNo, &GMat, &ground[gNo]->GetWay().CurTransX[RailNum]) == true) {
			unsigned int num;
			float dis;
			if (NowGroNum(enemy[(enemy.size() - 1)]->GetMatCar(), &num, &dis) == true) {
				enemy[(enemy.size() - 1)]->SetGroNum(num);
			}
			M_C_Car_Pop->Car_Init_Rear_N();
		}
	}

	//Update
	if (enemy.size() > 0) {
		//�n�ʔ���
		for (unsigned int e = 0; e < enemy.size(); e++) {
			if (enemy[e]->GetFlgCar() == true) {
				//enemy�ƒn�ʔ���
				unsigned int num;
				float dis;
				if (NowGroNum(enemy[e]->GetMatCar(), &num, &dis) == true) {
					enemy[e]->SetGroNum(num);
				}
				else {
					if (EndFlg == true) {
						delete enemy[e];
						enemy.erase(enemy.begin() + e);
						e--;
					}
				}
			}
		}
		//AI
		if (EndFlg == false) {
			for (unsigned int i = 0; i < enemy.size(); i++) {
				CHARAData*Data;
				int ChaNum = 0;
				ChaNum += 1;
				Data = new CHARAData[ChaNum];
				Data[0] = player->GetData();
				enemy[i]->UpdateAi(Data, (unsigned int)ChaNum, ground);
				delete Data;
			}
		}
	}
	return false;
}

bool GameScene::UpdateEnemyMove(void)
{
	if (enemy.size() > 0) {
		for (unsigned int i = 0; i < enemy.size(); i++) {
			//
			if (enemy[i]->GetFlgCar() == true) {
				enemy[i]->UpdateAll(ground);//Update
				//�ړ��x�N�g���̃T�C�Y�̏�����
				enemy[i]->SetQuaVecSize(1.0f);
			}
		}
	}
	return false;
}

bool GameScene::ForMoveJudg(CONSTITUTION Con, D3DXMATRIX StartMat, D3DXMATRIX EndMat, bool PlayerFlg, bool EnemyFlg, unsigned int No, D3DXVECTOR3 RayVec1, D3DXVECTOR3 RayVec2, D3DXVECTOR3 RayVec3, float * SpeedMul2,const D3DXVECTOR3 *ScalPos)
{
	int CarFlg = 0;//�v���C���[���G�l�~�[����ʎԂ����ʂ���Flg
	if (PlayerFlg == true) {
		//�v���C���[
		CarFlg = 1;
	}
	else {
		if (EnemyFlg == true) {
			if ((enemy.size() <= 0) || (enemy[No]->GetFlgCar() == false)) {
				return false;
			}
			//�G�l�~�[
			CarFlg = 2;
		}
		else {
			//��ʎ�
			CarFlg = 3;
		}
	}
	D3DXVECTOR3 *MoveVec=new D3DXVECTOR3[3];//�ړ��x�N�g��
	float *VecSize=new float[3];//�x�N�g���̒���
	MoveVec[0] = RayVec1;
	MoveVec[1] = RayVec2;
	MoveVec[2] = RayVec3;
	for (int i = 0; i < 3; i++) {
		VecSize[i] = D3DXVec3Length(&MoveVec[i]);
		if (VecSize[i] < 0.0f)VecSize[i] *= -1.0f;
		VecSize[i] += 0.1f;
		D3DXVec3Normalize(&MoveVec[i], &MoveVec[i]);//�ړ��x�N�g���̐��K��
	}
	D3DXMATRIX TransMat1, TransMat2,TransMat3;//�����̃��C���ˈʒu
	TransMat1 = judg.GetTransMatScal(&D3DXVECTOR3(Con.PosSmall.x, 0.0f, Con.PosBig.z), ScalPos);
	TransMat2 = judg.GetTransMatScal(&D3DXVECTOR3(Con.PosBig.x, 0.0f, Con.PosBig.z), ScalPos);
	TransMat3 = judg.GetTransMatScal(&D3DXVECTOR3(0.0f, 0.0f, Con.PosBig.z), ScalPos);
	
	TransMat1 = TransMat1 * StartMat;
	TransMat2 = TransMat2 * StartMat;
	TransMat3 = TransMat3 * StartMat;
	//���C�̒����ƍŏ�
	float Dis, *SmallDis=new float[3];
	for (int i = 0; i < 3; i++) {
		SmallDis[i] = VecSize[i];
	}
	bool *JudgFlg = new bool[3];
	for (int i = 0; i < 3; i++) {
		JudgFlg[i] = false;
	}

	//player����
	if (CarFlg != 1) {
		//���肷��
		if(EndFlg==false){
		//�i�荞��
			if (judg.ball(StartMat, player->GetMatCar(), (float)RadJudgF) == true) {
				D3DXVECTOR3 JudgPos;//���C�̎n�_
				//�����珇�Ԃ�
				for (int i = 0; i < 3; i++) {
					if (i == 0)JudgPos = D3DXVECTOR3(TransMat1._41, TransMat1._42, TransMat1._43);
					if (i == 1)JudgPos = D3DXVECTOR3(TransMat3._41, TransMat3._42, TransMat3._43);
					if (i == 2)JudgPos = D3DXVECTOR3(TransMat2._41, TransMat2._42, TransMat2._43);
					//���C����
					if (judg.Mesh(JudgPos, MoveVec[i], player->GetForMoveEndMat(), player->GetColMod(), &Dis, 0) == true) {
						//��������
						float Dis2;
						D3DXVECTOR3 Pos2, Vec2;
						D3DXMATRIX Mat;
						for (int n = 0; n < 3; n++) {
							if (n == 0) {
								Mat = judg.GetTransMatScal(&D3DXVECTOR3(Con.PosSmall.x, 0.0f, Con.PosBig.z), ScalPos);
								Mat = Mat * EndMat;
								judg.SetPosM(&Pos2, Mat);
								D3DXVec3TransformNormal(&Vec2, &D3DXVECTOR3(0.0f, 0.0f, 1.0f), &Mat);
							}
							if (n == 1) {
								Mat = judg.GetTransMatScal(&D3DXVECTOR3(0.0f, 0.0f, Con.PosBig.z), ScalPos);
								Mat = Mat * EndMat;
								judg.SetPosM(&Pos2, Mat);
								D3DXVec3TransformNormal(&Vec2, &D3DXVECTOR3(0.0f, 0.0f, 1.0f), &Mat);
							}
							if (n == 2) {
								Mat = judg.GetTransMatScal(&D3DXVECTOR3(Con.PosBig.x, 0.0f, Con.PosBig.z), ScalPos);
								Mat = Mat * EndMat;
								judg.SetPosM(&Pos2, Mat);
								D3DXVec3TransformNormal(&Vec2, &D3DXVECTOR3(0.0f, 0.0f, 1.0f), &Mat);
							}
							if (judg.Mesh(Pos2, Vec2, player->GetForMoveEndMat(), player->GetColMod(), &Dis2) == true) {
								if (Dis < SmallDis[i]) {
									SmallDis[i] = Dis;
									JudgFlg[i] = true;
								}
							}
						}
					}
				}
			}
		}
	}
	//�G����
	if (enemy.size() > 0) {
		for (unsigned int e = 0; e < enemy.size(); e++) {
			if ((CarFlg == 2) && (No == e)||(enemy[e]->GetSkyType()==true)) {
				//���肵�Ȃ�
			}
			else {
				//���肷��
				//�����Ă����邩
				if (enemy[e]->GetFlgCar() == true) {
					//�i�荞�݋�������
					if (judg.ball(StartMat, enemy[e]->GetMatCar(), (float)RadJudgF) == true) {
						D3DXVECTOR3 JudgPos;//���C�̎n�_
			            //�����珇�Ԃ�
						for (int i = 0; i < 3; i++) {
							if (i == 0)JudgPos = D3DXVECTOR3(TransMat1._41, TransMat1._42, TransMat1._43);
							if (i == 1)JudgPos = D3DXVECTOR3(TransMat3._41, TransMat3._42, TransMat3._43);
							if (i == 2)JudgPos = D3DXVECTOR3(TransMat2._41, TransMat2._42, TransMat2._43);
							//���C����
							if (judg.Mesh(JudgPos, MoveVec[i], enemy[e]->GetForMoveEndMat(), enemy[e]->GetColMod(), &Dis,0) == true) {
								//��������
								float Dis2;
								D3DXVECTOR3 Pos2, Vec2;
								D3DXMATRIX Mat;
								for (int n = 0; n < 3; n++) {
									if (n == 0) {
										Mat = judg.GetTransMatScal(&D3DXVECTOR3(Con.PosSmall.x, 0.0f, Con.PosBig.z), ScalPos);
										Mat = Mat * EndMat;
										judg.SetPosM(&Pos2,Mat);
										D3DXVec3TransformNormal(&Vec2, &D3DXVECTOR3(0.0f, 0.0f, 1.0f), &Mat);
									}
									if (n == 1) {
										Mat = judg.GetTransMatScal(&D3DXVECTOR3(0.0f, 0.0f, Con.PosBig.z), ScalPos);
										Mat = Mat * EndMat;
										judg.SetPosM(&Pos2, Mat);
										D3DXVec3TransformNormal(&Vec2, &D3DXVECTOR3(0.0f, 0.0f, 1.0f), &Mat);
									}
									if (n == 2) {
										Mat = judg.GetTransMatScal(&D3DXVECTOR3(Con.PosBig.x, 0.0f, Con.PosBig.z), ScalPos);
										Mat = Mat * EndMat;
										judg.SetPosM(&Pos2, Mat);
										D3DXVec3TransformNormal(&Vec2, &D3DXVECTOR3(0.0f, 0.0f, 1.0f), &Mat);
									}
									if (judg.Mesh(Pos2, Vec2, enemy[e]->GetForMoveEndMat(), enemy[e]->GetColMod(), &Dis2) == true) {
										if (Dis < SmallDis[i]) {
											SmallDis[i] = Dis;
											JudgFlg[i] = true;
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
	//���C����������
	if ((JudgFlg[0] == true)|| (JudgFlg[1] == true) || (JudgFlg[2] == true)) {
		for (int i = 0; i < 3; i++) {
			SmallDis[i]= (VecSize[i])/(VecSize[1])*((SmallDis[i]) / (VecSize[i]));
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
	}
	delete[] MoveVec;
	delete[] VecSize;
	delete[] SmallDis;
	delete[] JudgFlg;

	return true;
}

D3DXMATRIX GameScene::ForMoveEnd(CONSTITUTION Con, QuaForMove q, D3DXMATRIX TransMat)
{
	motion.Formove(Con, &q.NowMat, &q.AnimeFrame, ground, &q.QuaInitFlg, &q.QuaMatInitFlg, &q.SpeedMul, q.SpeedMul2, &q.StartMat, &q.EndMat,
		&q.WayVec, &q.CurFlg, &q.CurVec, q.BodyHeight);
	q.NowMat = TransMat * q.NowMat;
	return q.NowMat;
}

void GameScene::CameraWallJudg(void)
{
	//���C
	D3DXVECTOR3 Vec = camera->GetPos() - camera->GetLook();
	//���C�T�C�Y
	float Dis, SmallDis = D3DXVec3Length(&Vec);
	//���C�̐��K��
	D3DXVec3Normalize(&Vec, &Vec);
	//����t���O
	bool JudgFlg = false;
	//�ǔ���
	//�n�ʂ̑��݊m�F
	if (ground.size() > 0) {
		//���݂���
		//�n�ʂ̐�
		for (unsigned int g = 0; g < ground.size(); g++) {
			//�͈͍i�荞��
			if (judg.ball(camera->GetPos(), ground[g]->GetMat(), (float)RadJudgF) == true) {
				//�͈͓�
				//���t���O
				bool LeftFlg = true;
				//�ǂ̐�
				for (int w = 0; w < 2; w++) {
					//���E����
					if (w == 0) {
						//��
						LeftFlg = true;
					}
					else {
						//�E
						LeftFlg = false;
					}
					//�ǂ̓����������Ȃ����߂̊g��s��
					D3DXMATRIX ScalY;
					D3DXMatrixScaling(&ScalY, 1.3f, 1.0f, 1.0f);
					//���C����
					if (judg.Mesh(camera->GetLook(), Vec, ScalY*ground[g]->GetWaMat(&LeftFlg), ground[g]->GetColModWall(&LeftFlg), &Dis) == true) {
						//��������
						if (Dis < SmallDis) {
							SmallDis = Dis;
							JudgFlg = true;
						}
					}
				}
			}
		}
	}
	//����I��
	//�J�����̈ʒu�Z�b�g
	if (JudgFlg == true) {
		camera->SetCamPos(&(camera->GetLook() + Vec * (SmallDis - 0.01f)));
	}

	//�ǂ̃��b�V���̎コ�����߂锻��
	bool Flg;
	for (unsigned int g = 0; g < ground.size(); g++) {
		if (judg.ball(camera->GetPos(), ground[g]->GetMat(),  400.0f) == true) {
			Flg = false;
			ground[g]->SetDoawRadFlg(&Flg);
		}
		else {
			Flg = true;
			ground[g]->SetDoawRadFlg(&Flg);
		}
	}
}

bool GameScene::GetBulletBirthFlg(void)
{
	if (EndFlg == true)return false;
	if ((key.LClickF_N() == true) && (BulletBirthFlg == false))return false;
	return true;
}

void GameScene::BombInit(const D3DXMATRIX * Mat)
{
	SoundCamera scB;
	scB.CamPos = camera->GetPos();
	scB.CamLook = camera->GetLook();
	scB.CamHead = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	explo.push_back(new Explo(*Mat, &scB));
	return;
}

bool GameScene::EnemyDelete(const unsigned int * EnemyNo)
{
	if ((*EnemyNo < 0) || (*EnemyNo > enemy.size() - 1))return false;

	if (enemy[*EnemyNo]->GetFlgCar() == false) {
		if (enemy[*EnemyNo]->GetDeadFlg() == false) {
			enemy[*EnemyNo]->SetDeadFlg(true);
			BombInit(&enemy[*EnemyNo]->GetMatCar());
			int sc = 1000;
			score->ScoreUp(&sc);
			return true;
		}
	}
	return false;
}

bool GameScene::EnemyBirth(const int * EnemyNo, D3DXMATRIX * GroundMat,float * TransX)
{
	C_Enemy_Manager Manager;
	enemy.push_back(Manager.Get_Enemy(EnemyNo,*GroundMat,TransX));
	return true;

}

void GameScene::ChangeSceneFade(int ChangeSceneNo)
{
	if (fade->GetMoveFlg() == false) {
		if (SceneChangeFlg == false) {
			SceneNo = ChangeSceneNo;
			SceneChangeFlg = true;
			bool BlackFlg = true;
			if (ChangeSceneNo == GameNo)BlackFlg = false;
			fade->SetIn(BlackFlg);

			//�L�[����s�\
			key.SetFlg(true);
		}
	}
}

void GameScene::ChangeSceneFade(int ChangeSceneNo, int NextStageNo)
{
	ChangeSceneFade(ChangeSceneNo);
	ChangeStageNo = NextStageNo;
}

bool GameScene::SetScene(void)
{
	if (SceneNo == TitleNo) {
		sceneManager.changeScene(new TitleScene());
		return false;
	}
	if (SceneNo == StageSelectNo) {
		sceneManager.changeScene(new StageSelectScene());
		return false;
	}
	if (SceneNo == GameNo) {
		sceneManager.changeScene(new GameScene(ChangeStageNo));
		return false;
	}
	return true;
}

void GameScene::SetMenu(bool PauseFlg, bool ClearFlg, bool OverFlg)
{
	if (Menu.size() > 0)return;

	float yUp;
	int Mode;
	//�|�[�Y------------------------------------
	if (PauseFlg == true) {
		yUp = 20.0f;
		Mode = 1;

		Menu.push_back(new C_PauseTouch(
			&D3DXVECTOR3(1280.0f / 2.0f, 720.0f / 5.0f*4.0f, 0.0f), &D3DXVECTOR3(0.35f, 0.4f, 1.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), &yUp,&Mode));
		return;
	}
	//�X�e�[�W�N���A---------------------------------------
	if (ClearFlg == true) {
		yUp = 20.0f;
		Mode = 2;

		Menu.push_back(new C_ClearTouch(
			&D3DXVECTOR3(1280.0f / 2.0f, 720.0f / 5.0f*4.0f, 0.0f), &D3DXVECTOR3(0.35f, 0.4f, 1.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), &yUp, &Mode));
		return;
	}
	//�Q�[���I�[�o�[---------------------------------------
	if (OverFlg == true) {
		yUp = 35.0f;
		Mode = 3;

		Menu.push_back(new C_OverTouch(
			&D3DXVECTOR3(1280.0f / 2.0f, 720.0f / 5.0f*4.0f, 0.0f), &D3DXVECTOR3(0.35f, 0.4f, 1.0f), &D3DXVECTOR3(1.0f, 1.0f, 1.0f), &yUp, &Mode));
		return;
	}

	return;
}

void GameScene::DeleteMenu(void)
{
	if (Menu.size() > 0) {
		for (unsigned int m = 0; m < Menu.size(); m++) {
			delete Menu[m];
			Menu.erase(Menu.begin() + m);
			m--;
		}
	}
}

bool GameScene::UpdateMenu(void)
{
	if (Menu.size() <= 0)return false;

	int Touch = Menu[0]->TouchNow2();

	if (Touch > 0) {
		//mouse->SetTouchFlg();
	}
	else {
		return false;
	}

	if (key.LClickF() != true)return false;

	//�|�[�Y��--------------------------------
	if (Menu[0]->GetMenuMode() == 1) {
		//�v���C������������
		if (Touch == 1) {
			if (pause->GetDFlg() == true) {
				pause->SetDFlg(false);
				mouse->Init();
				mouse->ChaDrawFlg(false);
				bgm->StartSound();
				pause->SetStaSavFlg(false);

				//���j���[�폜
				DeleteMenu();
				return true;
			}
		}

		//�Z���N�g������������
		if (Touch == 2) {
			if (pause->GetDFlg() == true) {
				ChangeSceneFade(StageSelectNo);
				return true;
			}
		}
	}

	//�N���A��----------------------------------------
	if (Menu[0]->GetMenuMode() == 2) {
		//�^�C�g��������������
		if (Touch == 1) {
			ChangeSceneFade(TitleNo);
			return true;
		}

		//�Z���N�g������������
		if (Touch == 2) {
			ChangeSceneFade(StageSelectNo);
			return true;
		}
	}

	//�Q�[���I�[�o�[��----------------------------------------
	if (Menu[0]->GetMenuMode() == 3) {
		//���g���C������������
		if (Touch == 1) {
			ChangeSceneFade(GameNo, StageNo);
			return true;
		}

		//�Z���N�g������������
		if (Touch == 2) {
			ChangeSceneFade(StageSelectNo);
			return true;
		}

		//�^�C�g��������������
		if (Touch == 3) {
			ChangeSceneFade(TitleNo);
			return true;
		}
	}

	//�Q�[���I�[�o�[��

	return true;
}

bool GameScene::GroundCreate(unsigned int *GNo)
{
	if (judg.ball(player->GetMatCar(), ground[*GNo]->GetMat(), player->GetRadF()) == false) {

		if (player->GetGroNum() < *GNo)return false;
		if (ground[*GNo]->GetFlg() == false) return false;

		delete ground[*GNo];
		ground.erase(ground.begin() + *GNo);
		*GNo -= 1;

		D3DXMATRIX Mat[2];
		Mat[0] = ground[ground.size() - 1]->GetMat0();
		Mat[1] = ground[ground.size() - 1]->GetMat1();

		int StopNum=2;
		if (GroCou.size() == 0) {//�n�ʂ̌`��
			GroCou.push_back(new Cou(0, StopNum, 1, true, false));
		}
		if (cou->CouJudge() == false) cou->SetNum(0);

		const int L_Type=0;
		int L_Type2 = Init_Ground_Push(&Mat[1], &Mat[0], &L_Type);
		if(L_Type2>= 0) {
			if (M_C_Ground_Pop != nullptr) {
				M_C_Ground_Pop->Ground_Pop_Rear_N();
			}
			if (L_Type2 == 0) {
				cou->CouUpd();
			}
		}

		//�O���̏�����
		if (LightCount->Update() == true) {
			int wNum = 2;
			ground[ground.size() - 1]->InitLight(&wNum);
		}


		if (GroCou.size() > 0) {
			for (unsigned int g = 0; g < GroCou.size(); g++) {
				GroCou[g]->CouUpd();
				if (GroCou[g]->CouJudge() == false) {
					for (unsigned int z = 0; z < GroCou.size(); z++) {
						delete GroCou[z];
						GroCou.erase(GroCou.begin() + z);
						z--;
					}
					if (GroCou.size() <= 0) {
						break;
					}
				}
			}
		}
	}
	else {
		//�V�i�̓��𔻒�ł���悤�ɂ���
		if (ground[*GNo]->GetFlg() == false) {
			ground[*GNo]->SetFlg(true);
		}
	}
	return true;
}

void GameScene::Pos2DUpdate(const D3DXMATRIX * mProj, const D3DXMATRIX * mView, const D3DVIEWPORT9 * Viewport)
{
	if (enemy.size() <= 0)return;
	for (unsigned int e = 0; e < enemy.size(); e++) {
		//���v�Z
		enemy[e]->GetPos2DSet(mProj, mView, Viewport);
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

void GameScene::AllNew(void)
{
	//��
	M_C_SmokeCar = new C_SmokeCar();

	M_C_Ground_Pop = new C_Ground_Pop_New(1);
}

void GameScene::AllDelete(void)
{
	delete debugT;
	//�n�ʂ̍폜
	for (unsigned int i = 0; i < ground.size(); i++) {
		delete ground[i];
		ground.erase(ground.begin() + i); i--;
	}

	if (GroCou.size() > 0) {
		for (unsigned int g = 0; g < GroCou.size(); g++) {
			delete GroCou[g];
			GroCou.erase(GroCou.begin() + g);
			g--;
		}
	}
	delete cou;
	//�G�̍폜
	for (unsigned int i = 0; i < enemy.size(); i++) {
		delete enemy[i];
		enemy.erase(enemy.begin() + i); i--;
	}
	for (unsigned int i = 0; i < explo.size(); i++) {
		delete explo[i];
		explo.erase(explo.begin() + i); i--;
	}
	delete player;
	delete sky;
	delete camera;
	delete aiming;
	delete debug;
	delete GaOv;
	delete war;
	delete pause;
	delete spear;
	//�X�R�A�̍폜
	delete score;

	//�ΉԂ̍폜
	if (SparkV.size() > 0) {
		for (unsigned int s = 0; s < SparkV.size(); s++) {
			delete SparkV[s];
			SparkV.erase(SparkV.begin() + s);
			s--;
		}
	}

	//�Ԃ̏����폜
	if (M_C_Car_Pop != nullptr) {
		delete M_C_Car_Pop;
	}

	//�}�E�X�̍폜
	delete mouse;

	//�t�F�[�h�̍폜
	delete fade;

	//�e���RD�̍폜
	if (BHole3D.size() > 0) {
		for (unsigned int b = 0; b < BHole3D.size(); b++) {
			delete BHole3D[b];
			BHole3D.erase(BHole3D.begin() + b);
			b--;
		}
	}

	//�v���C���[�̏��폜
	delete PlayerBody;

	//���C�g�̃J�E���g�_�E���̍폜
	if (LightCount != nullptr) {
		delete LightCount;
	}
	if (M_C_SmokeCar != nullptr) {
		delete M_C_SmokeCar;
	}

	//�n�ʂ̏��폜
	if (M_C_Ground_Pop != nullptr) {
		delete M_C_Ground_Pop;
	}
}

bool GameScene::Update_Bgm(void)
{
	//bgm�̃A�b�v�f�[�g
	bool bFlg = true;
	bgm->Update(&bFlg);

	return true;
}

bool GameScene::Update_Debug(void)
{
	//�t���[�����̑���

	if (GetAsyncKeyState('1') & 0x8000) {
		MaxCount += 1;
		if (MaxCount > 60)MaxCount = 60;
	}
	if (GetAsyncKeyState('2') & 0x8000) {
		MaxCount -= 1;
		if (MaxCount < 1)MaxCount = 1;
	}

	if (key.XKeyF() == true)player->SetHP(1);

	return true;
}

bool GameScene::Update_Fade(void)
{
	//�t�F�[�h�̃A�b�v�f�[�g
	if (fade->Update() == true) {
		//�L�[�̖��͉�

	}
	else {
		if (fade->GetMoveEndFlg() == true) {
			if (SceneChangeFlg == true)return SetScene();
		}
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
	
	Update_Ground();

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
	if (EndFlg == false) {
		if (fade->GetMoveFlg() == false) {
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
	if (NowGroNum(player->GetMatCar(), &num, &Dis) == true) {
		player->SetGroNum(num);//�n�ʂ̎擾
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
	player->UpdateCarFM(ground);
	//�ړ��x�N�g���̃T�C�Y�̏�����
	player->SetQuaVecSize(1.0f);
	//�G�̈ړ�
	UpdateEnemyMove();

	//������
	Update_Car_SideJudg();

	//�ŏIUpdate
	//player->SetParts(camera->GetAngX(),camera->GetAngY());
	if (enemy.size() > 0) {
		for (unsigned int e = 0; e < enemy.size(); e++) {
			//if (enemy[e]->GetFlgCar() == true) {
				enemy[e]->SetParts(ground);
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
	CameraWallJudg();

	//�v���C���[�ƒn�ʔ���2
	if (NowGroNum(player->GetMatCar(), &num, &Dis) == true) {
		player->SetGroNum(num);//�n�ʂ̎擾
		eneFlg = true;//�G�̏o���J�n
	}

	//--------------------------------------------
	//�Ԃ̓���������̏���
	//--------------------------------------------

	Update_Bullet();

	//================================================================================
	//�G
	//================================================================================
	if (UpdateE() == false) {
		if (EndFlg == false) {
			EndFlg = true;
			GaOv->Update(true, EndFlg);
			SetMenu(false, true, false);
		}
	}

	//��
	sky->Update(player->GetMatCar());

	Update_Explo();

	war->Update();

	Update_Spark();

	Update_CarSmoke();

	Update_Bullet_Hole();

	Update_Pop_End();

	return true;
}

bool GameScene::Update_Game_Pause(void)
{
	//�I�������
	if (EndFlg == true) {
		mouse->ChaDrawFlg(true);
	}
	else {
		//�|�[�Y
		if (key.RETURNKeyF() == true) {
			if (pause->GetDFlg() == false) {
				pause->SetDFlg(true);
				mouse->ChaDrawFlg(true);
				bgm->StopSound();
				//���[�h�̋���
				if ((GetAsyncKeyState('8') & 0x8000) && (GetAsyncKeyState('9') & 0x8000) && (GetAsyncKeyState('0') & 0x8000)) {
					pause->SetStaSavFlg(true);
				}
				SetMenu(true, false, false);
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

bool GameScene::Update_Ground(void)
{
	if (ground.size() < 1) return false;

	for (unsigned int i = 0; i < ground.size(); i++) {
		ground[i]->SuperUpdate();
		//�����̓��̍폜�ƍ쐬
		GroundCreate(&i);
	}

	return true;
}

bool GameScene::Update_Explo(void)
{
	if (explo.size() < 1)return false;

	//����
	for (unsigned int i = 0; i < explo.size(); i++) {
		if (explo[i]->ExplUpdate(&camera->GetMat()) == false) {
			delete explo[i];
			explo.erase(explo.begin() + i);
			i--;
		}
	}

	return true;
}

bool GameScene::Update_Spark(void)
{
	//�ΉԂ̃A�b�v�f�[�g
	if (SparkV.size() < 1) return false;

	for (unsigned int s = 0; s < SparkV.size(); s++) {
		if (SparkV[s]->UpdateSuper() == false) {
			//�폜
			delete SparkV[s];
			SparkV.erase(SparkV.begin() + s);
			s--;
		}
	}

	return true;
}

bool GameScene::Update_CarSmoke(void)
{
	if (M_C_SmokeCar == nullptr) return false;

	//int CarNo = player->GetBody().CarBodyNo;
	//M_C_SmokeCar->Update_CS(&player->GetCharaBase(), &CarNo, &player->GetMatCar(), &player->GetMoveVec());

	return true;
}

bool GameScene::Update_Bullet_Hole(void)
{
	//�e���RD�̃A�b�v�f�[�g
	if (BHole3D.size() < 1) return false;

	for (unsigned int b = 0; b < BHole3D.size(); b++) {
		if (BHole3D[b]->UpdateHol3D() == false) {
			delete BHole3D[b];
			BHole3D.erase(BHole3D.begin() + b);
			b--;
		}
	}

	return true;
}

bool GameScene::Update_Camera_Car(void)
{
	//�J������plaeyr�̑O���ɐU���������N�H�[�^�j�I���̏�����
	if (EndFlg != false) return false;
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
	l_RayR.Mat = judg.SetMatP(camera->GetPos());
	l_RayR.Ray = camera->GetVec();
	float Rad = (float)RadJudgF*2.0f;
	//�G�̃��C����
	BulletJudgEnemy(&l_DisD, &l_RayR, &Rad);
	if (l_DisD.Type > 0)Hit_Data.Flg = true;
	//�Ə��̕ω�
	if (Hit_Data.Flg == true) {
		aiming->ChaFlg();
	}
	else {
		aiming->ResFlg();
	}
	//�n��
	BulletJudgGround(&l_DisD, &l_RayR, NULL, &Rad);
	if (l_DisD.Type > 0)Hit_Data.Flg = true;
	//�����̃��C����
	//�o���b�g�̏o������
	if (Hit_Data.Flg == false) {
		player->Set_Gun_Ray_Data(&Hit_Data);
	}
	else {
		Hit_Data.Mat = judg.SetMatP(camera->GetPos() + l_RayR.Ray * l_DisD.SamllDis);
		player->Set_Gun_Ray_Data(&Hit_Data);
	}

	//================================================================================
	//�e
	//================================================================================

	//�e�̒a������
	//BulletBirthFlg = GetBulletBirthFlg();
	////player�e��Update
	////player->GUpdateB(&BulletBirthFlg);
	//SoundCamera sc;
	//sc.CamPos = camera->GetPos();
	//sc.CamLook = camera->GetLook();
	//sc.CamHead = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	//bool KeyFlg = key.LClickF_N();
	//player->UpdateBulPla(&KeyFlg, &BulletBirthFlg, &sc);
	//BulletJudg(&co_PlayerCar, NULL);
	//player->UpdateBulletMove();
	//bool BBFlgB = player->GetBulBirFlgB();
	//SoundGun->Update(&BBFlgB);

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
	EndMat = ForMoveEnd(player->GetCon(), player->GetQuaForMove(), player->GetTransMatCar());
	player->SetForMoveEndMat(EndMat);
	//�ړ��x�N�g���v�Z
	D3DXMATRIX TransMat1, TransMat2, Trans;//�����̃��C���ˈʒu
	D3DXVECTOR3 ScalPosB = player->GetScalPosCar();
	TransMat1 = judg.GetTransMatScal(&D3DXVECTOR3(player->GetCon().PosSmall.x, 0.0f, player->GetCon().PosBig.z), &ScalPosB);
	TransMat2 = judg.GetTransMatScal(&D3DXVECTOR3(player->GetCon().PosBig.x, 0.0f, player->GetCon().PosBig.z), &ScalPosB);
	Trans = judg.GetTransMatScal(&D3DXVECTOR3(0.0f, 0.0f, player->GetCon().PosBig.z), &ScalPosB);
	player->SetForMoveVec(judg.MatMatVec(TransMat1*player->GetMatCar(), TransMat1*player->GetForMoveEndMat()), 0);
	player->SetForMoveVec(judg.MatMatVec(Trans*player->GetMatCar(), Trans*player->GetForMoveEndMat()), 1);
	player->SetForMoveVec(judg.MatMatVec(TransMat2*player->GetMatCar(), TransMat2*player->GetForMoveEndMat()), 2);

	//enemy
	if (enemy.size() > 0) {//enemy�̑��݊m�F
		//enemy�̐�
		for (unsigned int e = 0; e < enemy.size(); e++) {
			if (enemy[e]->GetFlgCar() == true) {
				//�ړ���̍s��쐬
				EndMat = ForMoveEnd(enemy[e]->GetCon(), enemy[e]->GetQuaForMove(), enemy[e]->GetTransMatCar());
				enemy[e]->SetForMoveEndMat(EndMat);
				//�ړ��x�N�g���v�Z
				D3DXMATRIX TransMat1, TransMat2, Trans;//�����̃��C���ˈʒu
				ScalPosB = enemy[e]->GetScalPosCar();

				TransMat1 = judg.GetTransMatScal(&D3DXVECTOR3(enemy[e]->GetCon().PosSmall.x, 0.0f, enemy[e]->GetCon().PosBig.z), &ScalPosB);
				TransMat2 = judg.GetTransMatScal(&D3DXVECTOR3(enemy[e]->GetCon().PosBig.x, 0.0f, enemy[e]->GetCon().PosBig.z), &ScalPosB);
				Trans = judg.GetTransMatScal(&D3DXVECTOR3(0.0f, 0.0f, enemy[e]->GetCon().PosBig.z), &ScalPosB);

				enemy[e]->SetForMoveVec(judg.MatMatVec(TransMat1*enemy[e]->GetMatCar(), TransMat1*enemy[e]->GetForMoveEndMat()), 0);
				enemy[e]->SetForMoveVec(judg.MatMatVec(Trans*enemy[e]->GetMatCar(), Trans*enemy[e]->GetForMoveEndMat()), 1);
				enemy[e]->SetForMoveVec(judg.MatMatVec(TransMat2*enemy[e]->GetMatCar(), TransMat2*enemy[e]->GetForMoveEndMat()), 2);
			}
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
		Mul = player->GetCon().SpeedMulJudg;
		//����
		ForMoveJudg(player->GetCon(), player->GetDrawMatCar(), player->GetForMoveEndMat(), true, false, 0, player->GetForMoveVec(0), player->GetForMoveVec(1), player->GetForMoveVec(2), &Mul, &player->GetScalPosCar());
		//Mul��{�̂ɓ����
		player->SetQuaVecSize(Mul);
		//�Ō�̌J��Ԃ��ȊO
		if (i != MaxJudg - 1) {
			//�V�����ړ�����쐬
			EndMat = ForMoveEnd(player->GetCon(), player->GetQuaForMove(), player->GetTransMatCar());
			player->SetForMoveEndMat(EndMat);
			//Mul�̏�����
			player->SetQuaVecSize(1.0f);
		}

		//enemy
		if (enemy.size() > 0) {
			for (unsigned int e = 0; e < enemy.size(); e++) {
				if ((enemy[e]->GetFlgCar() == true) && (enemy[e]->GetSkyType() == false)) {
					//enemy��Vec�T�C�Y
					Mul = enemy[e]->GetCon().SpeedMulJudg;
					//����
					ForMoveJudg(enemy[e]->GetCon(), enemy[e]->GetMatCar(), enemy[e]->GetForMoveEndMat(), false, true, e, enemy[e]->GetForMoveVec(0), enemy[e]->GetForMoveVec(1), enemy[e]->GetForMoveVec(2), &Mul, &enemy[e]->GetScalPosCar());
					//Mul��{�̂ɓ����
					enemy[e]->SetQuaVecSize(Mul);
					//�Ō�̌J��Ԃ��ȊO
					if (i != MaxJudg - 1) {
						//�V�����ړ�����쐬
						EndMat = ForMoveEnd(enemy[e]->GetCon(), enemy[e]->GetQuaForMove(), enemy[e]->GetTransMatCar());
						enemy[e]->SetForMoveEndMat(EndMat);
						//Mul�̏�����
						enemy[e]->SetQuaVecSize(1.0f);
					}
				}
			}
		}
	}
	/*�����蔻�芮��*/

	return true;
}

bool GameScene::Update_Car_SideJudg(void)
{
	//������
	WallJudg(true, true, false, 0);
	WallJudg(false, true, false, 0);

	if (enemy.size() <1) return true;

	for (unsigned int e = 0; e < enemy.size(); e++) {
		if ((enemy[e]->GetFlgCar() == true) && (enemy[e]->GetSkyType() == false)) {
			WallJudg(true, false, true, e);
			WallJudg(false, false, true, e);
		}
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
	if ((key.AKey() == true)) {
		D3DXMATRIX Trans;
		D3DXMatrixTranslation(&Trans, -1.0f*0.08f, 0.0f, 0.0f);
		Trans = Trans * player->GetTransMatCar();
		player->SetTransMatCar(&Trans);
		Trans = player->GetTransMatCar()*player->GetCon().JudgMat;
		player->SetMatCar(&Trans);
		//������
		WallJudg(true, true, false, 0);
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
		WallJudg(false, true, false, 0);
		player->SetRodAngY(0.3f, true);
		LRKeyFlg = true;
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

int GameScene::Init_Ground_Push(const D3DXMATRIX * Mat1, const D3DXMATRIX * Mat0, const int * Type)
{
	S_GROUND_INIT_DATA L_Data = M_C_Ground_Pop->Get_Pop_Data_N();

	if ((cou->GetNum() == 1) && (L_Data.gType == Co_Ground_Type_Straight)) {
		ground.push_back(new BillBase(*Mat1, *Mat0, L_Data.gType, L_Data.Ang, L_Data.Length, L_Data.LengthAuto));
		return L_Data.gType;
	}
	else {
		ground.push_back(new Bill(*Mat1, *Mat0, L_Data.gType, L_Data.Ang, L_Data.Length, L_Data.LengthAuto));
		return L_Data.gType;
	}
	return 0;
}

bool GameScene::Update_Pop_End(void)
{
	if (M_C_Car_Pop == nullptr) return false;

	if (EndFlg == true) return false;

	//���݂̐������Ă���G���̒���
	int Num = 0;

	if (enemy.size() > 0) {
		for (auto && e : enemy) {
			if (e->GetFlgCar() == true)Num++;
		}
	}

	M_C_Car_Pop->Set_Now_Enemy_Num_N(&Num);

	Set_Ground_Data();

	if (M_C_Car_Pop->Get_Change_Class_EndFlg() == true) {
		if (M_C_Car_Pop->Get_Stage_Phase_Data_N().Phase_Type == Co_Phase_Type_Boss) {
			war->SetFlg(true);
			return true;
		}
	}
	
	//Pop�̏I���m�F����
	if (M_C_Car_Pop->Get_Stage_Phase_Data_N().Phase_Type == Co_Phase_Type_End) {
		Set_Game_Clear();
		return false;
	}

	return true;
}

bool GameScene::Get_Car_Pop(const int * Car_Type)
{
	//�Q�[���I��Flg
	if (EndFlg == true)return false;

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
	if (EndFlg == true)return false;

	if (war->GetFlg() == true)return false;

	return true;
}

void GameScene::Set_Ground_Data(void)
{
	if (M_C_Ground_Pop == nullptr)return;

	if (M_C_Car_Pop == nullptr)return;

	int No = M_C_Car_Pop->Get_GroundNo();

	if (No == M_C_Ground_Pop->Get_GroundNo()) return;
	
	M_C_Ground_Pop->New_Pop(&No);
}

void GameScene::Set_Game_Over(void)
{
	if (EndFlg == true)return;

	//player�����񂾂Ƃ��̏���
	BombInit(&player->GetMatCar());
	EndFlg = true;
	GaOv->Update(false, EndFlg);
	for (unsigned int e = 0; e < enemy.size(); e++) {
		enemy[e]->SetPlaEnd(true/*, player->GetSpeedCar()*/);
	}
	player->SetSpeedCar(player->GetSpeedCar()*0.0f);
	war->SetFlg(false);
	//���j���[�̕\��
	SetMenu(false, false, true);
}

void GameScene::Set_Game_Clear(void)
{
	if (EndFlg == true)return;

	EndFlg = true;
	GaOv->Update(true, EndFlg);
	SetMenu(false, true, false);
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
		if (enemy[i]->Get_Gun_Num() > 0) {
			for (unsigned int g = 0; g < enemy[i]->Get_Gun_Num(); g++) {
				if (enemy[i]->Get_Gun_Data(&g).Ray_Judg_Flg == true) {
					//���C����
					BULLETJUDGDATA b;
					b.SamllDis = enemy[i]->Get_Gun_Data(&g).RayDis;
					RAYDATA r;
					r.Mat = enemy[i]->Get_Gun_Data(&g).DrawBase.Mat;
					D3DXVec3TransformNormal(&r.Ray, &D3DXVECTOR3(0.0f, 0.0f, 1.0f), &r.Mat);
					float Rad = (float)RadChara*2.0f;
					BulletJudgPlayer(&b, &r, &Rad);
					bool Flg = false;
					if (b.Type > 0)Flg = true;

					enemy[i]->Set_Ray_Hit_Flg(&g, &Flg);
					enemy[i]->Set_Ray_Dis(&g, &b.SamllDis);
				}
			}
		}
	}

	return true;
}

bool GameScene::Update_Bullet_Init(void)
{
	if (player != nullptr) {
		player->Init_Bullet();
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

int GameScene::Get_Rail_Num(const int * Way_Rail_Num, const int * Pop_Rail_Num)
{
	int No = *Pop_Rail_Num;

	if (No == Co_Rail_Type_Random) {
		No = rand() % (*Way_Rail_Num);
		return No;
	}

	if (No < 0)No = 0;
	if (No >= *Way_Rail_Num)No = (*Way_Rail_Num) - 1;

	return No;
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

void GameScene::BulletJudgGround(BULLETJUDGDATA * BJD, const RAYDATA *RD, bool *HitFlg, const float *Rad)
{
	//�n�ʐ�
	if (ground.size() <= 0)return;

	float Dis;
	bool JudgFlg;

	if (HitFlg != nullptr) {
		*HitFlg = false;
	}

	for (unsigned int g = 0; g < ground.size(); g++) {
		if (judg.ball(RD->Mat, ground[g]->GetMat(), *Rad) == true) {//�i�荞��
			JudgFlg = false;
			//���C�����ޕ���
			if (ground[g]->GetIdenFlg() == false) {
				//���C����
				if (judg.RayPolM(RD->Mat, ground[g]->GetVer(0), ground[g]->GetVer(1), ground[g]->GetVer(2), ground[g]->GetVer(3), ground[g]->GetMat(), RD->Ray, &Dis) == true) {
					JudgFlg = true;
					if (HitFlg != nullptr) {
						*HitFlg = true;
					}
				}
			}
			else {
				//���C����
				if (judg.RayPolM(RD->Mat, ground[g]->GetVer(0), ground[g]->GetVer(1), ground[g]->GetVer(2), ground[g]->GetVer(3), RD->Ray, &Dis) == true) {
					JudgFlg = true;
					if (HitFlg != nullptr) {
						*HitFlg = true;
					}
				}

			}
			if (JudgFlg == true) {//����������
				//���C�������������ɒe�̈ړ���Vec�̒������Z�������ׂ�
				if (Dis < BJD->SamllDis) {
					BJD->SamllDis = Dis;
					BJD->Type = co_Ground;
					BJD->JudgNo1 = g;
				}
			}
		}

		//�ǔ���
		for (int w = 0; w < 2; w++) {
			//�񖇂̕ǔ���
			bool LeftFlg = true;
			if (w == 1)LeftFlg = false;
			if (judg.ball(RD->Mat, ground[g]->GetWaMat(&LeftFlg, 0), *Rad) == true) {
				JudgFlg = false;
				//���C����
				if (judg.Mesh(judg.SetPosM(RD->Mat), RD->Ray, ground[g]->GetWaMat(&LeftFlg), ground[g]->GetColModWall(&LeftFlg), &Dis) == true) {
					if (HitFlg != nullptr) {
						*HitFlg = true;
					}
					//���C�������������ɒe�̈ړ���Vec�̒������Z�������ׂ�
					if (Dis < BJD->SamllDis) {
						BJD->SamllDis = Dis;
						BJD->Type = co_Wall;
						BJD->JudgNo1 = g;
						BJD->JudgNo2 = (unsigned int)w;
					}
				}
			}
		}
	}
	return;
}

void GameScene::BulletJudgPlayer(BULLETJUDGDATA * BJD, const RAYDATA * RD, const float *Rad)
{
	D3DXVECTOR3 BPos;//BulletPos
	judg.SetPosM(&BPos, RD->Mat);

	float Dis;

	if (judg.ball(RD->Mat, player->GetMatCar(), *Rad) == true) {//�i�荞��
	//���C����
		//�{�f�B
		if (judg.Mesh(BPos, RD->Ray, player->GetDrawMatCar(), player->GetMeshCar(), &Dis) == true) {
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

void GameScene::BulletJudgEnemy(BULLETJUDGDATA * BJD, const RAYDATA * RD, const float *Rad)
{
	if (enemy.size() <= 0)return;

	D3DXVECTOR3 BPos;
	judg.SetPosM(&BPos, RD->Mat);

	float Dis;

	//enemy�̐�
	for (unsigned int e = 0; e < enemy.size(); e++) {
		if (judg.ball(RD->Mat, enemy[e]->GetMatCar(), *Rad) == true) {//�i�荞��
			//���C����
			//�{�f�B
			if (judg.Mesh(BPos, RD->Ray, enemy[e]->GetDrawMatCar(), enemy[e]->GetMeshCar(), &Dis) == true) {
				//�ő��菬������
				if (Dis < BJD->SamllDis) {
					BJD->SamllDis = Dis;
					BJD->Type = co_EnemyCar;
					BJD->JudgNo1 = e;
				}
			}
			//�p�[�c
			if (enemy[e]->Get_Car_Parts_Num() > 0) {
				for (unsigned int p = 0; p < enemy[e]->Get_Car_Parts_Num(); p++) {
					//if (enemy[e]->GetPartsData(&p).MeshDrawFlg <= 0)continue;
					if (enemy[e]->Get_Parts_Draw_Draw_JudgFlg(&p) == Co_Draw_Mesh) {
						if (judg.Mesh(BPos, RD->Ray, enemy[e]->Get_Parts_Draw_DrawMat(&p)
							, enemy[e]->Get_Parts_Draw_Mesh(&p), &Dis) == true) {
							//�ő��菬������
							if (Dis < BJD->SamllDis) {
								BJD->SamllDis = Dis;
								BJD->Type = co_EnemyParts;
								BJD->JudgNo1 = e;
								BJD->JudgNo2 = p;
							}
						}
					}
					if (enemy[e]->Get_Parts_Draw_Draw_JudgFlg(&p) == Co_Draw_Pol) {
						int a = 0, b = 1, c = 2, d = 3;
						if (judg.RayPolM(RD->Mat, enemy[e]->Get_Parts_Draw_Pol_Pos(&p, &a), enemy[e]->Get_Parts_Draw_Pol_Pos(&p, &b)
							, enemy[e]->Get_Parts_Draw_Pol_Pos(&p, &c), enemy[e]->Get_Parts_Draw_Pol_Pos(&p, &d)
							, enemy[e]->Get_Parts_Draw_DrawMat(&p), RD->Ray, &Dis) == true) {
							//�ő��菬������
							if (Dis < BJD->SamllDis) {
								BJD->SamllDis = Dis;
								BJD->Type = co_EnemyParts;
								BJD->JudgNo1 = e;
								BJD->JudgNo2 = p;
							}
						}
					}
				}
			}
			//�e
			if (enemy[e]->Get_Gun_Num() > 0) {
				for (unsigned int g = 0; g < enemy[e]->Get_Gun_Num(); g++) {
					//if (enemy[e]->GetGunData(&g).Base.DrawFlg != true)continue;
					if (enemy[e]->Ray_Judg_Gun_Flg(&g) == true) {
						if (enemy[e]->Get_Gun_Draw_Parts_Num(&g) > 0) {
							for (unsigned int g_p = 0; g_p < enemy[e]->Get_Gun_Draw_Parts_Num(&g); g_p++) {
								if (enemy[e]->Get_Gun_Draw_Parts_Draw_JudgFlg(&g, &g_p) == Co_Draw_Mesh) {
									if (judg.Mesh(BPos, RD->Ray, enemy[e]->Get_Gun_Draw_Parts_Draw_Mat(&g, &g_p)
										, enemy[e]->Get_Gun_Draw_Parts_Mesh(&g, &g_p), &Dis) == true) {
										//�ő��菬������
										if (Dis < BJD->SamllDis) {
											BJD->SamllDis = Dis;
											BJD->Type = co_EnemyGun;
											BJD->JudgNo1 = e;
											BJD->JudgNo2 = g;
											BJD->JudgNo3 = g_p;
										}
									}
								}
							}
						}
					}
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
	judg.SetPosM(&BPos, RD->Mat);

	//enemy�̐�
	for (unsigned int e = 0; e < enemy.size(); e++) {
		if (judg.ball(RD->Mat, enemy[e]->GetMatCar(), *Rad) == true) {//�i�荞��

			//�p�[�c
			if (enemy[e]->Get_Car_Parts_Num() > 0) {
				for (unsigned int p = 0; p < enemy[e]->Get_Car_Parts_Num(); p++) {

					if (enemy[e]->Get_Parts_Draw_Draw_JudgFlg(&p) == Co_Draw_Ball) {
						if (judg.ball(BPos, enemy[e]->Get_Parts_Draw_DrawMat(&p), enemy[e]->Get_Parts_Draw_Dis(&p)) == true) {
							//�ő��菬������
							BJD->Type = co_EnemyParts;
							BJD->JudgNo1 = e;
							BJD->JudgNo2 = p;
						}
					}

				}
			}

		}
	}
}

bool GameScene::SetBulletDamage(const BULLETJUDGDATA* BJD, const RAYDATA *RD, const int Damage)
{
	if (BJD->Type < 0)return false;

	//�n��///////////////////////////////////////////////////////////////////////////////////
	//�n��
	if (SetBulletDamageGround(BJD,RD) == true)return true;
	//��
	if (SetBulletDamageWall(BJD, RD) == true)return true;

	//�v���C���[/////////////////////////////////////////////////////////////////////////////
	//�ԑ�
	if (SetBulletDamagePlaCar(BJD,&Damage) == true)return true;
	//�W���p�[�c
	if (SetBulletDamagePlaParts(BJD, &Damage) == true)return true;
	//�e
	if (SetBulletDamagePlaGun(BJD, &Damage) == true)return true;

	//�G�l�~�[//////////////////////////////////////////////////////////////////////////////
	//�ԑ�
	if (SetBulletDamageEneCar(BJD,&Damage) == true)return true;
	//�W���p�[�c
	if (SetBulletDamageEneParts(BJD, &Damage) == true)return true;
	//�e
	if (SetBulletDamageEneGun(BJD, &Damage) == true)return true;
	
	//�������Ă��Ȃ�
	return false;
}

bool GameScene::SetBulletDamageGround(const BULLETJUDGDATA* BJD, const RAYDATA *RD)
{
	if (BJD->Type != co_Ground)return false;
	//�Ή�
	D3DXVECTOR3 RayPos;
	RayPos = judg.SetPosM(RD->Mat) + RD->Ray * BJD->SamllDis;
	int SpeType = 0;
	float Ang = 0.0f;
	SparkV.push_back(new C_BulGro(&ground[BJD->JudgNo1]->GetMat(), &RayPos));
	//�e���RD
	RayPos = judg.SetPosM(RD->Mat) + RD->Ray * (BJD->SamllDis - 0.01f);
	BHole3D.push_back(new C_BulHol3D(&ground[BJD->JudgNo1]->GetMat(), &RayPos, 2));
	
	return true;
}

bool GameScene::SetBulletDamageWall(const BULLETJUDGDATA* BJD, const RAYDATA *RD)
{
	if (BJD->Type != co_Wall)return false;
	//�Ή�
	D3DXVECTOR3 RayPos;
	RayPos = judg.SetPosM(RD->Mat) + RD->Ray * BJD->SamllDis;
	int SpeType = 1;
	float Ang = 0.0f;
	bool BulWallFlg = true;
	if (BJD->JudgNo2 == 1)BulWallFlg = false;
	//�Ή�
	for (int s = 0; s < 5; s++) {
		SparkV.push_back(new C_SparkDamage(&ground[BJD->JudgNo1]->GetWaMat(&BulWallFlg, 0), &RayPos, &SpeType, &Ang));
	}
	//�e���RD
	RayPos = judg.SetPosM(RD->Mat) + RD->Ray * (BJD->SamllDis - 0.01f);
	BHole3D.push_back(new C_BulHol3D(&ground[BJD->JudgNo1]->GetWaMat(&BulWallFlg, 0), &RayPos, 1));
	return true;
}

bool GameScene::SetBulletDamagePlaCar(const BULLETJUDGDATA* BJD, const int * Damage)
{
	if (BJD->Type != co_PlayerCar)return false;

	if (player->SetHP(*Damage, false) == true) {
		//�_���[�W���󂯂���
		int sc = -10;
		score->ScoreUp(&sc);
	}
	return true;
}

bool GameScene::SetBulletDamagePlaParts(const BULLETJUDGDATA* BJD, const int * Damage)
{
	if (BJD->Type != co_PlayerParts)return false;

	/*if (player->SetDamageParts(HitMesh, Damage) == true) {

	}*/

	return true;
}

bool GameScene::SetBulletDamagePlaGun(const BULLETJUDGDATA* BJD, const int * Damage)
{
	return false;
}

bool GameScene::SetBulletDamageEneCar(const BULLETJUDGDATA* BJD, const int * Damage)
{
	if (BJD->Type != co_EnemyCar)return false;

	if (enemy[BJD->JudgNo1]->GetFlgCar() == false)return true;

	if (enemy[BJD->JudgNo1]->SetHP(*Damage, false) == true) {
		EnemyDelete(&BJD->JudgNo1);
	}

	return true;
}

bool GameScene::SetBulletDamageEneParts(const BULLETJUDGDATA* BJD, const int * Damage)
{
	if (BJD->Type != co_EnemyParts)return false;

	enemy[BJD->JudgNo1]->Damage_CarParts(&BJD->JudgNo2, Damage);

	return true;
}

bool GameScene::SetBulletDamageEneGun(const BULLETJUDGDATA* BJD, const int * Damage)
{
	if (BJD->Type != co_EnemyGun)return false;

	enemy[BJD->JudgNo1]->Damage_Gun(&BJD->JudgNo2, Damage);

	return true;
}


