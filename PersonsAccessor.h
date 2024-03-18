#pragma once
#include <atldbcli.h>
#include "Persons.h"

/// <summary>
/// Custom Access for Persons
/// </summary>
class CPersonAccessor {
protected:


	// Define column numbers as constants
	enum {
		COLUMN_ID = 1,
		COLUMN_UPDATE_COUNTER,
		COLUMN_PERSON_NAME,
		COLUMN_PERSON_SURNAME,
		COLUMN_PERON_FAMILY,
		COLUMN_PERSON_UCN,
		COLUM_PERSON_CITY_ID,
	};

	BEGIN_ACCESSOR_MAP(CPersonAccessor, 2)
		BEGIN_ACCESSOR(0, true)
		COLUMN_ENTRY(COLUMN_ID, m_recAccessorData.lId)
		END_ACCESSOR()

		BEGIN_ACCESSOR(1, true)
		COLUMN_ENTRY(COLUMN_UPDATE_COUNTER, m_recAccessorData.lUpdateCounter)
		COLUMN_ENTRY(COLUMN_PERSON_NAME, m_recAccessorData.szName)
		COLUMN_ENTRY(COLUMN_PERSON_SURNAME, m_recAccessorData.szSurname)
		COLUMN_ENTRY(COLUMN_PERON_FAMILY, m_recAccessorData.szFamily)
		COLUMN_ENTRY(COLUMN_PERSON_UCN, m_recAccessorData.szUCN)
		COLUMN_ENTRY(COLUM_PERSON_CITY_ID, m_recAccessorData.lCityId)
		END_ACCESSOR()
	END_ACCESSOR_MAP()

public:
	PERSONS m_recAccessorData;
};