#pragma once
#include<d3dx9.h>
#include<string>
#include<map>
#include"Struct.h"
class XfileManager {
private:
	std::map<std::string, XFILE>xfileList;
public:
	~XfileManager();
	void GetXfile(XFILE *x,std::string FileName);
	XFILE GetXfile(std::string FileName);
	void AllDelete(void);
};

