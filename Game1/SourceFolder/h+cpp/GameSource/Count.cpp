#include "Count.h"

C_Count::C_Count(const int * Start)
{
	//‰Šú‰»
	CountStart = *Start;

	StartFlg = true;

}

bool C_Count::Update(void)
{
	SetNow();

	CountDownNow--;

	if (CountDownNow <= 0)StartFlg = true;

	return StartFlg;
}

void C_Count::UpCount(void)
{
	CountDownNow++;
}

void C_Count::SetNow(void)
{
	if (StartFlg != true)return;

	CountDownNow=CountStart;

	StartFlg = false;
}
