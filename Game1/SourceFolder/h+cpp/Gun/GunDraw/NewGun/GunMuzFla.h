#pragma once
#include"GunBullet.h"

class C_GunMuzFla :public C_GunBullet {
public:
	C_GunMuzFla() {};
	virtual MuzFlaBase* GetMuzFla() {
		return new MuzFlaBase();
	}
protected:

private:
	
};