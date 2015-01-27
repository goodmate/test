#pragma once

#pragma warning(disable:4786)

#include <string>
#include <Windows.h>

using namespace std;

class CIni
{
public:
	CIni(const char *fileName);
	virtual ~CIni();

	// Loads settings from ini file
	void  LoadString (const char *keyName, char *returnedString, DWORD nSize, char *defaultValue = "");
	int   LoadInt    (const char *keyName, int defaultValue = 0);
	float LoadFloat  (const char *keyName, float defaultValue = 0.0);

	// Saves settings to ini file
	void SaveString (const char *keyName, char *strData);
	void SaveInt    (const char *keyName, int intData);
	void SaveFloat  (const char *keyName, float floatData);

	void Transfer (bool bSave, const char *keyName, char *strData, DWORD nSize, char *defaultData = "");
	void Transfer (bool bSave, const char *keyName, bool &boolData,   bool defaultData = false);
	void Transfer (bool bSave, const char *keyName, int &intData,     int defaultData = 0);
	void Transfer (bool bSave, const char *keyName, long &longData,   long defaultData = 0);
	void Transfer (bool bSave, const char *keyName, DWORD &dwordData, DWORD defaultData = 0);
	void Transfer (bool bSave, const char *keyName, float &floatData, float defaultData = 0.0f);
	void Transfer (bool bSave, const char *keyName, double &doubleData, double defaultData = 0.0);

private:
	// char _appName[MAX_PATH];
	char *_appName;
	char _fileName[MAX_PATH];
};

