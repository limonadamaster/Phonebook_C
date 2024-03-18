#pragma once
#include <cstring>
#include "CTypedPtrArraySelfClean.h"
#include <afx.h>

/// <summary>
/// Constants (magic numbers) 
/// </summary>
const int nPhoneNumberLen = 64 + 1;

/// <summary>
/// Struct wich represents PHONE_NUMBERS table from DB
/// </summary>
struct PHONE_NUMBERS {
	/// <summary> Id of the phone number </summary>
	long lId;
	/// <summary>Update counter wich will count the record updates</summary>
	long lUpdateCounter;
	/// <summary>Id of the person </summary>
	long lPersonId;
	/// <summary>Id of the phone type </summary>
	long lPhoneTypeId;
	/// <summary>Phone number</summary>
	TCHAR szPhoneNumber[nPhoneNumberLen];

	/// <summary> When we call constructor, the object members will be zeroed.</summary>
	PHONE_NUMBERS()
	{
		SecureZeroMemory(this, sizeof(*this));
	}
};
typedef CTypedPtrArraySelfClean <PHONE_NUMBERS*> CPhoneNumbersTypedPtrArray;