#pragma once
#include"../../Draw/DrawBase2/Draw3D_Base2.h"
#include<vector>

class C_Effect_Base {
public:
	~C_Effect_Base();

	virtual void Set_MoveVec(const D3DXVECTOR3 *MoveVec);

	virtual void Draw(const D3DXVECTOR3 *CameraPos);

	virtual bool Update(void);
protected:
	std::vector<C_Draw3D_Base2*>M_Draw;

	//�S�폜
	void Delete_ALL(void);

	//�S�Ă��������t���O
	bool Delete_Flg(void);

private:

};