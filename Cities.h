#pragma once
#pragma once
#include <cstring>
#include "CTypedPtrArraySelfClean.h" 

/// <summary>
/// Constants (magic numbers) 
/// </summary>
const int nCityNameLen = 32 + 1;
const int nDistrictLen = 32 + 1;
/// <summary>
///  Struct wich represents CITIES table from DB
/// </summary>
struct CITIES {
	/// <summary> Id of the city </summary>
	long lId;
	/// <summary>Update counter wich will count the record updates</summary>
	long lUpdateCounter;
	/// <summary>Name of the city</summary>
	TCHAR szCityName[nCityNameLen];
	/// <summary>Name of the district</summary>
	TCHAR szDistrict[nDistrictLen];

	/// <summary> When we call constructor, the object members will be zeroed.</summary>
	CITIES()
	{
		SecureZeroMemory(this, sizeof(*this));
	}
};
typedef CTypedPtrArraySelfClean <CITIES*> CCitiesTypedPtrArray;