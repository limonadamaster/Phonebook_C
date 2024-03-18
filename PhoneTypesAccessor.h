#pragma once
#include <atldbcli.h>
#include "PhoneTypes.h"

/// <summary>
/// Custom Access for PhoneTypes
/// </summary>
class CPhoneTypesAccessor {
protected:


	// Define column numbers as constants
	enum {
		COLUMN_ID = 1,
		COLUMN_UPDATE_COUNTER,
		COLUMN_PHONE_TYPE,

	};

	BEGIN_ACCESSOR_MAP(CPhoneTypesAccessor, 2)
		BEGIN_ACCESSOR(0, true)
		COLUMN_ENTRY(COLUMN_ID, m_recAccessorData.lId)
		END_ACCESSOR()

		BEGIN_ACCESSOR(1, true)
		COLUMN_ENTRY(COLUMN_UPDATE_COUNTER, m_recAccessorData.lUpdateCounter)
		COLUMN_ENTRY(COLUMN_PHONE_TYPE, m_recAccessorData.szPhoneType)
		END_ACCESSOR()
	END_ACCESSOR_MAP()

public:
	PHONE_TYPES m_recAccessorData;

};