#pragma once
#include"Spark.h"

class C_Spark2 :public C_Spark {
public:
	//バージョン１
	C_Spark2(const D3DXMATRIX *Mat, const D3DXVECTOR3 *Pos);
	//バージョン２
	//C_Spark2(const D3DXMATRIX *Mat, const D3DXVECTOR3 *Pos, const bool *LeftFlg);
	//バージョン3（壁）
	C_Spark2(const D3DXMATRIX *Mat, const D3DXVECTOR3 *Pos, const bool *LeftFlg, const bool *InitFlg);
	//バージョン4（車）
	C_Spark2(const D3DXMATRIX *Mat, const D3DXVECTOR3 *Pos, const bool *InitFlg);
protected:
	bool UpdateSpark(void);
};