#pragma once
#include"Key.h"

class C_KeyTrue :public Key {
public:
	//�E�N���b�N
	bool RClick();
	//���N���b�N
	bool LClick();
	//���N���b�N+KeyFlg
	bool LClickF();
	//���N���b�N+KeyFlg
	bool LClickF_N();
private:
	static bool LClickFlg;
};