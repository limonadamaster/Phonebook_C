#pragma once
#include <cstring>
#include "CTypedPtrArraySelfClean.h"
#include <afx.h>

/// <summary>
/// Constants (magic numbers) 
/// </summary>
const int nNameLen = 64 + 1;
const int nSurnameLen = 64 + 1;
const int nFamilyLen = 64 + 1;
const int nUCNLen = 32 + 1;
const int nAddressLen = 64 + 1;

/// <summary>
/// Struct wich represents PERSONS table from DB
/// </summary>
struct PERSONS {
	/// <summary> Id of the person </summary>
	long lId;
	/// <summary>Update counter wich will count the record updates</summary>
	long lUpdateCounter;
	/// <summary>Person's name</summary>
	TCHAR szName[nNameLen];
	/// <summary>Person's surname</summary>
	TCHAR szSurname[nSurnameLen];
	/// <summary>Person's family</summary>
	TCHAR szFamily[nFamilyLen];
	/// <summary>Person's UCN</summary>
	TCHAR szUCN[nUCNLen];
	/// <summary>Id of the city which person live</summary>
	long lCityId;

	/// <summary> When we call constructor, the object members will be zeroed.</summary>
	PERSONS()
	{
		SecureZeroMemory(this, sizeof(*this));
	}

};
typedef CTypedPtrArraySelfClean <PERSONS*> CPersonsTypedPtrArray;