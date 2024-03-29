#include "Option.h"

void C_Option::Read(void)
{
	FILE *fp_b;

	// 読み込み
	if (fopen_s(&fp_b, "../GameFolder/Data/OptionData/OptionData.dat", "rb") == 0) {
		fread(&optionData, sizeof(S_OptionData), 1, fp_b);
		fclose(fp_b);
	}
	else {
		// 初期化
		InitData();

		// 新規作成
		Write();
	}
}

void C_Option::Write(void)
{
	FILE *fp_b;

	// 書き込み
	if (fopen_s(&fp_b, "../GameFolder/Data/OptionData/OptionData.dat", "wb") == 0) {
		fwrite(&optionData, sizeof(S_OptionData), 1, fp_b);
		fclose(fp_b);
	}
}

void C_Option::Change(void)
{

}

void C_Option::InitData(void)
{
	optionData.BGMVolume = -5000;
	optionData.SEVolume = -5000;
	optionData.sensitivity = 4.0f;
	optionData.reverseLR = false;
	optionData.reverseUD = false;
}
