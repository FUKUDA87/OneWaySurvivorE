#pragma once
#include"../../EnemyA.h"

class C_Enemy_No101 :public C_EnemyA {
public:
	C_Enemy_No101(const D3DXMATRIX * GroundMat, const float * TransX);
protected:
	//�Ԃ̓����蔻��p�̏��̏�����
	void New_Car_Judg_Parts(void);
private:

};