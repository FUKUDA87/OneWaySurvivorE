#pragma once
#include"CarBase.h"
#include"GunMoveBaseE2.h"
#include"CarParts.h"

class C_CarE :public C_CarBase, public C_GunMoveBaseE2,public C_CarParts {
public:
	C_CarE();
	~C_CarE();
protected:

private:

};