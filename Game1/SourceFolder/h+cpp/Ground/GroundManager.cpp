#include "GroundManager.h"
#include"../GameSource/Judgment.h"
#include"../Const/Const_Rail_Type.h"

c_GroundManager::c_GroundManager(C_PlayerBase * player)
{
	//�O���̊Ԋu������
	int CountInit = 4;
	LightCount = new C_Count(&CountInit);

	cou = new Cou(0, 5, 1, true, false);
	int i = 0, z;
	ground.push_back(new C_Ground_Object(&i));
	z = (int)ground[0]->GetPosZ() * 2;
	i = (int)player->GetRadF() / z;
	delete ground[0];
	ground.erase(ground.begin() + 0);
	for (int n = i * (-1); n < i; n++) {
		if (cou->CouJudge() == false) {
			cou->SetNum(0);
		}
		ground.push_back(new C_Ground_Object(&n));

		if (cou->GetNum() == 1) ground[ground.size() - 1]->Init_Bill();

		//�O���̏�����
		if (LightCount->Update() == true)ground[ground.size() - 1]->Init_Light();

		cou->CouUpd();
	}
	for (unsigned int i = 0; i < ground.size(); i++) {

		float L_Radius = player->GetRadF();

		Judg judg;
		if (judg.BallJudg(&judg.SetPosM(&player->GetMatCar()), &judg.SetPosM(&ground[i]->GetMat()), &L_Radius) != false) continue;

		delete ground[i];
		ground.erase(ground.begin() + i);
		i--;

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
	// �n�ʂ̓����蔻��
	if (JudgNowGround(&num, &Dis, player->GetMatCar()) == true) {
		player->SetGroNum(&num);//�n�ʂ̎擾
	}

	M_C_Ground_Pop = new C_Ground_Pop_New(1);
}

c_GroundManager::~c_GroundManager()
{
	if (ground.size() > 0) {
		for (unsigned int gc = 0; gc < ground.size(); gc++) {
			delete ground[gc];
			ground.erase(ground.begin() + gc); 
			gc--;
		}
	}

	if (GroCou.size() > 0) {
		for (unsigned int g = 0; g < GroCou.size(); g++) {
			delete GroCou[g];
			GroCou.erase(GroCou.begin() + g);
			g--;
		}
	}

	if (cou != nullptr)delete cou;

	if (LightCount != nullptr) delete LightCount;

	//�n�ʂ̏��폜
	if (M_C_Ground_Pop != nullptr) delete M_C_Ground_Pop;
	
}

void c_GroundManager::Draw3D(void)
{
	if (ground.size() <= 0)return;

	for (auto && g : ground) g->SuperDraw();
	
}

bool c_GroundManager::Update(C_PlayerBase *player)
{
	if (ground.size() < 1) return false;

	for (unsigned int gc = 0; gc < ground.size(); gc++) {
		ground[gc]->SuperUpdate();

		//�����̓��̍폜�ƍ쐬
		float L_Radius = player->GetRadF();

		Judg judg;
		if (judg.BallJudg(&judg.SetPosM(&player->GetMatCar()), &judg.SetPosM(&ground[gc]->GetMat()), &L_Radius) == false)
		{

			if (player->GetCon().GroNum < gc)continue;
			if (ground[gc]->GetFlg() == false)continue;

			delete ground[gc];
			ground.erase(ground.begin() + gc);
			gc--;

			D3DXMATRIX Mat[2];
			Mat[0] = ground[ground.size() - 1]->GetMat0();
			Mat[1] = ground[ground.size() - 1]->GetMat1();

			int StopNum = 2;
			if (GroCou.size() == 0) {//�n�ʂ̌`��
				GroCou.push_back(new Cou(0, StopNum, 1, true, false));
			}
			if (cou->CouJudge() == false) cou->SetNum(0);

			const int L_Type = 0;

			S_GROUND_INIT_DATA L_Data = M_C_Ground_Pop->Get_Pop_Data_N();
			ground.push_back(new C_Ground_Object(&Mat[1], &Mat[0], &L_Data));
			if ((cou->GetNum() == 1) && (L_Data.gType == Co_Ground_Type_Straight)) ground[ground.size() - 1]->Init_Bill();

			int L_Type2 = L_Data.gType;/*Init_Ground_Push(&Mat[1], &Mat[0], &L_Type);*/
			if (L_Type2 >= 0) {
				if (M_C_Ground_Pop != nullptr) {
					M_C_Ground_Pop->Ground_Pop_Rear_N();
				}
				if (L_Type2 == 0) {
					cou->CouUpd();
				}
			}

			//�O���̏�����
			if (LightCount->Update() == true) ground[ground.size() - 1]->Init_Light();

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
			if (ground[gc]->GetFlg() == false) {
				ground[gc]->SetFlg(true);
			}
		}
	}

	return true;
	
}

bool c_GroundManager::JudgNowGround(unsigned int * GroundNumber, float * Dis, const D3DXMATRIX Mat)
{
	if (ground.size() <= 0) return false;

	float size;
	// �n�ʃ��C����
	for (unsigned int g = 0; g < ground.size(); g++) {

		float L_Radius = 40.0f;

		Judg judg;

		// �����̎��͂̒n�ʂ����𔻒�
		if (judg.BallJudg(&judg.SetPosM(&Mat), &judg.SetPosM(&ground[g]->GetMat()), &L_Radius) != true) continue;

		// �n�ʂ�4���_�쐬
		D3DXVECTOR3 v[4];
		for (int i = 0; i < 4; i++) v[i] = ground[g]->GetVer(i);

		// �n�ʂ̔|���S���̐������@���擾
		bool L_IdenFlg = ground[g]->GetIdenFlg();

		// ���C����
		if (judg.RayJudg_Polygon(&judg.SetPosM(&Mat), &D3DXVECTOR3(0.0f, -1.0f, 0.0f), &ground[g]->GetMat(),
			&v[0], &v[1], &v[2], &v[3], &size, &L_IdenFlg) != true) continue;

		// ���C�������������̏���

		*GroundNumber = g;
		*Dis = size;

		return true;

	}

	return false;
}

void c_GroundManager::SetGroundPop(const int * RoadNo)
{
	if (M_C_Ground_Pop == nullptr)return;

	if (*RoadNo == M_C_Ground_Pop->Get_GroundNo()) return;

	M_C_Ground_Pop->New_Pop(RoadNo);
}

void c_GroundManager::InitCarPopData(unsigned int *gNo, D3DXMATRIX *GroundMat, float *TransX,
	const unsigned int *playerGroundNum,const S_CAR_INIT_DATA *Data)
{
	
	*gNo = *playerGroundNum + Data->GroundNo;
	//�n�ʂ����邩�̔���
	if (*gNo < 0)*gNo = 0;
	if (*gNo > ground.size() - 1)*gNo = ground.size() - 1;
	//�Ԑ������߂�
	int Ground_Rail_Num = ground[*gNo]->GetWay().RailNum;
	int RailNum = Data->WayNo;

	if (RailNum == Co_Rail_Type_Random) {
		RailNum = rand() % (Ground_Rail_Num);
	}
	else
	{
		if (RailNum < 0)RailNum = 0;
		if (RailNum >= Ground_Rail_Num)RailNum = (Ground_Rail_Num)-1;
	}

	//�n�ʂ̈ʒu
	*GroundMat = ground[*gNo]->GetWay().StartMat;

	//�n�ʂ̏����ʒu�̉���
	*TransX = ground[*gNo]->GetWay().CurTransX[RailNum];
}

void c_GroundManager::BulletJudg(BULLETJUDGDATA * BJD, const RAYDATA * RD, bool * HitFlg, const float * Rad)
{
	//�n�ʐ�
	if (ground.size() <= 0)return;

	float Dis;
	bool JudgFlg;

	if (HitFlg != nullptr) {
		*HitFlg = false;
	}

	for (unsigned int g = 0; g < ground.size(); g++) {
		Judg judg;
		if (judg.BallJudg(&judg.SetPosM(&RD->Mat), &judg.SetPosM(&ground[g]->GetMat()), Rad) == true) {//�i�荞��
			JudgFlg = false;

			bool L_IdenFlg = ground[g]->GetIdenFlg();

			//���C����
			if (judg.RayJudg_Polygon(&judg.SetPosM(&RD->Mat), &RD->Ray, &ground[g]->GetMat(),
				&ground[g]->GetVer(0), &ground[g]->GetVer(1), &ground[g]->GetVer(2), &ground[g]->GetVer(3), &Dis, &L_IdenFlg) == true) {

				//���C�������������̏���

				JudgFlg = true;
				if (HitFlg != nullptr) {
					*HitFlg = true;
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
		for (int w = 0; w < ground[g]->Get_Wall_Num(); w++) {
			//�񖇂̕ǔ���
			if (judg.BallJudg(&judg.SetPosM(&RD->Mat), &judg.SetPosM(&ground[g]->Get_Mat_Wall(&w)), Rad) == true) {
				JudgFlg = false;
				//���C����
				if (judg.RayJudg_Mesh(&judg.SetPosM(&RD->Mat), &RD->Ray, &ground[g]->Get_DrawMat_Wall(&w), ground[g]->GetColModWall(), &Dis) == true) {
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

void c_GroundManager::FrustumCulling(const S_Frustum_Vec * FV_Data, const D3DXVECTOR3 *CamPos)
{
	if (ground.size() <= 0) return;

	for (unsigned int gc = 0; gc < ground.size(); gc++)
	{
		Judg judg;

		/*��*/
		if (ground[gc]->Get_Wall_Num() > 0) 
		{
			for (int w = 0; w < ground[gc]->Get_Wall_Num(); w++) {
				D3DXVECTOR3 pos = judg.SetPosM(&ground[gc]->Get_Mat_Wall(&w)) - *CamPos;
				float Radius = ground[gc]->Get_Data_Wall(&w).CullingRad;

				bool DrawFlg;

				// �㉺���E�Ƃ̔�r(Near,Far�͏ȗ�) normal �E center > radius
				judg.Judg_Frustum(&DrawFlg, FV_Data, &pos, &Radius);

				ground[gc]->Set_Draw_Flg_Wall(&w, &DrawFlg);
			}
		}

		/*�I�u�W�F�N�g*/
		if (ground[gc]->Get_Object_Draw_Num() > 0)
		{
			for (unsigned int o = 0; o < ground[gc]->Get_Object_Draw_Num(); o++) {
				S_Base3D_2 Data = ground[gc]->Get_Object_Data(&o);
				D3DXVECTOR3 pos = judg.SetPosM(&Data.Base.Mat) - *CamPos;

				bool DrawFlg;

				// �㉺���E�Ƃ̔�r(Near,Far�͏ȗ�) normal �E center > radius
				judg.Judg_Frustum(&DrawFlg, FV_Data, &pos, &Data.CullingRad);

				ground[gc]->Set_DrawFlg_Object(&o, &DrawFlg);
			}
		}
	}
}

bool c_GroundManager::SideJudg(const S_SideJudgChara * Data, const D3DXMATRIX * JudgMat_Base, 
	const D3DXVECTOR3 * Ray_Vec, float * Small_Dis, int * RayHit_No, D3DXMATRIX * RayHit_Mat,const float *Radius)
{
	if (ground.size() <= 0)return false;

	//�ǂ�
	int w = 1;
	if (Data->LeftFlg == true)w = 0;

	Judg judg;
	D3DXVECTOR3 Ray_Pos = judg.SetPosM(JudgMat_Base);

	bool Wall_Hit_Flg = false;

	//�n�ʐ�
	for (unsigned int g = 0; g < ground.size(); g++) {

		if (judg.BallJudg(&judg.SetPosM(JudgMat_Base), &judg.SetPosM(&ground[g]->Get_Mat_Wall(&w)), Radius) != true) continue;

		float Dis;

		//���C����
		if (judg.RayJudg_Mesh(&Ray_Pos, Ray_Vec, &ground[g]->Get_DrawMat_Wall(&w), ground[g]->GetColModWall(), &Dis) != true) continue;

		if (Dis > *Small_Dis) continue;

		*Small_Dis = Dis;
		*RayHit_No = 1;
		*RayHit_Mat = ground[g]->Get_DrawMat_Wall(&w);

		Wall_Hit_Flg = true;

	}

	return Wall_Hit_Flg;
}
