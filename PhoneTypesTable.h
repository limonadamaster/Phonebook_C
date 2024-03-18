#pragma once
#include "PhoneTypes.h"            
#include "PhoneTypesAccessor.h"    
#include "CTypedPtrArraySelfClean.h"
#include <atldbcli.h>
#include "Table.h"
#include <atlstr.h>

/// <summary>
/// Class which give accsess to DB. With this class we can make CRUD operations. 
/// </summary>
class CPhoneTypesTable :
	public CTableBase<PHONE_TYPES, CPhoneTypesAccessor, CPhoneTypesTypedPtrArray>
{

	//Constructor / Destructor
	//----------------
public:
	CPhoneTypesTable();
	virtual ~CPhoneTypesTable();
};