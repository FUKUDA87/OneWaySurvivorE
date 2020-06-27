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

	//全削除
	void Delete_ALL(void);

	//全てが消えたフラグ
	bool Delete_Flg(void);

private:

};