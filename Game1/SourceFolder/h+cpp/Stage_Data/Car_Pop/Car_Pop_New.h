#pragma once
#include"Car_Pop_Base.h"

class C_Car_Pop_New {
public:
	C_Car_Pop_New(const int *StageNo);
	~C_Car_Pop_New();

	//更新処理
	bool Update(const bool *MoveFlg);

	//車の出現の情報渡し
	S_CAR_INIT_DATA Get_Next_Car_Data_N(void);

	//ステージの構成情報渡し
	S_STAGE_PHASE_DATA Get_Stage_Phase_Data_N(void);

	//車の出現可能渡し
	bool Get_Car_Pop_Flg_N(void);

	//車が出現した時にする処理
	void Car_Init_Rear_N(void);

	//今の敵数の取得
	void Set_Now_Enemy_Num_N(const int * Enemy_Num);

	//クラスが変更した確認
	bool Get_Change_Class_EndFlg(void) {
		return Change_Class_EndFlg;
	}

	//地面情報 
	int Get_GroundNo(void);


protected:
	C_Car_Pop_Base* M_C_Car_Pop_Base;

	//クラスが変わった時のFlg
	bool Change_Class_EndFlg;
private:

};