#pragma once
#include"CarBase.h"
#include"GunMoveBase.h"
#include"PartsBase.h"
#include<vector>
#include"../Draw3DBase/PartsBase.h"
#include"../Draw3DBase/CarParts.h"

class C_Car :public C_CarBase,public C_GunMoveBase,public C_CarParts{
public:
	C_Car();
	~C_Car();
protected:
	
private:

};