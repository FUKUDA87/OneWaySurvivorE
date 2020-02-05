#pragma once
#include"Car_Parts_Data.h"
#include"../GameSource/StructClass/Parts_Set_Size.h"

class C_Car_Parts_Size :public C_Car_Parts_Data {
public:
	~C_Car_Parts_Size();
protected:
	//サイズの新規検索項目の作成
	void New_Car_Parts_Size(const int TypeNo, const int JointNo, const D3DXVECTOR3* ScalPos);
	void New_Car_Parts_Size(const int TypeNo, const int JointNo, const float Size);

	//検索
	D3DXVECTOR3 Get_Car_Parts_Size(const S_PARTS_SET_DATA_No* No);

	//データの作成
	S_PARTS_SET_DATA_No Get_Data_No(const int TypeNo, const int JointNo);
private:
	std::vector<C_Parts_Set_Size*>M_Parts_Size;

	//サイズ情報の削除
	void Delete_All_Parts_Size(void);
};