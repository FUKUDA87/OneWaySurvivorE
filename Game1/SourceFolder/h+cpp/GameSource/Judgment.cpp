#include"Judgment.h"
extern LPDIRECT3DDEVICE9		lpD3DDevice;	// Direct3DDeviceインターフェイス
extern HWND Hwnd;
extern D3DXVECTOR3 CamPosG;

bool Judg::ball(D3DXMATRIX mat1, D3DXMATRIX mat2,float rad) {
	D3DXVECTOR3 pos1,pos2,targetPos;
	pos1 = D3DXVECTOR3(mat1._41, mat1._42, mat1._43);
	pos2 = D3DXVECTOR3(mat2._41, mat2._42, mat2._43);
	targetPos = pos2 - pos1;
	float length = D3DXVec3Length(&targetPos);
	if (length < rad) {
		return true;
	}
	return false;
}

bool Judg::ball(D3DXVECTOR3 PosA, D3DXMATRIX MatB, float Rad)
{
	bool Flg = false;
	D3DXMATRIX Mat;
	Mat=SetMatP(PosA);
	Flg=ball(Mat, MatB, Rad);
	return Flg;
}

bool Judg::ball(D3DXMATRIX mat1, D3DXMATRIX mat2, float rad,D3DXMATRIX *Trans1,D3DXMATRIX *Trans2)
{
	D3DXVECTOR3 pos1, pos2, targetPos;
	pos1 = D3DXVECTOR3(mat1._41, mat1._42, mat1._43);
	pos2 = D3DXVECTOR3(mat2._41, mat2._42, mat2._43);
	targetPos = pos2 - pos1;
	float length = D3DXVec3Length(&targetPos);
	if (length < rad) {
		D3DXVec3Normalize(&targetPos, &targetPos);
		targetPos *= (rad) - length;
		pos2 += targetPos;
		pos2.y = 0.0f;
		D3DXMatrixTranslation(Trans2, pos2.x, pos2.y, pos2.z);
		return true;
	}
	return false;
}

float Judg::ball(D3DXMATRIX mat1, D3DXMATRIX mat2)
{
	D3DXVECTOR3 pos1, pos2, targetPos;
	pos1 = D3DXVECTOR3(mat1._41, mat1._42, mat1._43);
	pos2 = D3DXVECTOR3(mat2._41, mat2._42, mat2._43);
	targetPos = pos2 - pos1;
	float length = D3DXVec3Length(&targetPos);
	return length;
}

bool Judg::ball(judgDeta *jd, D3DXMATRIX matB, float radB, int damB)
{
	if (ball(jd->Mat, matB, jd->Rad + radB) == true) {
		jd->Hp -= damB;
		if (HPj(&jd->Hp, &jd->MaxHp) == true) {
			return true;
		}
	}
	return false;
}

bool Judg::HPj(int *NowHp, int *NowMaxHp)
{
	if (*NowHp < 0) {
		*NowHp = 0;
		return false;
	}
	else {
		if (*NowHp > *NowMaxHp) {
			*NowHp = *NowMaxHp;
		}
	}
	return true;
}

bool Judg::RayPolM(D3DXMATRIX mat,D3DXVECTOR3 v0, D3DXVECTOR3 v1, D3DXVECTOR3 v2, D3DXVECTOR3 v3, D3DXMATRIX pmat,D3DXVECTOR3 ray,float *Dis)
{
	D3DXVECTOR3 Pos,VPos[4];
	Pos = D3DXVECTOR3(mat._41, mat._42, mat._43);
	D3DXVec3TransformCoord(&VPos[0], &v0, &pmat);
	D3DXVec3TransformCoord(&VPos[1], &v1, &pmat);
	D3DXVec3TransformCoord(&VPos[2], &v2, &pmat);
	D3DXVec3TransformCoord(&VPos[3], &v3, &pmat);
	D3DXVec3Normalize(&ray, &ray);
	if (D3DXIntersectTri(&VPos[0], &VPos[1], &VPos[2], &Pos, &ray, NULL, NULL, Dis) ||
		D3DXIntersectTri(&VPos[0], &VPos[2], &VPos[3], &Pos, &ray, NULL, NULL, Dis)) {
		return true;
	}
	return false;
}

bool Judg::RayPolP(D3DXVECTOR3 Pos, D3DXVECTOR3 v0, D3DXVECTOR3 v1, D3DXVECTOR3 v2, D3DXVECTOR3 v3, D3DXMATRIX pmat, D3DXVECTOR3 ray, float * Dis)
{
	D3DXVECTOR3 VPos[4];
	D3DXVec3TransformCoord(&VPos[0], &v0, &pmat);
	D3DXVec3TransformCoord(&VPos[1], &v1, &pmat);
	D3DXVec3TransformCoord(&VPos[2], &v2, &pmat);
	D3DXVec3TransformCoord(&VPos[3], &v3, &pmat);
	D3DXVec3Normalize(&ray, &ray);
	if (D3DXIntersectTri(&VPos[0], &VPos[1], &VPos[2], &Pos, &ray, NULL, NULL, Dis) ||
		D3DXIntersectTri(&VPos[0], &VPos[2], &VPos[3], &Pos, &ray, NULL, NULL, Dis)) {
		return true;
	}
	return false;
}

bool Judg::RayPolP(D3DXVECTOR3 Pos, D3DXVECTOR3 v0, D3DXVECTOR3 v1, D3DXVECTOR3 v2, D3DXVECTOR3 v3, D3DXVECTOR3 ray, float * Dis)
{
	D3DXVECTOR3 VPos[4];
	VPos[0] = v0;
	VPos[1] = v1;
	VPos[2] = v2;
	VPos[3] = v3;
	D3DXVec3Normalize(&ray, &ray);
	if (D3DXIntersectTri(&VPos[0], &VPos[1], &VPos[2], &Pos, &ray, NULL, NULL, Dis) ||
		D3DXIntersectTri(&VPos[0], &VPos[2], &VPos[3], &Pos, &ray, NULL, NULL, Dis)) {
		return true;
	}
	return false;
}

bool Judg::RayPolM(D3DXMATRIX Mat,D3DXVECTOR3 v0, D3DXVECTOR3 v1, D3DXVECTOR3 v2, D3DXVECTOR3 v3, D3DXVECTOR3 ray, float * Dis)
{
	D3DXVECTOR3 Pos,VPos[4];
	Pos = D3DXVECTOR3(Mat._41, Mat._42, Mat._43);
	VPos[0] = v0;
	VPos[1] = v1;
	VPos[2] = v2;
	VPos[3] = v3;
	D3DXVec3Normalize(&ray, &ray);
	if (D3DXIntersectTri(&VPos[0], &VPos[1], &VPos[2], &Pos, &ray, NULL, NULL, Dis) ||
		D3DXIntersectTri(&VPos[0], &VPos[2], &VPos[3], &Pos, &ray, NULL, NULL, Dis)) {
		return true;
	}
	return false;
}

D3DXVECTOR3 Judg::Pos2D(D3DXVECTOR3 pos3D)
{
	D3DXMATRIX IdenMat;
	D3DXMatrixIdentity(&IdenMat);
	D3DXVECTOR3 pos2D;
	if (D2Flg == true) {
		D3DXVec3Project(&pos2D, &pos3D, &SViewport, &SmProj, &SmView, &IdenMat);
	}
	return pos2D;
}

void Judg::Pos2Dpvv(D3DXMATRIX mProj, D3DXMATRIX mView, D3DVIEWPORT9 Viewport)
{
	SmProj = mProj;
	SmView = mView;
	SViewport = Viewport;
	if (D2Flg == false) {
		D2Flg = true;
	}
}

D3DXVECTOR3 Judg::Pos2DPE(D3DXMATRIX eMat, D3DXMATRIX pMat)
{
	D3DXVECTOR3 Pos, EPos;
	if (D2Flg == true) {
		EPos = D3DXVECTOR3(eMat._41, eMat._42, eMat._43);
		Pos = Pos2D(EPos);
		if ((Pos.z < 0) || (Pos.z > 1)) {
			//playerからみて逆の位置のenemy
			D3DXVECTOR3 PPos, vec;
			PPos = D3DXVECTOR3(pMat._41, pMat._42, pMat._43);
			vec = PPos - EPos;
			EPos = PPos + vec;
			EPos.y = eMat._42;
			Pos = Pos2D(EPos);
			Pos.z = 2.0f;
		}
	}
	return Pos;
}

double Judg::Ang(D3DXVECTOR3 pla,D3DXVECTOR3 tar,D3DXVECTOR3 vec)
{
	//playerの方に向くtargetの計算---------------------------------------------------
	//2が向いているベクトル
	D3DXVECTOR3 Vec;
	D3DXMATRIX Pla;
	D3DXMatrixTranslation(&Pla, pla.x, pla.y, pla.z);
	D3DXVec3TransformNormal(&Vec, &vec, &Pla);
	//白の内積を求める
	double nowAng;
	nowAng = D3DXVec3Dot(&vec, &Vec);
	nowAng = D3DXToDegree(acos(nowAng));
	if (Vec.x < 0) {
		nowAng = -nowAng;
	}
	//
	D3DXVECTOR3 kPos, pPos, TargetVec;
	TargetVec = tar - pla;
	D3DXVec3Normalize(&TargetVec, &TargetVec);
	double toAng;
	toAng = D3DXVec3Dot(&vec, &TargetVec);
	toAng = D3DXToDegree(acos(toAng));
	if (TargetVec.x < 0) {
		toAng = -toAng;
	}
	//
	double ang;
	ang = toAng - nowAng;

	if (ang > 180.0f) ang -= 360.0f;
	if (ang < -180.0f)ang += 360.0f;

	//float f = 3.0f;
	//if (ang > f)ang = f;
	//if (ang < -f)ang = -f;
	//D3DXMatrixRotationY(&katsuoRot, D3DXToRadian(ang));

	return ang;
}

bool Judg::Mesh(D3DXVECTOR3 pos, D3DXVECTOR3 vec,D3DXMATRIX mat, LPD3DXMESH mesh, float * Dis)
{
	//セットする
	D3DXMATRIX InvMat;
	D3DXMatrixInverse(&InvMat, NULL, &mat);
	D3DXVECTOR3 LocalPos, LocalVec;
	D3DXVec3TransformCoord(&LocalPos, &pos, &InvMat);
	D3DXVec3TransformNormal(&LocalVec, &vec, &InvMat);
	//レイ判定
	BOOL Hit;
	D3DXIntersect(mesh, &LocalPos, &LocalVec, &Hit, NULL, NULL, NULL, Dis, NULL, NULL);
	if (Hit == TRUE) {
		return true;
	}
	else {
		return false;
	}
}

bool Judg::Mesh(D3DXMATRIX MatA, int VecNumA, float BodyRadA, D3DXMATRIX MatB, LPD3DXMESH MeshB)
{
	//方向Vec
	D3DXVECTOR3 Vec;
	//VecNumAの確認
	//前か確認
	if (VecNumA == 0) {
		//前のベクトル作成
		Vec = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	}
	else {
		//後ろか確認
		if (VecNumA == 1) {
			//後ろのベクトル作成
			Vec = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		}
		else {
			//左か確認
			if (VecNumA == 2) {
				//左のベクトル作成
				Vec = D3DXVECTOR3(-1.0f, 0.0f, 0.0f);
			}
			else {
				//右か確認
				if (VecNumA == 3) {
					//右のベクトル作成
					Vec = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
				}
				else {
					//全て違う場合は判定しない
					return false;
				}
			}
		}
	}
	//方向ベクトルの作成
	D3DXVec3TransformNormal(&Vec, &Vec, &MatA);
	
	//長さ用
	float Dis;
	//MatAのPos
	D3DXVECTOR3 PosA;
	//PosAにMatAの座標を入れる
	PosA = SetPosM(MatA);
	//レイ判定
	if (Mesh(PosA, Vec, MatB, MeshB, &Dis) == true) {

	}
	return false;
}

bool Judg::Mesh(D3DXVECTOR3 pos, D3DXVECTOR3 vec, D3DXMATRIX mat, LPD3DXMESH mesh, float * Dis, int m)
{
	//セットする
	D3DXMATRIX InvMat;
	D3DXMatrixInverse(&InvMat, NULL, &mat);
	D3DXVECTOR3 LocalPos, LocalVec;
	D3DXVec3TransformCoord(&LocalPos, &pos, &InvMat);
	D3DXVec3TransformNormal(&LocalVec, &vec, &InvMat);
	//レイ判定
	BOOL Hit;
	DWORD Cou;
	D3DXIntersect(mesh, &LocalPos, &LocalVec, &Hit, NULL, NULL, NULL, Dis, NULL, &Cou);
	if ((Hit == TRUE)||(Cou>=2)) {
		return true;
	}
	else {
		return false;
	}
}

bool Judg::CroDot(D3DXMATRIX mat, D3DXMATRIX *rot, D3DXVECTOR3 targetPos, D3DXVECTOR3 FrontVec, double *Ang, double ang, bool angF)
{
	D3DXMATRIX InvMat;
	D3DXMatrixInverse(&InvMat, NULL, &mat);
	D3DXVECTOR3 TargetPos;
	D3DXVec3TransformCoord(&TargetPos, &targetPos, &InvMat);
	D3DXVECTOR3 RotAxis;
	D3DXVec3Cross(&RotAxis, &FrontVec, &TargetPos);
	D3DXVec3Normalize(&TargetPos, &TargetPos);
	float Dot;
	Dot = D3DXVec3Dot(&FrontVec, &TargetPos);
	if (Dot > 1)Dot = 1;
	if (Dot < -1)Dot = -1;
	*Ang = D3DXToDegree(acos(Dot));
	if (angF == true) {
		if (*Ang > ang)*Ang = ang;
	}
	D3DXMatrixRotationAxis(rot, &RotAxis, D3DXToRadian((float)*Ang));
	return true;
}

bool Judg::TarRotX(D3DXMATRIX mat, D3DXMATRIX * rot, D3DXVECTOR3 targetPos, D3DXVECTOR3 FrontVec)
{
	D3DXMATRIX InvMat;
	D3DXMatrixInverse(&InvMat, NULL, &mat);
	D3DXVECTOR3 TargetPos;
	D3DXVec3TransformCoord(&TargetPos, &targetPos, &InvMat);
	//TargetPos.y = 0;
	D3DXVECTOR3 RotAxis;
	D3DXVec3Cross(&RotAxis, &FrontVec, &TargetPos);
	D3DXVec3Normalize(&TargetPos, &TargetPos);
	double Dot,Ang;
	Dot = D3DXVec3Dot(&FrontVec, &TargetPos);
	if (Dot > 1)Dot = 1;
	if (Dot < -1)Dot = -1;
	Ang = D3DXToDegree(acos(Dot));
	D3DXMatrixRotationAxis(rot, &RotAxis, D3DXToRadian((float)Ang));
	return true;
}

bool Judg::TarRotY(D3DXMATRIX mat,D3DXMATRIX *rotY, D3DXVECTOR3 targetPos, D3DXVECTOR3 FrontVec)
{
	mat._42 = 0.0f;
	targetPos.y = 0.0f;
	FrontVec.y = 0.0f;
	//playerの方に向くカツオの計算
	//カツオが向いているベクトル
	D3DXVECTOR3 kVec;
	D3DXVec3TransformNormal(&kVec, &FrontVec, &mat);
	//白の内積を求める
	double nowAng;
	nowAng = D3DXVec3Dot(&FrontVec, &kVec);
	nowAng = D3DXToDegree(acos(nowAng));
	if (kVec.x < 0) {
		nowAng = -nowAng;
	}
	//
	D3DXVECTOR3 kPos, pPos, TargetVec;
	kPos = D3DXVECTOR3(mat._41, mat._42, mat._43);
	pPos = targetPos;
	TargetVec = pPos - kPos;
	TargetVec.y = 0.0f;
	D3DXVec3Normalize(&TargetVec, &TargetVec);
	double toAng;
	toAng = D3DXVec3Dot(&FrontVec, &TargetVec);
	toAng = D3DXToDegree(acos(toAng));
	if (TargetVec.x < 0) {
		toAng = -toAng;
	}
	//
	double angs;
	angs = toAng - nowAng;

	if (angs > 180.0f) angs -= 360.0f;
	if (angs < -180.0f)angs += 360.0f;

	D3DXMatrixRotationY(rotY, D3DXToRadian((float)angs));
	return true;
}

bool Judg::TarEndMat(D3DXMATRIX * mat, D3DXMATRIX TransMat, D3DXMATRIX * RotXMat, D3DXMATRIX * RotYMat, D3DXVECTOR3 TargetPos, D3DXVECTOR3 FrontVec)
{
	D3DXMATRIX Mat;
	Mat = TransMat;
	TarRotY(Mat, RotYMat, TargetPos, FrontVec);
	Mat = (*RotYMat)*Mat;
	TarRotX(Mat, RotXMat, TargetPos, FrontVec);
	Mat = (*RotXMat)*Mat;
	*mat = Mat;
	return true;
}



D3DXVECTOR3 Judg::SetPosM(D3DXMATRIX Mat)
{
	return D3DXVECTOR3(Mat._41, Mat._42, Mat._43);
}

bool Judg::SetPosM(D3DXVECTOR3 *Pos, D3DXMATRIX Mat)
{
	*Pos = D3DXVECTOR3(Mat._41, Mat._42, Mat._43);
	return true;
}

D3DXMATRIX Judg::SetMatP(D3DXVECTOR3 Pos)
{
	D3DXMATRIX Mat;
	Mat._41 = Pos.x;
	Mat._42 = Pos.y;
	Mat._43 = Pos.z;
	return Mat;
}

bool Judg::SetMatP(D3DXMATRIX * Mat, D3DXVECTOR3 Pos)
{
	Mat->_41 = Pos.x;
	Mat->_42 = Pos.y;
	Mat->_43 = Pos.z;
	return true;
}

bool Judg::AnimeProc(D3DXMATRIX * NowMat, D3DXMATRIX StartMat, D3DXMATRIX EndMat, float AnimeFrame)
{
	D3DXQUATERNION StartQua, EndQua, NowQua;
	D3DXQuaternionRotationMatrix(&StartQua, &StartMat);
	D3DXQuaternionRotationMatrix(&EndQua, &EndMat);
	D3DXQuaternionSlerp(&NowQua, &StartQua, &EndQua, AnimeFrame);
	D3DXMatrixRotationQuaternion(NowMat, &NowQua);

	D3DXVECTOR3 StartPos, EndPos, NowPos;
	SetPosM(&StartPos, StartMat);
	SetPosM(&EndPos,EndMat);
	D3DXVec3Lerp(&NowPos, &StartPos, &EndPos, AnimeFrame);
	SetFloatQ(&NowPos);
	SetMatP(NowMat, NowPos);
	return true;
}

bool Judg::AnimeProc(D3DXVECTOR3 * NowPos, D3DXVECTOR3 StartPos, D3DXVECTOR3 EndPos, float AnimeFrame)
{
	D3DXVec3Lerp(NowPos, &StartPos, &EndPos, AnimeFrame);
	return true;
}

bool Judg::AnimeFrameInc(float * AnimeFrame, float up, bool upFlg)
{
	if (upFlg == true) {
		*AnimeFrame += up;
	}
	if (*AnimeFrame < 0.0f) {
		*AnimeFrame = 0.0f;
		return false;
	}
	if (*AnimeFrame > 1.0f) {
		*AnimeFrame = 1.0f;
		return false;
	}
	return true;
}

bool Judg::Quaternion(D3DXMATRIX * NowMat, D3DXMATRIX StartMat, D3DXMATRIX EndMat, float * AnimeFrame, float up, bool upFlg)
{
	bool Flg;
	Flg=AnimeFrameInc(AnimeFrame, up, upFlg);
	AnimeProc(NowMat,StartMat,EndMat,*AnimeFrame);
	return Flg;
}

bool Judg::Quaternion(D3DXVECTOR3 * NowPos, D3DXVECTOR3 StartPos, D3DXVECTOR3 EndPos, float * AnimeFrame, float up, bool upFlg)
{
	bool Flg;
	Flg = AnimeFrameInc(AnimeFrame, up, upFlg);
	AnimeProc(NowPos, StartPos, EndPos, *AnimeFrame);
	return Flg;
}

D3DXVECTOR3 Judg::DisPos(D3DXVECTOR3 PosA, D3DXVECTOR3 PosB, float Dis)
{
	D3DXVECTOR3 PosD,Vec;
	Vec = PosB - PosA;
	D3DXVec3Normalize(&Vec, &Vec);
	PosD = PosA + Vec * Dis;
	return PosD;
}

D3DXVECTOR3 Judg::Billboard(const D3DXVECTOR3 OldPos, const D3DXVECTOR3 NowPos, const D3DXVECTOR3 camPos, const float Size)
{
	D3DXVECTOR3 LPos, EPos, CPos, cVec, eVec, vec;
	LPos = OldPos;
	EPos = NowPos;
	CPos = camPos;
	cVec = CPos - LPos;
	eVec = EPos - LPos;
	D3DXVec3Normalize(&cVec, &cVec);
	D3DXVec3Normalize(&eVec, &eVec);
	D3DXVec3Cross(&vec, &cVec, &eVec);
	D3DXVec3Normalize(&vec, &vec);
	vec = vec * Size;
	return vec;
}

D3DXVECTOR3 Judg::Billboard(const D3DXVECTOR3 OldPos, const D3DXVECTOR3 NowPos, const float Size,const bool Reverse)
{
	D3DXVECTOR3 LPos, EPos, CPos, cVec, eVec, vec;
	LPos = OldPos;
	EPos = NowPos;
	CPos = CamPosG;
	if (Reverse == false) {
		cVec = CPos - LPos;
		eVec = EPos - LPos;
	}
	else {
		cVec = CPos - EPos;
		eVec = LPos - EPos;
	}
	D3DXVec3Normalize(&cVec, &cVec);
	D3DXVec3Normalize(&eVec, &eVec);
	D3DXVec3Cross(&vec, &cVec, &eVec);
	D3DXVec3Normalize(&vec, &vec);
	vec = vec * Size;
	return vec;
}

bool Judg::LineLine(const D3DXVECTOR2 PosA, const D3DXVECTOR2 VecA, const D3DXVECTOR2 PosB, const D3DXVECTOR2 VecB, float * Dis)
{
	D3DXVECTOR2 posA, posB, vecA, vecB;
	posA = PosA;
	vecA = VecA;

	posB = PosB;
	vecB = VecB;

	//線の法線を調べます。座標ベクトル B から座標ベクトル A を引いてベクトルABを求めます。
	D3DXVECTOR2 pvB;
	pvB = vecB - posB;

	//時計回りに90度回転します。
	D3DXVECTOR2 n;
	n = D3DXVECTOR2(-pvB.y, pvB.x);

	//法線を正規化します。
	D3DXVec2Normalize(&n, &n);


	//とりあえず下の式で t が求まります。
	float d;
	d = -(posB.x * n.x + posB.y * n.y);
	*Dis = -(n.x * posA.x + n.y * posA.y + d) / (n.x * vecA.x + n.y * vecA.y);
	if ((*Dis > 0.0f) && (*Dis <= 1.0f)) {

	}
	else {
		return false;
	}

	//点が線に含まれているかどうか。
	D3DXVECTOR2 posC;
	posC = posA + vecA * (*Dis);
	D3DXVECTOR2 acVec, bcVec;
	acVec = posC - posB;
	bcVec = posC - vecB;
	float Dot;
	Dot = (acVec.x * bcVec.x) + (acVec.y * bcVec.y);

	if ((Dot < 0.0f)) {
		return true;
	}
	return false;
}

D3DXVECTOR2 Judg::HalfSize(const D3DXVECTOR3 sPos, const int Width, const int Height)
{
	D3DXVECTOR2 Pos;
	Pos =D3DXVECTOR2((float)Width / 2.0f*sPos.x,(float)Height / 2.0f*sPos.y);
	return Pos;
}

bool Judg::PlaneP(RECT * rc, const D3DXVECTOR3 PosA, const D3DXVECTOR3 sPos, const int Width, const int Height)
{
	D3DXVECTOR2 PosL, PosR,size;
	size = HalfSize(sPos, Width, Height);
	PosL = D3DXVECTOR2( PosA.x - size.x,PosA.y - size.y);
	PosR = D3DXVECTOR2( PosA.x + size.x,PosA.y + size.y);
	*rc = { (int)PosL.x,(int)PosL.y,(int)PosR.x,(int)PosR.y };
	return true;
}

bool Judg::PlaneCri(const D3DXVECTOR3 PosA, const D3DXVECTOR3 sPos, const int Width, const int Height)
{
	RECT rcM;
	PlaneP(&rcM, PosA, sPos, Width, Height);
	POINT Pt;
	Pt = GetPoint();
	if ((Pt.x > rcM.left) && (Pt.x < rcM.right) && (Pt.y > rcM.top) && (Pt.y < rcM.bottom)) {
		return true;
	}
	return false;
}

bool Judg::PlaneCri(const D3DXMATRIX MatA, const D3DXVECTOR3 sPos, const int Width, const int Height)
{
	RECT rcM;
	D3DXVECTOR3 pos;
	SetPosM(&pos, MatA);
	PlaneP(&rcM, pos, sPos, Width, Height);
	POINT Pt;
	Pt = GetPoint();
	if ((Pt.x > rcM.left) && (Pt.x < rcM.right) && (Pt.y > rcM.top) && (Pt.y < rcM.bottom)) {
		return true;
	}
	return false;
}

POINT Judg::GetPoint(void)
{
	POINT Pt;
	GetCursorPos(&Pt);
	ScreenToClient(Hwnd, &Pt);
	return Pt;
}

bool Judg::LineLine3D(D3DXVECTOR3 * GetPos, D3DXVECTOR3 PosA1, D3DXVECTOR3 PosA2, D3DXVECTOR3 PosB1, D3DXVECTOR3 PosB2)
{
	//交差判定------------------------------------------------------------------
	/*bool Flg;
	if ((D3DXToDegree(acos(D3DXVec3Dot(&(PosA2 - PosA1), &(PosB1 - PosA1))))*D3DXToDegree(acos(D3DXVec3Dot(&(PosA2 - PosA1), &(PosB2 - PosA1)))) < 0.0f) &&
		(D3DXToDegree(acos(D3DXVec3Dot(&(PosB2 - PosB1), &(PosA1 - PosB1))))*D3DXToDegree(acos(D3DXVec3Dot(&(PosB2 - PosB1), &(PosA2 - PosB1)))) < 0.0f)) {
		Flg = true;
	}
	else {
		return false;
	}*/
	//交点----------------------------------------------------------------------
	D3DXVECTOR3 b = PosB2 - PosB1,b2,b3,s1,s2;
	D3DXVec3Normalize(&b, &b);
	D3DXVec3Normalize(&b2, &(PosA1 - PosB1));
	D3DXVec3Cross(&s1, &b, &b2);
	double d1 = D3DXVec3Length(&s1);
	if (d1 < 0.0f) {
		d1 = d1*(-1.0f);
	}
	//if (d1 > 1.0f)d1 = 1.0f;
	//d1 = D3DXToDegree(acos(d1));
	D3DXVec3Normalize(&b3, &(PosA2 - PosB1));
	D3DXVec3Cross(&s2,&b, &b3);
	double d2 = D3DXVec3Length(&s2);
	if (d2 < 0.0f) {
		d2 = d2*(-1.0f);
	}
	//if (d2 > 1.0f)d2 = 1.0f;
	//d2 = D3DXToDegree(acos(d2));
	double t = d2 / (d2 + d1);//-------------------------------------

	D3DXVECTOR3 e = PosB1 - PosB2, e2, e3;
	D3DXVec3Normalize(&e, &e);
	D3DXVec3Normalize(&e2, &(PosA1 - PosB2));
	double f1 = D3DXVec3Dot(&e, &e2);
	if (f1 < 0.0f) {
		f1 = f1 * (-1.0f);
	}
	//if (d1 > 1.0f)d1 = 1.0f;
	f1 = D3DXToDegree(acos(f1));
	D3DXVec3Normalize(&e3, &(PosA2 - PosB2));
	double f2 = D3DXVec3Dot(&e, &e3);
	if (f2 < 0.0f) {
		f2 = f2 * (-1.0f);
	}
	//if (d2 > 1.0f)d2 = 1.0f;
	f2 = D3DXToDegree(acos(f2));
	double u = f1 / (f1 + f2);//------------------------------------
	double o = u - t;
	o = o / 2.0f;

	*GetPos= PosA1 + (PosA2 - PosA1) * ((float)t);
	//線と点判定----------------------------------------------------------------
	/*D3DXVECTOR3 acVec, bcVec;
	acVec = *GetPos - PosA1;
	bcVec = *GetPos - PosA2;
	float Dot;
	Dot = (acVec.x * bcVec.x) + (acVec.y * bcVec.y)+ (acVec.z * bcVec.z);
	if ((Dot < 0.0f)) {
		return true;
	}*/
	return false;
}

D3DXMATRIX Judg::VecTransMat(D3DXVECTOR3 VecA)
{
	D3DXMATRIX TransMat;
	D3DXMatrixTranslation(&TransMat, VecA.x, VecA.y, VecA.z);
	return TransMat;
}

bool Judg::SetppMat(D3DXMATRIX * Mat, D3DXVECTOR3 PosA, D3DXVECTOR3 PosB, D3DXVECTOR3 PosC, int RailNum, bool bc)
{
	if ((RailNum != 5)) {
		return false;
	}
	D3DXVECTOR3 Vec, Pos;
	Vec = PosB - PosA;
	Vec /= 2.0f;
	SetMatP(&Mat[2], (PosA + Vec));
	D3DXVec3Normalize(&Vec, &Vec);
	SetPosM(&Pos, Mat[2]);
	SetMatP(&Mat[1], (Pos + -(Vec*5.0f)));
	SetMatP(&Mat[0], (Pos + -(Vec * 10.0f)));
	SetMatP(&Mat[3], (Pos + (Vec * 5.0f)));
	SetMatP(&Mat[4], (Pos + (Vec * 10.0f)));

	float f = 2.0f;
	if (bc == true) {
		Vec = PosC - PosB;
	}
	else {
		Vec = PosC - PosA;
	}
	//D3DXVec3Normalize(&Vec, &Vec);
	Vec /= f;
	for (int i = 0; i < RailNum; i++) {
		SetPosM(&Pos, Mat[i]);
		Pos += Vec;
		SetFloatQ(&Pos);
		SetMatP(&Mat[i], Pos);
	}
	return true;
}

bool Judg::MatMatVec(D3DXVECTOR3 * Vec, D3DXMATRIX MatA, D3DXMATRIX MatB)
{
	D3DXVECTOR3 PosA, PosB;
	SetPosM(&PosA, MatA);
	SetPosM(&PosB, MatB);
	*Vec = PosB - PosA;
	return true;
}

D3DXVECTOR3 Judg::MatMatVec(D3DXMATRIX MatA, D3DXMATRIX MatB)
{
	D3DXVECTOR3 PosA, PosB;
	SetPosM(&PosA, MatA);
	SetPosM(&PosB, MatB);
	PosA = PosB - PosA;
	return PosA;
}

bool Judg::VecMatIn(D3DXMATRIX * Mat, D3DXVECTOR3 Vec)
{
	D3DXVECTOR3 Pos;
	SetPosM(&Pos, *Mat);
	Pos += Vec;
	SetMatP(Mat, Pos);
	return true;
}

bool Judg::SetFloatQ(float *f)
{
	(*f)=(float)((int)((*f)*1000.0f)) / 1000.0f;
	return true;
}

bool Judg::SetFloatQ(D3DXVECTOR3 *Pos)
{
	SetFloatQ(&Pos->x);
	SetFloatQ(&Pos->y);
	SetFloatQ(&Pos->z);
	return true;
}

float Judg::SlashFloat(float fA, float fB)
{
	int iA, iB;
	iA = ((int)(fA*1000.0f)) * 1000;
	iB = (int)(fB*1000.0f);
	return ((float)(iA/iB)/1000.0f);
}

bool Judg::BigFloat(float * fA, float fB)
{
	if (*fA < fB)*fA = fB;
	return true;
}

bool Judg::SmallFloat(float * fA, float fB)
{
	if (*fA > fB)*fA = fB;
	return true;
}

float Judg::GetRad(XFILE * Mesh, DWORD * NumVertex,D3DXVECTOR3 *PosBig,D3DXVECTOR3 *PosSmall)
{
	/*LPD3DXMESH TmpMesh;
	Mesh->lpMesh->CloneMeshFVF(D3DXMESH_NPATCHES | D3DXMESH_MANAGED, D3DFVF_XYZ | D3DFVF_NORMAL| D3DFVF_TEX1, lpD3DDevice, &TmpMesh);
	                                                                   座標         法線           テクスチャ座標              クローン
	Mesh->lpMesh->Release();
	Mesh->lpMesh = TmpMesh;*/

	*NumVertex = Mesh->lpMesh->GetNumVertices();

	CLONEVERTEX *pV;
	D3DXVECTOR3 BigPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f), SmallPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	Mesh->lpMesh->LockVertexBuffer(0, (LPVOID*)&pV);
	for (DWORD No = 0; No < *NumVertex; No++) {
		BigFloat(&BigPos.x, (pV + No)->Pos.x);
		BigFloat(&BigPos.y, (pV + No)->Pos.y);
		BigFloat(&BigPos.z, (pV + No)->Pos.z);
		SmallFloat(&SmallPos.x, (pV + No)->Pos.x);
		SmallFloat(&SmallPos.y, (pV + No)->Pos.y);
		SmallFloat(&SmallPos.z, (pV + No)->Pos.z);
	}
	*PosBig = BigPos;
	*PosSmall = SmallPos;
	//半径を求める処理
	float Big, Small, size;
	Big = D3DXVec3Length(&BigPos);
	if (Big < 0.0f)Big *= -1.0f;
	Small = D3DXVec3Length(&SmallPos);
	if (Small < 0.0f)Small *= -1.0f;
	if (Big > Small) {
		size = Big;
	}
	else {
		size = Small;
	}
	Mesh->lpMesh->UnlockVertexBuffer();
	return size;
}

float Judg::GetRad(XFILE * Mesh, DWORD * NumVertex, D3DXVECTOR3 * PosBig, D3DXVECTOR3 * PosSmall, bool a)
{
	return 0.0f;
}

void Judg::ReverseFlg(bool * Flg)
{
	if (*Flg == true) {
		*Flg = false;
	}
	else {
		*Flg = true;
	}
}

void Judg::ScalingMat(D3DXMATRIX * ScalMat, const D3DXVECTOR3 * Pos)
{
	D3DXMatrixScaling(ScalMat, Pos->x, Pos->y, Pos->z);
	return;
}

void Judg::InitRotX(const D3DXMATRIX * Mat,D3DXMATRIX * RotX)
{
	//今の行列
	D3DXMATRIX nMat=*Mat;
	D3DXVECTOR3 pVec, ppVec;
	D3DXVec3TransformNormal(&pVec, &D3DXVECTOR3(0.0f, 0.0f, 1.0f), &nMat);
	ppVec = pVec;

	float Dot, Ang;

	//RotYの計算
	D3DXMATRIX CamRotY, CamRotX;
	ppVec.y = 0;
	//内積
	Dot = D3DXVec3Dot(&D3DXVECTOR3(0.0f, 0.0f, 1.0f), &ppVec);
	if (Dot > 1.0f)Dot = 1.0f;
	if (Dot < -1.0f)Dot = -1.0f;
	Ang = (float)D3DXToDegree(acos(Dot));
	if (ppVec.x < 0.0f)Ang *= -1.0f;
	D3DXMatrixRotationY(&CamRotY, D3DXToRadian(-Ang));


	//RotXの計算
	nMat = CamRotY * nMat;
	D3DXVec3TransformNormal(&pVec, &D3DXVECTOR3(0.0f, 0.0f, 1.0f), &nMat);
	//内積
	Dot = D3DXVec3Dot(&D3DXVECTOR3(0.0f, 0.0f, 1.0f), &pVec);
	if (Dot > 1.0f)Dot = 1.0f;
	if (Dot < -1.0f)Dot = -1.0f;
	Ang = (float)D3DXToDegree(acos(Dot));
	if (pVec.y > 0.0f)Ang *= -1.0f;
	D3DXMatrixRotationX(&CamRotX, D3DXToRadian(Ang));
	*RotX = CamRotX;
}

QuaAnimeC Judg::InitQuaAnime(const D3DXMATRIX * StartMat, const D3DXMATRIX * EndMat, const float * NowAnime, const float * AnimeFrame)
{
	QuaAnimeC qa;
	qa.NowMat = qa.StartMat = *StartMat;
	qa.EndMat = *EndMat;
	qa.NowAnime = *NowAnime;
	qa.AnimeFrame = *AnimeFrame;
	return qa;
}

void Judg::InitMatPos(D3DXMATRIX * Mat, D3DXVECTOR3 * TransPos, D3DXVECTOR3 * ScalPos)
{
	D3DXMatrixTranslation(Mat, 0.0f, 0.0f, 0.0f);
	*TransPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	*ScalPos = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
}

void Judg::SetTransMat(D3DXMATRIX * TransMat, const D3DXVECTOR3 * TransPos)
{
	D3DXMatrixTranslation(TransMat, TransPos->x, TransPos->y, TransPos->z);
}

D3DXMATRIX Judg::GetDrawMat(const D3DXMATRIX * Mat,D3DXMATRIX * ScalMat, const D3DXVECTOR3 * ScalPos)
{
	ScalingMat(ScalMat, ScalPos);
	D3DXMATRIX Tmp = *Mat;
	Tmp = *ScalMat*Tmp;
	return Tmp;
}

BASE3D Judg::GetInitBase3D(const D3DXVECTOR3 * InitPos, const D3DXVECTOR3 * TransPos, const D3DXVECTOR3 * ScalPos, const double * AngX, const  double * AngY, const  double * AngZ)
{
	BASE3D b;

	b.Pos = *InitPos;
	SetTransMat(&b.Mat, &b.Pos);
	b.TraPos = *TransPos;
	SetTransMat(&b.Trans, &b.TraPos);
	b.ScaPos = *ScalPos;
	ScalingMat(&b.Scal, &b.ScaPos);

	b.AngX = *AngX;
	D3DXMatrixRotationX(&b.RotX, D3DXToRadian((float)b.AngX));
	b.AngY = *AngY;
	D3DXMatrixRotationY(&b.RotY, D3DXToRadian((float)b.AngY));
	b.AngZ = *AngZ;
	D3DXMatrixRotationZ(&b.RotZ, D3DXToRadian((float)b.AngZ));

	return b;
}

D3DXMATRIX Judg::GetTransMatScal(const D3DXVECTOR3 * TransPos, const D3DXVECTOR3 * ScalPos)
{
	D3DXMATRIX Tmp;
	D3DXMatrixTranslation(&Tmp, TransPos->x*ScalPos->x, TransPos->y*ScalPos->y, TransPos->z*ScalPos->z);
	return Tmp;
}

D3DXMATRIX Judg::GetMatY(const D3DXMATRIX * MatA, const D3DXMATRIX * MatB)
{
	D3DXMATRIX Tmp;
	Tmp = *MatB;
	Tmp = *MatA*Tmp;
	return Tmp;
}

D3DXVECTOR3 Judg::GetVecVec(const D3DXVECTOR3 * VecA, const D3DXVECTOR3 * VecB)
{
	D3DXVECTOR3 A = *VecA,B=*VecB,Vec;
	Vec.x = A.x*B.x;
	Vec.y = A.y*B.y;
	Vec.z = A.z*B.z;
	return Vec;
}

D3DXVECTOR3 Judg::GetVecVec_S(const D3DXVECTOR3 * VecA, const D3DXVECTOR3 * VecB)
{
	D3DXVECTOR3 A = *VecA, B = *VecB, Vec;
	Vec.x = A.x/B.x;
	Vec.y = A.y/B.y;
	Vec.z = A.z/B.z;
	return Vec;
}

BASE3D Judg::InitGunParts(const Object3DGun * Init)
{
	BASE3D Base;
	Base.TraPos = Init->TransPos;
	SetTransMat(&Base.Trans, &Base.TraPos);

	Base.ScaPos = Init->ScalPos;
	ScalingMat(&Base.Scal, &Base.ScaPos);

	Base.DrawFlg = Init->DrawFlg;

	Base.AngX = Init->AngX;
	D3DXMatrixRotationX(&Base.RotX,D3DXToRadian((float)Base.AngX));

	Base.AngY = Init->AngY;
	D3DXMatrixRotationY(&Base.RotY, D3DXToRadian((float)Base.AngY));

	Base.AngZ = Init->AngZ;
	D3DXMatrixRotationZ(&Base.RotZ, D3DXToRadian((float)Base.AngZ));

	return Base;
}

Object3DGun Judg::InitSetPartsData(const float AngX, const float AngY, const float AngZ, const D3DXVECTOR3 * TransPos, const D3DXVECTOR3 * ScalPos, const bool DrawFlg)
{
	Object3DGun o;
	o.AngX=AngX;
	o.AngY = AngY;
	o.AngZ = AngZ;
	o.TransPos = *TransPos;
	o.ScalPos = *ScalPos;
	o.DrawFlg = DrawFlg;
	return o;
}

GUNDRAWNOS Judg::GetInitGUNDRAWNOS(const int GunNo, const int BulletNo, const int MuzFlaNo, const int LaserNo)
{
	GUNDRAWNOS g;
	g.GunNo = GunNo;
	g.BulletNo = BulletNo;
	g.MuzFlaNo = MuzFlaNo;
	g.LaserNo = LaserNo;
	return g;
}

S_Smog Judg::GetInitSmog(const D3DXVECTOR3 *MoveVec, const D3DXVECTOR3 *Frame, const int Alpha, const int AStart, const int AUp, const float PolSize, const float PolBit, const float PolBitUp, const S_Random *Random)
{
	S_Smog L_S_Smog;
	L_S_Smog.MoveVec = *MoveVec;
	L_S_Smog.Frame = *Frame;
	L_S_Smog.Alpha = Alpha;
	L_S_Smog.AStart = AStart;
	L_S_Smog.AUp = AUp;
	L_S_Smog.PolSize = PolSize;
	L_S_Smog.PolBit = PolBit;
	L_S_Smog.PolBitUp = PolBitUp;
	L_S_Smog.Random = *Random;

	return L_S_Smog;
}

S_Random Judg::GetInitRand(const int x, const int y, const int z)
{
	S_Random r;
	r.x = x;
	r.y = y;
	r.z = z;
	return r;
}

D3DXVECTOR3 Judg::VecPos(D3DXMATRIX MatA, D3DXVECTOR3 VecA)
{
	D3DXMATRIX TransMat;
	D3DXVECTOR3 Pos;
	SetPosM(&Pos, MatA);
	Pos = VecA - Pos;
	return Pos;
}
