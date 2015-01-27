#include "stdafx.h"
#include "Ini.h"
#include <windows.h>
#include <stdio.h>
#include <tchar.h>

#pragma warning (disable:4996)

CIni::CIni(const char *fileName)
{
	_appName = "Property";

	::GetCurrentDirectory(MAX_PATH, _fileName);
	_tcscat(_fileName, "\\");
	_tcscat(_fileName, fileName);
	
	//strncpy (_fileName, fileName, MAX_PATH);
}

CIni::~CIni()
{
}

void CIni::SaveString(const char *keyName, char * strData)
{
	WritePrivateProfileString(_appName, keyName, strData, _fileName);
}

void CIni::SaveInt(const char *keyName, int intData)
{
	char strData[32+10];
	_snprintf (strData, 32, "%d", intData);
	WritePrivateProfileString(_appName, keyName, strData, _fileName);
}

void CIni::SaveFloat(const char *keyName, float floatData)
{
	char strData[64+10];
	_snprintf (strData, 64, "%g", floatData);
	WritePrivateProfileString(_appName, keyName, strData, _fileName);
}

void CIni::LoadString(const char *keyName, char *returnedString, DWORD nSize, char *defaultValue)
{
	GetPrivateProfileString(_appName, keyName, defaultValue, returnedString, nSize, _fileName);	
}

int CIni::LoadInt(const char *keyName, int defaultValue)
{
	return GetPrivateProfileInt(_appName, keyName, defaultValue, _fileName);
}

float CIni::LoadFloat(const char *keyName, float defaultValue)
{
	char defaultString[64];
	_snprintf (defaultString, 64, "%g", defaultValue);

	char returnedString[128] = "";
	GetPrivateProfileString(_appName, keyName, defaultString, returnedString, sizeof(returnedString), _fileName);	
	return (float)atof (returnedString);
}

void CIni::Transfer (bool bSave, const char *keyName, char *strData, DWORD nSize, char *defaultData)
{
	if (bSave) SaveString (keyName, strData);
	else       LoadString (keyName, strData, nSize, defaultData);
}

void CIni::Transfer (bool bSave, const char *keyName, bool &boolData, bool defaultData)
{
	if (bSave) SaveInt (keyName, boolData ? 1 : 0);
	else       boolData = LoadInt (keyName, defaultData) ? true : false;
}

void CIni::Transfer (bool bSave, const char *keyName, int &intData, int defaultData)
{
	if (bSave) SaveInt (keyName, intData);
	else       intData = LoadInt (keyName, defaultData);
}

void CIni::Transfer (bool bSave, const char *keyName, long &longData, long defaultData)
{
	if (bSave) SaveInt (keyName, (int)longData);
	else       longData = (int)LoadInt (keyName, (int)defaultData);
}

void CIni::Transfer (bool bSave, const char *keyName, DWORD &dwordData, DWORD defaultData)
{
	if (bSave) SaveInt (keyName, (int)dwordData);
	else       dwordData = (int)LoadInt (keyName, (int)defaultData);
}

void CIni::Transfer (bool bSave, const char *keyName, float &floatData, float defaultData)
{
	if (bSave) SaveFloat (keyName, floatData);
	else       floatData = LoadFloat (keyName, defaultData);
}

void CIni::Transfer (bool bSave, const char *keyName, double &doubleData, double defaultData)
{
	if (bSave) SaveFloat (keyName, (float)doubleData);
	else       doubleData = (float)LoadFloat (keyName, (float)defaultData);
}