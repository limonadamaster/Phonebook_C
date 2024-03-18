#pragma once
#include "CTypedPtrArraySelfClean.h"
#include <afx.h>

/// <summary>
/// Constants (magic numbers) 
/// </summary>
const int nPhoneTypeLen = 128 + 1;
/// <summary>
///  Struct wich represents PHONE_TYPES table from DB
/// </summary>
struct PHONE_TYPES {
	/// <summary> Id of record type of phone </summary>
	long lId;
	/// <summary>Update counter wich will count the record updates</summary>
	long lUpdateCounter;
	/// <summary> The name of phone type </summary>
	TCHAR szPhoneType[nPhoneTypeLen];

	/// <summary> When we call constructor, the object members will be zeroed.</summary>
	PHONE_TYPES()
	{
		SecureZeroMemory(this, sizeof(*this));
	}
};
typedef CTypedPtrArraySelfClean <PHONE_TYPES*> CPhoneTypesTypedPtrArray;

