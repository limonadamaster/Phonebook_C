#pragma once
#include "Cities.h"
#include "Persons.h"
#include "PhoneNumbers.h"
#include "PhoneTypes.h"

class CPerson {

	// Constructor & Destructor
	// ------------------------
public:
	CPerson() = default;

	CPerson(PERSONS* pPerson) {
		recPerson = *pPerson;
	}

	virtual ~CPerson() = default;


	// Methods
	// ------------------------
public:
	//This method return the only PERSONS object
	PERSONS& GetPerson() {
		return recPerson;
	}


public:
	// The person object
	PERSONS recPerson;
	// City name
	CString strCityName;
	// Phone types array
	CPhoneTypesTypedPtrArray personPhoneTypes;
	// Phone numbers array
	CPhoneNumbersTypedPtrArray personPhoneNumbers;


};
typedef CTypedPtrArraySelfClean <CPerson*> CPersonDataTypedPtrArray;
