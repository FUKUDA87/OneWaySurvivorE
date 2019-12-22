#pragma once
#include<d3dx9.h>
#include"Fade.h"

class Pause :public Fade {
public:
	Pause();
	~Pause() {};
	//表示
	void Draw2DPau();
	//アップデート
	bool UpdatePau();
	//表示の有無Flg入れ
	void SetDFlg(bool Flg) {
		pau.Base.DrawFlg = Flg;
	}
	//表示の有無Flg渡し
	bool GetDFlg(void) {
		return pau.Base.DrawFlg;
	}

	//ステージセーブの有無Flg入れ
	void SetStaSavFlg(bool Flg) {
		StageSaveFlg = Flg;
	}
	//ステージセーブの有無Flg渡し
	bool GetStaSavFlg(void) {
		return StageSaveFlg;
	}
protected:
	CHARA2D pau;
private:
	//ステージの情報記録用Flg
	bool StageSaveFlg;
};