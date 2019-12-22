#pragma once
#include"SceneSoundManager.h"

class C_StageSSM :public C_SceneSoundManager {
public:
	C_StageSSM();
	~C_StageSSM();

	//ƒNƒ‰ƒX

protected:

private:
	void InitSSM(void);
	void EndSSM(void);
};