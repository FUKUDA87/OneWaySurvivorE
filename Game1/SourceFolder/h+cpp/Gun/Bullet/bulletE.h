#pragma once
#include"../../Player/Aiming.h"

class GunBase {
	Aiming* Get() {
		return new Aiming();
	}
};