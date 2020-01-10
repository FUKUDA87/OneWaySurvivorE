#pragma once
#include"Smog.h"
#include<vector>

class C_SmokeCar {
public:
	C_SmokeCar();
	~C_SmokeCar();
	//アップデート
	bool Update_CS(const CHARABASE* CharaBase, const int *CarNo, const D3DXMATRIX *CarMat, const D3DXVECTOR3* CarMoveVec);
	//表示
	void Draw3D_CS(const D3DXVECTOR3 *CamPos);
private:
	//煙クラス
	std::vector<C_Smog*>M_C_Smoke;

	/*関数*/

	//煙全て削除
	void AllDelete_Smoke(void);
};