#pragma once
#include <atldbcli.h>
#include "PhoneNumbers.h"

/// <summary>
/// Custom Access for PhoneNumbers
/// </summary>
class CPhoneNumbersAccessor {
protected:


	// Define column numbers as constants
	enum {
		COLUMN_ID = 1,
		COLUMN_UPDATE_COUNTER,
		COLUMN_PHONE_NUMBER_PERSON_ID,
		COLUMN_PHONE_NUMBER_PHONE_TYPE_ID,
		COLUMN_PHONE_NUMBER

	};

	BEGIN_ACCESSOR_MAP(CPhoneNumbersAccessor, 2)
		BEGIN_ACCESSOR(0, true)
		COLUMN_ENTRY(COLUMN_ID, m_recAccessorData.lId)
		END_ACCESSOR()

		BEGIN_ACCESSOR(1, true)
		COLUMN_ENTRY(COLUMN_UPDATE_COUNTER, m_recAccessorData.lUpdateCounter)
		COLUMN_ENTRY(COLUMN_PHONE_NUMBER_PERSON_ID, m_recAccessorData.lPersonId)
		COLUMN_ENTRY(COLUMN_PHONE_NUMBER_PHONE_TYPE_ID, m_recAccessorData.lPhoneTypeId)
		COLUMN_ENTRY(COLUMN_PHONE_NUMBER, m_recAccessorData.szPhoneNumber)
		END_ACCESSOR()
	END_ACCESSOR_MAP()

public:
	PHONE_NUMBERS m_recAccessorData;
};