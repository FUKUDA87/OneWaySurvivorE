#include "GunAPartsA.h"
#include"../../../../MaterialManager/XfileManager.h"

extern XFileManager xfileManager;

c_GunAPartsA::c_GunAPartsA()
{
	mesh = xfileManager.GetMesh("gun1.x");
}
