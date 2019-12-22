#include "Smoke2.h"
#include"../GameSource/Judgment.h"

extern Judg judg;
extern LPDIRECT3DDEVICE9	lpD3DDevice;

#define	FVF_VERTEX (D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1)

C_Smoke2::C_Smoke2(const D3DXVECTOR3 * Pos):C_Smog(Pos)
{
	InitS();
	for (int s = 0; s < SmokeNum; s++) {
		SmokePos[s] = *Pos;
	}
	for (int m = 0; m < SmokeNum * 2;m++) {
		for (int s = 0; s < SmokeNum; s++) {
			SmokePos[s].y += yUp;
		}
		for (int s = SmokeNum - 1; s > 0; s--) {
			SmokePos[s] = SmokePos[s - 1];
		}
		SmokePos[0] = *Pos;
	}
}

C_Smoke2::~C_Smoke2()
{
	//位置の削除
	delete[] SmokePos;
	//スモックの削除
	if (smoke.size() > 0) {
		for (unsigned int s = 0; s < smoke.size(); s++) {
			delete smoke[s];
			smoke.erase(smoke.begin() + s);
			s--;
		}
	}
}

void C_Smoke2::InitS(void)
{
	//スモーク数の初期化
	SmokeNum = 10;
	SmokeNumDraw = 10;
	//位置の初期化
	SmokePos = new D3DXVECTOR3[SmokeNum];
}

bool C_Smoke2::Update(const int * NowHp, const int * MaxHp, const D3DXVECTOR3 * NowPos)
{
	//位置の更新
	for (int s = 0; s < SmokeNum; s++) {
		SmokePos[s].y += yUp;
	}
	for (int s = SmokeNum-1; s >0; s--) {
		SmokePos[s] = SmokePos[s - 1];
	}
	SmokePos[0] = *NowPos;

	//現在のHpの状況確認と煙の出現
	if (*NowHp < (int)((float)*MaxHp*0.3f)) {
		int MaxNum = 1;
		for (int i = 0; i < MaxNum; i++) {
			float NA = 0.0f;
			float NF = 0.2f;
			smoke.push_back(new PolQuaAni);
			smoke[smoke.size() - 1]->Qac = judg.InitQuaAnime(&judg.SetMatP(SmokePos[0] /*+ (SmokePos[2]- SmokePos[0])*((1.0f/(float)MaxNum*(float)i))*/), &judg.SetMatP(SmokePos[SmokeNum - 1]), &NA, &NF);
			smoke[smoke.size() - 1]->AlphaMax = smoke[smoke.size() - 1]->Alpha = 255;
			smoke[smoke.size() - 1]->PolSizeNow = smoke[smoke.size() - 1]->PolSizeSmall = 0.4f;
			smoke[smoke.size() - 1]->PolSizeMax = 1.0f;
		}
	}
	return true;
}

bool C_Smoke2::UpdateQua(void)
{
	//移動のクォータニオン
	if (smoke.size() > 0) {
		for (unsigned int s = 0; s< smoke.size(); s++) {
			bool DelFlg = false;
			if (judg.Quaternion(&smoke[s]->Qac.NowMat, smoke[s]->Qac.StartMat, smoke[s]->Qac.EndMat, &smoke[s]->Qac.NowAnime, smoke[s]->Qac.AnimeFrame, true) == false) {
				DelFlg = true;
				delete smoke[s];
				smoke.erase(smoke.begin() + s);
				s--;
			}
			if (DelFlg == false) {
				smoke[s]->Alpha = (int)((float)smoke[s]->AlphaMax*smoke[s]->Qac.NowAnime);
				smoke[s]->PolSizeNow = (smoke[s]->PolSizeMax - smoke[s]->PolSizeSmall)*smoke[s]->Qac.NowAnime;
			}
		}
	}
	return true;
}

void C_Smoke2::Draw3D(const D3DXVECTOR3 * CamPos)
{
	//UpdateQua();

	//表示
	lpD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	lpD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	lpD3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	lpD3DDevice->SetFVF(FVF_VERTEX);//バグ
	lpD3DDevice->SetTexture(0, smog.TEX.Tex);
	if (smoke.size() > 0) {
		for (unsigned int s = 0; s < smoke.size(); s++) {
			for (int c = 0; c < 4; c++) {
				smog.v[c].Color = D3DCOLOR_ARGB(smoke[s]->Alpha, 100, 100, 100);
			}
			lpD3DDevice->SetTransform(D3DTS_WORLD, &smog.Base.Mat);
			//ビルボード
			D3DXVECTOR3 vec, oPos, nPos;
			vec = D3DXVECTOR3(0.0f, 1.0f*smoke[s]->PolSizeNow, 0.0f);
			nPos = judg.SetPosM(smoke[s]->Qac.NowMat) + vec;
			oPos = judg.SetPosM(smoke[s]->Qac.NowMat) - vec;
			vec = judg.Billboard(oPos, nPos, *CamPos, vec.y);
			smog.v[0].Pos = nPos - vec;
			smog.v[1].Pos = nPos + vec;
			smog.v[2].Pos = oPos + vec;
			smog.v[3].Pos = oPos - vec;
			smog.v[0].Tex = D3DXVECTOR2(0.0f, 0.0f);
			smog.v[1].Tex = D3DXVECTOR2(1.0f, 0.0f);
			smog.v[2].Tex = D3DXVECTOR2(1.0f, 1.0f);
			smog.v[3].Tex = D3DXVECTOR2(0.0f, 1.0f);
			lpD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, smog.v, sizeof(VERTEX));//2はポリゴン数
		}
	}
	lpD3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	lpD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	lpD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
}

