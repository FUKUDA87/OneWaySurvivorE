#pragma once
#include<d3dx9.h>

class C_Count {
public:
	C_Count(const int *Start);
	//カウントダウン
	bool Update(void);
	//間隔の調整用
	void UpCount(void);
protected:

private:
	//今減る数
	int CountDownNow;
	//始まりの数
	int CountStart;
	//切り替えFlg
	bool StartFlg;
	//代入
	void SetNow(void);
};