#pragma once
#include"GunBullet.h"
#include"../../Muz/MuzFlaBase.h"

class C_GunMuzFla :public C_GunBullet {
public:
	virtual MuzFlaBase* GetMuzFla() {
		return new MuzFlaBase();
	}
protected:
	
private:
	
};