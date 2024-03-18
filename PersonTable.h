#pragma once
#include "Persons.h"            
#include "PersonsAccessor.h"    
#include "CTypedPtrArraySelfClean.h"
#include <atldbcli.h>
#include "Table.h"
#include <atlstr.h>

/// <summary>
/// Class which give accsess to DB. With this class we can make CRUD operations. 
/// </summary>
class CPersonTable :
	public CTableBase<PERSONS, CPersonAccessor, CPersonsTypedPtrArray>
{

	//Constructor / Destructor
	//----------------
public:
	CPersonTable();
	virtual ~CPersonTable();
};