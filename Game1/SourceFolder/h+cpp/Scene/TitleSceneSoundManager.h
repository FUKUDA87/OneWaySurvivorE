#pragma once
#include"SceneSoundManager.h"
#include"../Sound/Click.h"

class C_TitleSSM :public C_SceneSoundManager {
public:
	C_TitleSSM();
	~C_TitleSSM();

	//ƒNƒ‰ƒX

protected:
	C_ClickSound *ClickSound;
private:
	void InitSSM(void);
	void EndSSM(void);
};