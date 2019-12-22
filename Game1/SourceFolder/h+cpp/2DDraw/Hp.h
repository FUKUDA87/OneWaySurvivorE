#pragma once
#include<d3dx9.h>
#include"../GameSource/Struct.h"
//#ifndef HP_H
//#define HP_H

class HP{
public:
	void Init();
	HP() { Init(); };
	~HP() {};
	//dispÇ™trueÇ»ÇÁÇOÇ…Ç»Ç¡ÇƒÇ‡è¡Ç¶Ç»Ç¢
	virtual bool Update(int Max,int nowHp,bool disp);
	virtual void Draw();

	virtual bool UpdateAll(int Max, int nowHp, bool disp) {
		Update(Max,nowHp,disp);
		return true;
	}
	virtual void DrawAll() {
		Draw();
		return;
	}
	void SetPos(D3DXVECTOR3 pos) { hp.Base.Pos=pos; };
	void SetFlg(bool b) { hp.Base.Flg= b; };
protected:
	CHARA2D hp;
	CHARA2D Php;
};

//#endif //!HP_H