#include "HpD.h"

void HpD::InitNum()
{
	Slash.TEX = { NULL,18,28,NULL,NULL };
	Slash.TEX.Tex = textureManager.GetTexture("slash2.png", Slash.TEX.Width, Slash.TEX.Height, NULL);
	Slash.Base.Pos = hp.Base.Pos + (hp.Base.ScaPos / 2.0f);
	Slash.Base.ScaPos = D3DXVECTOR3(1.0f*0.6f, 20.0f / (float)Slash.TEX.Height*0.6f, 0.0f);
	D3DXMatrixScaling(&Slash.Base.Scal, Slash.Base.ScaPos.x, Slash.Base.ScaPos.y, Slash.Base.ScaPos.z);

	D3DXMatrixScaling(&Num.Base.Scal, 0.5f*0.6f, 0.5f*0.6f, 1.0f);
}

bool HpD::UpdateNum(int Max, int nowHp, bool disp)
{
	Hp = nowHp;
	Maxhp = Max;
	return true;
}

void HpD::DrawNum()
{
	//Slashの表示
	RECT rcSla = { 0,0,Slash.TEX.Width,Slash.TEX.Height };
	D3DXMatrixTranslation(&Slash.Base.Mat, Slash.Base.Pos.x, Slash.Base.Pos.y, NULL);
	D3DXMATRIX tmp;
	tmp = Slash.Base.Scal*Slash.Base.Mat;
	lpSprite->SetTransform(&tmp);
	lpSprite->Draw(Slash.TEX.Tex, &rcSla, &D3DXVECTOR3((float)Slash.TEX.Width / 2.0f, (float)Slash.TEX.Height / 2.0f, 0), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
	//hpとMaxhpの表示
	int w = Num.TEX.Width / 10, h = Num.TEX.Height;
	RECT rcNum[] = {
	{0 + w * 0,0,w + w * 0,h},
	{0 + w * 1,0,w + w * 1,h},
	{0 + w * 2,0,w + w * 2,h},
	{0 + w * 3,0,w + w * 3 - 3,h},
	{0 + w * 4,0,w + w * 4,h},
	{0 + w * 5,0,w + w * 5,h},
	{0 + w * 6,0,w + w * 6,h},
	{0 + w * 7,0,w + w * 7,h},
	{0 + w * 8,0,w + w * 8,h},
	{0 + w * 9,0,w + w * 9,h} };
	Num.Base.ScaPos = D3DXVECTOR3(Slash.TEX.Width*Slash.Base.ScaPos.x / (float)w, Slash.TEX.Height*Slash.Base.ScaPos.y / (float)h, Slash.Base.ScaPos.z);
	D3DXMatrixScaling(&Num.Base.Scal, Num.Base.ScaPos.x, Num.Base.ScaPos.y, Num.Base.ScaPos.z);
	char cScore[64];
	sprintf_s(cScore, sizeof(cScore), "%d", Hp);
	D3DXMATRIX spWorld, spTrans;
	spWorld = Slash.Base.Mat;
	D3DXMatrixTranslation(&spTrans, -(float)Slash.TEX.Width*Slash.Base.ScaPos.x + 0.2f, 0, 0);
	int i;
	for (i = 0; cScore[i] != '\0'; i++);
	//NowHpの表示
	for (i -= 1; i >= 0; i--) {
		spWorld *= spTrans;
		D3DXMATRIX tmp;
		tmp = Num.Base.Scal *spWorld;
		lpSprite->SetTransform(&tmp);
		lpSprite->Draw(Num.TEX.Tex, &rcNum[cScore[i] - '0'], &D3DXVECTOR3((float)w / 2.0f, (float)h / 2.0f, 0), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
	}
	//MaxHpの表示
	char cMax[64];
	sprintf_s(cMax, sizeof(cMax), "%d", Maxhp);
	for (i = 0; cMax[i] != '\0'; i++);
	D3DXMATRIX maWorld, maTrans;
	maWorld = Slash.Base.Mat;
	D3DXMatrixTranslation(&maTrans, (float)Slash.TEX.Width*Slash.Base.ScaPos.x + 0.2f, 0, 0);
	for (int n = 0; n < i; n++) {
		maWorld *= maTrans;
		D3DXMATRIX tmp;
		tmp = Num.Base.Scal *maWorld;
		lpSprite->SetTransform(&tmp);
		lpSprite->Draw(Num.TEX.Tex, &rcNum[cMax[n] - '0'], &D3DXVECTOR3((float)w / 2.0f, (float)h / 2.0f, 0), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
	}
}

bool HpD::UpdateAll(int Max, int nowHp, bool disp)
{
	Update(Max, nowHp, disp);
	UpdateNum(Max, nowHp, disp);
	return true;
}

void HpD::DrawAll()
{
	Draw();
	DrawNum();
	return;
}
