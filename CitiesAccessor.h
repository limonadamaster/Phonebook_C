#pragma once
#include <atldbcli.h>
#include "Cities.h"

/// <summary>
/// Custom Access for Cities
/// </summary>
class CCitiesAccessor {
protected:


	// Define column numbers as constants
	enum {
		COLUMN_ID = 1,
		COLUMN_UPDATE_COUNTER,
		COLUMN_PERSON_NAME,
		COLUMN_PERSON_SURNAME
	};

	BEGIN_ACCESSOR_MAP(CCitiesAccessor, 2)
		BEGIN_ACCESSOR(0, true)
		COLUMN_ENTRY(COLUMN_ID, m_recAccessorData.lId)
		END_ACCESSOR()

		BEGIN_ACCESSOR(1, true)
		COLUMN_ENTRY(COLUMN_UPDATE_COUNTER, m_recAccessorData.lUpdateCounter)
		COLUMN_ENTRY(COLUMN_PERSON_NAME, m_recAccessorData.szCityName)
		COLUMN_ENTRY(COLUMN_PERSON_SURNAME, m_recAccessorData.szDistrict)
		END_ACCESSOR()
	END_ACCESSOR_MAP()

public:
	CITIES m_recAccessorData;
};