#include"Camera.h"
#include"../Key/Key.h"
#include"../GameSource/Judgment.h"

extern Key key;

void Camera::Init()
{
	camPos = D3DXVECTOR3(0, 0, 0);
	camAngY = 0;
	camAngX = 0;
	Big = -3.0;
	Small = -2.0;
	camSize = Big;
	D3DXMatrixTranslation(&CamMat, 0.0f, 0.0f, 0.0f);

	//�N�H�[�^�j�I���̏�����
	QuaFlg = false;
	Anime = 0.0f;
	IncFlg = false;

}

Camera::Camera() {
	Init();
}
Camera::Camera(D3DXMATRIX PlayerMat)
{
	Init();
	CamMat = PlayerMat;
	Judg judg;
	judg.SetMatP(&CamMat, &D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	D3DXMatrixRotationX(&CamRotX, D3DXToRadian(0.0f));
	D3DXMatrixRotationY(&CamRotY, D3DXToRadian(0.0f));
	//��]�̏�����
	if (1) {
		D3DXVECTOR3 cVec, ccVec;
		D3DXVec3TransformNormal(&cVec, &D3DXVECTOR3(0.0f, 0.0f, 1.0f), &CamMat);
		ccVec = cVec;

		//RotY�̌v�Z
		ccVec.y = 0;
		float Dot, Ang;
		Dot = D3DXVec3Dot(&D3DXVECTOR3(0.0f, 0.0f, 1.0f), &ccVec);
		if (Dot > 1.0f)Dot = 1.0f;
		if (Dot < -1.0f)Dot = -1.0f;
		Ang = (float)D3DXToDegree(acos(Dot));
		if (ccVec.x < 0.0f)Ang *= -1.0f;
		D3DXMatrixRotationY(&CamRotY, D3DXToRadian(Ang));
		
		//RotX�̌v�Z
		D3DXMATRIX CCamMat;
		CCamMat = CamRotY * CamRotX;
		D3DXVec3TransformNormal(&ccVec, &D3DXVECTOR3(0.0f, 0.0f, 1.0f), &CCamMat);
		Dot = D3DXVec3Dot(&ccVec, &cVec);
		if (Dot > 1.0f)Dot = 1.0f;
		if (Dot < -1.0f)Dot = -1.0f;
		Ang = (float)D3DXToDegree(acos(Dot));
		if (ccVec.y > cVec.y)Ang *= -1.0f;
		D3DXMatrixRotationX(&CamRotX, D3DXToRadian(Ang));
	}
}
Camera::~Camera() {
	
}

bool Camera::UpdateM(bool MouFlg)
{
	//float sen = 4.0f;//���x
	//mouse->CamUpdate(&camAngX, &camAngY, sen, 1, 1, IncFlg);
	//if ((MouFlg == true) && (QuaFlg == false)) {
	//	float limit = 89.0f;
	//	if (camAngX > limit)camAngX = limit;
	//	if (camAngX < -limit)camAngX = -limit;
	//	if (camAngX < -30.0f) { camSize = Small; }
	//	else {
	//		camSize = Big;
	//	}
	//	D3DXMATRIX RotXMat, RotYMat;
	//	D3DXMatrixRotationX(&RotXMat, D3DXToRadian(camAngX));
	//	D3DXMatrixRotationY(&RotYMat, D3DXToRadian(camAngY));
	//	CamRotX = RotXMat * CamRotX;
	//	CamRotY = RotYMat * CamRotY;
	//}
	return true;
}

bool Camera::UpdateM(bool MouFlg, C_Mouse * mouse)
{
	float sen = 4.0f;//���x
	mouse->CamUpdate(&camAngX, &camAngY, sen, 1, 1, IncFlg);
	if ((MouFlg == true) && (QuaFlg == false)) {
		float limit = 89.0f;
		if (camAngX > limit)camAngX = limit;
		if (camAngX < -limit)camAngX = -limit;
		if (camAngX < -30.0f) { camSize = Small; }
		else {
			camSize = Big;
		}
		D3DXMATRIX RotXMat, RotYMat;
		D3DXMatrixRotationX(&RotXMat, D3DXToRadian(camAngX));
		D3DXMatrixRotationY(&RotYMat, D3DXToRadian(camAngY));
		CamRotX = RotXMat * CamRotX;
		CamRotY = RotYMat * CamRotY;
	}
	return true;
}

bool Camera::Update(D3DXMATRIX mat) {
	D3DXVECTOR3 Pos;
	Pos = D3DXVECTOR3(mat._41, mat._42, mat._43);
	camLook=Pos+D3DXVECTOR3(0.0f, 0.6f, 0.0f);
	D3DXVec3TransformNormal(&camPos, &D3DXVECTOR3(0, 0, camSize), &GetMat());
	camPos += camLook;
	return true;
}


float Camera::GetSize(D3DXVECTOR3 Pos,D3DXVECTOR3 Look) {
	float xx, zz;
	xx =  Pos.x- Look.x;
	zz = Pos.z - Look.z;
	xx = (float)pow(xx, 2.0f);
	zz = (float)pow(zz, 2.0f);
	float xz;
	xz = xx + zz;
	bool xyz;
	if (xz < 0) {
		xyz = true;
	}
	else {
		xyz = false;
	}
	xz = (float)sqrt(xz);
	if (xyz = true) {
		xz = -xz;
	}
	if (xz > camSize) xz = camSize;
	if (xz < (-camSize))xz = (-camSize);
	return xz;
}
D3DXVECTOR3 Camera::GetVec()
{
	D3DXVECTOR3 vec;
	vec = camLook - camPos;
	D3DXVec3Normalize(&vec, &vec);
	return vec;
}
D3DXMATRIX Camera::GetMat(void)
{
	CamMat = CamRotX * CamRotY;
	return CamMat;
}
void Camera::SetQuaMat(const D3DXMATRIX * EndQuaRotXMat, const D3DXMATRIX * EndQuaRotYMat, const float * QuaFrameUp)
{
	if (QuaFlg == false) {
		StartRotXMat = CamRotX;
		StartRotYMat = CamRotY;
		EndRotXMat = *EndQuaRotXMat;
		EndRotYMat = *EndQuaRotYMat;
		FrameUp = *QuaFrameUp;
		Anime = 0.0f;
		QuaFlg = true;
	}
}
void Camera::RotXJudg(const D3DXMATRIX * PlayerMat)
{
	D3DXVECTOR3 PVec, XVec;
	D3DXVec3TransformNormal(&PVec, &D3DXVECTOR3(0.0f, 0.0f, 1.0f), PlayerMat);
	D3DXVec3TransformNormal(&XVec, &D3DXVECTOR3(0.0f, 0.0f, 1.0f), &(CamRotX**PlayerMat));

	double Dot, Ang;
	Dot=D3DXVec3Dot(&PVec, &XVec);
	if (Dot > 1.0f)Dot = 1.0f;
	if (Dot < -1.0f)Dot = -1.0f;
	Ang = D3DXToDegree(acos(Dot));
	if (PVec.y < XVec.y)Ang *= -1.0f;

	//���
	float AngBig,AngSmall;
	AngBig = 21.0f;
	AngSmall = -30.0f;
	bool Flg=false;
	if (Ang >AngBig) {
		Ang = AngBig;
		Flg = true;
	}
	if (Ang < AngSmall) {
		Ang = AngSmall;
		Flg = true;
	}
	if (Flg == true) {
		D3DXMatrixRotationX(&CamRotX, D3DXToRadian((float)Ang));
	}
}
void Camera::WallJudg(const int *RadF, c_GroundManager *groundManager)
{
	//���C
	D3DXVECTOR3 Vec = camPos - camLook;
	//���C�T�C�Y
	float Dis, SmallDis = D3DXVec3Length(&Vec);
	//���C�̐��K��
	D3DXVec3Normalize(&Vec, &Vec);
	//����t���O
	bool JudgFlg = false;
	//�ǔ���
	//�n�ʂ̑��݊m�F
	if (groundManager->GetGroundNum() > 0) {
		//���݂���
		//�n�ʂ̐�
		for (unsigned int gc = 0; gc < groundManager->GetGroundNum(); gc++) {

			float L_Radius = (float)*RadF;

			Judg judg;

			//�͈͍i�荞��
			if (judg.BallJudg(&camPos, &judg.SetPosM(&groundManager->GetGroundMat(&gc)), &L_Radius) != true) continue;

			//�͈͓�
			//���t���O
			bool LeftFlg = true;
			//�ǂ̐�
			for (unsigned int wc = 0; wc < groundManager->GetWallNum(&gc); wc++) {
				//�ǂ̓����������Ȃ����߂̊g��s��
				D3DXMATRIX ScalY;
				D3DXMatrixScaling(&ScalY, 1.3f, 1.0f, 1.0f);
				//���C����
				if (judg.RayJudg_Mesh(&camLook, &Vec, &(ScalY*groundManager->GetWallDrawMat(&gc,&wc)), groundManager->GetWallColMesh(&gc,&wc), &Dis) == true) {
					//��������
					if (Dis < SmallDis) {
						SmallDis = Dis;
						JudgFlg = true;
					}
				}
			}

		}
	}
	//����I��
	//�J�����̈ʒu�Z�b�g
	if (JudgFlg == true) {
		SetCamPos(&(camLook + Vec * (SmallDis - 0.01f)));
	}
}

void Camera::InitCarCameraMove(const bool *GameEndFlg, const bool *KeyFlg, const D3DXMATRIX *PlayerMat)
{
	//�J������plaeyr�̑O���ɐU���������N�H�[�^�j�I���̏�����
	if (*GameEndFlg != false) return;
	//�O���ɐU������v�Z
	if ((*KeyFlg != true) || (GetQuaFlg() != false))return;

	D3DXVECTOR3 cVec, ccVec, pVec, ppVec;
	D3DXVec3TransformNormal(&cVec, &D3DXVECTOR3(0.0f, 0.0f, 1.0f), &GetMat());
	D3DXVec3TransformNormal(&pVec, &D3DXVECTOR3(0.0f, 0.0f, 1.0f), PlayerMat);
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
	D3DXMATRIX Mat = *PlayerMat;
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
	SetQuaMat(&CamRotX, &CamRotY, &FrameUp);

}

bool Camera::UpdateQua(const bool *GameEndFlg, const bool *KeyFlg, const D3DXMATRIX *PlayerMat)
{
	InitCarCameraMove(GameEndFlg,KeyFlg,PlayerMat);

	if (QuaFlg == true) {
		Anime += FrameUp;
		if (Anime > 1.0f) {
			Anime = 1.0f;
			QuaFlg = false;
		}
		Judg judg;
		judg.AnimeProc(&CamRotX, StartRotXMat, EndRotXMat, Anime);
		judg.AnimeProc(&CamRotY, StartRotYMat, EndRotYMat, Anime);
	}
	return true;
}
D3DXVECTOR3 Camera::GetLook(void) {
	return camLook;
}
D3DXVECTOR3 Camera::GetPos(void) {
	return camPos;
}
