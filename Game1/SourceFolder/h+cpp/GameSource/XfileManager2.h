#pragma once
#include<d3dx9.h>
#include<string>
#include<map>
#include"Struct.h"
class XfileManager2 {
private:
	std::map<std::string, XFILE_B>xfileList;
public:
	~XfileManager2();
	XFILE_B GetXfile(std::string FileName);
	void AllDelete(void);
};