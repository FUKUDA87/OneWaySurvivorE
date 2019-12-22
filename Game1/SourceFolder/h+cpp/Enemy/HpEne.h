#pragma once
#include"../GameSource/TextureManager.h"
#include"../2DDraw/Hp.h"
#include"../GameSource/Struct.h"
#include<d3dx9.h>
#include"../GameSource/Judgment.h"

extern TextureManager textureManager;
extern Judg judg;
extern LPD3DXSPRITE lpSprite;	// スプライト
extern LPDIRECT3DDEVICE9		lpD3DDevice;
#define	FVF_VERTEX (D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1)

class HpEne :public HP {
protected:
	Pol HE;
public:
	HpEne() {
		Php.TEX = { NULL,200,100,NULL,NULL,NULL };
		Php.TEX.Tex = textureManager.GetTexture("../GameFolder/Material/Texture/HpE5.png", Php.TEX.Width, Php.TEX.Height,NULL);
		HE.Base.DrawFlg = false;
	};
	~HpEne() {};
	//dispがtrueなら０になっても消えない
	bool Update(const D3DXVECTOR3 PosA, const D3DXVECTOR3 vecA,const D3DXVECTOR2 posP, const int Max,const int nowHp,const bool disp) {
		if (nowHp <= 0) {
			HE.Base.DrawFlg = false;
			return false;
		}
		float per;
		if (nowHp < Max) {
			per = ((float)nowHp) / ((float)Max);
			if (per < 0.0f) {
				per = 0.0f;
			}
		}
		else {
			per = 1.0f;
		}
		per = 0.5f*per;
		HE.v[0].Tex = D3DXVECTOR2(0.5f-per, 0.0f);
		HE.v[1].Tex = D3DXVECTOR2(1.0f-per, 0.0f);
		HE.v[2].Tex = D3DXVECTOR2(1.0f-per, 1.0f);
		HE.v[3].Tex = D3DXVECTOR2(0.5f-per, 1.0f);
		for (int i = 0; i < 4; i++) {
			HE.v[i].Color= D3DCOLOR_ARGB(255, 255, 255, 255);
		}
		HE.Base.Pos = PosA + vecA;
		D3DXVECTOR3 PosS, PosE,vec;
		D3DXVECTOR2 pol = posP;
		if (pol.y < 0.0f)pol.y *= -1.0f;
		PosS = HE.Base.Pos +D3DXVECTOR3(0.0f, pol.y, 0.0f);
		PosE = HE.Base.Pos + D3DXVECTOR3(0.0f, -pol.y, 0.0f);
		if (pol.x < 0.0f)pol.x *= -1.0f;
		vec=judg.Billboard(PosS, PosE, pol.x, false);
		HE.v[0].Pos = PosS + vec;
		HE.v[1].Pos = PosS - vec;
		HE.v[2].Pos = PosE - vec;
		HE.v[3].Pos = PosE + vec;

		//表示の確認
		if ((HE.Base.DrawFlg == false) && (disp == true))HE.Base.DrawFlg = true;

		return true;
	};
	void Draw() {
		if (HE.Base.DrawFlg == true) {
			//lpD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
			lpD3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
			lpD3DDevice->SetTexture(0, Php.TEX.Tex);
			D3DXMatrixIdentity(&HE.Base.Mat);
			lpD3DDevice->SetTransform(D3DTS_WORLD, &HE.Base.Mat);
			lpD3DDevice->SetFVF(FVF_VERTEX);//バグ
			lpD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, HE.v, sizeof(VERTEX));//2はポリゴン数
			lpD3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
			//lpD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
		}
	};
	void Draw(const bool *Flg,const int *NowHp) {
		//表示の確認
		if (*NowHp <= 0)return;
		if ((HE.Base.DrawFlg == false) && (*Flg == true))HE.Base.DrawFlg = true;
		Draw();
	}
	void SetFlg(bool DrawFlg) {
		HE.Base.DrawFlg = DrawFlg;
	}
};