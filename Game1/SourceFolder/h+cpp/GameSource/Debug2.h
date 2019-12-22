#pragma once
#include<d3dx9.h>
#include<stdio.h>

extern LPD3DXFONT lpFontS;
extern float AngD;
extern unsigned int NumD;
extern bool FlgD;

class DebugT {
protected:
	bool Flg,tFlg;
	D3DXVECTOR2 Pos;
	float Ang;
public:
	DebugT() { Flg = true; };
	~DebugT() {};
	void Update(bool b) {
		Flg = b;
		Ang = AngD;
	}
	void Draw2DT() {
		if (Flg == true) {
			RECT rcCon = { 0,0,0,0 };
			char TextB[200];
			sprintf_s(TextB, sizeof(TextB), "%f", AngD);
			lpFontS->DrawTextA(NULL, TextB, -1, &rcCon, DT_LEFT | DT_NOCLIP, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
	}
	void Draw2DTd() {
		//if (Flg == true) {
			RECT rcCon = { 0,050,0,50 };
			char TextB[200];
			sprintf_s(TextB, sizeof(TextB), "%d", NumD);
			lpFontS->DrawTextA(NULL, TextB, -1, &rcCon, DT_LEFT | DT_NOCLIP, D3DCOLOR_ARGB(255, 255, 255, 255));
		//}
	}
	void Draw2DTc() {
		if (tFlg == false) {
			tFlg = FlgD;
		}
		if (tFlg == true) {
		RECT rcCon = { 0,100,0,100 };
		char TextB[200];
		sprintf_s(TextB, sizeof(TextB), "nan");
		lpFontS->DrawTextA(NULL, TextB, -1, &rcCon, DT_LEFT | DT_NOCLIP, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
	}
	void Draw2DF(float f, int x, int y) {
		RECT rcCon = { x,y,0,0 };
		char TextB[200];
		sprintf_s(TextB, sizeof(TextB), "%f", f);
		lpFontS->DrawTextA(NULL, TextB, -1, &rcCon, DT_LEFT | DT_NOCLIP, D3DCOLOR_ARGB(255, 255, 255, 255));
	}
	void SetPos(float x, float y) {
		Pos.x = x;
		Pos.y = y;
	}
};