#include "PartsBase.h"

extern LPDIRECT3DDEVICE9		lpD3DDevice;	// Direct3DDeviceインターフェイス
void DrawMesh(XFILE *XFile);

C_PartsBase::C_PartsBase()
{
	Speed.Now = 0;
	Speed.Max = 0;
	M_Car_ScalPos = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	M_Base3D.ScaPos= D3DXVECTOR3(1.0f, 1.0f, 1.0f);
}

C_PartsBase::~C_PartsBase()
{
	Draw_AllDelete();
}

void C_PartsBase::Draw_Parts(const D3DXVECTOR3 *CameraPos)
{
	Draw_Draw(CameraPos);
}

void C_PartsBase::Set_ScalPos_Body(const D3DXVECTOR3 * set_Car_ScalPos)
{
	M_Car_ScalPos = *set_Car_ScalPos;
	Set_Body_ScalPos_Draw();
}

D3DXMATRIX C_PartsBase::Get_Draw_Mat(void)
{
	Judg judg;
	if (M_Draw == nullptr)return judg.Get_Mat_Init();

	return M_Draw->Get_Mat();
}

D3DXMATRIX C_PartsBase::Get_Draw_DrawMat(void)
{
	Judg judg;
	if (M_Draw == nullptr)return judg.Get_Mat_Init();

	return M_Draw->Get_DrawMat();
}

D3DXVECTOR3 C_PartsBase::Get_Draw_ScalPos(void)
{
	if (M_Draw == nullptr)return D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	return M_Draw->Get_ScalPos();
}

void C_PartsBase::Set_All_Draw_Mat(const D3DXMATRIX * Mat)
{
	if (M_Draw == nullptr)return;

	M_Draw->Set_Mat(Mat);
}

void C_PartsBase::Set_Body_ScalPos_Draw(void)
{
	if (M_Draw == nullptr)return;

	M_Draw->Set_ScalPos_Update(&M_Car_ScalPos);

}

void C_PartsBase::SetSpeed(const int * GetNowSpeed, const int * GetMaxSpeed)
{
	Speed.Now = *GetNowSpeed;
	Speed.Max = *GetMaxSpeed;
}

void C_PartsBase::Draw_New(C_Draw3D_Base2 * set_Draw)
{
	Draw_AllDelete();

	M_Draw = set_Draw;
}

int C_PartsBase::Get_Draw_Draw_JudgFlg(void)
{
	if (M_Draw == nullptr)return 0;

	return M_Draw->Get_Draw_JudgFlg();
}

D3DXVECTOR3 C_PartsBase::Get_Draw_Pol_Pos(const int * PosNo)
{
	if (M_Draw == nullptr)return D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	return M_Draw->Get_Pol_Pos(PosNo);
}

LPD3DXMESH C_PartsBase::Get_Draw_Mesh(void)
{
	return M_Draw->Get_Mesh();
}

bool C_PartsBase::Get_Draw_Iden_Flg(void)
{
	if (M_Draw == nullptr)return false;

	return M_Draw->Get_IdenFlg();
}

void C_PartsBase::Draw_AllDelete(void)
{
	if (M_Draw==nullptr)return;

	delete M_Draw;
}

void C_PartsBase::Draw_Draw(const D3DXVECTOR3 * CameraPos)
{
	if (M_Draw == nullptr)return;

	M_Draw->Draw3D(CameraPos);
}

void C_PartsBase::Set_TransPos(const D3DXVECTOR3 * set_Pos)
{
	M_Base3D.TraPos = *set_Pos;
}
