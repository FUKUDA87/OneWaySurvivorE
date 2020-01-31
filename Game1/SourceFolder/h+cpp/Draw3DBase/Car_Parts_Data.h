#pragma once
#include"Car_Parts_Base.h"
#include"CarBase.h"

class C_Car_Parts_Data:public C_CarBase {
public:
	~C_Car_Parts_Data();
	
	//情報数渡し
	unsigned int Get_Data_Num(void) {
		return M_Data.size();
	}
	//車のパーツ位置の情報
	S_CAR_PARTS_DATA Get_Data(const unsigned int *PartsNo);

	//情報入手
	void Set_Data(const S_CAR_PARTS_DATA *Data);
protected:
	std::vector<S_CAR_PARTS_DATA*>M_Data;

	//全情報削除
	void Delete_ALL_Data(void);

};