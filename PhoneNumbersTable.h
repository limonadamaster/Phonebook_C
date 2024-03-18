#pragma once
#include "PhoneNumbers.h"            
#include "PhoneNumbersAccessor.h"    
#include "CTypedPtrArraySelfClean.h"
#include <atldbcli.h>
#include "Table.h"
#include <atlstr.h>

/// <summary>
/// Class which give accsess to DB. With this class we can make CRUD operations. 
/// </summary>
class CPhoneNumbersTable :
	public CTableBase<PHONE_NUMBERS, CPhoneNumbersAccessor, CPhoneNumbersTypedPtrArray>
{

	//Constructor / Destructor
	//----------------
public:
	CPhoneNumbersTable();
	virtual ~CPhoneNumbersTable();
};