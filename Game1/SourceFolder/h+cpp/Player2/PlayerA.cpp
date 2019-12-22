#include "PlayerA.h"

C_PlayerA::C_PlayerA()
{
	BodyData.CarBodyNo = CarNo1;
	BodyData.TireNo = TireNo1;
	BodyData.StandNo = StandNo1;
	BodyData.GunNo = 1;
	InitPlayerA();
}

C_PlayerA::C_PlayerA(const BODYDATA * Data)
{
	SetBody(Data);

	//SaveCar();
}

C_PlayerA::~C_PlayerA()
{
}

void C_PlayerA::SetBody(const BODYDATA * Data)
{
	//情報のセット
	BodyData = *Data;
	//パーツのセット
	InitPlayerA();
}

void C_PlayerA::SaveCar(void)
{
	//パーツ情報の読み込み
	int DrawNum;
	DrawNum = CarDataManager.GetDrawNum(BodyData.CarBodyNo,true);
	for (int c = 0; c < DrawNum; c++) {
		CarDataManager.GetDrawSet(BodyData.CarBodyNo, &c,true);
	}
}

void C_PlayerA::InitPlayerA(void)
{

	//車初期化
	SetMeshCar(BodyData.CarBodyNo);

	SetCarParts(&BodyData,true);

	
}

void C_PlayerA::InitPlayerAB(void)
{

	//パーツの削除
	DeleteParts();

	//車初期化
	SetMeshCar(BodyData.CarBodyNo);

	//パーツ情報の読み込み
	int DrawNum;
	//表示数の読み込み
	DrawNum = CarDataManager.GetDrawNum(BodyData.CarBodyNo, true);
	//表示物の初期化
	//表示数
	for (int c = 0; c < DrawNum; c++) {
		//表示情報の読み込み
		PARTS P;
		CarDataManager.GetDrawSet(BodyData.CarBodyNo, &c, true);
	}
}
