#include "PartsBase.h"

extern LPDIRECT3DDEVICE9		lpD3DDevice;	// Direct3DDeviceインターフェイス
void DrawMesh(XFILE *XFile);

const int DrawMeshNo = 1;
const int DeadMeshNo = 2;

C_PartsBase::C_PartsBase(const PARTS * InitGetParts)
{
	Parts = *InitGetParts;
	InitParts();
}

C_PartsBase::~C_PartsBase()
{
	
}

void C_PartsBase::Draw3DParts(void)
{
	if (Parts.PolFlg == true)return;
	Draw3DDrawMesh();
	Draw3DDaedMesh();
}

bool C_PartsBase::UpdateParts(const D3DXMATRIX * Mat)
{
	InitParts();
	Parts.Base.Mat = Parts.Base.Trans**Mat;
	return true;
}

bool C_PartsBase::UpdateParts(const D3DXMATRIX * Mat, const D3DXVECTOR3 * ScalPos)
{
	ScalParts(ScalPos);
	//行列の合成
	Parts.Base.Mat = Parts.Base.Trans**Mat;
	return true;
}

D3DXMATRIX C_PartsBase::GetDrawMatParts(void)
{
	D3DXVECTOR3 ScalPos;
	//拡大のベクトルセット
	ScalPos = judg.GetVecVec(&Parts.Base.ScaPos, &ScalPosBody);
	//拡大行列の合成
	D3DXMATRIX Mat=judg.GetDrawMat(&Parts.Base.Mat, &Parts.Base.Scal, &ScalPos);
	return Mat;
}

void C_PartsBase::SetSpeed(const int * GetNowSpeed, const int * GetMaxSpeed)
{
	NowSpeed = *GetNowSpeed;
	MaxSpeed = *GetMaxSpeed;
}

void C_PartsBase::Draw3DDrawMesh(void)
{
	if (Parts.MeshDrawFlg != DrawMeshNo)return;
	lpD3DDevice->SetTransform(D3DTS_WORLD, &GetDrawMatParts());
	DrawMesh(&Parts.Mesh.DrawMesh);
}

void C_PartsBase::Draw3DDaedMesh(void)
{
	if (Parts.MeshDrawFlg != DeadMeshNo)return;
	lpD3DDevice->SetTransform(D3DTS_WORLD, &GetDrawMatParts());
	DrawMesh(&Parts.Mesh.DeadMesh);
}

void C_PartsBase::InitParts(void)
{
	ScalPosBody = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	judg.SetTransMat(&Parts.Base.Trans, &Parts.Base.TraPos);
}

void C_PartsBase::ScalParts(const D3DXVECTOR3 * ScalPos)
{
	D3DXVECTOR3 TransPos,l_ScalPos=*ScalPos;
	//ベクトル同士の掛け算
	TransPos = judg.GetVecVec(&Parts.Base.TraPos, &l_ScalPos);
	//配置行列
	D3DXMatrixTranslation(&Parts.Base.Trans, TransPos.x, TransPos.y, TransPos.z);
	//車体の行列のセット
	if (Parts.PolFlg == true)l_ScalPos.z = 1.0f;
	ScalPosBody = l_ScalPos;
}
