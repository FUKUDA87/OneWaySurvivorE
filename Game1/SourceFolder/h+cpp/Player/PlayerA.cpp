#include "PlayerA.h"
#include"../Gun/GunDraw/Gun_Type/Gun_Gatling_1.h"

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
	C_CarDataManager Manager;
	DrawNum = Manager.GetDrawNum(BodyData.CarBodyNo,true);
	for (int c = 0; c < DrawNum; c++) {
		Manager.GetDrawSet(BodyData.CarBodyNo, &c,true);
	}
}

void C_PlayerA::InitPlayerA(void)
{

	//車初期化
	SetMeshCar(BodyData.CarBodyNo);

	//NewEffect(new c_Ball3DEffect(Car.Base.BodRad, 1.0f));

	New_Set_Car_Parts(&BodyData);

	
}
