#pragma once
#include"MeshDataManagerBase.h"

class C_CarDataManager :public C_MeshDataManagerBase {
public:
	//表示数の読み込み
	int GetDrawNum(int CarNo, bool SaveFlg);
	//表示設定の読み込み
	S_CAR_PARTS_DATA GetDrawSet(int CarNo, const int *DrawNo, bool SaveFlg);
protected:
private:
	//検索表示数
	bool DrawNumJudg(int CarNo);
	//検索設定
	bool DrawSetJudg(int CarNo, const int *DrawNo);
};