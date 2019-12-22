#pragma once
#include<d3dx9.h>
#include<stdio.h>
#include"../../GameSource/Struct.h"
#include"../../GameSource/Const.h"

class C_MeshDataManagerBase {
public:
	//表示数の読み込み
	virtual int GetDrawNum(int CarNo,bool SaveFlg)=0;
	//表示設定の読み込み
	virtual PARTSBASE GetDrawSet(int CarNo,const int *DrawNo, bool SaveFlg) = 0;
protected:
	//セーブ・ロード用
	FILE* fp;
	FILE *fp_b;
	char FName[100];

	//表示数-----------------------------------------
	//セーブ
	void SaveDN(int CarNo,int DrawNum);
	//ロード
	int LoadDN(int CarNo);
	//txtロードdatセーブ
	void LoadSaveDN(int CarNo);

	//表示情報----------------------------------------
	//セーブ
	void SaveDS(int CarNo, const int *DrawNo,const PARTSBASE *Par);
	//ロード
	PARTSBASE LoadDS(int CarNo, const int *DrawNo);
	//txtロードdatセーブ
	void LoadSaveDS(int CarNo, const int *DrawNo);
	//初期化パーツ
	PARTSBASEINT InitPartsDS(void);

private:
	//変換＜－Int
	PARTSBASE ChangePB(const PARTSBASEINT *Par);
	//変換ー＞Int
	PARTSBASEINT ChangePBI(const PARTSBASE *Par);
};